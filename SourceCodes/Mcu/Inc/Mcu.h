#ifndef MCU_H
#define MCU_H
#include "types.h"
#include "main.h"

#define MAX_4_DECIMAL                   9999u

//LED

#define LED1                GPIO_Pin_12
#define LED2                GPIO_Pin_11
#define LED3                GPIO_Pin_10
#define LED4                GPIO_Pin_9
#define LED5                GPIO_Pin_8
#define _led_select_CHRG()	GPIO_SetBits(GPIOB, GPIO_Pin_4)
#define _led_clear_CHRG()		GPIO_ResetBits(GPIOB, GPIO_Pin_4)
#define _led_select_FG()		GPIO_SetBits(GPIOB, GPIO_Pin_3)
#define _led_clear_FG()			GPIO_ResetBits(GPIOB, GPIO_Pin_3)
//#define _led_red_On()       GPIO_ResetBits(GPIOB, GPIO_Pin_5)       // pin is inverted
//#define _led_red_Off()      GPIO_SetBits(GPIOB, GPIO_Pin_5)         // pin is inverted
//#define _ledRed             GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_5)
#define _led_red_On()       GPIO_ResetBits(GPIOA, GPIO_Pin_14)       // pin is inverted
#define _led_red_Off()      GPIO_SetBits(GPIOA, GPIO_Pin_14)         // pin is inverted
#define _ledRed             GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_14)

#define OP_Charging()             GPIO_ResetBits(GPIOA, GPIO_Pin_6)
#define OP_Discharging()          GPIO_SetBits(GPIOA, GPIO_Pin_6)


// 5V
#define _Port_5V_On()			  GPIO_SetBits(GPIOA, GPIO_Pin_15)
#define _Port_5V_Off()			GPIO_ResetBits(GPIOA, GPIO_Pin_15)

// PV
#define SetChrgCtrlPin()	  GPIO_SetBits(GPIOB, GPIO_Pin_6)
#define ClrChrgCtrlPin()		GPIO_ResetBits(GPIOB, GPIO_Pin_6)
#define SetChrg0vPin()			GPIO_SetBits(GPIOA, GPIO_Pin_5)
#define ClrChrg0vPin()			GPIO_ResetBits(GPIOA, GPIO_Pin_5)

#define GetFMButton()       GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)
#define EnableFM()          GPIO_SetBits(GPIOB, GPIO_Pin_7)
#define DisableFM()         GPIO_ResetBits(GPIOB, GPIO_Pin_7)

//#define EnablePV()          GPIO_SetBits(GPIOA, PORTA_PVEN)
//#define DisablePV()         GPIO_ResetBits(GPIOA, PORTA_PVEN)

#define Get_PAYG_RX()       GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_1)   

#define ADC_CH_MAX          4

// Device State
#define HIBERNATING		      0		// when ports are inactive - only button push and PV charge to wake
#define SLEEPING			      1		// when ports are active and we need short and activity detect
#define ACTIVE				      2		// when battery is charging or discharging

#define BUTTON_DEBOUNCE_TIME  50		// 50 = 50ms/1ms
#define BUTTON_HOLD_TIME		  2000u	        // 2000*1ms

#define TRIM_FLASHE           0
#define TRIM_TRUE             1
// RTC interrupter configuration mode 
#define MODE_40MS             1
#define MODE_1SECOND          2
#define MODE_2SECOND          3
#define MODE_20SECOND         4

#define PORTA_12V_H_8V5_L   GPIO_Pin_1    

//#define PORTA_UCEN          GPIO_Pin_5
#define PORTA_0V_CHARGE         GPIO_Pin_5
#define PORTA_UCOUT_PVEN         GPIO_Pin_6
#define PORTA_LED5          GPIO_Pin_8
#define PORTA_LED4          GPIO_Pin_9
#define PORTA_LED3          GPIO_Pin_10
#define PORTA_LED2          GPIO_Pin_11
#define PORTA_LED1          GPIO_Pin_12
#define PORTB_OMPEN         GPIO_Pin_5
#define PORTA_5VEN          GPIO_Pin_15   

#define PORTB_LEDCOM2       GPIO_Pin_3
#define PORTB_LEDCOM1       GPIO_Pin_4
//#define PORTA_PVEN          GPIO_Pin_5    
#define PORTA_REDLED        GPIO_Pin_14  

#define PORTB_12VEN         GPIO_Pin_7
#define PORTB_CHARG         GPIO_Pin_6

#define PORTF_PAYGOUT       GPIO_Pin_0
#define PORTF_PAYGIN        GPIO_Pin_1
#define PORTA_KEYIN         GPIO_Pin_4

#define PORTA_AN_UCADC      GPIO_Pin_0
#define PORTA_AN_PVFB       GPIO_Pin_7

#define PORTB_AN_5VFB       GPIO_Pin_0
#define PORTB_AN_12FB       GPIO_Pin_1

//#define PORTB_UC_PWM        GPIO_Pin_6

#define CHANNEL_UCADC       ADC_Channel_0
#define CHANNEL_KEY         ADC_Channel_4
#define CHANNEL_TRIM        ADC_Channel_5
#define CHANNEL_PBFB        ADC_Channel_7
#define CAANNEL_5V          ADC_Channel_8
#define CAANNEL_12V          ADC_Channel_9

#define TIME_CALIBRATION_STANDBY        60*60
#define TIME_INIT_STANDBY               60*59
#define MAX_CALIBRATION_TIMES            (24*7)

extern GLP_bool LSI_Calibartion_Standby;
extern uint32_t time_counter_calibration;
extern uint8_t calibration_number;

extern volatile bool    Flag_1MS;
extern __IO uchar Flag_RTC_TRIM;
extern void McuInit(void);
extern void McuDelayMs(DWORD dwMs);
extern WORD McuGetAdcValue(DWORD dwChannel);
u16 get_reboot_counter(void);
//uchar get_trim_status(void);
void TrimAdcInit(void);

void Init_Enter_sleep(void);
void Init_Enter_stop(void);
void init_exit_stop(void);
void RTC_Config_Minute(void);
void McuPvInit(void);
void ADC1_Config_Channel(uint32_t ADC_Channel);
void clr_RTC_time(void);
void IoInit(void);
void delay(uint t);
void config_RTC_Clock(void);
void handle_rtc_calibration(void);
void RTC_Config_for_SK405(uchar mode);
void RTC_20S_Init(void);
#endif
