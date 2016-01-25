#include "mcu.h"
#include "Mobile.h"
#include "UI.h"
#include "ADC.h"
#include "Fuel.h"
#include "nv.h"
#include "Events.h"
#include "main.h"
#include "record.h"
#include "ADC.h"
#include "Light.h"
#include <string.h>

__IO uint32_t LsiFreq =40000;
__IO uint32_t CaptureNumber = 0, PeriodValue = 0;
__IO uint32_t IC1ReadValue1 = 0, IC1ReadValue2 =0;
__IO uchar Flag_RTC_TRIM = 0;
volatile bool    Flag_1MS;
volatile DWORD gdw1msCounter= 0;    

static uint32_t Register_backup = 399;
static GLP_bool Flag_Startup = GLP_TRUE;

GLP_bool flag_PowerOn = GLP_TRUE;
GLP_bool LSI_Calibartion_Standby = GLP_FALSE;
uint32_t time_counter_calibration =  TIME_INIT_STANDBY;
uint8_t calibration_number = 0;
// use for 1ms counter
void Isr1msTimeBaseRoutine(void);
extern void payg_interrupts_cable_handle_rx_edge(void); 
#ifdef EN_PROTECTION
static void Flash_Protect(void);
void Flash_Protect(void)
{
   if(SET != FLASH_OB_GetRDP())
   {
      FLASH_Unlock();  	//
      FLASH_OB_Unlock();
      FLASH_OB_RDPConfig(OB_RDP_Level_1);
      FLASH_OB_Lock();
      FLASH_Lock();
      FLASH_OB_Launch();  //
   }
}
#endif 

void handle_rtc_calibration(void)
{
    switch(RTC_calibration_step)
    {
      case RTC_CALIBRATION_RADY:
      HSI_ms_counter = 0; 
      LSI_second_counter = 0; 
      break;
      
      case RTC_CALIBRATION_GOING:
        
      break;      
      
      case RTC_CALIBRATION_OVER:
#ifdef DEBUG_LSI_CALIBRATION      
      Send_Message("\n!\n");
  while(get_UART_Active());                 // Waiting until uart is idle.
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
#endif           
      if(HSI_ms_counter !=0)
      {
        LsiFreq = LsiFreq * (LSI_second_counter*1000) /HSI_ms_counter;
        if((LsiFreq > 30000) && (LsiFreq<50000)) 
        {
        
          LSI_Calibartion_Standby = GLP_FALSE;
          time_counter_calibration = 0;
          if(system_state != ACTIVE)
          {
              ++calibration_number;
          }
          else
          {
            calibration_number = 0;
          }     
        }
        else
        {
            LsiFreq = 40000;
        }
        config_RTC_Clock();                   // Delete RTC configure for test 2016 0125
//        Send_Message("\nLSI:");         // Add for test 
//        Send_Number(LsiFreq);
      }
      RTC_calibration_step = RTC_CALIBRATION_PROHIBIT;
      break;
      
      case RTC_CALIBRATION_PROHIBIT:
      default:
      RTC_calibration_step = RTC_CALIBRATION_RADY;
      break;     
    }
#ifdef DEBUG_LSI_CALIBRATION   
    if(system_state == HIBERNATING)
    {
      Send_Message("\n&:");
      Send_Number();
  while(get_UART_Active(RTC_calibration_step));                 // Waiting until uart is idle.
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
    }
#endif        
}

// Angaza interrupt wake up MCU
void EXTI0_1_IRQHandler(void) {
  if(EXTI_GetFlagStatus(EXTI_Line1))
  {
      EXTI_ClearFlag(EXTI_Line1);
      payg_interrupts_cable_handle_rx_edge();   
      system_state = ACTIVE;
      set_delay_sleep_ms(1000);
  }
}
//  sysTick interrupt once very 1 millisecond 
void SysTick_Handler(void)
{
  Flag_1MS= TRUE;
  if(RTC_calibration_step == RTC_CALIBRATION_GOING )
    ++HSI_ms_counter;  
}

void config_RTC_Clock(void)
{

  RTC_InitTypeDef   RTC_InitStructure;  

//  if((LsiFreq > 30000) && (LsiFreq<50000)) 
 
    RTC_InitStructure.RTC_AsynchPrediv = 99;
    RTC_InitStructure.RTC_SynchPrediv	=  ((LsiFreq+50)/100) - 1;
    RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
    RTC_Init(&RTC_InitStructure);

 #ifdef DEBUG_LSI_CALIBRATION
  Send_Message("\nLSI:");
  Send_Number(LsiFreq);
  Send_Message("\n");
  while(get_UART_Active());                 // Waiting until uart is idle.
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
#endif
}

