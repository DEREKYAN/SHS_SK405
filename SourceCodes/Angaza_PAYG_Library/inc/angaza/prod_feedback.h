#ifndef __ANGAZA__PROD_FEEDBACK_H__
#define __ANGAZA__PROD_FEEDBACK_H__

#include "angaza/payg_state.h"

#define CONST_BLINKS_NEAR_DISABLE       24       //  12*(ON 100mS) 12*(OFF 100mS) Red led and illumination LED blinks at the same time
#define CONST_BLINKS_DISABLE            30      // 15*(ON 100mS) 15*(OFF 100mS) Red led and illumination LED blinks at the same time
#define CONST_BLINKS_100MS              5       // Base on 20 mS

extern uint8_t payg_ui_step; 
extern uint8_t payg_ui_on,payg_ui_off;
extern uint8_t credit_ui_step;	
extern uint8_t flag_green;                     // 1 is green, 0 is red


/** Error status of a given feedback function call.
 */
enum prod_feedback_error
{
    /** The invocation was successful; no error occurred.
     */
    PROD_FEEDBACK_ERROR_NONE,

    /** The requested pattern could not be performed because of battery level.
     */
    PROD_FEEDBACK_ERROR_BATTERY_LOW,

    /** The requested pattern is not currently supported.
     *
     * This error may be returned if a given script is not yet implemented by,
     * or not applicable to, this product.
     */
    PROD_FEEDBACK_ERROR_UNSUPPORTED,
};

/** Name of a specific feedback pattern.
 */
enum prod_feedback_script
{
    /** No feedback to user is requested.
     */
    PROD_FEEDBACK_SCRIPT_NONE,
    /** Request user feedback indicating 'invalid PAYG message received'.
     * For example, if a code was received that is not an actual PAYG message.
     */
    PROD_FEEDBACK_SCRIPT_MESSAGE_INVALID,
    /** Request user feedback indicating 'valid PAYG message received, 
     * not applied'.
     */
    PROD_FEEDBACK_SCRIPT_MESSAGE_VALID,
    /** Request user feedback indicating 'valid PAYG message received, rejected'.
     * For example, if a code was an actual PAYG message, but has wrong information
     * (such as a wrong sequence/ID number).
     */
    PROD_FEEDBACK_SCRIPT_MESSAGE_REJECTED,
    /** Request user feedback indicating 'valid PAYG message received, and applied'.
     * For example, if user enters a valid code to add credit to the device.
     */
    PROD_FEEDBACK_SCRIPT_MESSAGE_APPLIED,
    /** Request user feedback indicating 'valid keypress received'.
     * Useful when user is entering code digit-by-digit.
     */
    PROD_FEEDBACK_SCRIPT_KEY_ACCEPTED,
    /** Request user feedback indicating 'invalid keypress received'.
     * Useful if, while entering a code, user enters a wrong key.
     */
    PROD_FEEDBACK_SCRIPT_KEY_REJECTED,
};

/** Asynchronously initiate a specific user-feedback script.
 *
 * This function is called by the Angaza PAYG firmware library, which passes
 * a `prod_feedback_script` value indicating the type of feedback which
 * should be signalled to the user.  It it up to the manufacturer to
 * implement user feedback (LEDs, etc) representing this feedback type.
 *
 * The details of this feedback may differ across products. The suggested
 * feedback pattern for a lantern-class product:
 *
 * - The illumination LED should cycle through each of the light's brightness
 *   levels, plus the "off" state, starting from its lowest brightness.
 * - The lamp should pause for roughly 300 ms between each transition.
 * - This cycle should repeat four times.
 * - Finally, the lamp should return to the brightness level (or "off") that
 *   was present before the response was initiated.
 *
 * This response may be produced when certain communications transactions are
 * successfully completed, such as the application of payment.
 *
 * The initiation of any feedback pattern must be asynchronous: this function
 * must return within 10 ms, rather than, e.g., waiting for completion of the
 * pattern.
 *
 * Valid status codes:
 *
 * - PROD_FEEDBACK_ERROR_NONE
 * - PROD_FEEDBACK_ERROR_BATTERY_LOW
 * - PROD_FEEDBACK_ERROR_UNSUPPORTED
 *
 *
 * \par Example Scenario:\n
 * (For reference only. Actual implementation will differ based on product)
 * -# PAYG library receives a valid keycode sequence or other PAYG message.
 * -# PAYG library instructs product to display feedback pattern:
 *      - @code
 *      // (Inside PAYG library)
 *      prod_feedback_script to_display = PROD_FEEDBACK_SCRIPT_MESSAGE_VALID;
 *      prod_feedback_start(to_display);
 *      @endcode
 * -# `prod_feedback_start` initiates appropriate product-specific user feedback. 
 *      - @code 
 *      // (Inside product firmware, in body of `prod_feedback_start` function)
 *      switch (script)
 *      {
 *          case PROD_FEEDBACK_SCRIPT_MESSAGE_VALID:
 *              enable_output_PWM(output_LED); // product enables LED output
 *              display_LED_success_blinks(); // product displays 'success' pattern
 *              break;
 *          // other cases here
 *      }
 *      return PROD_FEEDBACK_ERROR_NONE;
 *      @endcode
 *
 * \warning May be called at interrupt time.
 * \return a valid status code (of type `prod_feedback_error`)
 */
enum prod_feedback_error prod_feedback_start(enum prod_feedback_script script);

/** Receive notification from the library that the PAYG state has changed.
 *
 * This information may be useful to product code by allowing it to enable or
 * disable functionality according to the new state. However, the body of this
 * function can, in some cases, be left empty, and payg_state_get_current() be
 * polled instead.
 *
 * \par Example Scenario:\n
 * (For reference only.  Actual implementation will differ based on product)
 * -# PAYG library internally calculates product should be DISABLED
 * -# PAYG library calls `prod_feedback_handle_state_change()`
 *      - @code
 *      // (Inside product firmware, in `prod_feedback_handle_state_change`)
 *      if (payg_state_is_enabled())
 *      {
 *          // product transitioned to 'enabled' state, indicate to user
 *          enable_output_PWM(output_LED);
 *          display_LED_success_blinks();
 *      }
 *      else
 *      {
 *         payg_state cur_state = payg_state_get_current();
 *         
 *         switch(payg_state)
 *         {
 *             case PAYG_STATE_DISABLED:
 *                 //disable product functionality
 *             case PAYG_STATE_ENABLED_NEAR_DISABLED:
 *                 //indicate to user that product is near cutoff
 *         }
 *      }
 *      @endcode
 *
 * \warning May be called at interrupt time.
 */
void prod_feedback_handle_state_change(void);

bool Is_Communication_Indication(void);
bool IS_PAYG_IDLE(void);
//void start_near_disable_display(void);
void start_disable_display(void);
void pay_ng_indication(void);

#endif