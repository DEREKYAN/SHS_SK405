#include "UI.h"			
#include "ADC.h"		// adc levels
#include "Fuel.h"		// fuel level
#include "PV.h"			// is charging
#include "Events.h"		// timing
#include "Mcu.h"
#include "radio.h"
#include "nv.h"
#include "Mobile.h"
#include "record.h"
#include "main.h"
#include "Events.h"
#include <angaza/angaza.h>

#define CREDIT_LED_OFF        0
#define CREDIT_LED_ON_DUTY    1
#define CREDIT_LED_OFF_DUTY   2

uint8_t  credit_on_off_duty;



// UI Variables
static volatile uint red_led_blink_timer = 0;
static uchar red_led_blink_conter = 0;
static uchar interval_6second_counter = 0;
static uchar PAYG_comm_green_led_time = 0;

// Private Function Prototypes
static void Display_Battery_Level(void);
static void Display_Charge_Level(void);
static void Update_Charge_Rate_Persistence(uint charge_rate, uint* persistence, uint led_pin);
static void Display_PAYG_Commnuication(void);


static void Display_PAYG_Commnuication(void)
{
    ++PAYG_comm_green_led_time;
    if((payg_ui_step % 2) ==0)
    {
        TurnOff_UI();
        if(flag_green == 0)
        {
#ifndef DEBUG_PORT            
            _led_red_On();
#endif            
        }
        else 
        {
          GPIO_ResetBits(GPIOA, (LED1 | LED2 | LED3 | LED4 | LED5)); 
          _led_select_CHRG();
        }
 
        credit_on_off_duty = CREDIT_LED_ON_DUTY;        // Add
        if(PAYG_comm_green_led_time > payg_ui_on)
        {
            PAYG_comm_green_led_time = 0;
            --payg_ui_step;
            credit_on_off_duty = CREDIT_LED_OFF;        
        }
    }
    else
    {
        TurnOff_UI();
        credit_on_off_duty = CREDIT_LED_OFF_DUTY;               // Add 
        if(PAYG_comm_green_led_time > payg_ui_off)
        {
            PAYG_comm_green_led_time = 0;
            --payg_ui_step;
            credit_on_off_duty = CREDIT_LED_OFF;        
        }        
        
    }
}

void set_red_led_blink_conter(void)
{
    red_led_blink_conter = 6;
}


void red_led_blink(void)
{
    
    if(red_led_blink_conter != 0)
    {
        ++interval_6second_counter;
        if(interval_6second_counter>=6)
        {
            interval_6second_counter = 0;
#ifndef DEBUG_PORT              
            _led_red_On();
#endif            
            red_led_blink_timer = 8000;
            while(red_led_blink_timer != 0)
            {
              red_led_blink_timer--;
            }
#ifndef DEBUG_PORT              
            _led_red_Off();	
#endif           
            --red_led_blink_conter;
        }
    }
}

// Handles Display of the UI, by alternating between the battery level LEDs and the charge rate LEDs
// Called by Events Interrupt and Fast Wake
void Handle_UI(void) {
  if(Is_Communication_Indication())
  {
    Display_PAYG_Commnuication();   
  }
  else
  {
    static bool ui_fuel = TRUE;
    if (ui_fuel) 
    {				                                // show fuel gage UI
        Display_Battery_Level();
        ui_fuel = FALSE;
    } 
    else 
    {									// show charge UI
        Display_Charge_Level();
        ui_fuel = TRUE;
    }
  }
}

// This function turns off the UI
// Called by Startup and Test_Activity
void TurnOff_UI(void) {
#ifndef DEBUG_PORT  
  _led_red_Off();
#endif  

  GPIO_ResetBits(GPIOB, GPIO_Pin_4 | GPIO_Pin_3);
  GPIO_SetBits(GPIOA, (LED1 | LED2 | LED3 | LED4 | LED5));
}

// This function turns off the UI
// Called by Startup and Test_Activity
void TurnOn_UI(void) {
#ifndef DEBUG_PORT
  _led_red_On();
#endif  
  GPIO_SetBits(GPIOB, GPIO_Pin_4 | GPIO_Pin_3);
  GPIO_ResetBits(GPIOA, (LED1 | LED2 | LED3 | LED4 | LED5));
}
// This function clears the RED LED blink timer, so it responds immideately to a button push
void Clear_Red_LED_Blink_Timer(void) {
  red_led_blink_timer = 0;
}

// This function computes if an charge rate LED should display based on charge rate persistence
// Called by Display_Charge_Level
static void Update_Charge_Rate_Persistence(uint charge_rate, uint* persistence, uint led_pin) {
  if ((adc_ave.ave_i_charging > charge_rate) && ((*persistence) < UI_PERSISTENCE_MAX_LEVEL)) 
    ++(*persistence);
  else if ((*persistence) > UI_PERSISTENCE_MIN_LEVEL)
    --(*persistence);
  if ((*persistence) >= UI_PERSISTENCE_ON_LEVEL)
    GPIO_ResetBits(GPIOA, led_pin);
  else if ((*persistence) <= UI_PERSISTENCE_OFF_LEVEL)
    GPIO_SetBits(GPIOA, led_pin);
}

// This function handles displaying the charge rate
// Called by Handle UI