void clr_RTC_time(void)
{
  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

   if (RTC_EnterInitMode() != ERROR)
  {
    /* Set the RTC_TR register */
    RTC->TR = (uint32_t)0;
    /* Exit Initialization mode */
    RTC_ExitInitMode();
    /* If  RTC_CR_BYPSHAD bit = 0, wait for synchro else this check is not needed */
    if ((RTC->CR & RTC_CR_BYPSHAD) == RESET)
    {
      RTC_WaitForSynchro();
    }
  }
  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;

}
/////////////////////////////////

// Configure system clock 8Mhz
void McuTimeBaseInit(){
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 8000);
}

// Initialize ADC port
void McuAdcInit(void){
  ADC_InitTypeDef     ADC_InitStructure;
  GPIO_InitTypeDef    GPIO_InitStructure;
  
//  RCC_AHBPeriphClockCmd((RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB) , ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  GPIO_InitStructure.GPIO_Pin = PORTA_AN_UCADC | PORTA_AN_PVFB;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = PORTB_AN_5VFB | PORTB_AN_12FB;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

//  ADC_DeInit(ADC1);
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, ENABLE);
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, DISABLE);
 
  ADC_StructInit(&ADC_InitStructure);
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
  ADC_Init(ADC1, &ADC_InitStructure); 

  ADC1_Config_Channel(CHANNEL_UCADC);
  ADC1_Config_Channel(CHANNEL_KEY);
  ADC1_Config_Channel(CHANNEL_PBFB);
  ADC1_Config_Channel(CAANNEL_5V);
  ADC1_Config_Channel(CAANNEL_12V);
  ADC1_Config_Channel(ADC_Channel_17);
  ADC_GetCalibrationFactor(ADC1);
  ADC_Cmd(ADC1, ENABLE);
  ADC->CCR |= ADC_CCR_VREFEN;
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY));
}

void ADC1_Config_Channel(uint32_t ADC_Channel)
{
    ADC_ChannelConfig(ADC1, ADC_Channel , ADC_SampleTime_71_5Cycles);   // Derek check 5.1uS adc peroid
}

// Initialize port for TRIM because extern reference voltage used PV control port
void TrimAdcInit(void)
{
  //ADC_InitTypeDef     ADC_InitStructure;
  GPIO_InitTypeDef    GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = ADC_Channel_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  ADC_Cmd(ADC1, DISABLE);  
  ADC1_Config_Channel(ADC_Channel_5);
  ADC_GetCalibrationFactor(ADC1);
  ADC_Cmd(ADC1, ENABLE);
  ADC->CCR |= ADC_CCR_VREFEN;
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY));  
}

void McuUartInit(DWORD dwBr){
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  USART_DeInit(USART1);
  //CLOCK
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  //GPIO
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  //USART
  USART_InitStructure.USART_BaudRate = dwBr;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART1, &USART_InitStructure);
  //NVIC
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  //
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  USART_ITConfig(USART1, USART_IT_TXE, DISABLE);                               // this gets enabled when a message is transmitted
  USART_Cmd(USART1, ENABLE);
}

void IoInit(void)
{

  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  
  RCC_AHBPeriphClockCmd((RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB), ENABLE);  
 
  GPIO_InitStructure.GPIO_Pin = PORTA_0V_CHARGE | PORTA_UCOUT_PVEN | PORTA_LED5 | PORTA_LED4 | PORTA_LED3 | PORTA_LED2 | PORTA_LED1 | PORTA_5VEN | PORTA_12V_H_8V5_L;
#ifndef DEBUG_PORT 
    GPIO_InitStructure.GPIO_Pin |= PORTA_REDLED;
#endif   
    
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  _Port_5V_Off();    
  GPIO_ResetBits(GPIOA,PORTA_UCOUT_PVEN);
    
  GPIO_InitStructure.GPIO_Pin = PORTB_LEDCOM2 | PORTB_LEDCOM1 | PORTB_OMPEN | PORTB_12VEN | PORTB_CHARG /*No MPPT*/;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  TurnOn_UI();

  GPIO_SetBits(GPIOB, PORTB_OMPEN);
  Light_Init();
  
#ifdef ANGAZA
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE); 
  // configure GPO_PAYG
  GPIO_InitStructure.GPIO_Pin = PORTF_PAYGOUT;
  GPIO_Init(GPIOF, &GPIO_InitStructure);
  GPIO_ResetBits(GPIOF, GPIO_Pin_0);                    // output low
