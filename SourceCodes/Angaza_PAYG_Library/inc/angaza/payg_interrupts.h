/** PAYG library functions to be called on specific interrupt events.
 *
 * *The bodies of these functions are already implemented by Angaza in this
 * PAYG library.* The product manufacturer (you) should add code to the product
 * firmware, typically inside raw interrupt-service routines, that *calls*
 * these functions when appropriate.
 *
 * Some of these interrupt handlers may be left undefined unless specific
 * library support is enabled. For example, the payg_interrupts_ir_* routine(s)
 * will be undefined unless IR receiver support is enabled via
 * ANGAZA_LIBRARY_INCLUDE_IR.
 */

#ifndef __ANGAZA__PAYG_INTERRUPTS_H__
#define __ANGAZA__PAYG_INTERRUPTS_H__

#include <stdint.h>
#include <stdbool.h>
#include "angaza/config.h"
#include "angaza/prod_keypad.h"

// TIMCMP INTERRUPT(S)

#if ANGAZA_LIBRARY_INCLUDE_CABLE

/** Inform PAYG code that the high-precision timer period has elapsed.
 *
 * *The body of this function is already implemented by Angaza in this PAYG
 * library.* Product firmware code, written by the product manufacturer, will
 * *call* this function, typically inside the raw interrupt-service routine.
 *
 * \par Example Scenario:\n
 * (For reference only.  Actual implementation will differ based on product)
 * -# High-precision timer assigned to PAYG use by product has elapsed
 *    - @code
 *    // (Inside product firmware for a product using PAYG cable.  Inside PAYG timer ISR)
 *    void TIM14_IRQHandler(void)
 *    // TIM14 ISR
 *    {
 *        // first call the product-specific code to stop the timer
 *        prod_timcmp_stop();
 *        // then call this function to indicate to library that timer elapsed.
 *        payg_interrupts_timcmp_handle_elapsed();
 *    }
 *    @endcode
 *
 * \warning May called at interrupt time.
 */
void payg_interrupts_timcmp_handle_elapsed(void);

#endif

// KEYPAD INTERRUPT(S)

#if ANGAZA_LIBRARY_INCLUDE_KEYPAD

/** Inform PAYG code that a non-IR keypad button has been pressed.
 *
 * *The body of this function is already implemented by Angaza in this PAYG
 * library.* Product firmware code, written by the product manufacturer, will
 * *call* this function, typically inside the raw interrupt-service routine.
 *
 * Must be called every time a non-IR key is received.
 *
 * \par Example Scenario:\n
 * (For reference only.  Actual implementation will differ based on product)
 * -# Product firmware receives a keypress
 * -# Product firmware translates keypress into `prod_keypad_key`
 * -# Product firmware passes `prod_keypad_key` to PAYG library
 *      - @code
 *      // (Inside product firmware, after key is pressed)
 *      struct prod_keypad_key key;
 *      bool valid_key;
 *      key.type = PROD_KEYPAD_KEY_TYPE_CHAR;
 *
 *     // product firmware reads raw keypress
 *      uint8 raw_keycode = read_raw_keypress();
 *
 *      // translate the raw_keycode into a character for PAYG library
 *      switch(raw_keycode)
 *      {
 *          case 48:
 *              key.value.character = '0';
 *              valid_key = true;
 *              break;
 *          case 49:
 *              key.value.character = '1';
 *              valid_key = true;
 *              break;
 *          case 50:
 *              key.value.character = '2';
 *              valid_key = true;
 *              break;
 *          // other valid keys handled here
 *          default:
 *              //invalid keypress
 *              valid_key = false;
 *              break;
 *      }
 *      // only pass PAYG library valid keycodes
 *      if (valid_key)
 *      {
 *          payg_interrupts_keypad_handle_key(key);
 *      }
 *      @endcode
 *
 * \warning May be called at interrupt time.
 */
void payg_interrupts_keypad_handle_key(struct prod_keypad_key key);

#endif

// CABLE INTERRUPT(S)

#if ANGAZA_LIBRARY_INCLUDE_CABLE

/** Inform PAYG code that the cable-receive input has changed logic levels.
 *
 * *The body of this function is already implemented by Angaza in this PAYG
 * library.* The product manufacturer (you) should write code, typically inside
 * the raw interrupt-service routine, that *calls* this function.
 *
 * This function should be called on any rising *or* falling edge.
 *
 * The redundant "extern" tag is present only to emphasize that this
 * implementation is provided by PAYG rather than by product code.
 *
 * * \par Example Scenario:\n
 * (For reference only.  Actual implementation will differ based on product)
 * - # Product receives rising *or* falling edge on PAYG cable RX input
 * - # Product code passes level of PAYG cable RX input to PAYG library
 *     - @code
 *       void EXTI0_1_IRQHandler(void)
 *       {
 *          //clear the current interrupt
 *          EXTI_ClearITPendingBit(PAYG_RX_EXT_EXTI_LINE);
 *
 *          //inform PAYG library that an edge on payg_rx has arrived
 *          payg_interrupts_cable_handle_rx_edge();
 *       }
 *       @endcode
 *
 * \warning May be called at interrupt time.
 * \note Interrupt latency should be relatively consistent:
 * the delay between the physical edge transition and the
 * invocation of this handler should not vary across calls by
 * more than 5 microseconds.
 */
void payg_interrupts_cable_handle_rx_edge(void);

#endif

// INFRARED INTERRUPT(S)

#if ANGAZA_LIBRARY_INCLUDE_IR

/** Inform PAYG code that the IR-receive input pin changed logic levels.
 *
 * *The body of this function is already implemented by Angaza in this PAYG
 * library.* Product firmware code, written by the product manufacturer, will
 * *call* this function, typically inside the raw interrupt-service routine.
 *
 * This function should be called on any rising *or* falling edge. It is
 * defined only if ANGAZA_LIBRARY_INCLUDE_IR resolves to true.
 *
 * \note Interrupt latency should be relatively consistent:
 * the delay between the physical edge transition and the
 * invocation of this handler should not vary across calls by
 * more than 5 microseconds.
 *
 * \par Example Scenario:\n
 * (For reference only.  Actual implementation will differ based on product)
 * -# Interrupt for infrared (IR) receiver indicates rising *or* falling edge
 * -# Product code passes the level of the IR RX input to PAYG library
 *     - @code
 *     void EXTI0_1_IRQHandler(void)
 *     {
 *         // Clear the current interrupt
 *         EXTI_ClearITPendingBit(PINOUT_IR_RX_EXTI_LINE);
 *
 *         bool payg_rx_pin_level = GPIO_ReadInputDataBit(PINOUT_IR_RX_BANK, PINOUT_IR_RX_PIN);
 *
 *         // Callback to PAYG library
 *         payg_interrupts_ir_handle_rx_edge(payg_rx_pin_level);
 *      }
 *      @endcode
 *
 * \warning May be called at interrupt time.
 * \param true iff the ir rx pin reads logic high
 * \return void
 */
void payg_interrupts_ir_handle_rx_edge(bool rx_pin_level);

#endif
#endif
