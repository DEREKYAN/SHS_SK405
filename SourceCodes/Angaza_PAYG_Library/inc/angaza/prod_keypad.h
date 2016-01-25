/** \file Interface to a keypad connected to the MCU in some way.
 *
 * *To be implemented in product firmware by the manufacturer.*
 *
 * Used by PAYG code to receive non-IR keypad input. Only defined if
 * ANGAZA_LIBRARY_INCLUDE_KEYPAD is defined in angaza_config.h.
 *
 * Relevant interrupts:
 *
 * - payg_interrupts_keypad_handle_key()
 *
 * See documentation in payg_interrupts.h.
 */

#ifndef __ANGAZA__PROD_KEYPAD_H_
#define __ANGAZA__PROD_KEYPAD_H_

#include "angaza/config.h"

#if ANGAZA_LIBRARY_INCLUDE_KEYPAD
#if ANGAZA_KEYCODE_PROTOCOL == ANGAZA_KEYCODE_PROTOCOL_SMALL
#elif ANGAZA_KEYCODE_PROTOCOL == ANGAZA_KEYCODE_PROTOCOL_FULL
#else
#error "No supported keycode protocol configured."
#endif

/** Type of key input received.
 *
 * For example, is it a standard ASCII character, such as "X" or "*"?
 * Or is it a special key, such as a unique "enter" or "stop" key?
 */
enum prod_keypad_key_type
{
    /** The key is a standard ASCII character.
     */
    PROD_KEYPAD_KEY_TYPE_CHAR,
};

/** Value of key input received.
 *
 * For example, if the key is a standard ASCII character, exactly which
 * character is it? Each member of the union corresponds one-to-one with a
 * member of the `prod_keypad_key_type` union.
 */
union prod_keypad_key_value
{
    char character;
};

/** Type and value of a single, specific received keypress.  Used by product
 * code when calling payg_interrupts_keypad_handle_key().
 *
 * Example:
 * @code
 * prod_keypad_key key_0;
 * key_0.type = PROD_KEYPAD_KEY_TYPE_CHAR;
 * key_0.value = '0';
 * @endcode
 */
struct prod_keypad_key
{
    /** Type of key; typically PROD_KEYPAD_KEY_TYPE_CHAR for keys
     * representing single ASCII characters.
     */
    enum prod_keypad_key_type type;
    /** Value of key; if type is PROD_KEYPAD_KEY_TYPE_CHAR, typically
     * this is a character i.e. '1', 'A', '0', etc)
     */
    union prod_keypad_key_value value;
};

#endif
#endif