#endif

  
#ifdef ANGAZA
  //GPIO
  GPIO_InitStructure.GPIO_Pin = PORTF_PAYGIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_Init(GPIOF, &GPIO_InitStructure);
  //EXTI
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);                        // must be enabled for read and write of registers
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource1);

  EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;                // Triggered by both edges 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  //NVIC
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);  
#else
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE); 
  GPIO_InitStructure.GPIO_Pin = PORTF_PAYGOUT | PORTF_PAYGIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN; 
  GPIO_Init(GPIOF, &GPIO_InitStructure);
#endif  
  
  GPIO_InitStructure.GPIO_Pin = PORTA_KEYIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  //EXTI
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);                        // must be enabled for read and write of registers
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource4);
//  EXTI_StructInit(&EXTI_InitStructure);
  EXTI_InitStructure.EXTI_Line = EXTI_Line4;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  //NVIC
  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_15_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);   
  
  McuAdcInit();

  
  Initial_ADC_Offset();
    

  GPIO_SetBits(GPIOB, PORTB_12VEN);
  _Port_5V_On();
  GPIO_ResetBits(GPIOB, PORTB_CHARG);

}




// Initialize all 
void McuInit(void){
#ifdef EN_PROTECTION
  Flash_Protect();
#endif
  
  IoInit();

  McuUartInit(9600);
  SysTick_Config(SystemCoreClock / 1000);

  init_fuel_const();
  //handler_reboot_counter();
  Clear_Fuel_Gage_And_Voltage();
  __enable_interrupt();           // Eanble interrupt 
  RTC_Config_for_SK405(MODE_40MS);
  
  configure_manmul_off();                                             // Delete for test 20160121
  memset(&adc_sum.sum_v_battery, 0, sizeof(struct ADC_SUM_STRUCT));
  memset(&adc_ave.ave_i_battery, 0, sizeof(struct ADC_AVE_AVERAGE));
  adc_ave.ave_v_battery = 3300;
}
// Initialize for sleep mode 
void Init_Enter_sleep(void)
{
#ifndef DEBUG_PORT  
//    _led_red_Off();
#endif
    GPIO_ResetBits(GPIOB, PORTB_OMPEN);
    if(system_state == HIBERNATING)
    {  
      GPIO_ResetBits(GPIOB, GPIO_Pin_3 | GPIO_Pin_4);      // Clear LED BAR
       _led_red_Off();
    }
    else
    {
      GPIO_ResetBits(GPIOB, GPIO_Pin_4);      // Clear LED BAR   
      reflash_fuel_LED_bar();
    }
    SysTick->CTRL  &= ~SysTick_CTRL_ENABLE_Msk;                    /* Enable SysTick IRQ and SysTick Timer */

   {                         // Configure UART TX pin as general input PA2 pin
      GPIO_InitTypeDef GPIO_InitStructure;


      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6;      
      if(RTC_20S_Flag)
      GPIO_InitStructure.GPIO_Pin |= (GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12);         
         
      if(adc_ave.ave_v_battery>=2500)      
      GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_5; 
      
      

#ifndef DEBUG_PORT
    GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_13;
      
#endif     
         
      if(RTC_20S_Flag)
      {
          GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_15;
      }
      
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;   
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
      GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;         
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
      GPIO_Init(GPIOA, &GPIO_InitStructure);      
          
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6; 
      if(RTC_20S_Flag)   
      {
        GPIO_InitStructure.GPIO_Pin |=  GPIO_Pin_7 | GPIO_Pin_3 ;
      }
      GPIO_Init(GPIOB, &GPIO_InitStructure); 
     
   }
  
    if(adc_ave.ave_v_battery>=2500)
    {
        ClrChrg0vPin(); 
    }
    else
    {
        SetChrg0vPin();
    }
    ADC->CCR &= ~ADC_CCR_VREFEN;                       // disable internal ADC voltage     
    ADC_Cmd(ADC1, DISABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, DISABLE);
}

// Initialize for exit stop 
void init_exit_stop(void)
{
  {                        // set back PA2 as UART TX ports 
    
    GPIO_InitTypeDef GPIO_InitStructure;
  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_15;

#ifndef DEBUG_PORT
    GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_14;      
#endif         
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;

    GPIO_Init(GPIOA, &GPIO_InitStructure);  
   
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;

    GPIO_Init(GPIOB, &GPIO_InitStructure);

  }

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  ADC->CCR |= ADC_CCR_VREFEN;
  ADC_Cmd(ADC1, ENABLE);
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY));
}


