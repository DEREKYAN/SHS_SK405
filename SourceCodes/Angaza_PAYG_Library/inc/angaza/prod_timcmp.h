/** \file Interface to a high-precision timer on this MCU.
 *
 * *To be implemented in product firmware by the manufacturer (you).*
 *
 * Used by PAYG code to time input and output signals. Necessary only if
 * support for, e.g., cable or IR inputs are defined.
 *
 * Relevant interrupts:
 *
 * - payg_interrupts_timcmp_handle_elapsed()
 *
 * See documentation in payg_interrupts.h.
 */

#ifndef __ANGAZA__PROD_TIMCMP_H__
#define __ANGAZA__PROD_TIMCMP_H__

#include <stdint.h>

/** Error status of a high-precision timer routine.
 */
enum prod_timcmp_error
{
    /** The invocation was successful; no error occurred.
     */
    PROD_TIMCMP_ERROR_NONE,

    /** The specified duration is unsupported (e.g., it is too long).
     */
    PROD_TIMCMP_ERROR_DURATION_UNSUPPORTED,

    /** The timer is not started, but is required for this operation.
     */
    PROD_TIMCMP_ERROR_NOT_STARTED,
};

/** Start or restart the high-precision timer.
 *
 * The timer measures elapsed time in microseconds starting when this function
 * is called. The timer invokes the prod_timcmp_handle_elapsed() callback after
 * the specified duration has elapsed. The timer must stop naturally after the
 * duration elapses and the callback is invoked. Timer error must be less than
 * 10%.
 *
 * The prod_timcmp_get_microseconds_elapsed() routine may be used to read the
 * current elapsed time while the timer is running. If this start routine is
 * called while the timer is running, it is restarted.
 *
 * The timer need not support durations larger than 8000 us.
 *
 * \par Example Scenario:\n
 * (For reference only.  Actual implementation will differ based on product)
 * -# Product receives interrupt on PAYG RX communications line
 * -# Product indicates this to PAYG library via payg_interrupts_cable_handle_rx_edge()
 * -# PAYG library begins the high-precision timer, to measure the incoming pulse.
 *     - @code
 *      // (inside product code, inside prod_timcmp_start())
 *      tim14_init.TIM_CounterMode       = TIM_CounterMode_Up;
 *      tim14_init.TIM_Period            = duration_us; //duration <= 8000 us
 *      tim14_init.TIM_ClockDivision     = TIM_CKD_DIV1;
 *      tim14_init.TIM_RepetitionCounter = 0;
 *
 *      TIM_TimeBaseInit(TIM14, &tim14_init);
 *
 *      TIM_UpdateRequestConfig(TIM14, TIM_UpdateSource_Regular);
 *
 *      TIM_ClearITPendingBit(TIM14, TIM_IT_Update);
 *
 *      TIM_ITConfig(TIM14, TIM_IT_Update, ENABLE);
 *
 *      NVIC_SetPriority(TIM14_IRQn, 15);
 *      NVIC_EnableIRQ(TIM14_IRQn);
 *
 *      timer_is_running = true;
 *
 *      TIM_Cmd(TIM14, ENABLE);
 *
 *      return PROD_TIMCMP_ERROR_NONE;
 *      @endcode
 *
 * Valid status codes:
 *
 * - PROD_TIMCMP_ERROR_NONE
 * - PROD_TIMCMP_ERROR_DURATION_UNSUPPORTED
 *
 * \warning May be called at interrupt time.
 * \warning Must complete in 10 us or less.
 * \param duration_us duration in microseconds
 * \return a valid status code
 */
enum prod_timcmp_error prod_timcmp_start(uint16_t duration_us);

/** Stop the high-precision timer.
 *
 * The callback must not not be invoked after this function returns (unless the
 * timer is restarted).
 *
 * \par Example Scenario:\n
 * (For reference only.  Actual implementation will differ based on product)
 * -# PAYG library receives a valid PAYG message
 * -# PAYG library stops the high precision timer, by calling prod_timcmp_stop()
 * -# Product uses TIM14 for PAYG high-precision timer
 *     - @code
 *     // (inside product code, inside prod_timcmp_stop())
 *
 *      if (timer_is_running)
 *      {
 *       // Disable the timer
 *       TIM_Cmd(TIM14, DISABLE);
 *
 *       // Clear any interrupt which might have just occurred
 *       TIM_ClearITPendingBit(TIM14, TIM_IT_Update);
 *
 *       // Turn off TIM14 clocks to conserve power
 *       RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, DISABLE);
 *
 *       timer_is_running = false;
 *      }
 *      return PROD_TIMCMP_ERROR_NONE;
 *      @endcode
 *
 * Valid status codes:
 *
 * - PROD_TIMCMP_ERROR_NONE
 *
 * \warning May be called at interrupt time.
 * \return a valid status code
 */
enum prod_timcmp_error prod_timcmp_stop(void);

/** Read the time elapsed thus far on the high-precision timer, without
 * stopping it.
 *
 * Valid status codes:
 *
 * - PROD_TIMCMP_ERROR_NONE
 * - PROD_TIMCMP_ERROR_NOT_STARTED
 *
 * \par Example Scenario:\n
 * (For reference only.  Actual implementation will differ based on product)
 * -# PAYG library is timing a pulse on the PAYG RX Comm IO
 * -# PAYG library requires the time since the edge began
 * -# PAYG library calls prod_timcmp_get_microseconds_elapsed(elapsed_us*)
 * -# When prod_timcmp_get_microseconds_elapsed returns PROD_TIMCMP_ERROR_NONE,
 *       PAYG library examines the value of elapsed_us.
 *
 *     - @code
 *     // (inside product code, example definition of prod_timcmp_get_microseconds_elapsed())
 *       enum prod_timcmp_error prod_timcmp_get_microseconds_elapsed(uint16_t* elapsed_us)
 *      {
 *          // good practice to ensure that timer access is locked when in use.
 *          uint32_t                mutual_excl_value;
 *          enum prod_timcmp_error  result = PROD_TIMCMP_ERROR_NONE;
 *
 *          // use mutex locks if they are available.
 *          mutual_excl_value = mutual_excl_start();
 *
 *          if (timer_is_running)
 *          {
 *              *elapsed_us = TIM14->CNT;
 *
 *              if (*elapsed_us == 0)
 *              {
 *                  // Count overflowed, and so return the full elapsed time
 *                  *elapsed_us = TIM14->ARR;
 *              }
 *          }
 *          else
 *          {
 *              result = PROD_TIMCMP_ERROR_NOT_STARTED;
 *          }
 *
 *          mutual_excl_end(mutual_excl_value);
 *          return result;
 *       }
 *      @endcode
 *
 * \warning May be called at interrupt time.
 * \param elapsed_us out parameter to be filled with the microseconds elapsed
 * \return a valid status code
 */
enum prod_timcmp_error prod_timcmp_get_microseconds_elapsed(uint16_t* elapsed_us);
bool get_timer_is_running(void);
#endif
