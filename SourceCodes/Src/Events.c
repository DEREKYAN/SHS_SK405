#include "ADC.h"
#include "Fuel.h"
#include "Mobile.h" // for mobile fault
#include "UART.h"
#include "Events.h"
#include "UI.h"
#include "PV.h"
#include "MCU.h"
#include "radio.h"
#include "nv.h"
#include "keypad.h"
#include "SKBridgePAYG.h"
#include "record.h"
#include "Light.h"

#define CONST_BUTTON    1000
uchar time_idle_counter = 0;
extern void payg_state_consume_credit(const uint32_t amount);  // speed up to consume credit by derek *60
bool button_req_inactive =FALSE;		// Require that turn off system while button is long pressed
uint RTC_Second = 0;
FALG_14HOURS_TYPE flag_14_handler_status;
static u16 press_button_over_20seond =0;
static uint system_idle_time = 0;			// variable value -- system idle status time counter
volatile uchar system_state = ACTIVE;                     // Variable value -- system status (e.g: ACTIVE, SLEEP, HIBERNATION)                    

enum RTC_CALIBRATION_TYPE RTC_calibration_step = RTC_CALIBRATION_PROHIBIT;
uint32_t HSI_ms_counter, LSI_second_counter; 
// The following table is used to detect different key down event 
const u16 ADC_KEY_TABLE[6] = {POWER_SW11, SW11_SW12, SW12_SW13, SW13_SW14, SW14_SW15, SW15_MAX};
const u16 key_max[5] = {ADC_SW11_MAX,ADC_SW12_MAX,ADC_SW13_MAX,ADC_SW14_MAX,ADC_SW15_MAX};
const u16 key_min[5] = {ADC_SW11_MIN,ADC_SW12_MIN,ADC_SW13_MIN,ADC_SW14_MIN,ADC_SW15_MIN};
volatile GLP_bool RTC_second_flag = GLP_FALSE;		// RTC 1 Second interrupter flag bit 
static volatile uchar button_idle_time = 0;		// The time counter that button event is idle.	
uint RTC_second_elapsed = 0;			// second elapsed for PAYG 
extern uint32_t payg_all_process(uint32_t seconds_elapsed);
static void payg_14hours_handler(uint32_t time_second);


void payg_second_elapsed_handle(void)
{
   if(RTC_second_flag)
   {    
        RTC_second_flag = GLP_FALSE;
        payg_state_consume_credit(RTC_second_elapsed*SPEED_UP_NUMBER);  // speed up to consume credit by derek *60   
        payg_all_process(RTC_second_elapsed);     
        event_second_record(RTC_second_elapsed*SPEED_UP_NUMBER);
        if(get_user_set_flag() == CONST_NV_USED)
        {  
            payg_14hours_handler(RTC_second_elapsed*SPEED_UP_NUMBER);
            inc_uint_counter(&uart_nvram.nvram.unv_working_life_time,RTC_second_elapsed*SPEED_UP_NUMBER);
        }
        else
        {
            inc_uint_counter(&uart_nvram.nvram.unv_inventory_time,RTC_second_elapsed*SPEED_UP_NUMBER);
        }
        if((system_state != ACTIVE) && (!LSI_Calibartion_Standby) && (calibration_number < MAX_CALIBRATION_TIMES))
        {
            time_counter_calibration += RTC_second_elapsed *SPEED_UP_CALIBRATION;            

            if(time_counter_calibration >= TIME_CALIBRATION_STANDBY)
            {
                LSI_Calibartion_Standby =  GLP_TRUE;
            }
        }        
   	RTC_second_elapsed = 0;
        
//        Send_Number(RTC_second_elapsed);     // Add for test 
        #ifdef  DEBUG_LSI_CALIBRATION
//        Send_Message("\nRTC\n");
        #endif          
   }
}