void delay(uint t)
{
    while(t != 0)
      --t;
}
       

/**
  * @brief  Configure the RTC peripheral by selecting the clock source.
  * @param  None
  * @retval None
  */
void RTC_Config_for_SK405(uchar mode)
{
  RTC_InitTypeDef   RTC_InitStructure;
  RTC_TimeTypeDef RTC_TimeStructure;
  NVIC_InitTypeDef NVIC_InitStructure; 
  EXTI_InitTypeDef EXTI_InitStructure;
  RTC_AlarmTypeDef RTC_AlarmStructure;
  /* Enable the PWR clock */
/*
  if(Flag_Startup)
  {
    Flag_Startup = GLP_FALSE;

  }
  else
  {
      Register_backup = RTC->ALRMASSR & 0x7FFF;
  }
*/
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
  /* Allow access to RTC */
  PWR_BackupAccessCmd(ENABLE);

  /* Reset RTC Domain */
  RCC_BackupResetCmd(ENABLE);
  RCC_BackupResetCmd(DISABLE);

/* LSI used as RTC source clock */
/* The RTC Clock may varies due to LSI frequency dispersion. */   
  /* Enable the LSI OSC */ 
  RCC_LSICmd(ENABLE);

  /* Wait till LSI is ready */  
  while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
  {
  }

  /* Select the RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
   
  /* Enable the RTC Clock */
  RCC_RTCCLKCmd(ENABLE);

  /* Wait for RTC APB registers synchronisation */
  RTC_WaitForSynchro();

  /* Calendar Configuration */
  RTC_InitStructure.RTC_AsynchPrediv = 99;
  RTC_InitStructure.RTC_SynchPrediv	=  ((LsiFreq+50)/100) - 1;
  RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
  RTC_Init(&RTC_InitStructure);  

  /* EXTI configuration *******************************************************/
  EXTI_ClearITPendingBit(EXTI_Line17);
  EXTI_InitStructure.EXTI_Line = EXTI_Line17;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Enable the RTC Wakeup Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

    
    /* Set the alarm X+5s */
  switch(mode)
  {
    case MODE_40MS:
    RTC_AlarmStructure.RTC_AlarmMask = RTC_AlarmMask_All;
    RTC_SetAlarm(RTC_Format_BCD, RTC_Alarm_A, &RTC_AlarmStructure);

  // 20ms中断一次, 1s中断50次
 //   RTC_AlarmSubSecondConfig(RTC_Alarm_A, Register_backup, RTC_AlarmSubSecondMask_SS14_3);
    
    RTC_AlarmSubSecondConfig(RTC_Alarm_A, ((LsiFreq+50)/100-1), RTC_AlarmSubSecondMask_SS14_3);
    
    
    break;
  
    case MODE_20SECOND:
 
    RTC_AlarmStructure.RTC_AlarmTime.RTC_H12     = RTC_H12_AM;
    RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours   = 0x00;
    RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes = 0x00;
    RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds = 0x20;
    RTC_AlarmStructure.RTC_AlarmDateWeekDay = 0x31;
    RTC_AlarmStructure.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
    RTC_AlarmStructure.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay;
    RTC_SetAlarm(RTC_Format_BCD, RTC_Alarm_A, &RTC_AlarmStructure);
    
    RTC_AlarmSubSecondConfig(RTC_Alarm_A, ((LsiFreq+50)/100-1), RTC_AlarmSubSecondMask_None);

//    RTC_AlarmSubSecondConfig(RTC_Alarm_A, Register_backup, RTC_AlarmSubSecondMask_None);

    break;
  }

  RTC_ITConfig(RTC_IT_ALRA, ENABLE);
    
  /* Enable the alarm */
  RTC_AlarmCmd(RTC_Alarm_A, ENABLE);

  /* Set the time to 00h 00mn 00s AM */
  RTC_TimeStructure.RTC_H12     = RTC_H12_AM;
  RTC_TimeStructure.RTC_Hours   = 0x00;
  RTC_TimeStructure.RTC_Minutes = 0x00;
  RTC_TimeStructure.RTC_Seconds = 0x00;  
  RTC_SetTime(RTC_Format_BCD, &RTC_TimeStructure);
}




           