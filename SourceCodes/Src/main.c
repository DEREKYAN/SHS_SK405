#include "Mobile.h"
#include "Mcu.h"
#include "UART.h"
#include "Events.h"
#include "PV.h"
#include "ADC.h"
#include "UI.h"
#include "radio.h"
#include "nv.h"
#include "Fuel.h"
#include "record.h"
#include "Light.h"
#include "main.h"
#include "watchdog.h"
#include "SKBridgePAYG.h"
#include <angaza/angaza.h>
#include <stdlib.h>
#include <string.h>

// This file should only contain the main loop, and any sub-functions not defined in other modules used to break out code in order to make the main loop more read-able.
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
//static uchar test = 0;
static u16 Count_1MS = 0;                   // 1mS counter, maximum 1000, 1 second
static uchar Count_20MS;                    // 20ms counter, maximum 20, 20 milliseconds
static bool waiting_second_flag;            // The flag: delay 1 second to enable system status output by UART
static void process_second_event(void);     // The function:  call 1 second event processing function.
GLP_bool RTC_20S_Flag = FALSE;           // Set 20 Second interrupt @ hibernation status
u16 delay_sleep_ms = 1000;                 // Add 20000 for test 
//RCC_ClocksTypeDef test;
extern void Initial_Cable_Data(void);
extern void nonvol_init(void);
void Configure_RTC_2second(void);
void SYSCLKConfig_STOP(void);
void Initial_UART(void);

int main(void){
  
  ///////////// add for IAP
  uint32_t i;
  for(i=0;i<48;i++)
  {
      VectorTable[i] = *(__IO uint32_t *)(APPLICATION_ADDRESS+(i<<2));   // Set new interrupter address because IAP use new interrupter entry
  }
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);     // Must enable RCC_APB2Periph_SYSCFG 
  SYSCFG_MemoryRemapConfig(SYSCFG_MemoryRemap_SRAM);        // Must call function SYSCFG_MemoryRemapConfig
  
  McuInit();                      // Call the function to initialize MCU register according to hardware and RAM

  init_nv_flash();                // Process the record that is written only once  (e.g. production serial, internal ref voltage etc) 
  read_data_from_NV();            // Process the record that is output by UART
  nonvol_init();
  payg_all_init();
  watchdog_start(); 
