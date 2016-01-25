#include "Light.h"
#include "Events.h"
#include "ADC.h"
#include "Fuel.h"
#include "UART.h"
#include "Mcu.h"
#include "record.h"
#include "Mobile.h"
#include "SKBridgePAYG.h"

enum LIGHT_STATUS_TYPE Light_State;
void Light_fault_occur(void);

// Private Function Prototypes
/*
static bool Is_Light_Short(void);
static void Port_12V(void);
static void Port_9V(void);
static void Port_Off(void);
*/
/*
 * TO DO:
 * 
 */

// Shared Functions

// This function initializes the light output into the off state
// Called by main init
//#define LIGHT_12V_SHORT_THRESHOLD                   8200            // 8.2V protect 
//#define LIGHT_8V5_SHORT_THRESHOLD                   5600            // 5.6 protect 
void Light_Init(void) {
  Light_State = LIGHT_OFF;
  Light_Port_Off();
}


void Light_Port_Off(void)
{
  GPIO_ResetBits(GPIOB, PORTB_12VEN);
  GPIO_ResetBits(GPIOA, PORTA_12V_H_8V5_L); 
}

void Light_Port_Low(void)
{
  GPIO_SetBits(GPIOB, PORTB_12VEN);
  GPIO_ResetBits(GPIOA, PORTA_12V_H_8V5_L);   
}

void Light_Port_Hight(void)
{
  GPIO_SetBits(GPIOB, PORTB_12VEN);
  GPIO_SetBits(GPIOA, PORTA_12V_H_8V5_L);   
}

// 12V 8.2    8.5  5.6V 
// This function tests and responds to a light short or battery overtemperature condition
void Handle_Light_Short(void) {
  static uchar light_fault_time = 0;
  switch(Light_State)
  {
      case LIGHT_LOW:
      if(adc_ave.ave_v_lihgtfb < LIGHT_8V5_SHORT_THRESHOLD)
        ++light_fault_time;
      else
        light_fault_time = 0;
      
       break;
      
      case LIGHT_NORMAL:
      if(adc_ave.ave_v_lihgtfb < LIGHT_12V_SHORT_THRESHOLD)
      ++light_fault_time;
      else
      light_fault_time = 0;
      break;

      default:
      light_fault_time = 0;  
      break;
  }
  if(light_fault_time >=2)
  {
    Light_fault_occur();
    light_fault_time = 0;  
  }
}

void Light_fault_occur(void)
{
    Light_State = LIGHT_FAULT;
    inc_usi_counter(&uart_nvram.nvram.unv_light_scp);
    Send_Message("\n12VFS ");	
    Send_Number(adc_ave.ave_v_lihgtfb); 
}

// This function handles the light state machine
// Called by main
/*
    LIGHT_OFF, 
    LIGHT_FAULT,
LIGHT_MANUAL_OFF,
    LIGHT_LOW,
    LIGHT_NORMAL,
*/
void Handle_Light(void) 
{
  static u16 light_fault_reset_timer = 0;
    switch (Light_State) {
      case LIGHT_OFF:
        if ((get_system_idle_time() < CONST_3DAY) && !Is_Empty_Fuel() && (CREDIT_DISABLE != get_credit_status())) 
        {
          if(Is_Low_Fuel())
          {
                Light_State = LIGHT_LOW;
          }
          else
          {
              Light_State = LIGHT_NORMAL;
          }
/*
          Mobile_State = MOBILE_ON;
          _Port_5V_On();							// enable mosfet to 5V regulators
          Send_Message("5V_O");						//6
*/          
        }
        break;
/*        
      case LIGHT_MANUAL_OFF:
        _Port_5V_Off();								// disable mosfet to 5V regulators
        break;
*/        
      case LIGHT_FAULT:
        light_fault_reset_timer++;
 //       if (system_state < ACTIVE)
 //       light_fault_reset_timer += 49;
        if (light_fault_reset_timer >= MOBILE_FAULT_TIME)
        {
          Light_State = LIGHT_OFF;
          light_fault_reset_timer = 0;
        }
        break;
        
      case LIGHT_LOW:
      case LIGHT_NORMAL:
      if (Is_Empty_Fuel() || (CREDIT_DISABLE == get_credit_status())) 
      {	                                // if low or empty fuel, or time out has been reached
          Light_State = LIGHT_OFF;						// set mobile state to off
      }  
      else if(get_system_idle_time() >= CONST_3DAY)
      {
          Light_State = LIGHT_OFF;	
      }
      else
      {  
//        Handle_Light_Short();
        if(Light_State != LIGHT_FAULT)
        {  
          if(Is_Low_Fuel())
          {
            Light_State = LIGHT_LOW;
            Handle_Light_Short();
          }
          else
          {
            Light_State = LIGHT_NORMAL;
            Handle_Light_Short();
          }
        }
      }
    }
    
    
//    Light_State = LIGHT_OFF;	        // Add for test 
    
    switch (Light_State) 
    {
      case LIGHT_OFF:
      case LIGHT_FAULT:
      case LIGHT_MANUAL_OFF:  
      
      Light_Port_Off();
      break;
	
      case LIGHT_LOW:
      Light_Port_Low();
      break;
      
      case LIGHT_NORMAL:
      Light_Port_Hight();
      break;
      
      default:

      Light_State = LIGHT_OFF;
      break;
    }
}

// EOF
