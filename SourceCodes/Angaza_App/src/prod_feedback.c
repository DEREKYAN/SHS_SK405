#include <stdlib.h>
#include "stm32f0xx.h"
#include "angaza.h"
#include "payg_state.h"
#include "prod_feedback.h"
#include "SKBridgePAYG.h"

/** Feedback pattern timing
 *
 *  The follow arrays specify the LED feedback patterns
 *  for the prod_feedback_start(enum prod_feedback_script script)
 *  function.
 *
 *  A positive value is the number of milliseconds to turn on the LED.
 *  A negative value is the number of milliseconds to turn off the LED.
 *  A zero value terminates the sequence.
 */
// Derek change for platform M3 
/*
static uint8_t pattern_key_accepted[] = {2, 35, 15};		//  Two step Mode 3 5*35 =175,5*15=75mS, count up per 5 second 
static uint8_t pattern_key_rejected[] = {6, 15, 15};
static uint8_t pattern_msg_valid[]    = {6, 120, 80};
static uint8_t pattern_msg_invalid[]  = {24,15,15};
static uint8_t pattern_msg_applied[]  = {12,120,80};
*/

static uint8_t pattern_key_accepted[] = {3, 35, 15,1};		//  Two step Mode 3 5*35 =175,5*15=75mS, count up per 5 second 
static uint8_t pattern_key_rejected[] = {7, 15, 15,0};
static uint8_t pattern_msg_valid[]    = {7, 120, 80,1};
static uint8_t pattern_msg_invalid[]  = {25,15,15,0}; 
//static uint8_t pattern_msg_applied[]  = {13,120,80};

uint8_t payg_ui_step; 
uint8_t payg_ui_on,payg_ui_off;
uint8_t flag_green;                     // 1 is green, 0 is red
enum payg_state payg_credit_state;

uint8_t credit_ui_step;			// timer Base 20mS,  100mS ON  100mS OFF

static void set_illumination(uint8_t* t);
/*
void start_near_disable_display(void)
{
	credit_ui_step = CONST_BLINKS_NEAR_DISABLE;
}
*/
bool IS_PAYG_IDLE(void)
{
	bool flag_payg_idle;
	flag_payg_idle = false;
	if((payg_ui_step == 0) && (credit_ui_step == 0))
	flag_payg_idle = true;
	return flag_payg_idle;
}

bool Is_Communication_Indication(void)
{
	bool flag_communication_Indication = false;
	if(payg_ui_step !=0)
	flag_communication_Indication = true;
	return flag_communication_Indication;
}

// Derek add to set PAYG status indicate with illumination LED
static void set_illumination(uint8_t* t)
{
	payg_ui_step = t[0];
	payg_ui_on = t[1];
	payg_ui_off = t[2];
	flag_green = t[3];
}

/** Receive notification from the library that the PAYG state has changed.
 *
 * This information may be useful to product code by allowing it to enable or
 * disable functionality according to the new state. However, the body of this
 * function can, in some cases, be left empty, and payg_state_get_current() be
 * polled instead.
 *
 * \warning May be called at interrupt time.
 */
void prod_feedback_handle_state_change(void)
{
#if 0  
 /* 
	payg_credit_state = payg_state_get_current();
//        static enum payg_state payg_state_backup = PAYG_STATE_ENABLED;
//        static uint32_t message_number =0;  // Add for test 
        
	switch (payg_credit_state)
	{
		case PAYG_STATE_DISABLED:
		case PAYG_STATE_ENABLED_NEAR_DISABLED:
//                if(payg_state_backup >= PAYG_STATE_ENABLED) 
//		start_near_disable_display();
//                Send_Message("\nFeedback:");
//                message_number++;                             // Add for test 
//                Send_Number(message_number);                  // Add for test 
//                Send_Message("\n");
                
			break;

		case PAYG_STATE_ENABLED:
		case PAYG_STATE_ENABLED_UNLOCKED:

			break;
	}
//        payg_state_backup = payg_credit_state;
//        Send_Message("\nCredit:");
//        Send_Number(payg_state_backup);
  */
#endif
}

/*
void handle_disable_UI(void)
{
    static enum payg_state payg_state_backup = PAYG_STATE_DISABLED;
    payg_credit_state = payg_state_get_current();
    if((payg_state_backup >= PAYG_STATE_ENABLED)  && (payg_credit_state < PAYG_STATE_ENABLED))
      pay_ng_indication();
//      start_near_disable_display();
    payg_state_backup = payg_credit_state;
}
*/

/** Asynchronously initiate a specific user-feedback script.
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
 * \return a valid status code
 */
enum prod_feedback_error prod_feedback_start(enum prod_feedback_script script)
{
	switch (script)
	{
		case PROD_FEEDBACK_SCRIPT_NONE:
			break;

		case PROD_FEEDBACK_SCRIPT_MESSAGE_INVALID:
			set_illumination(pattern_msg_invalid);
			
			break;

		case PROD_FEEDBACK_SCRIPT_MESSAGE_VALID:
			set_illumination(pattern_msg_valid);
			break;

		case PROD_FEEDBACK_SCRIPT_MESSAGE_REJECTED:
			set_illumination(pattern_msg_invalid);
			break;

		case PROD_FEEDBACK_SCRIPT_MESSAGE_APPLIED:
			set_illumination(pattern_msg_valid);
			break;

		case PROD_FEEDBACK_SCRIPT_KEY_ACCEPTED:
			set_illumination(pattern_key_accepted);
			break;

		case PROD_FEEDBACK_SCRIPT_KEY_REJECTED:
			set_illumination(pattern_key_rejected);
			break;

		default:
			return PROD_FEEDBACK_ERROR_UNSUPPORTED;
	}

	return PROD_FEEDBACK_ERROR_NONE;

}

void pay_ng_indication(void)
{
  set_illumination(pattern_msg_invalid);
  time_near_disable = 0;
}