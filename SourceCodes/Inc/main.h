/**
  ******************************************************************************
  * @file    Project/STM32F0xx_StdPeriph_Templates/main.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-May-2012
  * @brief   Header for main.c module
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"
   
#define CONST_1S                        1000    // const 1 second base on 1 millisecond
#define CONST_20MS                      20      // const 20 millisecond base on 1 millisecond
#define EVENT_BUTTON_20MS_1             1       // the following const function is the same: once per 20 millisecond
#define EVENT_UI_20MS_2                 2       // The different event in different 1 millisecond
#define EVENT_MOBILE_20MS_3             3
#define EVENT_PV_20MS_4                 4
#define EVENT_PAYG_20MS_5               5

#define EVENT_RTC_20MS_6                6        
#define EVENT_UI_20MS_7                 7
#define EVENT_LGIHGT_20MS_8             8
#define EVENT_PAYG_SECOND_20MS_9        9
#define EVENT_UI_20MS_12                12
#define EVENT_PV_20MS_14                14
#define EVENT_PAYG_20MS_15              15
    
#define EVENT_UI_20MS_17                17
#define EVENT_LIGHT_20MS_18             18

#define APPLICATION_ADDRESS     (uint32_t)0x08000C00  // Application program start from page 4,  Bootoader use Page 0 ~ Page 3 

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

// The following code lines are defined interrupter entery according to differet compiler

#if   (defined ( __CC_ARM ))
  __IO uint32_t VectorTable[48] __attribute__((at(0x20000000)));
#elif (defined (__ICCARM__))
#pragma location = 0x20000000
  __no_init __IO uint32_t VectorTable[48];
#elif defined   (  __GNUC__  )
  __IO uint32_t VectorTable[48] __attribute__((section(".RAMVectorTable")));
#elif defined ( __TASKING__ )
  __IO uint32_t VectorTable[48] __at(0x20000000);
#endif

typedef enum {GLP_FALSE = 0, GLP_TRUE = !GLP_FALSE} GLP_bool;  
  
extern GLP_bool RTC_20S_Flag;
void set_delay_sleep_ms(uint16_t t);  
GLP_bool get_delay_sleep_status(void);
  
#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
// EOF
