// This file should not be modified.
// Modify or replace "angaza_config.h" instead to replace specific definitions.

#ifndef __ANGAZA__CONFIG_DEFAULTS_H__
#define __ANGAZA__CONFIG_DEFAULTS_H__

#include "angaza_custom_config.h" // user-specified configuration

//
// COMPILER-SPECIFIC MACROS
//

// GNU gcc?
#if defined(__GNUC__)
    #define ANGAZA_PACKED_STRUCT struct __attribute__((packed))
    #define ANGAZA_PACKED_UNION union __attribute__((packed))
// IAR ICC?
#elif defined(__IAR_SYSTEMS_ICC__)
    #define ANGAZA_PACKED_STRUCT __packed struct
    #define ANGAZA_PACKED_UNION __packed union
// something else?
#else
    #ifndef ANGAZA_PACKED_STRUCT
        #error "Unrecognized compiler. Defaults unavailable. Please define ANGAZA_PACKED_STRUCT."
    #endif
    #ifndef ANGAZA_PACKED_UNION
        #error "Unrecognized compiler. Defaults unavailable. Please define ANGAZA_PACKED_UNION."
    #endif
#endif

//
// DEBUG MACROS
//

// use static asserts by default only under c11 and above
#ifndef ANGAZA_STATIC_ASSERT
    #if __STDC_VERSION__ >= 201112L
        #define ANGAZA_STATIC_ASSERT(b, m) _Static_assert(b, m)
    #else
        #define ANGAZA_STATIC_ASSERT(b, m)
    #endif
#endif

// do not use runtime asserts by default
#ifndef ANGAZA_ASSERT
    #ifdef ANGAZA_USE_DEFAULT_ASSERT // typically defined only during unit tests
        #include <assert.h>
        #define ANGAZA_ASSERT(b, m) assert(b)
    #else
        #define ANGAZA_ASSERT(b, m)
    #endif
#endif

//
// STATE DEFAULTS
//

// define basic time parameters
//
#define ANGAZA_SECONDS_IN_HOUR 3600
#define ANGAZA_HOURS_IN_DAY 24
#define ANGAZA_SECONDS_IN_DAY (ANGAZA_SECONDS_IN_HOUR * ANGAZA_HOURS_IN_DAY)

// by default assume calendar-time credit and use two days
#ifndef ANGAZA_DEFAULT_LOW_CREDIT_THRESHOLD
    #define ANGAZA_DEFAULT_LOW_CREDIT_THRESHOLD (2 * ANGAZA_SECONDS_IN_DAY)
#endif

//
// DATA CHANNELS ENABLED
//

#ifndef ANGAZA_LIBRARY_INCLUDE_KEYPAD
    #define ANGAZA_LIBRARY_INCLUDE_KEYPAD 1 // must be 1 if IR support is included
#endif

#ifndef ANGAZA_LIBRARY_INCLUDE_CABLE
    #define ANGAZA_LIBRARY_INCLUDE_CABLE 1
#endif

#ifndef ANGAZA_LIBRARY_INCLUDE_IR
    #define ANGAZA_LIBRARY_INCLUDE_IR 0
#endif

//
// KEYCODE DEFAULTS
//

// by default assume a small-keypad protocol on a "12345" keypad
#ifndef ANGAZA_KEYCODE_PROTOCOL
    #define ANGAZA_KEYCODE_PROTOCOL ANGAZA_KEYCODE_PROTOCOL_SMALL
#endif

#ifndef ANGAZA_DEFAULT_KEYCODE_START_CHAR
#if ANGAZA_KEYCODE_PROTOCOL==ANGAZA_KEYCODE_PROTOCOL_SMALL
    #define ANGAZA_DEFAULT_KEYCODE_START_CHAR '5'
#else
    #define ANGAZA_DEFAULT_KEYCODE_START_CHAR '*'
#endif
#endif

#ifndef ANGAZA_DEFAULT_KEYCODE_END_CHAR
#if ANGAZA_KEYCODE_PROTOCOL==ANGAZA_KEYCODE_PROTOCOL_SMALL
// Choose an impossible keycode for ending a smallpad message. Smallpad
// messages will end based on message length.
    #define ANGAZA_DEFAULT_KEYCODE_END_CHAR '!'
#else
    #define ANGAZA_DEFAULT_KEYCODE_END_CHAR '#'
#endif
#endif

#ifndef ANGAZA_DEFAULT_KEYCODE_ALPHABET
#if ANGAZA_KEYCODE_PROTOCOL==ANGAZA_KEYCODE_PROTOCOL_SMALL
    #define ANGAZA_DEFAULT_KEYCODE_ALPHABET "1234" // does not include start and end symbols
#else
    #define ANGAZA_DEFAULT_KEYCODE_ALPHABET "0123456789"
#endif
#endif

#ifndef ANGAZA_DEFAULT_KEYCODE_TIMEOUT
    #define ANGAZA_DEFAULT_KEYCODE_TIMEOUT 16
#endif

//
// OTHER CONFIGURATION CHECKS
//

#ifndef ANGAZA_PAYG_MANUFACTURER_ID
    #error "ANGAZA_PAYG_MANUFACTURER_ID must be defined."
#endif

#ifndef ANGAZA_PAYG_PRODUCT_ID
    #error "ANGAZA_PAYG_PRODUCT_ID must be defined."
#endif

#ifndef MANUFACTURER_PROD_FIRMWARE_ID
	#error "MANUFACTURER_PROD_FIRMWARE_ID must be defined."
#endif

#ifndef ANGAZA_PAYG_FIRMWARE_ID
	#error "ANGAZA_PAYG_FIRMWARE_ID must be defined."
#endif

#endif
