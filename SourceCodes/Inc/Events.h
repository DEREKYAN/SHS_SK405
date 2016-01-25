#ifndef __EVENTS_H__
#define __EVENTS_H__
#include "Config.h"
#include "main.h"

typedef union
{
  struct
  {

    uint32_t flag_any_fault:                    1;              
    uint32_t fault_occur:                       1;   
    uint32_t flag_fuel_computed_low:            1;             
    uint32_t flag_slope_computed_low:           1;             
    uint32_t flag_voltage_trigger_low:          1;                
    uint32_t flag_empty_battery_trigger:        1;    
    uint32_t flag_CV_charging:                  1;  
    uint32_t flag_full_battery:                 1;  

  } data_bit;                                   
  
  uint32_t data_int32 ;                           
 
} FALG_14HOURS_TYPE;

enum RTC_CALIBRATION_TYPE
{
    RTC_CALIBRATION_PROHIBIT, 
    RTC_CALIBRATION_RADY,
    RTC_CALIBRATION_GOING,
    RTC_CALIBRATION_OVER,
};

extern uint RTC_second_elapsed;
extern uint32_t HSI_ms_counter, LSI_second_counter; 
extern enum RTC_CALIBRATION_TYPE RTC_calibration_step;    

extern volatile uchar system_state;
extern volatile GLP_bool RTC_second_flag;
extern FALG_14HOURS_TYPE flag_14_handler_status;
extern bool button_req_inactive;
extern uint RTC_Second;
extern uchar time_idle_counter;

void Check_Button(void);
void handler_user_set_flag(void);
void inc_usi_counter( u16* counter);
void inc_uint_counter(uint* counter,uint t);

bool get_RTC_second_flag(void);
void clear_RTC_second_flag(void);
void set_RTC_second_flag(void);
bool Is_stop(void);
void add_system_idle_time(void);
uchar get_System_State(void);
bool get_button_req_inactive(void);
void clear_button_req_inactive(void);
void event_second_long_key(void);
void clear_RTC_timer_counter(void);
void payg_second_elapsed_handle(void);

#define CONST_LOGNG_BUTTON_PRESSED      150            // 3 second base on 20mS
#define UART_SEND_MASK						0x0040
#define EMPTY_BATT_LIGHT_ON_TIME	                        500		// 10s = 500x 20ms (LIGHT_EVENTS_TIME) SKJ project 

#define HIBERNATING							0		// when ports are inactive - only button push and PV charge to wake
#define SLEEPING							1		// when ports are active and we need short and activity detect
#define ACTIVE								2		// when battery is charging or discharging
#define CONST_14HOURS                   (14*60*60)

// The following ADC value is calculated with divider, high side pull-up resister and low side key-down resister 
#define ADC_POWER               4095*0/(0+22)
#define ADC_SW11                4095*1/(1+22)
#define ADC_SW12                4095*2/(2+22)
#define ADC_SW13                4095*3/(3+22)
#define ADC_SW14                4095*4.02/(4.02+22)
#define ADC_SW15                4095*5.1/(5.1+22)
#define ADC_MAX                 4095*10/(10+22)

#define ADC_SW11_MAX            (s16)(ADC_SW11*1.1)
#define ADC_SW11_MIN            (s16)(ADC_SW11*0.9)

#define ADC_SW12_MAX            (s16)(ADC_SW12*1.1)
#define ADC_SW12_MIN            (s16)(ADC_SW12*0.9)

#define ADC_SW13_MAX            (s16)(ADC_SW13*1.1)
#define ADC_SW13_MIN            (s16)(ADC_SW13*0.9)

#define ADC_SW14_MAX            (s16)(ADC_SW14*1.1)
#define ADC_SW14_MIN            (s16)(ADC_SW14*0.9)

#define ADC_SW15_MAX            (s16)(ADC_SW15*1.1)
#define ADC_SW15_MIN            (s16)(ADC_SW15*0.9)

// Threshold ADC value of different button down   
#define POWER_SW11              (s16)((ADC_POWER+ADC_SW11)/2)
#define SW11_SW12               (s16)((ADC_SW11 + ADC_SW12)/2)
#define SW12_SW13               (s16)((ADC_SW12 + ADC_SW13)/2)
#define SW13_SW14               (s16)((ADC_SW13 + ADC_SW14)/2)
#define SW14_SW15               (s16)((ADC_SW14 + ADC_SW15)/2)
#define SW15_MAX                (s16)((ADC_SW15 + ADC_MAX)/2)

// Flag test functions - in conditional statement must test these first to clear flag
bool Test_Timing_Flag(uint mask);
bool Is_Low_Voltage(void);
bool Is_Empty_Voltage(void);
void Exit_Active_Command(void);
bool Is_Button_Active(void);
void Set_Button_Active_Short(void);
void Set_Button_Active_Long(void);
void Clear_Button_Active(void);
uchar Get_System_State(void);
void Set_System_State(uchar new_system_state);
uint get_system_idle_time(void);
bool Is_Button_Idle(void);
void set_manu_turn_off_counter(u16 data);
void clear_system_idle_time(void);
GLP_bool inc_event_counter( u16* counter);
void configure_manmul_off(void);
#endif
// EOF
