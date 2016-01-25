/** \file Interface to MCU IO pins connected to the infrared (IR) receiver circuit.
 *
 * *To be implemented in product firmware by the manufacturer.*
 *
 * Used by PAYG code to receive IR input. Only defined if
 * ANGAZA_LIBRARY_INCLUDE_IR is defined in angaza_config.h.
 *
 * Relevant interrupts:
 *
 * - payg_interrupts_ir_handle_rx_edge()
 *
 * See documentation in payg_interrupts.h.
 */

#ifndef __ANGAZA__PROD_IR_H__
#define __ANGAZA__PROD_IR_H__

#include "angaza/config.h"

#if ANGAZA_LIBRARY_INCLUDE_IR
#if !ANGAZA_LIBRARY_INCLUDE_KEYPAD
#error "Angaza library keypad support required for IR support"
#endif

#include <stdbool.h>

/** Set the logic level on the MCU_Override_EN output.  This is only relevant
 * for systems using the low-power mode Angaza IR receiver hardware.  This
 * function body can be empty in other scenarios.
 *
 * \par Example Scenario:\n
 * -# PAYG library detects the beginning of an IR message
 * -# PAYG library attempts to force IR receiver to 'full-power' mode
 *  - @code
 *  // (Inside product firmware, in `prod_ir_override_enable(bool level`)
 *  if(level)
 *  {
 *      GPIOF->BSRR = PAYG_IR_OVERRIDE_GPO;
 *  }
 *  else
 *  {
 *      GPIOF->BRR = PAYG_IR_OVERRIDE_GPO;
 *  }
 *        @endcode
 *
 * \warning May be called at interrupt time.
 * \param logic level to apply to the MCU_Override_EN pin (true == high)
 */
void prod_ir_override_enable(bool level);

#endif
#endif
