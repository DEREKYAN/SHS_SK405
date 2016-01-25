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

#define FOREVER_FLASH_START             (uint32_t)0x08007C00              // PAGE 31
#define REBOOT_FLASH_START              (uint32_t)(0x08007C00 + 100)      // reset counter, Flash start address
#define USER_SET_FLASH_START            (uint32_t)(0x08007FFE)            //  Flash add for flag that means lantern is used more than 2 hours 

static uchar trim_rx_counter = 0;     // Trim receive chars counters
static u16 uart_rx_verf ;             // extern reference from UART input          
//static u16 reboot_counter = 0;        // Reboot counter 
u16 watchdong_reset_counter = 0;
u16 low_bat_reset_counter = 0;
u16 power_on_reset_counter = 0;

static void ATE_Trim(void);           

uchar rx_char;

static union u_nv
{
  struct
  {
      uchar nv_trim_flag ;      //1
      uchar nv_SN[17];          //18     
      u16 nv_date;              //20
      u16 nv_vref;              //22
  }nv_array;
  
  uint nv_buff[6];              // 4*6 = 24
  
}nv_flash_data;
// Get user status message 
u16 get_user_set_flag(void)
{
    u16 user_flag;
    user_flag = nv_get_halfword(USER_SET_FLASH_START);
    if(user_flag != CONST_NV_USED)
    {
      user_flag = CONST_NV_UNUSED;
    }
    return user_flag;
}
// Write user flag to NV flash 
void write_nv_user_set_flag(void)
{
  FLASH_Unlock();
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);  
  FLASH_ProgramHalfWord(USER_SET_FLASH_START,CONST_NV_USED);  
  FLASH_Lock();        
}
// Handle reboot
void handler_reboot_counter(u16 type)
{
  u16 i;
  watchdong_reset_counter = 0;
  low_bat_reset_counter = 0;
  power_on_reset_counter = 0;
  if(get_user_set_flag() == CONST_NV_USED)
  {  
    for(i=0;i<400;i++)
    {
       if(0xFFFF == nv_get_halfword(REBOOT_FLASH_START+2*i))
       break;
       else if(TYPE_WATCHDOG_RESET == nv_get_halfword(REBOOT_FLASH_START+2*i))
       {
         ++watchdong_reset_counter;
       }
       else if(TYPE_LOW_VOL_RESET == nv_get_halfword(REBOOT_FLASH_START+2*i))
       {
         ++low_bat_reset_counter;
       }
       else if(TYPE_POWER_ON_RESET == nv_get_halfword(REBOOT_FLASH_START+2*i))
       {
          ++power_on_reset_counter;
       }
    }
    if(i != 400)
    {
      FLASH_Unlock();
	  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);  
      if(type == TYPE_WATCHDOG_RESET)
      {
        FLASH_ProgramHalfWord((REBOOT_FLASH_START+2*i),TYPE_WATCHDOG_RESET); 
        ++watchdong_reset_counter;
      }
      else if(type == TYPE_LOW_VOL_RESET)
      {
        FLASH_ProgramHalfWord((REBOOT_FLASH_START+2*i),TYPE_LOW_VOL_RESET); 
        ++low_bat_reset_counter;
      }
      else if(type == TYPE_POWER_ON_RESET)
      {
        FLASH_ProgramHalfWord((REBOOT_FLASH_START+2*i),TYPE_POWER_ON_RESET); 
        ++power_on_reset_counter;          
      }
      FLASH_Lock();      
    }
  }
}

// Get unsigned short int value from NV flash address
u16 nv_get_halfword(uint address)
{
    u16 half_word;
    half_word = *(__IO u16 *)address;
    return half_word;
}
// Get trim status 
uchar get_trim_status(void)
{
    return nv_flash_data.nv_array.nv_trim_flag;
}
// Get product serial number 
uchar* get_flash_SN(void)
{
    return nv_flash_data.nv_array.nv_SN;
}
// Get made date from NV flash
u16 get_nv_date(void)
{
    return nv_flash_data.nv_array.nv_date;
}
// Get internal reference voltage from NV flash
u16 get_nv_vref(void)
{
    return nv_flash_data.nv_array.nv_vref;
}
// Set product made data to NV Flash 
void set_nv_date(u16 date)
{
    nv_flash_data.nv_array.nv_date = date;
}
// Set internal reference voltage to NV flash
void set_nv_vref(u16 vref)
{
    nv_flash_data.nv_array.nv_vref = vref;
}
// Set Trim flag to NV flash
void set_nv_trim_flag(void)
{
    nv_flash_data.nv_array.nv_trim_flag = 1;
}
// Initialize NV FLASH
void init_nv_flash(void)
{
 
  nv_read_int32(FOREVER_FLASH_START,nv_flash_data.nv_buff,6);
  if(nv_flash_data.nv_array.nv_trim_flag  != 1u)
  {
      ATE_Trim();
    }
  set_vrefint_mv(nv_flash_data.nv_array.nv_vref);
   
}

