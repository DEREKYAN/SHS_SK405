/** \file Interface to MCU pins connected to the cable-communication circuit.
 *
 * *To be implemented in product firmware by the manufacturer (you).*
 *
 * Used by PAYG code to receive and transmit data through an Angaza PAYG
 * communication cable.
 *
 * Note that in addition to the functions below, the MCU pins which the
 * manufacturer dedicates to cable PAYG must be initialized.  This occurs
 * within product code, not in the PAYG library.
 *
 * Relevant interrupts:
 *
 * - payg_interrupts_cable_handle_rx_edge()
 *
 * See documentation in payg_interrupts.h.
 */

#ifndef __ANGAZA__PROD_CABLE_H__
#define __ANGAZA__PROD_CABLE_H__

#include "angaza/config.h"

#if ANGAZA_LIBRARY_INCLUDE_CABLE

#include <stdbool.h>

/** Return the current logic level on the cable-receive input.
 *
 * \par Example Scenario:\n
 * (For reference only.  Actual implementation will differ based on product)
 * -# PAYG library is processing incoming PAYG cable message
 * -# PAYG library calls prod_cable_get_rx_pin()
 *     - @code
 *     // (Inside product firmware, in prod_cable_get_rx_pin())
 *     return GPIO_ReadInputDataBit(PAYG_GPIO_BANK, PAYG_RX_EXT_EXTI_LINE);
 *     @endcode
 *
 * \warning May be called at interrupt time.
 * \return true iff the pin is reading logic high
 */
bool prod_cable_get_rx_pin(void);

/** Set the current logic level on the cable-transmit output.
 *
 *
 * \par Example Scenario:\n
 * (For reference only.  Actual implementation will differ based on product)
 * -# PAYG library receives valid PAYG cable message, and will respond
 * -# PAYG library bitbangs the PAYG TX pin by calling prod_cable_set_tx_pin(level)
 *     - @code
 *   if (level)
 *   {
 *       GPIOF->BSRR = PAYG_TX_GPO;
 *   }
 *   else
 *   {
 *       GPIOF->BRR = PAYG_TX_GPO;
 *   }
 *    @endcode
 *
 * \warning May be called at interrupt time.
 * \param level logic level to apply on the output pin (true == high)
 */
void prod_cable_set_tx_pin(bool level);

#endif
#endif
