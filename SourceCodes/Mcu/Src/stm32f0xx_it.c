/**
  ******************************************************************************
  * @file    Project/STM32F0xx_StdPeriph_Templates/stm32f0xx_it.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-May-2012
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_it.h"
#include "main.h"
#include "record.h"    

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */

#include "Mobile.h"
#include "Mcu.h"
#include "UART.h"
#include "Events.h"
#include "PV.h"
#include "ADC.h"
#include "UI.h"

void RTC_IRQHandler(void)
{

  clear_RTC_timer_counter();
  if(RTC_second_flag)
  {  
    if(RTC_calibration_step == RTC_CALIBRATION_RADY)
    { 
      RTC_calibration_step = RTC_CALIBRATION_GOING;
    } 
    else if(RTC_calibration_step == RTC_CALIBRATION_GOING )
    {
      LSI_second_counter += RTC_Second;
      
      if(Flag_RTC_TRIM <5)
      {
        if(LSI_second_counter >= 20)
        {
            ++Flag_RTC_TRIM;
            RTC_calibration_step = RTC_CALIBRATION_OVER;
        }       
      }
      else
      {
        if(LSI_second_counter >= 60)
        {
            RTC_calibration_step = RTC_CALIBRATION_OVER;
        }
      }
    }
  }
      
  RTC_ClearITPendingBit(RTC_IT_ALRA);
  EXTI_ClearITPendingBit(EXTI_Line17);   
 
}    

void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
/*
void SysTick_Handler(void)
{
  Flag1MS_SysStick = TRUE;
 // extern void Isr1msTimeBaseRoutine(void);
 // Isr1msTimeBaseRoutine();
}
*/
/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
