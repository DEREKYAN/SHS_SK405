#include "watchdog.h"
#include "stm32f0xx.h"

#define KR_KEY_RELOAD    ((uint16_t)0xAAAA)
#define KR_KEY_ENABLE    ((uint16_t)0xCCCC)


/** Start the watchdog timer
 */
void watchdog_start(void)
// Start the watchdog timer
{

	IWDG->KR  = IWDG_WriteAccess_Enable;
	IWDG->PR  = IWDG_Prescaler_256;
	IWDG->RLR = 0x0fff;
	IWDG->KR  = KR_KEY_ENABLE;
}


/** Reload the watchdog timer
 *
 *  So that it does not expire and does not reset the system
 */
void watchdog_reload(void)
{
	IWDG->KR = KR_KEY_RELOAD;
}
