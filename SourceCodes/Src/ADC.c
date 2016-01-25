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
#include <stdlib.h>
#include <string.h>
#include "Light.h"
#include "Mobile.h"

u16 tracebuffer[64];
u16 tracebuffer_NULL[10];

struct ADC_RESULT_STRUCT adc_result;
struct ADC_SUM_STRUCT adc_sum;
struct ADC_AVE_AVERAGE adc_ave;
static u16 avg_vbatt_5mS = START_BATTERY_VOLTAGE;  // variable value -- battery voltage from average value of 5 avg_vbatt(mV) 
static u16 Vrefint_mV;            // Variable value -- Vrefint from NV FLASH (mV)

u16 get_Vrefint_mV(void)                        
{
    return Vrefint_mV;
}

void set_vrefint_mv(u16 vref)     // Read Vref from NV flash and set internal verf value 
{
  Vrefint_mV = vref;
}


void stop_delay(uint t)
{
    while(t !=0)
      --t;
}

void Handle_short_protect(void)
{
    uchar x = 0;
    memset(&adc_result.battery_adc, 0, 0);
    
    
    for (x = 0; x < (ADC_AVG_SAMPLES); x++) 
    {
        adc_result.battery_adc  += Sample_ADC(VREFINT);
        adc_result.Lightfb_adc += Sample_ADC(LINGH_ADC);
        adc_result.USBfb_adc += Sample_ADC(USB_ADC);
    }

    adc_result.battery_adc = (adc_result.battery_adc + ADC_AVG_SAMPLES/2)/ADC_AVG_SAMPLES;     
    adc_result.Lightfb_adc = (adc_result.Lightfb_adc + ADC_AVG_SAMPLES/2)/ADC_AVG_SAMPLES;  
    adc_result.USBfb_adc = (adc_result.USBfb_adc + ADC_AVG_SAMPLES/2)/ADC_AVG_SAMPLES;  
     
    adc_result.v_vdd = (4095 * Vrefint_mV +  adc_result.battery_adc/2)/adc_result.battery_adc;      // VDD =Vref*4095/ADC_vref  (mV)
    adc_result.v_USBfb =  9*(adc_result.USBfb_adc * adc_result.v_vdd  + 4095/2)/4095;                        //  ( 240K + 30K)/30K = 9
 
    if(Light_State == LIGHT_LOW)
    {
        adc_result.v_lihgtfb = 43*(adc_result.Lightfb_adc * adc_result.v_vdd  + 4095/2)/(4095*3); 
    }
    else if(Light_State == LIGHT_NORMAL)   
    {
        adc_result.v_lihgtfb = 201*(adc_result.Lightfb_adc * adc_result.v_vdd  + 4095/2)/(4095*10);    
    } 
    adc_ave.ave_v_USBfb = adc_result.v_USBfb;
    adc_ave.ave_v_lihgtfb = adc_result.v_lihgtfb;
    Handle_Light();
    Handle_Mobile();
    
}

/********************************************
** The function is ADC sample in sleep and hibernation mode     
********************************************/
void stop_adc_samples(void)
{
    uchar x = 0;
    
    GPIO_SetBits(GPIOB, PORTB_OMPEN);
    OP_Discharging();
    stop_delay(8000);
    
    memset(&adc_result.battery_adc, 0, 6);
    for (x = 0; x < (STOP_ADC_SAMPLES); x++) 
    {
        adc_result.battery_adc  += Sample_ADC(VREFINT); 
        adc_result.uc_adc += Sample_ADC(UC_ADC);     
        adc_result.PVfb_adc += Sample_ADC(PVFB_ADC);        
    }
    

    adc_result.battery_adc = (adc_result.battery_adc + STOP_ADC_SAMPLES/2)/STOP_ADC_SAMPLES;    
    adc_result.load_adc = (adc_result.uc_adc + STOP_ADC_SAMPLES/2)/STOP_ADC_SAMPLES;  
    adc_result.PVfb_adc = (adc_result.PVfb_adc + STOP_ADC_SAMPLES/2)/STOP_ADC_SAMPLES;
  
    adc_result.v_vdd = (4095 * Vrefint_mV +  adc_result.battery_adc/2)/adc_result.battery_adc;      // VDD =Vref*4095/ADC_vref  (mV)
    adc_result.v_PVfb  =  28*(adc_result.PVfb_adc * adc_result.v_vdd  + 4095/2)/(4095*3); 
     
    if(adc_result.load_adc > adc_result.discharging_adc_offset)
    {
      adc_result.i_discharging = 0;        
    }
    else
    {
      adc_result.i_discharging = ((adc_result.load_adc - adc_result.discharging_adc_offset)*adc_result.v_vdd)*100/(101*4095);
      if(adc_result.i_discharging > (-MIN_CURRENT))
          adc_result.i_discharging = 0;
    }
    adc_ave.ave_i_load = adc_result.i_discharging;
    adc_ave.ave_i_battery = adc_result.i_discharging;
    adc_ave.ave_v_battery = adc_result.v_vdd;
    adc_ave.ave_v_PVfb = adc_result.v_PVfb;

    OP_Charging();
    adc_result.Flag_Charing_Discharge = GLP_FALSE;   
}


