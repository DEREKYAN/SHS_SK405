#include <stddef.h>
#include <stdbool.h>
#include "stm32f0xx.h"

#include "prod_timcmp.h"
#include "angaza.h"

void mutual_excl_end(uint32_t prev_state);
uint32_t mutual_excl_start(void);

static bool timer_is_running = false;

/** Initialize the high-precision timer
 */
static void _timcmp_init(void)
{
#ifdef NO_MANUAL_SPACE_OPTS
	TIM_TimeBaseInitTypeDef tim16_init;
#endif
    
	// Setup Tim16 clocks
#ifdef NO_MANUAL_SPACE_OPTS
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM16, ENABLE);
#else
    RCC->APB2ENR |= RCC_APB2Periph_TIM16;
#endif
    
#ifdef NO_MANUAL_SPACE_OPTS
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM16, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM16, DISABLE);
#else
    RCC->APB2RSTR |= RCC_APB2Periph_TIM16;
    RCC->APB2RSTR &= ~RCC_APB2Periph_TIM16;
#endif

#ifdef NO_MANUAL_SPACE_OPTS
	TIM_TimeBaseStructInit(&tim16_init);

    tim16_init.TIM_Prescaler = SystemCoreClock / 1000000;  // for 1us resolution

    tim16_init.TIM_CounterMode       = TIM_CounterMode_Up;
	tim16_init.TIM_Period            = 0;
	tim16_init.TIM_ClockDivision     = TIM_CKD_DIV1;
	tim16_init.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM16, &tim16_init);
#else
	TIM16->CR1 = (TIM16->CR1 & (uint16_t)(~((uint16_t)TIM_CR1_CKD))) | (uint32_t)TIM_CKD_DIV1;

	/* Set the Autoreload value */
	TIM16->ARR = 0;

    TIM16->PSC = SystemCoreClock / 1000000;  // for 1us resolution
    
    /* Set the Repetition Counter value */
    TIM16->RCR = 0;
#endif

#ifdef NO_MANUAL_SPACE_OPTS
	TIM_UpdateRequestConfig(TIM16, TIM_UpdateSource_Regular);
#else
    TIM16->CR1 |= TIM_CR1_URS;
#endif

#ifdef NO_MANUAL_SPACE_OPTS
	TIM_ClearITPendingBit(TIM16, TIM_IT_Update);
#else
    TIM16->SR = (uint16_t)~TIM_IT_Update;
#endif

#ifdef NO_MANUAL_SPACE_OPTS
	TIM_ITConfig(TIM16, TIM_IT_Update, ENABLE);
#else
    TIM16->DIER |= TIM_IT_Update;
#endif

	NVIC_SetPriority(TIM16_IRQn, 15);
	NVIC_EnableIRQ(TIM16_IRQn);

	timer_is_running = true;
}


/** Start the high-precision timer.
 *
 * The timer measures elapsed time starting when this function is called. Timer
 * precision and accuracy must be 5 microseconds or better over the supported
 * duration. The timer invokes the prod_timcmp_handle_elapsed() callback after
 * the specified duration has elapsed. The timer must stop naturally after the
 * duration elapses and the callback is invoked.
 *
 * The prod_timcmp_get_microseconds_elapsed() routine may be used to read the
 * current elapsed time while the timer is running.
 *
 * The timer need not support durations larger than 8000 us.
 *
 * Valid status codes:
 *
 * - PROD_TIMCMP_ERROR_NONE
 * - PROD_TIMCMP_ERROR_DURATION_UNSUPPORTED
 *
 * \warning May be called at interrupt time.
 * \param duration_us duration in microseconds
 * \return a valid status code
 */
enum prod_timcmp_error prod_timcmp_start(uint16_t duration_us)
{
#ifdef NO_MANUAL_SPACE_OPTS
	TIM_TimeBaseInitTypeDef tim16_init;
#endif
    
	uint32_t                mutual_excl_value;
	mutual_excl_value = mutual_excl_start();

	if (timer_is_running)
	{
		// Disable the timer
#ifdef NO_MANUAL_SPACE_OPTS
		TIM_Cmd(TIM16, DISABLE);
#else
        TIM16->CR1 &= (uint16_t)(~((uint16_t)TIM_CR1_CEN));
#endif

		// Clear any interrupt which might have just occurred
#ifdef NO_MANUAL_SPACE_OPTS
		TIM_ClearITPendingBit(TIM16, TIM_IT_Update);
#else
        TIM16->SR = (uint16_t)~TIM_IT_Update;
#endif
	}
    else
    {
        _timcmp_init();
    }

	//__enable_interrupt();
	mutual_excl_end(mutual_excl_value);

#ifdef NO_MANUAL_SPACE_OPTS
	TIM_TimeBaseStructInit(&tim16_init);