void clear_RTC_timer_counter(void)
{
  uchar delay;
  delay = 5;
  RTC_TimeTypeDef RTC_TimeStructure;
  while( delay != 0)
  {
    RTC_GetTime(RTC_Format_BCD, &RTC_TimeStructure);	 
    RTC_Second = ((uint8_t)(RTC_TimeStructure.RTC_Seconds & (uint8_t)0xF0) >> (uint8_t)0x4) * 10;
    RTC_Second += (RTC_TimeStructure.RTC_Seconds & (uint8_t)0x0F);
    if(RTC_Second > 0)
    {    
//      Send_Message("RTC\n");	                // Add for test 
      RTC_second_elapsed += RTC_Second;
      time_idle_counter = RTC_Second;
      RTC_second_flag = GLP_TRUE;
      RTC_TimeStructure.RTC_H12     = RTC_H12_AM;
      RTC_TimeStructure.RTC_Hours   = 0x00;
      RTC_TimeStructure.RTC_Minutes = 0x00;
      RTC_TimeStructure.RTC_Seconds = 0x00;  
  
      RTC_SetTime(RTC_Format_BCD, &RTC_TimeStructure);

      break;
    }
     --delay;
  }

//  clr_RTC_time();

}

// The function return is button event status 
bool Is_Button_Idle(void)
{
    if((button_idle_time >= 3) || (press_button_over_20seond >= CONST_BUTTON))
        return TRUE;
          return FALSE;
}

// button push interrupt and SKJ button push
void EXTI4_15_IRQHandler(void) {
  if(EXTI_GetFlagStatus(EXTI_Line4))  
  EXTI_ClearFlag(EXTI_Line4);
  if(EXTI_GetFlagStatus(EXTI_Line6))
  EXTI_ClearFlag(EXTI_Line6);                                            // PB6 FM model button interrupter
  system_state = ACTIVE;
  button_idle_time = 0;
  press_button_over_20seond = 0;
}


static void payg_14hours_handler(uint32_t time_second)
{
  static uint32_t time_14hour;
  time_14hour +=time_second;
  if((flag_14_handler_status.data_bit.fault_occur) && (!flag_14_handler_status.data_bit.flag_any_fault))
  {
      flag_14_handler_status.data_bit.flag_any_fault = 1;
      inc_usi_counter(&uart_nvram.nvram.unv_any_fault);
  }
  
  if(time_14hour >= CONST_14HOURS)
  {
    time_14hour -= CONST_14HOURS;   
    flag_14_handler_status.data_int32 = 0;
  }
}

// Get system idle time 
uint get_system_idle_time(void)
{
    return system_idle_time;
}
// Add system idle time with 1 or 60 when RTC 1 second or 1 minute interrupt take place  
void add_system_idle_time(void)
{
  system_idle_time +=time_idle_counter * SPEED_UP_NUMBER ;
  time_idle_counter = 0;
}
// Clear idel time when system exit idle status
void clear_system_idle_time(void)
{
    system_idle_time = 0;
}
// Judge whether system enter Hiberation mode or not  
bool Is_stop(void)
{
  if(system_idle_time>= CONST_3DAY)	// If no operation in 15 days, system enter hibernation status 
  return TRUE;
    return FALSE;
}

// Add 1 to time counter. function parameter: unsigned 32 bits time counter address, 
// because timer counter output with hour units, 
// Maximum chars: 5
void inc_uint_counter(uint* counter,uint t)
{
      *counter +=t;
      if(*counter > (99999*60*60))
        *counter = 99999*60*60;
}

// Add 1 to time counter. function parameter: unsigned 16 bits time counter address, 
// Time counter maximum: 0xFFFF 
void inc_usi_counter( u16* counter)
{
    if(get_user_set_flag() == CONST_NV_USED)
    {
      if(*counter != 0xFFFF)
        ++(*counter);
      flag_14_handler_status.data_bit.fault_occur = 1;
    }
}

// Add 1 to time counter. function parameter: unsigned 16 bits time counter address, 
// Time counter maximum: 0xFFFF 
GLP_bool inc_event_counter( u16* counter)
{
    GLP_bool rt ;
    rt = GLP_FALSE;
    if(get_user_set_flag() == CONST_NV_USED)
    {
      if(*counter != 0xFFFF)
      ++(*counter); 
      rt = GLP_TRUE;
    }
    return rt;
}

// Lantern keep on, after 1 hours, system start to record user data to NV flash 
void handler_user_set_flag(void)
{
    
    static u16 user_set_flag_time = 0;
    if(adc_ave.ave_i_load < 0)
    {
        user_set_flag_time += SPEED_UP_NUMBER;
        if(user_set_flag_time >= (60*60*1))
        {  
            write_nv_user_set_flag();       
        } 
    }  
    else
    {
       user_set_flag_time = 0;
    } 
}

