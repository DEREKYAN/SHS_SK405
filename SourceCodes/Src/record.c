#include "ADC.h"
#include "Fuel.h"
#include "Mobile.h"
#include "UART.h"
#include "Events.h"
#include "PV.h"
#include "MCU.h"
#include "radio.h"
#include "nv.h"
#include "record.h" 


// TRIM:  SN:1234567890123 15364(date) 2505(mV,verf)
/**************************************************************
SKx3x project base on MCU STM32F030K6, FLASH area:
------------------------------------------------------------------
0x0800 0000 - 0x0800 03FF     1K  PAGE0    |
0x0800 0400 - 0x0800 07FF     1K  PAGE1    |       Sector 0
0x0800 0800 - 0x0800 0BFF     1K  PAGE2    |       
0x0800 0C00 - 0x0800 0FFF     1K  PAGE3    |   
-------------------------------------------------------------------
0x0800 1000 - 0x0800 13FF     1K  PAGE4    |
0x0800 1400 - 0x0800 17FF     1K  PAGE5    |       Sector 1
0x0800 1800 - 0x0800 1BFF     1K  PAGE6    |       
0x0800 1C00 - 0x0800 1FFF     1K  PAGE7    |   
-------------------------------------------------------------------
0x0800 2000 - 0x0800 23FF     1K  PAGE8    |
0x0800 2400 - 0x0800 27FF     1K  PAGE9    |       Sector 2
0x0800 2800 - 0x0800 2BFF     1K  PAGE10   |       
0x0800 2C00 - 0x0800 2FFF     1K  PAGE11   |   
-------------------------------------------------------------------
0x0800 3000 - 0x0800 33FF     1K  PAGE12   |
0x0800 3400 - 0x0800 37FF     1K  PAGE13   |       Sector 3
0x0800 3800 - 0x0800 3BFF     1K  PAGE14   |       
0x0800 3C00 - 0x0800 3FFF     1K  PAGE15   |   
-------------------------------------------------------------------
0x0800 4000 - 0x0800 43FF     1K  PAGE16   |
0x0800 4400 - 0x0800 47FF     1K  PAGE17   |       Sector 4
0x0800 4800 - 0x0800 4BFF     1K  PAGE18   |       
0x0800 4C00 - 0x0800 4FFF     1K  PAGE19   |   
-------------------------------------------------------------------
0x0800 5000 - 0x0800 53FF     1K  PAGE20   |
0x0800 5400 - 0x0800 57FF     1K  PAGE21   |       Sector 5
0x0800 5800 - 0x0800 5BFF     1K  PAGE22   |       
0x0800 5C00 - 0x0800 5FFF     1K  PAGE23   |   
-------------------------------------------------------------------
0x0800 6000 - 0x0800 63FF     1K  PAGE24   |
0x0800 6400 - 0x0800 67FF     1K  PAGE25   |       Sector 6
0x0800 6800 - 0x0800 6BFF     1K  PAGE26   |       
0x0800 6C00 - 0x0800 6FFF     1K  PAGE27   |   
-------------------------------------------------------------------
0x0800 7000 - 0x0800 73FF     1K  PAGE28   |
0x0800 7400 - 0x0800 77FF     1K  PAGE29   |       Sector 7
0x0800 7800 - 0x0800 7BFF     1K  PAGE30   |       
0x0800 7C00 - 0x0800 7FFF     1K  PAGE31   |   
-------------------------------------------------------------------
***************************************************************/

#define  SEGMENT_OF_3PAGES     10

//#define ID_OFFSET                       74u

union u_recond_nv uart_nvram;
static bool req_record_at_empty_fuel = FALSE;

// Record When fuel is empty
void set_req_record_at_empty_fuel(void)
{
    req_record_at_empty_fuel = TRUE;
}
// Record second event,  1 days or empty fuel + 1 hours, hold on 15 second @ Vbat > 2.5V, Write data to NV flash 
void event_second_record(u16 t)
{
    static uint record_time_counter = 0; 
    static uchar Vbat_steady_counter = 0;
    
    record_time_counter += t;
    if(((record_time_counter > 60*60) && req_record_at_empty_fuel) || (record_time_counter>(24*60*60)) )
    {
        if(adc_ave.ave_v_battery >= 2500)
        {
             ++Vbat_steady_counter;
             if(Vbat_steady_counter >=15)
             {
                Vbat_steady_counter = 0;
                req_record_at_empty_fuel = FALSE;
                record_time_counter = 0;
                save_record_data();
             }
        }
        else
        {
            Vbat_steady_counter = 0;
            req_record_at_empty_fuel = FALSE;
        }      
    }
    else
    {
        req_record_at_empty_fuel = FALSE;
    }  
}

void save_record_data(void)
{ 

  u16 flash_flag,i,j;
  GLP_bool flag_erase;
  flag_erase = GLP_FALSE;
  static u16 flast_erase_times;  
  
  flast_erase_times = *(__IO u16 *)(RECORD_END_FLASH_ADDRESS -2); 
  if(flast_erase_times == 0xFFFF)
  {
      flast_erase_times = 0;
  }
  if(flast_erase_times>1000)
    return;
  
  for(i=1;i<=SEGMENT_OF_3PAGES;i++)
  {
      flash_flag = *(__IO u16 *)((RECORD_END_FLASH_ADDRESS-2) -i*2);
	  if(flash_flag == 0xFFFF)
	  	break;
	  if(flash_flag != 0xA5A5)
	  	{
		  flag_erase = GLP_TRUE;
		  break;
	  	}
  }
  if(i>SEGMENT_OF_3PAGES)
 	flag_erase = GLP_TRUE;

  FLASH_Unlock();
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);
  if(flag_erase)
  {
//        Send_Message("\nErase page \n");
  	FLASH_ErasePage(0x08007800);
	++flast_erase_times;
	FLASH_ProgramHalfWord((RECORD_END_FLASH_ADDRESS - 2),flast_erase_times);
	i = 1;
  }

  for(j=0;j<25;j++)
  {  
    FLASH_ProgramWord((RECORD_START_FLASH_ADDRESS + (i-1) * 100 +j*4),uart_nvram.nvram_buff[j]);  
  }     
  FLASH_ProgramHalfWord(((RECORD_END_FLASH_ADDRESS-2) - i*2),0xA5A5);
 
  FLASH_Lock();  
}

// Read NV data from NV flash
void read_data_from_NV(void)
{
    u16 i,j;
    u16 flash_flag;
    for(i=1;i<=10;++i)
    {
        flash_flag = *(__IO u16 *)((RECORD_END_FLASH_ADDRESS -2)-i*2);

        if(flash_flag != 0xA5A5)
        break;
    }

    if(i > 1)
    {
      for(j=0;j<25;j++)
      {  
          uart_nvram.nvram_buff[j] = *(__IO uint *)(RECORD_START_FLASH_ADDRESS + (i-2) * 100 +j*4); 
      }        
    }
}

// EOF