    tim16_init.TIM_Prescaler = SystemCoreClock / 1000000;  // for 1us resolution

    tim16_init.TIM_CounterMode       = TIM_CounterMode_Up;
	tim16_init.TIM_Period            = duration_us;
	tim16_init.TIM_ClockDivision     = TIM_CKD_DIV1;
	tim16_init.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM16, &tim16_init);
    
    TIM_Cmd(TIM16, ENABLE);
#else
    /* Skip timer initialization that was done in _timcmp_init.
    *  This includes the CR1, PSC, and RCR registers
    */

	/* Set the Autoreload value */
	TIM16->ARR = duration_us;

	/* Generate an update event to reload the Prescaler and the Repetition counter
	     values immediately */
	TIM16->EGR = TIM_PSCReloadMode_Immediate;

	/* Enable the TIM Counter */
	TIM16->CR1 |= TIM_CR1_CEN;
#endif

	return PROD_TIMCMP_ERROR_NONE;
}


/** Stop the high-precision timer.
 *
 * The callback must not not be invoked after this function returns (unless the
 * timer is restarted).
 *
 * Valid status codes:
 *
 * - PROD_TIMCMP_ERROR_NONE
 *
 * \warning May be called at interrupt time.
 * \return a valid status code
 */
enum prod_timcmp_error prod_timcmp_stop(void)
{
	uint32_t                mutual_excl_value;
	mutual_excl_value = mutual_excl_start();

    // Stop timer if it is running
	if (timer_is_running)
	{
		// Disable the timer
#ifdef NO_MANUAL_SPACE_OPTS
		TIM_Cmd(TIM16, DISABLE);
#else
        TIM16->CR1 &= (uint16_t)(~((uint16_t)TIM_CR1_CEN));
#endif

		// Clear any interrupt which might have just occurred
#ifdef NO_MANUAL_SPACE_OPTS
		TIM_ClearITPendingBit(TIM16, TIM_IT_Update);
#else
        TIM16->SR = (uint16_t)~TIM_IT_Update;
#endif

		// Turn off TIM16 clocks to conserve power
#ifdef NO_MANUAL_SPACE_OPTS
	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM16, DISABLE);
#else
        RCC->APB2ENR &= ~RCC_APB2Periph_TIM16;
#endif

		timer_is_running = false;
	}

	//__enable_interrupt();
	mutual_excl_end(mutual_excl_value);

	return PROD_TIMCMP_ERROR_NONE;
}


/** Read the time elapsed thus far.
 *
 * Valid status codes:
 *
 * - PROD_TIMCMP_ERROR_NONE
 * - PROD_TIMCMP_ERROR_NOT_STARTED
 *
 * \warning May be called at interrupt time.
 * \param elapsed_us out parameter to be filled with the microseconds elapsed
 * \return a valid status code
 */
enum prod_timcmp_error prod_timcmp_get_microseconds_elapsed(uint16_t* elapsed_us)
{
	enum prod_timcmp_error  result = PROD_TIMCMP_ERROR_NONE;
	uint32_t                mutual_excl_value;
	mutual_excl_value = mutual_excl_start();

	if (timer_is_running)
	{
		*elapsed_us = TIM16->CNT;

		if (*elapsed_us == 0)
		{
			// Count overflowed, and so return the full elapsed time
			*elapsed_us = TIM16->ARR;
		}
	}
	else
	{
		result = PROD_TIMCMP_ERROR_NOT_STARTED;
	}

	mutual_excl_end(mutual_excl_value);

	return result;
}


/** Timer 16 ISR
 */
void TIM16_IRQHandler(void)
{
	prod_timcmp_stop();
    
#if ANGAZA_LIBRARY_INCLUDE_CABLE
	payg_interrupts_timcmp_handle_elapsed();
#endif
}


/** Indicates whether the high-precision timer is running
 *  
 * \return true if timer is running, otherwise false
 */
bool get_timer_is_running(void)
{
    return timer_is_running;
}


/** Start a mutually exclusive code sequence
 *
 * This function starts a mutually exclusive code sequence
 *
 * \return the previous mutually exclusive state
 */
uint32_t mutual_excl_start(void)
{
    uint32_t iser_value;

    iser_value = NVIC->ISER[0];

    NVIC->ICER[0] = 0xFFFFFFFF;

    return iser_value;
}


/** End a mutually exclusive code sequence
 *
 * This function ends a mutually exclusive code sequence.
 * The parameter prev_state must be the value returned from
 * the corresponding call to mutual_excl_start().
 *
 * \param  prev_state is the value from the previous mutual_excl_start() call
 */

void mutual_excl_end(uint32_t prev_state)
{
	// prev_state is the ISER register, and so
	// only enable interrupts if they were previously
	// enabled before the call to mutual_excl_start
	NVIC->ISER[0] = prev_state;
}



