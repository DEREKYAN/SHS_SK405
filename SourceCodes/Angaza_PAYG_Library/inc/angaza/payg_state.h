#ifndef __ANGAZA__PAYG_STATE_H__
#define __ANGAZA__PAYG_STATE_H__

#include <stdint.h>
#include <stdbool.h>

/** Enforcement state of the unit.
 */
enum payg_state
{
   /** Unit functionality should be restricted.
    *
    * The unit has not been paid off and its payment period has elapsed.
    * Product functionality should be disabled or otherwise restricted. When a
    * restricted product function is accessed and the product would normally
    * become active, the same pattern used for the near-disabled state should
    * be presented, and the product should instead then return to its inactive
    * state.
    */
   PAYG_STATE_DISABLED,

   /** Functionality should be unrestricted, but impending cutoff announced.
    *
    * The unit has not been paid off and nears the end of its payment period.
    * It should inform the user that functionality will soon be restricted. The
    * suggested method for providing this feedback on a lantern product
    * involves the illumination LED flashing at 5 Hz with a 50% duty cycle for
    * 2 seconds whenever either (i) the button is pressed and a light mode
    * other than "off" is entered, or (ii) the light is on and has been on for
    * 30 minutes since the last time the pattern was produced.
    */
   PAYG_STATE_ENABLED_NEAR_DISABLED,

   /** Unit functionality should be unrestricted.
    *
    * The unit has not yet been paid off, so the RTC must therefore continue to
    * be periodically backed up.
    */
   PAYG_STATE_ENABLED,

   /** Unit functionality should be unrestricted.
    *
    * The unit has been paid off, so the RTC need not be backed up.
    */
   PAYG_STATE_ENABLED_UNLOCKED,
};

/** Does the current PAYG state permit product functionality?
 *
 * May be polled by product firmware to determine if the product should be allowed
 * to operate or not (from a PAYG perspective).
 *
 * \par Example Scenario:\n
 * (For reference only.  Actual implementation will differ based on product)
 * -# User presses "on" button
 * -# Product asks PAYG library for enabled state
 * -# If PAYG_STATE_ENABLED, turn on product
 *     - @code
 *     bool turn_on_ok = false;
 *     // example: product checks payg_state (PAYG library) and
 *     // battery level (product-specific firmware) before turning on.
 *     if(payg_state_is_enabled() && battery_level_is_ok())
 *     {
 *         enable_main_light();
 *         enable_usb_outputs();
 *     }
 *     @endcode
 * \return true iff the current state is one of PAYG_STATE_ENABLED_*
 */
bool payg_state_is_enabled(void);

/** Return the current PAYG state.
 *
 * May be polled by product to determine the exact PAYG state (beyond PAYG_STATE_ENABLED
 * or PAYG_STATE_DISABLED).  Either `payg_state_is_enabled()` or `payg_state_get_current()`
 * must be used when the product needs to explicitly determine the PAYG state.
 *
 * \par Example Scenario:\n
 * (For reference only.  Actual implementation will differ based on product)
 * -# User presses "on" button
 * -# Product asks PAYG library for specific state
 * -# Product takes action according to specific state (e.g. feedback)
 *     - @code
 *         payg_state current_payg_state = payg_state_get_current();
 *         switch(current_payg_state) {
 *         case PAYG_STATE_ENABLED:
 *             // turn on product/enable functionality
 *              break;
 *         case PAYG_STATE_DISABLED:
 *             // turn off product/enable functionality
 *             break;
 *         // other cases here
 *         }
 *         @endcode
 *
 * \return the current PAYG state
 */
enum payg_state payg_state_get_current(void);

/** Inform the PAYG library that some credit has been consumed.
 *
 * The PAYG library tracks the amount of credit allowed, the overall credit
 * state, and so on, but it does not and cannot track the actual *consumption*
 * of PAYG credit. It relies on product code, implemented by the manufacturer,
 * to periodically call this function when credit is used up.
 *
 * Credit is most often defined in terms of wall-clock time. In that case, this
 * function should be called periodically according to the passage of time. It
 * should be passed the number of seconds elapsed since the last time the
 * function was called. The simplest approach is simply to call this function
 * one per second, every second, always passing amount `1`. Equally simple
 * would be to call this function once per minute, every minute, always passing
 * amount `60`. Regardless, the most straightforward approach will depend on
 * the product.
 *
 * \par Example Scenario 1:\n
 * (For reference only.  Actual implementation will differ based on product)
 * -# Product implements an RTC
 * -# Every minute, product RTC code calls payg_state_consume_credit()
 *     - @code
 *      if (min != last_minuteInHour)
 *      {
 *          last_minuteInHour = min;
 *          // Consume one minute of time (typically, passed as seconds)
 *          payg_state_consume_credit(60);
 *      }
 *      @endcode
 * \par Example Scenario 2:\n
 * (For reference only.  Actual implementation will differ based on product)
 * -# Product consumes credit in discrete usage-based 'chunks' (e.g. 'pump X gallons')
 * -# When product use exceeds a given 'chunk', consume credit.
 *      - @code
 *      uint8_t gallons_pumped;
 *      while (pump_is_running)
 *      {
 *          gallons_pumped = update_gallons_pumped();
 *      }
 *      // consume a 'chunk' of credit every 15 gallons pumped
 *      if (gallons_pumped % 15 == 0)
 *      {
 *          payg_state_consume_credit(1);
 *      }
 *      @endcode
 *
 * \note May be called at interrupt time.
 * \param amount amount of credit (e.g., number of seconds) used since the last call
 */
void payg_state_consume_credit(uint32_t amount);

#endif