static void Display_Charge_Level(void) {
  static uint persistence2 = UI_PERSISTENCE_INIT;
  static uint persistence3 = UI_PERSISTENCE_INIT;
  static uint persistence4 = UI_PERSISTENCE_INIT;
  static uint persistence5 = UI_PERSISTENCE_INIT;

  TurnOff_UI();                                                                 // Prevent leakage onto SOC display
  if(!Is_PV_idle()){
  // if (Is_Charging()) {			                                        // If Charging, Compute Charge Display
 // if (Is_PV_Regulation_Active()) {
  if(Is_PV_CV())
    {
      GPIO_ResetBits(GPIOA, (LED1 | LED2 | LED3 | LED4));
      GPIO_SetBits(GPIOA, LED5);                                                // turn off the fifth LED
    } else {
      Update_Charge_Rate_Persistence(CHARGE_RATE_5, &persistence5, LED5);
      Update_Charge_Rate_Persistence(CHARGE_RATE_4, &persistence4, LED4);
      Update_Charge_Rate_Persistence(CHARGE_RATE_3, &persistence3, LED3);		
      Update_Charge_Rate_Persistence(CHARGE_RATE_2, &persistence2, LED2);
      GPIO_ResetBits(GPIOA, LED1);                                              // Level LED 1 can't be turned on   
    }
  } else { 						                        // When Not Charging, Charge Display is off

    GPIO_SetBits(GPIOA, (LED1 | LED2 | LED3 | LED4 | LED5));

    persistence2 = UI_PERSISTENCE_OFF_LEVEL-1;
    persistence3 = UI_PERSISTENCE_OFF_LEVEL-1;
    persistence4 = UI_PERSISTENCE_OFF_LEVEL-1;
    persistence5 = UI_PERSISTENCE_OFF_LEVEL-1;

  }
  _led_select_CHRG();
  _led_clear_FG();
}

// This function handles displaying the fuel level.
// Called by Handle UI
static void Display_Battery_Level(void) {
  TurnOff_UI();    // Prevent leakage onto ROC display
  if(!RTC_20S_Flag)
  {
    reflash_fuel_LED_bar();
#if 0
    GPIO_WriteBit(GPIOA, LED5, ((Get_Fuel_Level() > get_fuel_level5()/* LEVEL_5*/)?Bit_RESET:Bit_SET));
    GPIO_WriteBit(GPIOA, LED4, ((Get_Fuel_Level() > get_fuel_level4()/*()LEVEL_4*/)?Bit_RESET:Bit_SET));
    GPIO_WriteBit(GPIOA, LED3, ((Get_Fuel_Level() > get_fuel_level3()/*LEVEL_3*/)?Bit_RESET:Bit_SET));
    GPIO_WriteBit(GPIOA, LED2, ((Get_Fuel_Level() > get_fuel_level2()/*LEVEL_2*/)?Bit_RESET:Bit_SET));
    GPIO_WriteBit(GPIOA, LED1, ((Get_Fuel_Level() >= get_fuel_low()/*LEVEL_LOW*/)?Bit_RESET:Bit_SET));
    _led_select_FG();
#endif
  }
  _led_clear_CHRG();
  
  if (Is_Low_Fuel()) {
#ifndef DEBUG_PORT    
    _led_red_On();
#endif    
  } 
  else
  {
#ifndef DEBUG_PORT    
    _led_red_Off();
#endif    
  }
  if(Is_Empty_Fuel())
  {
      static u16 led_empty = 0;

      if(led_empty<10)
      {
#ifndef DEBUG_PORT        
          _led_red_On();
#endif          
      }
      else
      {
#ifndef DEBUG_PORT        
          _led_red_Off();
#endif          
      }
      ++led_empty;
      if(led_empty>100)
      {
          led_empty = 0;
      }
  }
}

GLP_bool Is_PV_idle(void)
{
  GLP_bool flag_pv_idle;
  static uchar delay_pv_idle = 0;
  
  flag_pv_idle = GLP_TRUE;
  if(pv_state >= PV_0V_Charge)
  {
      delay_pv_idle = 30;
  }
  if(delay_pv_idle != 0)
  {
      --delay_pv_idle;
      flag_pv_idle = GLP_FALSE;
  }
/*  
  else
  {
      Send_Message("\n**");
  }
*/
  return flag_pv_idle;

}


void reflash_fuel_LED_bar(void)
{
    if(button_req_inactive)
    { 
        _led_clear_FG();
        _led_red_Off();
    }
    else
    {
      GPIO_WriteBit(GPIOA, LED5, ((Get_Fuel_Level() > get_fuel_level5()/* LEVEL_5*/)?Bit_RESET:Bit_SET));
      GPIO_WriteBit(GPIOA, LED4, ((Get_Fuel_Level() > get_fuel_level4()/*()LEVEL_4*/)?Bit_RESET:Bit_SET));
      GPIO_WriteBit(GPIOA, LED3, ((Get_Fuel_Level() > get_fuel_level3()/*LEVEL_3*/)?Bit_RESET:Bit_SET));
      GPIO_WriteBit(GPIOA, LED2, ((Get_Fuel_Level() > get_fuel_level2()/*LEVEL_2*/)?Bit_RESET:Bit_SET));
      GPIO_WriteBit(GPIOA, LED1, ((Get_Fuel_Level() >= get_fuel_low()/*LEVEL_LOW*/)?Bit_RESET:Bit_SET));
      _led_select_FG();  
      if(Is_Low_Fuel())
      {
        _led_red_On();
      }
      else
      {
        _led_red_Off();
      }
    }
}
// EOF
