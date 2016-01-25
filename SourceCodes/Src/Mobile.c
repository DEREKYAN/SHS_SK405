#include "Mobile.h"
#include "Mcu.h"
#include "UART.h"
#include "ADC.h"
#include "Fuel.h"
#include "Events.h"
#include "radio.h"
#include "PV.h"
#include "nv.h"
#include "UI.h"
#include "SKBridgePAYG.h"
#include "record.h"
#include <stdlib.h>
#include <string.h>

uchar Mobile_State = MOBILE_ON;  // mobile state variable
uint USB_heavy_load_time = 0;
uint USB_light_load_time = 0;
uchar mobile_idle_time = 0;

void event_second_load(void)
{
    int ave_power;
    if(adc_ave.ave_i_load < 0)
    {
      ave_power = -(adc_ave.ave_i_load * adc_ave.ave_v_battery/1000);
      if(Is_Low_Fuel())
      {
        inc_uint_counter(&uart_nvram.nvram.unv_low_battery_discharge_time,1*SPEED_UP_NUMBER); 
      }
      if(ave_power > 10000)
      {
        inc_uint_counter(&uart_nvram.nvram.unv_discharge_level_6_time,1*SPEED_UP_NUMBER);  
      }
      else if(ave_power > 8000)
      {
        inc_uint_counter(&uart_nvram.nvram.unv_discharge_level_5_time,1*SPEED_UP_NUMBER);  
      }    
      else if(ave_power > 6000)
      {
        inc_uint_counter(&uart_nvram.nvram.unv_discharge_level_4_time,1*SPEED_UP_NUMBER);  
      }        
      else if(ave_power > 4000)
      {
        inc_uint_counter(&uart_nvram.nvram.unv_discharge_level_3_time,1*SPEED_UP_NUMBER);  
      }            
      else if(ave_power > 2000)
      {
        inc_uint_counter(&uart_nvram.nvram.unv_discharge_level_2_time,1*SPEED_UP_NUMBER);  
      }              
      else if(ave_power > 0)
      {
        inc_uint_counter(&uart_nvram.nvram.unv_discharge_level_1_time,1*SPEED_UP_NUMBER);  
      }   
    }
}

//Judge whether mobile port is idle or not 
bool Is_Mobile_Idle(void)
{ 

    if(adc_ave.ave_i_load > (-MOBILE_IDLE_THESHOLD))
    {   
      if(mobile_idle_time != 0)
      {
        --mobile_idle_time;
      }
    }
    else
    {
       if(mobile_idle_time < 100)
       {
          ++mobile_idle_time;
       }
    }
    if(mobile_idle_time<50)
    return TRUE;
    return FALSE;
}

// Handle mobile port active time 
// This function handles the 5V state machine
// Called by main
void Handle_Mobile(void) {

  static u16 fault_reset_timer = 0;
  static uchar mobile_V_short_time = 0;
    switch (Mobile_State) {
      case MOBILE_OFF:
        if ((get_system_idle_time() < CONST_3DAY) && !Is_Low_Fuel() && !Is_Empty_Fuel() && (CREDIT_DISABLE != get_credit_status())) {
          Mobile_State = MOBILE_ON;
          _Port_5V_On();							// enable mosfet to 5V regulators
          Send_Message("5V_O");						//6
        }
        break;
      case MOBILE_MANUAL_OFF:
        _Port_5V_Off();								// disable mosfet to 5V regulators
        break;
      case MOBILE_FAULT:
        fault_reset_timer++;
//        if (system_state < ACTIVE)
//        fault_reset_timer += 49;
        if (fault_reset_timer >= MOBILE_FAULT_TIME)
          Mobile_State = MOBILE_OFF;
        break;
      case MOBILE_ON:
        if (adc_ave.ave_v_USBfb < MOBILE_SHORT_THRESHOLD) {                               // test for short
          {
   
            ++mobile_V_short_time;
            if(mobile_V_short_time>5)
            {  
              mobile_V_short_time = 0;
              _Port_5V_Off();							// disable mosfet to 5V regulators
              Mobile_State = MOBILE_FAULT;						// set mobile state to fault
              Send_Message("\n5V_F");					        //4
//          Send_Message("\n");			
              inc_usi_counter(&uart_nvram.nvram.unv_USB_ocp);
              fault_reset_timer = 0;
            }
          }
        } 
        else
        {
            mobile_V_short_time = 0;
        }
          if (Is_Low_Fuel() || Is_Empty_Fuel() || (CREDIT_DISABLE == get_credit_status())) {	                                // if low or empty fuel, or time out has been reached
          Mobile_State = MOBILE_OFF;						// set mobile state to off
          Send_Message("5V_E");
//          Send_Number(Get_Fuel_Level());
//          Send_Message("\n");
          _Port_5V_Off();       // disable mosfet to 5V regulators
        } else if (get_system_idle_time() >= CONST_3DAY ) {
          Mobile_State = MOBILE_OFF;						// set mobile state to off
          _Port_5V_Off();					// disable mosfet to 5V regulators
          inc_event_counter(&uart_nvram.nvram.unv_usb_port_off);
        }	
        else
        {
            _Port_5V_On();
        }
        break;
        default:
        break;
    }  
}

// Set new state of mobile port 
void Set_Mobile_State(uchar set_state) {
  Mobile_State = set_state;
}

// This function returns the 5V state
uchar Get_Mobile_State(void) {
  return Mobile_State;
}
// EOF
