#ifndef __ANGAZA__PAYG_ALL_H__
#define __ANGAZA__PAYG_ALL_H__

#include <stdint.h>

/** Initialize the library and all its internal submodules.
 *
 * Should be called by product code exactly once on power-up. Should be called
 * before any other library routines are invoked, and should thus be called
 * before any library-relevant interrupt handlers are configured.
 *
 * \par Example Scenario:\n
 * (For reference only.  Actual implementation will differ based on product)
 * @code
 * int main(void)
 * {
 *  // initialize power
 *  power_init();
 *
 *  //call payg_all_init ONCE
 *  payg_all_init();
 *
 *  // product initialization code and main executive loop below
 *  }
 * @endcode
 *
 * \warning Must not be called at interrupt time.
 */
void payg_all_init(void);

/** Deinitialize the library and all its internal submodules.
 *
 * Should be called by product code exactly once before any intentional
 * non-RAM-preserving reset. Must be called *after* payg_all_init(). After it
 * is called, no other library routines may be invoked other than
 * payg_all_init().
 *
 * If the product firmware never intentionally clears RAM, `payg_all_deinit()`
 * never needs to be called.  For example, `payg_all_deinit()` should be called anytime
 * that "NVIC_SystemReset()" will be called on an ARM CMSIS processor.
 *
 * To avoid preemptive external calls into the library from interrupt code,
 * service routines calling into the library should be disabled before the
 * library is deinitialized.
 *
 * This function is used primarily to save internal state to nonvolatile
 * storage before memory contents are lost. We therefore strongly recommend
 * that non-RAM-preserving resets are used sparingly, if at all, since they
 * will increase the volume of writes to nonvolatile storage. Assume that each
 * call to this function results in an additional four blocks written through
 * the prod_nv interface, and increase the endurance requirements accordingly.
 *
 * \par Example Scenario:\n
 * (For reference only.  Actual implementation will differ based on product)\n
 * User turns off product, product will go to sleep to save power:
 *      @code
 *      // call payg_all_deinit() before performing actions that intentionally clear RAM
 *      payg_all_deinit();
 *      // below, the actions cause the MCU to clear RAM
 *      product_stop_timers();
 *      product_full_power_reset();
 *      @endcode
 *
 * \warning Must not be called at interrupt time.
 */
void payg_all_deinit(void);

/** Perform any required PAYG processing.
 *
 * Product code must periodically call this function. Each time it is called,
 * it is passed the approximate number of seconds elapsed since the last call.
 * This routine drives low-accuracy internal timekeeping in the library. It is
 * acceptable if this number is not completely accurate (<= 10% error is fine;
 * even 20% may be acceptable).
 *
 * This function returns the maximum number of seconds that should elapse
 * before the *next* call to the function. For example, if payg_all_process()
 * returns 4, then at most 4 seconds should elapse before payg_all_process() is
 * called again. On that next call, the amount of time actually elapsed is
 * passed, to the nearest second rounding down.
 *
 * If prod_mainloop_request_processing() is called, then payg_all_process()
 * should be called as soon as possible, regardless of the maximum elapsed time
 * returned from the previous call.
 *
 * Elapsed time should accumulate. For example, if this function is called four
 * times spaced 300 ms apart, the `seconds_elapsed` parameter should be 0 for
 * the first three calls and 1 for the fourth call.
 *
 * In theory, this function could be called unconditionally every 20 ms,
 * although that approach would likely have unacceptable negative impact on
 * power consumption.
 *
 * \par Example Scenario:\n
 * (For reference only.  Actual implementation will differ based on product)\n
 * Periodically call payg_all_process.
 * @code
 * uint32_t systick_milliseconds = 0;
 * uint32_t systick_seconds_last_payg_process = 0;
 * // default to 4 seconds between calls
 * uint32_t max_seconds_until_next_payg_process = 4;
 *
 * int main(void)
 * {
 *     //initialization code above
 *     while (1)
 *     {
 *         if (systick_seconds - systick_seconds_last_payg_process >=
 *              max_seconds_until_next_payg_process - 1)
 *         {
 *             max_seconds_until_next_payg_process = payg_all_process(
 *                 seconds_elapsed_between_payg_process);
 *             systick_seconds_last_payg_process = systick_seconds;
 *         }
 *     }
 * }
 *
 * void SysTick_Handler(void)
 * {
 *     systick_milliseconds++;
 *     if(systick_milliseconds % 1000 == 999)
 *     {
 *        // second has elapsed
 *        systick_seconds++;
 *     }
 * }
 * @endcode
 *
 * \note Must not be called at interrupt time.
 * \return the maximum number of seconds before the next call
 */
uint32_t payg_all_process(uint32_t seconds_elapsed);

/** Get the computed low-accuracy uptime driven by payg_all_process().
 *
 * Only needed during debugging.  It is not necessary for product code to call this function.
 *
 * "Uptime" is the amount of time elapsed since the PAYG library started operating,
 * according to the library's internal tracking of time.  This function can be used
 * to determine if the PAYG library is successfully incrementing time.
 *
 * \par Example Scenario:\n
 * (For reference only.  Actual implementation will differ based on product)\n
 * -# Product code asks PAYG library for time elapsed
 *    @code
 *    // (product initialization code)
 *    payg_all_init();
 *    uint32_t payg_initial_time = payg_all_uptime();
 *
 *    // (inside main loop)
 *    uint32_t payg_rolling_time = payg_all_uptime();
 *
 *    // see `prod_mainloop.h` for info on a global flag requesting PAYG processing time.
 *    if (payg_rolling_time > max_uptime || payg_process_needed_global_flag)
 *    {
 *        // payg_rolling_time should always be increasing over payg_initial_time
 *        // if the PAYG library is keeping time successfully.
 *    }
 *    @endcode
 * \note May be called at interrupt time.
 * \return computed uptime in seconds
 */
uint32_t payg_all_uptime(void);

#endif
