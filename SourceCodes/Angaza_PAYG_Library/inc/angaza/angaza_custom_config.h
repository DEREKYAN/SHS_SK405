/** @file */

/*
 * Product/environment specific configuration variables.
 *
 * This file should be modified to reflect the target environment and product.
 * For instance, if a PAYG cable communications based product is being used,
 * ANGAZA_LIBRARY_INCLUDE_CABLE should be defined.
 */
#ifndef __ANGAZA_CUSTOM_CONFIG_H__
#define __ANGAZA_CUSTOM_CONFIG_H__

//fixed constants; do not override
#define ANGAZA_KEYCODE_PROTOCOL_FULL 1
#define ANGAZA_KEYCODE_PROTOCOL_SMALL 2
#define ANGAZA_PAYG_FIRMWARE_ID 0x01
//end fixed constants section

// All parameters below are product specific; manufacturer to determine
// appropriate values based upon product.

/** Set to '1' if keypad or IR PAYG communications are present
 */
#define ANGAZA_LIBRARY_INCLUDE_KEYPAD 1
/** Set to '1' if IR (infrared) PAYG communications are present
 */
#define ANGAZA_LIBRARY_INCLUDE_IR 0
/** Set to '1' if cable-based PAYG communications are present
 */
#define ANGAZA_LIBRARY_INCLUDE_CABLE 1

#if ANGAZA_LIBRARY_INCLUDE_KEYPAD
/**If a keypad is being used, define the alphabet used by the keypad.
 * (ANGAZA_KEYCODE_PROTOCOL_FULL or ANGAZA_KEYCODE_PROTOCOL_SMALL)
 */
    #define ANGAZA_KEYCODE_PROTOCOL ANGAZA_KEYCODE_PROTOCOL_SMALL
#endif

/** Maximum number of bytes provided for `prod_diag_get_data` `data_bytes`.
 *
 * When product code calls `prod_diag_get_data`, the data which it populates
 * in the `data_bytes` buffer must not exceed this value.
 * Default 24 Bytes.  Maximum 127 bytes.
 * ANGAZA_MAX_PROD_DIAG_DATA_SIZE_BYTES must be greater than or equal to
 * the largest 'Priority Block' of data implemented by this product.
 *
 * \warning This number of bytes is allocated on the stack.
 */
#define ANGAZA_PROD_DIAG_MAX_DATA_SIZE_BYTES 24

/** Keycode defaults, if used.  START_CHAR begins a keycode,
 * END_CHAR ends a keycode, and KEYCODE_ALPHABET is the list of valid
 * keys that are not start or end characters.
 */
#if ANGAZA_KEYCODE_PROTOCOL==ANGAZA_KEYCODE_PROTOCOL_FULL
    #define ANGAZA_DEFAULT_KEYCODE_START_CHAR '*'
    #define ANGAZA_DEFAULT_KEYCODE_END_CHAR '#'
    #define ANGAZA_DEFAULT_KEYCODE_ALPHABET "0123456789" // does not include start and end symbols
#else
    #define ANGAZA_DEFAULT_KEYCODE_START_CHAR '1'
    #define ANGAZA_DEFAULT_KEYCODE_END_CHAR '!'
    #define ANGAZA_DEFAULT_KEYCODE_ALPHABET "2345" // does not include start and end symbols
#endif

// ANGAZA_KEYCODE_NOT_RATE_LIMITED can be defined to disable rate limiting during development

/** Low-credit threshold.  Typically defined in seconds, as two calendar days.
 */
#define ANGAZA_DEFAULT_LOW_CREDIT_THRESHOLD (2 * 24 * 3600)

/** PAYG Manufacturer ID, assigned by Angaza. 0xFF is "undefined".
 */
#define ANGAZA_PAYG_MANUFACTURER_ID 0x00

/** PAYG Product ID, assigned by Angaza. 0xFF is "undefined".
 */
#define ANGAZA_PAYG_PRODUCT_ID 0x0001

/** Manufacturer-defined integrated product firmware ID.  0x00 if unused.
 */
#define MANUFACTURER_PROD_FIRMWARE_ID 0x00

#endif