// ADC button process function
void Check_Button()
{
    static uchar button_pin_backup = 6;			
    static bool button_pressed = FALSE;
    static bool button_processed = FALSE;
   
    static uchar long_key_count_20ms;
    static uchar button_pin;
    static uint key_ADC;

    key_ADC = adc_result.key_adc;				// Get key ADC value 		
    for(button_pin=0; button_pin<6;button_pin++)
    {
        if(key_ADC < ADC_KEY_TABLE[button_pin])		// Judge which key is pressed 
          break;
    }

    if((button_pin > 0 ) && (button_pin < 6))
    {
        if((key_ADC > key_max[button_pin-1]) || (key_ADC < key_min[button_pin-1]))
          button_pin = 0xFF;
    }  
    
    if(button_pin_backup == button_pin)			// Get rid off button debounce  
    { 
       
        if((button_pin_backup>=6) && (button_pin_backup != 0xFF))
        {
          // No button is pressed, clear all flag 	
          button_pressed = FALSE;				
          button_processed = FALSE;  
          long_key_count_20ms = 150;    // Delay 3S
          ++button_idle_time;
   /*       
          if(button_pressed)
          {
            Send_Message("#");
            Send_Number(button_pin_backup);
          }
          else
          {
            Send_Message("*");
            Send_Number(button_pin_backup);
          }
          */
        }
        else if(button_pin_backup != 0xFF)
        {
            button_idle_time = 0;
            if(press_button_over_20seond < CONST_BUTTON)
              ++press_button_over_20seond;
   /*         
            if(button_pressed)
            {
              Send_Message("$");
              Send_Number(button_pin_backup);
            }
            else
            {
              Send_Message("%");
              Send_Number(button_pin_backup);
            }           
     */       
            if(button_pressed)
            {
       //         Send_Message("!");
                --long_key_count_20ms;
                if(long_key_count_20ms == 0)
                {
                	// Long pushed
                    long_key_count_20ms = 50;
                    if(button_pin_backup == 0)
                    {
                        if(!button_processed)
                        {
                           button_processed = TRUE;
                           configure_manmul_off();
                           inc_event_counter(&uart_nvram.nvram.unv_manually_turn_off);
                           if(Is_Empty_Fuel())
                           {
                              set_red_led_blink_conter();	// Red indication blink @ empty fuel when button is pressed 
                           }
                        }
                    }      
                }
            }
            else
            {
                button_pressed = TRUE;
                Send_Message("\n　　　　　　　　　　　　　　　　　　　　　　　　　　　　\n"); 
                if(button_pin_backup == 0)
                {     

                    if(MOBILE_FAULT != Get_Mobile_State())
                    Set_Mobile_State(MOBILE_ON);
                    button_req_inactive =FALSE;
                    if(Light_State != LIGHT_FAULT)
                       Light_State = LIGHT_OFF;
      
                    if(Is_Empty_Fuel())
                    {
                      set_red_led_blink_conter();		// Red indicaton blinks @ emptey fuel when mode button is pressed 
                    }
                    inc_event_counter(&uart_nvram.nvram.unv_button_press);
                }
                else
                {
                   
                    set_keypad_to_credit(button_pin_backup); 
                    //  Add for debug 
 //                   Send_Message("="); 
                    Send_Message("\nK:");
                    Send_Number(button_pin_backup);
                    Send_Message("\n");
                }
            }
          }
    }
    else 
    {
      button_pin_backup = button_pin; 			// Get rid off button bounce 
    }
}

void configure_manmul_off(void)
{
//  light_state = OFF_LIGHT_STATE;
  Set_Mobile_State(MOBILE_MANUAL_OFF);	 // Lattern will be shut off and enter hibernaton mode when button is long pressed 
  
  Light_State = LIGHT_MANUAL_OFF;
  button_req_inactive = TRUE;   
}


// Get the flag that long pressed button require that system enter hibernation status bec
bool get_button_req_inactive(void)
{
    return button_req_inactive;
}
// When requre is processed, clear the flag 
void clear_button_req_inactive(void)
{
    button_req_inactive = FALSE;
}

// Clear the falg that button requre systen enter hibernation automally in 5 seconds
void event_second_long_key(void)
{
    static uchar button_req_inactive_time = 0;
    if(button_req_inactive)
    {
        ++button_req_inactive_time;
        if(button_req_inactive_time > 5)
        {
            button_req_inactive = FALSE;
        }
    }
    else
    {
        button_req_inactive_time = 0;
    }
}

// EOF