//  RTC_Config_for_SK405(MODE_20SECOND);
  while(!RTC_second_flag)
  {
  }
  TurnOff_UI();
  Send_Message("SG");

 // Set_Low_Fuel();               // Add for test 20160112
  while(1) {
  if( Flag_1MS)                   // Waiting for 1ms interrupter
  {
      Flag_1MS = FALSE;

      Run_ADC_Samples();          // Handle ADC samples 
 //     Handle_Light_State();       // Control lantern luminance according to mode 1, 2, 3. 
      
      Count_20MS = Count_1MS % CONST_20MS;    
      switch(Count_20MS)
      {
        case EVENT_BUTTON_20MS_1:   // The first millisecond among 20 milliseconds 
        Check_Button();             // handler button once per 20 milliseoconds
        break;
        
        case EVENT_UI_20MS_2:       // The second, seventh, twelfth,seventeenth millisecond among 20 milliseconds 
        handler_fuel();             // handle fuel gauge once per 5 milliseconds   
        Handle_UI();                // Handle UI once per 5 milliseconds  
        UART_Handle_Rx_Data();
        break;  
        
        case EVENT_MOBILE_20MS_3:   // The third millisecond among 20 milliseconds
        Handle_Mobile();            // Handle Mobile output once per 20 milliseconds
        break;
        
        case EVENT_PV_20MS_4:       // The fourth, fourteenth millisecond among 20 milliseconds
        Handle_PV();          // Handle PV charging once per 10 milliseconds
        break;        
        
        case EVENT_PAYG_20MS_5:
        handl_payg_all_process();
        break;

        case EVENT_RTC_20MS_6:
        handle_rtc_calibration();
        break;
        
        case EVENT_UI_20MS_7:
        handler_fuel();
        Handle_UI();
        UART_Handle_Rx_Data();
        break;          
        
        case EVENT_LGIHGT_20MS_8:  // The eighth milliseconds among 20 milliseconds 
        Handle_Light();  
        break;
        
        case EVENT_PAYG_SECOND_20MS_9:
        payg_second_elapsed_handle();
        break;
  
        case EVENT_UI_20MS_12:
        handler_fuel();
        Handle_UI();
        UART_Handle_Rx_Data();
        break;      
        
        case EVENT_PV_20MS_14:
        Handle_PV();
        break;
        
        case EVENT_PAYG_20MS_15:
        handl_payg_all_process();
        break;
        
        case EVENT_UI_20MS_17:
        handler_fuel();
        Handle_UI();
        UART_Handle_Rx_Data();
        break;
          
        case EVENT_LIGHT_20MS_18:     // The eighteenth milliseconds among 20 milliseconds
//        Check_Light_Events();         // Handle lantern event once per 20 millseconds
        break;
        
        default:
        
        break;
        
      }
      ++Count_1MS;
      if( 0 == Count_1MS%100)
      {
          if(waiting_second_flag)
          {
              UART_Send_Sequence(Count_1MS/100);      // Uart output one logging data symbol per 100milliseonds
          }      
      }
      
      if(Count_1MS > CONST_1S)
      {
          Count_1MS = 0;
          watchdog_reload();
          if(waiting_second_flag)
          {

            waiting_second_flag = FALSE;      // During the 1 second, don't output any logging data symbol
            if(flag_uart_output_start)
            {
                flag_uart_output_start = GLP_FALSE;
                if(UART_output_standby_counter !=0)
                  --UART_output_standby_counter;
            }
          }
          else
          {
            waiting_second_flag = TRUE;
          }
          process_second_event();             // Handle 1 second event to add time counter 

      }
      
     Configure_RTC_2second();

     if(/*Is_charging_idle()*/(Is_PV_idle()) && (adc_ave.ave_i_load == 0)  && Is_Button_Idle() && IS_PAYG_IDLE() \
            && (!get_flag_req_pay_process()) && get_delay_sleep_status() && get_uart_command_idle() && (UART_output_standby_counter == 0))       
//     if(0)     // Derek add for test 1028  
     {
//        Send_Message("\PV:");			// Add for test 
//    Send_Number(pv_state);
//            Send_Message("\n");			// Add for test 
            
        uchar ut;
        RTC_calibration_step = RTC_CALIBRATION_PROHIBIT;
        if(get_button_req_inactive())           // Long push button, system enter hibernation status 
        {
            clear_button_req_inactive();
              system_state = HIBERNATING;
        }
        else
        {
//             Set_System_State(SLEEPING);        // At first, system enter sleep status without any event (No charging/Discharging/button down)
              system_state = SLEEPING;
 //             RTC_Config_Mode(MODE_2SECOND);
              RTC_Config_for_SK405(MODE_40MS);
        }
         while(system_state != ACTIVE)    
        {
  
            watchdog_reload();
            if(LSI_Calibartion_Standby)
            {
                Configure_RTC_2second();
                Flag_RTC_TRIM = 0;
                handle_rtc_calibration();
                SysTick_Config(SystemCoreClock / 1000);  // system has been woken up, reset systick clock 
                ut = 'C';
                if(system_state != HIBERNATING)
                {
                  add_system_idle_time();        //So system idle time is added 1 second
                }
            }
            else if(system_state == HIBERNATING)
            {
                if(!RTC_20S_Flag)
                {
                    RTC_20S_Flag = GLP_TRUE;
 //                   RTC_Config_Mode(MODE_20SECOND);
                    RTC_Config_for_SK405(MODE_20SECOND);
                }
                ut = 'H';                         // UART will output char 'H' once per one minute
            }
            else
            {   
                // In sleep mode, system is woken up once per second 
                add_system_idle_time();        //So system idle time is added 1 second
                if(Is_stop())
                {
                    system_state = HIBERNATING;
                }
                
                ut = 'S';                             // UART will output char 'S' once per one second
            }
                
            while(get_UART_Active());                 // Waiting until uart is idle.
            while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
            if(LSI_Calibartion_Standby)
 //           if(0)
            {
                while(!RTC_second_flag)
                {
                    watchdog_reload();
                    handle_rtc_calibration();
                    if(system_state == ACTIVE)
                      break;
                }
            }
            else
            {  
              while(!RTC_second_flag)
              {
 //               ++test;
//                watchdog_reload();                             // Add for test 
                Init_Enter_sleep();                 // Initialize register to enter sleep mode 
                PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);     // Let system enter low power mode													//allows voltage to stabilize without causing FB fault
                init_exit_stop();               // Initialize to exit STOP mode   
//                watchdog_reload();                             // Add for test 
                Handle_short_protect();
                if(system_state == ACTIVE)
                break;       
              }   
              Initial_UART();
              stop_adc_samples(); 

            }                 
            if(adc_ave.ave_v_PVfb > adc_ave.ave_v_battery )    // Check PV charging 
            {
              if(adc_ave.ave_v_battery < BATTERY_EXIT_CV)
              {
                system_state = ACTIVE;
                set_PV_status(PV_ON);
              }
              else if(adc_ave.ave_v_battery < BATTERY_ON_TO_CV_LOW)
              {
                 system_state = ACTIVE;
                 set_PV_status(PV_CV);               
              }

            }
//            if(Get_Mobile_State() == MOBILE_ON )     
            {
                uchar i,j;
                j=0;
                for(i=0;i<10;i++)
                {
                    stop_adc_samples(); 
                    if(adc_result.i_discharging < 0 )
                    j++;
                }
                if(j>=5)
                {
                  system_state = ACTIVE;
                  mobile_idle_time = 70;
                }
            }
            if(system_state == ACTIVE)         
            {
               ut = '~';                            // Exit sleep mode or hibernation mode, ouput char '~' with uart 
               clear_system_idle_time();               // re-count system idle time
            } 
            

            UART_TX_SLEEP_STOP(ut);
            payg_second_elapsed_handle();

            red_led_blink();                    // Red will blink 6 times, once per 10 second when you press button to turn on lantern during empty fuel  
            
        } 
         SysTick_Config(SystemCoreClock / 1000);  // system has been woken up, reset systick clock
         memset(&adc_sum.sum_v_battery, 0, sizeof(struct ADC_SUM_STRUCT));
         adc_ave.counter = 0;
        adc_ave.pv_measuere_counter = 0;
        adc_ave.flag_disable_PV = 0;  
        RTC_calibration_step = RTC_CALIBRATION_PROHIBIT;
     }
  
    }
  }   
}
/*********************************************
** The function is called once per second 
** Add time counter @ a variety of status 
**********************************************/
static void process_second_event(void)
{
  event_second_long_key();          // Clear shut off system flag after 5 seconds
  red_led_blink();                  // Red will blink 6 times, once per 10 second when you press button to turn on lantern during empty fuel  
  
  if(get_user_set_flag() == CONST_NV_USED)
  {
//    event_second_light();             // Handle lantern time counter 
    event_second_pv();                // Handle PV time counter 
//    event_second_mobile();
    event_second_load();
  }
  else
  {
    handler_user_set_flag();          // handle whether system start to record.
  }  
}
// EOF
void set_delay_sleep_ms(u16 t)
{
  delay_sleep_ms = t;
}

GLP_bool get_delay_sleep_status(void)
{
    GLP_bool status = GLP_TRUE;
    if(delay_sleep_ms !=0)
    {
        --delay_sleep_ms;
        status = GLP_FALSE;
    }
    if(get_timer_is_running())
    {
        status = GLP_FALSE;
    }
    return status;  
}

void SYSCLKConfig_STOP(void)
{  
  /* Wait till HSE is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET)
  {}
}

void Configure_RTC_2second(void)
{
    if(RTC_20S_Flag)
    {
      __disable_interrupt();
      RTC_calibration_step = RTC_CALIBRATION_PROHIBIT;
      clear_RTC_timer_counter();
      __enable_interrupt(); 
      RTC_Config_for_SK405(MODE_40MS);
      RTC_20S_Flag = GLP_FALSE;
  }  
}

void Initial_UART(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);     
}