void Initial_ADC_Offset(void)
{
    uchar x = 0;
    uint sum_adc_offset = 0;

    OP_Discharging();  
    delay(20000);   
        
    for (x = 0; x < 64; x++)   
    {   
       u16 t;
       t = Sample_ADC(UC_ADC);
       sum_adc_offset += t;/*Sample_ADC(UC_ADC);*/   
       tracebuffer[x] = t;  
    }
    adc_result.discharging_adc_offset = (sum_adc_offset + 32)/64; 
    adc_result.Flag_Charing_Discharge = GLP_TRUE;

}

/********************************************
** The function is ADC sample in Active mode     
********************************************/
void Run_ADC_Samples(void)
{
    uchar x = 0;
    memset(&adc_result.battery_adc, 0, 12);
    
    
    for (x = 0; x < (ADC_AVG_SAMPLES); x++) 
    {
        u16 a;
        adc_result.battery_adc  += Sample_ADC(VREFINT);
        
        adc_result.uc_adc +=Sample_ADC(UC_ADC);
        adc_result.PVfb_adc += Sample_ADC(PVFB_ADC);
        adc_result.Lightfb_adc += Sample_ADC(LINGH_ADC);
        adc_result.USBfb_adc += Sample_ADC(USB_ADC);
        adc_result.key_adc += Sample_ADC(KEY_ADC);
    }

    adc_result.battery_adc = (adc_result.battery_adc + ADC_AVG_SAMPLES/2)/ADC_AVG_SAMPLES;    
    adc_result.uc_adc = (adc_result.uc_adc + (ADC_AVG_SAMPLES/*-1*/)/2)/(ADC_AVG_SAMPLES/*-1*/);  
    adc_result.PVfb_adc = (adc_result.PVfb_adc + ADC_AVG_SAMPLES/2)/ADC_AVG_SAMPLES;  
    adc_result.Lightfb_adc = (adc_result.Lightfb_adc + ADC_AVG_SAMPLES/2)/ADC_AVG_SAMPLES;  
    adc_result.USBfb_adc = (adc_result.USBfb_adc + ADC_AVG_SAMPLES/2)/ADC_AVG_SAMPLES;  
    adc_result.key_adc = (adc_result.key_adc + ADC_AVG_SAMPLES/2)/ADC_AVG_SAMPLES;  
     
    adc_result.v_vdd = (4095 * Vrefint_mV +  adc_result.battery_adc/2)/adc_result.battery_adc;      // VDD =Vref*4095/ADC_vref  (mV)
    adc_result.v_USBfb =  9*(adc_result.USBfb_adc * adc_result.v_vdd  + 4095/2)/4095;                        //  ( 240K + 30K)/30K = 9
    adc_result.v_PVfb  =  28*(adc_result.PVfb_adc * adc_result.v_vdd  + 4095/2)/(4095*3);               //  ( 100K + 12K)/12K = 
      
    if(Light_State == LIGHT_LOW)
    {
        adc_result.v_lihgtfb = 43*(adc_result.Lightfb_adc * adc_result.v_vdd  + 4095/2)/(4095*3); 
    }
    else if(Light_State == LIGHT_NORMAL)   
    {
        adc_result.v_lihgtfb = 201*(adc_result.Lightfb_adc * adc_result.v_vdd  + 4095/2)/(4095*10);    
    } 
    
    if(adc_result.Flag_Charing_Discharge)
    {
      adc_result.load_adc = adc_result.uc_adc;
      OP_Charging();
      adc_result.Flag_Charing_Discharge = GLP_FALSE;
      if(adc_result.load_adc > adc_result.discharging_adc_offset)
      {
          adc_result.i_discharging = 0;        
      }
      else
      {
          adc_result.i_discharging = ((adc_result.load_adc - adc_result.discharging_adc_offset)*adc_result.v_vdd)*100/(101*4095);
          if(abs(adc_result.i_discharging) < MIN_CURRENT)
            adc_result.i_discharging = 0;
      }
    }
    else
    {      
      adc_result.charging_adc = adc_result.uc_adc;
      OP_Discharging();
      adc_result.Flag_Charing_Discharge = GLP_TRUE;
      adc_result.i_charging = (adc_result.charging_adc * adc_result.v_vdd)/4095;     
        if(adc_result.i_charging < MIN_CURRENT)
          adc_result.i_charging = 0;
    }    

    ++adc_ave.counter;    
    
    if((adc_ave.counter != 1) && (adc_ave.counter != I_AVG_SAMPLE))
    {
      adc_result.i_battery = adc_result.i_charging + adc_result.i_discharging;
      adc_sum.sum_i_battery += adc_result.i_battery;

    }
    
    adc_sum.sum_v_battery += adc_result.v_vdd;
    adc_sum.sum_v_lihgtfb += adc_result.v_lihgtfb;
    adc_sum.sum_v_PVfb += adc_result.v_PVfb;
    adc_sum.sum_v_USBfb += adc_result.v_USBfb;

 
    if(adc_ave.counter >= I_AVG_SAMPLE)
    {
       int ave_i;
       adc_ave.counter = 0;
       adc_ave.ave_v_battery  = (adc_sum.sum_v_battery + I_AVG_SAMPLE/2)/I_AVG_SAMPLE;
    
       adc_ave.ave_v_lihgtfb = (adc_sum.sum_v_lihgtfb + I_AVG_SAMPLE/2)/I_AVG_SAMPLE;
       adc_ave.ave_v_PVfb = (adc_sum.sum_v_PVfb + I_AVG_SAMPLE/2)/I_AVG_SAMPLE;
       adc_ave.ave_v_USBfb = (adc_sum.sum_v_USBfb+ I_AVG_SAMPLE/2)/I_AVG_SAMPLE;
       ave_i = (adc_sum.sum_i_battery+ (I_AVG_SAMPLE-2)/2)/(I_AVG_SAMPLE-2);   
       if(adc_ave.flag_disable_PV == 0)
       {     
         adc_ave.ave_i_battery = ave_i;
         ++adc_ave.pv_measuere_counter;
         if(adc_ave.pv_measuere_counter > (1000/I_AVG_SAMPLE -1))
         {
            adc_ave.flag_disable_PV = 1;
            adc_ave.pv_measuere_counter = 0;

            // Shut off charging 
            ClrChrg0vPin();                     // PA5 low
            SetChrgCtrlPin();                   // PA1 high   
         }
       }
       else 
       {
          adc_ave.ave_i_load= ave_i;
          if(adc_ave.ave_i_load > (-MIN_CURRENT))
            adc_ave.ave_i_load = 0;
          adc_ave.ave_i_charging = adc_ave.ave_i_battery - adc_ave.ave_i_load;
          if(adc_ave.ave_i_charging < MIN_CURRENT)
            adc_ave.ave_i_charging = 0;
          adc_ave.flag_disable_PV = 0;
          Handler_PV_Port();
       }
       memset(&adc_sum.sum_v_battery, 0, sizeof(struct ADC_SUM_STRUCT));
        {
          static uchar re_initial_ADC_flag = 0;
            if(adc_ave.ave_v_battery <2500)
            {
                re_initial_ADC_flag = 0;
            }
            else
            {
                if(re_initial_ADC_flag == 0)
                {
                    re_initial_ADC_flag = 1;
                    McuAdcInit();
                }
            }
        }
       {
          static uchar flag_boot = 0;
          u16 boot_type;
          if(flag_boot == 0)
          {    
            flag_boot = 1;
            if(get_user_set_flag() == CONST_NV_USED)
            {   
              if(((RCC->CSR) & (RCC_CSR_IWDGRSTF | RCC_CSR_WWDGRSTF)) != 0)
              {
                boot_type = TYPE_WATCHDOG_RESET;              // Watchdog reset 
              }
              else if(((RCC->CSR) & RCC_CSR_SFTRSTF) != 0)
              {      
                boot_type =  TYPE_SOFTWARE_RESET;
              }
              else if(avg_vbatt_5mS >2700)
              {
                boot_type = TYPE_POWER_ON_RESET;              // Watchdog reset
              }
              else 
              {
                boot_type = TYPE_LOW_VOL_RESET;              // Watchdog reset
              }

              handler_reboot_counter(boot_type);
                
              RCC_ClearFlag();
                //              avg_vbatt_5mS
            }
          }
       }
    }
}

/*****************************************************************
**** Battery current sign
**** return + during charging and return - during - 
*****************************************************************/
uchar get_bat_in_out(int snum)
{
  uchar IO_char;
  if(snum>0)
  {
    IO_char = '+';
  }
  else if(snum==0)
  {
    IO_char = ' ';
  }
  else
  {
    IO_char = '-';
  }
  return IO_char;
}

/*****************************************************************
**** ADC convert function 
**** input: ADC channel
**** Output: ADC value
*****************************************************************/
uint Sample_ADC(uint channel) {
  ADC1->ISR = ADC_FLAG_EOC;
  ADC1->CHSELR = channel;
  ADC1->CR |= ADC_CR_ADSTART;
  while ((ADC1->ISR & ADC_FLAG_EOC)== 0);
  return ADC1->DR;
}
// EOF