// Trim internal reference voltage with ATE tools
static void ATE_Trim(void)
{
  static bool trim_flag =  TRUE;
  __enable_interrupt();
  RTC_second_flag = GLP_TRUE;
  while(trim_flag)
  {
      static uchar trim_time_counter = 0;
      static uchar trim_rx_counter_backup;  
      if(RTC_second_flag)
      {
        RTC_second_flag = GLP_FALSE;
        if(trim_rx_counter == 0)
        {
            UART_TX('T');
        }
        if(trim_rx_counter !=0)
        {
            if(trim_rx_counter_backup == trim_rx_counter)
            {
              ++trim_time_counter;
              if(trim_time_counter>100)
              {
                  trim_rx_counter = 0;
                  trim_rx_counter_backup = 0;
                  trim_time_counter = 0;
              }
            }
            else
            {
                trim_rx_counter_backup = trim_rx_counter;
                trim_time_counter = 0;
            }
        }

      }
      trim_flag = trim_uart_rx_handler();
      
      
  }
}
// Read NV flash data to RAM
void nv_read_int32(uint address,uint *buf, uchar inumbertoread)
{
    uchar i;
    i=0;
    while(i<inumbertoread)
    {
        *(buf+i) = *(__IO uint *)(address+4*i);
        i++;
    }
}

// Handle internal reference voltage trim
bool trim_uart_rx_handler(void)
{
  static bool tirm_processing_flag;
  uchar uart_rx_char;
  tirm_processing_flag = TRUE;
  TrimAdcInit();
  
  if(get_uart_char(&uart_rx_char))
  {
    if(trim_rx_counter == 0)
    {
      if(uart_rx_char == 'S')
      {
          nv_flash_data.nv_array.nv_SN[trim_rx_counter] = uart_rx_char;
          ++trim_rx_counter;
      }      
    }
    else
    {
        if(trim_rx_counter<16)
        nv_flash_data.nv_array.nv_SN[trim_rx_counter] = uart_rx_char; 
        else if(trim_rx_counter == 16)
        {
            nv_flash_data.nv_array.nv_SN[16] = '\0';
        }
        else if(trim_rx_counter == 17)
        {
            nv_flash_data.nv_array.nv_date = uart_rx_char - '0';
        }
        else if(trim_rx_counter <= 21)
        {
            nv_flash_data.nv_array.nv_date = 10*nv_flash_data.nv_array.nv_date + uart_rx_char - '0';
        }
        else if(trim_rx_counter == 22)
        {
        }
        else if(trim_rx_counter == 23)
        {

           uart_rx_verf = uart_rx_char - '0';
        }
        else if(trim_rx_counter <= 26)
        {
          uart_rx_verf = 10*uart_rx_verf+ uart_rx_char - '0';
        }
        
        ++trim_rx_counter;
        if(trim_rx_counter>=27)
        {
      
          trim_rx_counter = 0;
          if(extern_ver_trim())
          {
            tirm_processing_flag = FALSE;
          }
        }        
     }    
  }
  
  return tirm_processing_flag;
 }
// Calcuale internal reference voltage 
bool extern_ver_trim(void)
{
  bool trim_vref_ok;
  u16 ADC_vrefint, ADC_extern_ref;
  uchar ADC_times,i;
  uchar u_rx_char;
  
  
  trim_vref_ok = FALSE;
  ADC_vrefint = 0;
  ADC_extern_ref = 0;

  
  for(i=0;i<100;i++)
  {
      while(!Flag_1MS);
      Flag_1MS = FALSE;
  }
  
  
  for(ADC_times = 0; ADC_times<20; ADC_times++)
  {
      ADC_vrefint += Sample_ADC(VREFINT); 
      ADC_extern_ref += Sample_ADC(VEXTREF);
  }
  
  nv_flash_data.nv_array.nv_vref= (uart_rx_verf*ADC_vrefint + ADC_extern_ref/2)/ADC_extern_ref;
  if((nv_flash_data.nv_array.nv_vref>=1160) && (nv_flash_data.nv_array.nv_vref<=1240))
  {
    trim_vref_ok = TRUE;
    nv_flash_data.nv_array.nv_trim_flag = 1u;
    FLASH_Unlock();
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);  
    FLASH_ErasePage(FOREVER_FLASH_START);
    for(i=0;i<6;i++)
    {
        FLASH_ProgramWord((FOREVER_FLASH_START+4*i),nv_flash_data.nv_buff[i]);  
    }
    FLASH_Lock(); 
    Send_Message("\nTRIM OK\n");
    
    while(!get_uart_char(&u_rx_char));
    while(u_rx_char != 'E')
    {
      get_uart_char(&u_rx_char);    
    }    
    McuInit();
 /*   
    McuPvInit();
 */   
  }  
  else 
  {
    Send_Message("\nTRIM FAIL\n"); 
    trim_rx_counter = 0;
    
  }

  return trim_vref_ok;
}
// EOF
