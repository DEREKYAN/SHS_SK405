
#ifndef zcff52f35cb
#define zcff52f35cb
#ifndef z8e1516dce7
#define z8e1516dce7
#include <stdint.h>
#include <stdbool.h>
#include "angaza/config.h"
struct z1b13cb8355{uint8_t*data;uint16_t za97986366b;uint16_t z1b0920160b;uint16_t zfe9100a4d5;};void z6786d67f82(struct
 z1b13cb8355*zf4cb8b6d85,void*z99d100e6ed,uint16_t za97986366b,uint16_t z1b0920160b);static inline uint16_t ze22d465f94(
const struct z1b13cb8355*z74e6656378){return z74e6656378->z1b0920160b;}static inline const uint8_t*z624613859f(const 
struct z1b13cb8355*z74e6656378){return z74e6656378->data;}static inline uint16_t z16a1c88212(const struct z1b13cb8355*
z74e6656378){return z74e6656378->z1b0920160b;}static inline void z8906624378(struct z1b13cb8355*z74e6656378,uint16_t 
zfe9100a4d5){ANGAZA_ASSERT(zfe9100a4d5<=z74e6656378->z1b0920160b,
"\x70\x6f\x73\x69\x74\x69\x6f\x6e\x20\x6f\x75\x74\x20\x6f\x66\x20\x72\x61\x6e\x67\x65");z74e6656378->zfe9100a4d5=
zfe9100a4d5;}void z065a26b842(struct z1b13cb8355*z74e6656378,bool z2271b701d3);void z365bf70760(struct z1b13cb8355*
zf4cb8b6d85,uint8_t data,uint8_t z20a76dd807);bool z640f640f9e(struct z1b13cb8355*z74e6656378);uint8_t za73424de57(
struct z1b13cb8355*zf4cb8b6d85,uint8_t z20a76dd807);uint16_t zf2f51e5f3e(struct z1b13cb8355*zf4cb8b6d85,uint16_t 
z20a76dd807);struct zb67573ef41{const char*zdddcb7b2a7;uint16_t za97986366b;uint16_t z1b0920160b;uint16_t zfe9100a4d5;};
void z64165e61c2(struct zb67573ef41*zf24083af1c,const char*zdddcb7b2a7,uint16_t z1b0920160b);uint16_t zb8218113d3(const 
struct zb67573ef41*zf24083af1c);uint16_t z2e20d85074(const struct zb67573ef41*zf24083af1c);uint16_t zc2036ed302(const 
struct zb67573ef41*zf24083af1c);uint8_t zfe57514e4c(struct zb67573ef41*zf24083af1c,uint8_t count);uint16_t zc0ebd1fee3(
struct zb67573ef41*zf24083af1c,uint8_t count);uint32_t zd3ebf43594(struct zb67573ef41*zf24083af1c,uint8_t count);
uint32_t z507a1af07b(struct zb67573ef41*zf24083af1c,uint8_t count,bool*z059d0babaa);struct zb76bf3e611{uint8_t*
z99d100e6ed;uint8_t z9a01099768;};void z8671bdb0b7(struct zb76bf3e611*z8ab80f1355,uint8_t*z99d100e6ed,uint8_t 
z9a01099768);void zd0bb34864a(struct zb76bf3e611*z8ab80f1355,uint16_t z272d53e6a2);void z9ca5833747(struct zb76bf3e611*
z8ab80f1355,uint16_t z272d53e6a2);bool zd4d38c4135(const struct zb76bf3e611*z8ab80f1355,uint16_t z272d53e6a2);void 
z8644bc3e61(struct zb76bf3e611*z8ab80f1355);struct z4d335faab1{uint8_t z99d100e6ed[(0xb57+589-0xd94)];};struct 
z2991aa66f2{uint8_t z99d100e6ed[(0x10bb+5541-0x2658)];};struct z2991aa66f2 z1b82a670fc(const struct z4d335faab1*key,
const void*data,uint16_t data_size);void z844f2a9dbe(const struct z4d335faab1*key,const void*zd5753f6c49,uint16_t 
z65c78f7747,void*z2f95e13be5,uint16_t ze12ce6b9ca);uint64_t z38e71292f7(const struct z2991aa66f2*value);static inline 
uint16_t zcddc7faa45(uint16_t z2bf3f1cf4d){uint16_t zacea26b15c;uint8_t*z99d100e6ed=(uint8_t*)&zacea26b15c;z99d100e6ed[
(0xa6f+5306-0x1f29)]=z2bf3f1cf4d>>(0x745+1952-0xedd);z99d100e6ed[(0x1164+508-0x135f)]=z2bf3f1cf4d&(0x1d9f+2390-0x25f6);
return zacea26b15c;}static inline uint16_t z020f7db9be(uint16_t zacea26b15c){uint8_t*z99d100e6ed=(uint8_t*)&zacea26b15c;
return(((uint16_t)(z99d100e6ed[(0x1042+4018-0x1ff4)]))<<(0x161+5109-0x154e))|z99d100e6ed[(0xb0a+3638-0x193f)];}
#endif
#ifndef __ANGAZA__CONFIG_DEFAULTS_H__
#define __ANGAZA__CONFIG_DEFAULTS_H__
#include "angaza_custom_config.h" 
#if defined(__GNUC__)
#define ANGAZA_PACKED_STRUCT struct __attribute__((packed))
#define ANGAZA_PACKED_UNION union __attribute__((packed))
#elif defined(__IAR_SYSTEMS_ICC__)
#define ANGAZA_PACKED_STRUCT __packed struct
#define ANGAZA_PACKED_UNION __packed union
#else
#ifndef ANGAZA_PACKED_STRUCT
#error "Unrecognized compiler. Defaults unavailable. Please define ANGAZA_PACKED_STRUCT."
#endif
#ifndef ANGAZA_PACKED_UNION
#error "Unrecognized compiler. Defaults unavailable. Please define ANGAZA_PACKED_UNION."
#endif
#endif
#ifndef ANGAZA_STATIC_ASSERT
#if __STDC_VERSION__ >= 201112L
#define ANGAZA_STATIC_ASSERT(b, m) _Static_assert(b, m)
#else
#define ANGAZA_STATIC_ASSERT(b, m)
#endif
#endif
#ifndef ANGAZA_ASSERT
#ifdef ANGAZA_USE_DEFAULT_ASSERT 
#include <assert.h>
#define ANGAZA_ASSERT(b, m) assert(b)
#else
#define ANGAZA_ASSERT(b, m)
#endif
#endif
#define ANGAZA_SECONDS_IN_HOUR (0x18e8+4082-0x1aca)
#define ANGAZA_HOURS_IN_DAY (0xfb9+155-0x103c)
#define ANGAZA_SECONDS_IN_DAY (ANGAZA_SECONDS_IN_HOUR * ANGAZA_HOURS_IN_DAY)
#ifndef ANGAZA_DEFAULT_LOW_CREDIT_THRESHOLD
#define ANGAZA_DEFAULT_LOW_CREDIT_THRESHOLD ((0x1541+3669-0x2394) * ANGAZA_SECONDS_IN_DAY)
#endif
#ifndef ANGAZA_LIBRARY_INCLUDE_KEYPAD
#define ANGAZA_LIBRARY_INCLUDE_KEYPAD (0x158d+2211-0x1e2f) 
#endif
#ifndef ANGAZA_LIBRARY_INCLUDE_CABLE
#define ANGAZA_LIBRARY_INCLUDE_CABLE (0x1405+1322-0x192e)
#endif
#ifndef ANGAZA_LIBRARY_INCLUDE_IR
#define ANGAZA_LIBRARY_INCLUDE_IR (0x16a8+3462-0x242e)
#endif
#ifndef ANGAZA_KEYCODE_PROTOCOL
#define ANGAZA_KEYCODE_PROTOCOL ANGAZA_KEYCODE_PROTOCOL_SMALL
#endif
#ifndef ANGAZA_DEFAULT_KEYCODE_START_CHAR
#if ANGAZA_KEYCODE_PROTOCOL==ANGAZA_KEYCODE_PROTOCOL_SMALL
#define ANGAZA_DEFAULT_KEYCODE_START_CHAR ((char)(0x457+2596-0xe46))
#else
#define ANGAZA_DEFAULT_KEYCODE_START_CHAR ((char)(0x11f1+3068-0x1dc3))
#endif
#endif
#ifndef ANGAZA_DEFAULT_KEYCODE_END_CHAR
#if ANGAZA_KEYCODE_PROTOCOL==ANGAZA_KEYCODE_PROTOCOL_SMALL
#define ANGAZA_DEFAULT_KEYCODE_END_CHAR ((char)(0xa84+5143-0x1e7a))
#else
#define ANGAZA_DEFAULT_KEYCODE_END_CHAR ((char)(0x969+6118-0x212c))
#endif
#endif
#ifndef ANGAZA_DEFAULT_KEYCODE_ALPHABET
#if ANGAZA_KEYCODE_PROTOCOL==ANGAZA_KEYCODE_PROTOCOL_SMALL
#define ANGAZA_DEFAULT_KEYCODE_ALPHABET "\x31\x32\x33\x34" 
#else
#define ANGAZA_DEFAULT_KEYCODE_ALPHABET "\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39"
#endif
#endif
#ifndef ANGAZA_DEFAULT_KEYCODE_TIMEOUT
#define ANGAZA_DEFAULT_KEYCODE_TIMEOUT (0xecb+1225-0x1384)
#endif
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
extern const struct z4d335faab1 z6d5a43b8b0;extern const struct z4d335faab1 zd11d3d22f1;extern const uint32_t 
zdb7c7920ef;void z298f1a3407(void);static inline void z1a20bd9908(void){}uint32_t zfbd8489fdf(void);struct z4d335faab1 
z08cb6f63d6(void);void za2fa47d1c8(uint32_t z7f789751c5,const struct z4d335faab1*z23dd9c5ec7);static inline uint16_t 
zccf927d73f(void){return(uint16_t)ANGAZA_PAYG_FIRMWARE_ID<<(0x149a+1654-0x1b08)|MANUFACTURER_PROD_FIRMWARE_ID;}
#endif
#ifndef z6913fc1a45
#define z6913fc1a45
#include "angaza/payg_nv_block.h"
#ifndef z8e1516dce7
#define z8e1516dce7
#include <stdint.h>
#include <stdbool.h>
#include "angaza/config.h"
struct z1b13cb8355{uint8_t*data;uint16_t za97986366b;uint16_t z1b0920160b;uint16_t zfe9100a4d5;};void z6786d67f82(struct
 z1b13cb8355*zf4cb8b6d85,void*z99d100e6ed,uint16_t za97986366b,uint16_t z1b0920160b);static inline uint16_t ze22d465f94(
const struct z1b13cb8355*z74e6656378){return z74e6656378->z1b0920160b;}static inline const uint8_t*z624613859f(const 
struct z1b13cb8355*z74e6656378){return z74e6656378->data;}static inline uint16_t z16a1c88212(const struct z1b13cb8355*
z74e6656378){return z74e6656378->z1b0920160b;}static inline void z8906624378(struct z1b13cb8355*z74e6656378,uint16_t 
zfe9100a4d5){ANGAZA_ASSERT(zfe9100a4d5<=z74e6656378->z1b0920160b,"position out of range");z74e6656378->zfe9100a4d5=
zfe9100a4d5;}void z065a26b842(struct z1b13cb8355*z74e6656378,bool z2271b701d3);void z365bf70760(struct z1b13cb8355*
zf4cb8b6d85,uint8_t data,uint8_t z20a76dd807);bool z640f640f9e(struct z1b13cb8355*z74e6656378);uint8_t za73424de57(
struct z1b13cb8355*zf4cb8b6d85,uint8_t z20a76dd807);uint16_t zf2f51e5f3e(struct z1b13cb8355*zf4cb8b6d85,uint16_t 
z20a76dd807);struct zb67573ef41{const char*zdddcb7b2a7;uint16_t za97986366b;uint16_t z1b0920160b;uint16_t zfe9100a4d5;};
void z64165e61c2(struct zb67573ef41*zf24083af1c,const char*zdddcb7b2a7,uint16_t z1b0920160b);uint16_t zb8218113d3(const 
struct zb67573ef41*zf24083af1c);uint16_t z2e20d85074(const struct zb67573ef41*zf24083af1c);uint16_t zc2036ed302(const 
struct zb67573ef41*zf24083af1c);uint8_t zfe57514e4c(struct zb67573ef41*zf24083af1c,uint8_t count);uint16_t zc0ebd1fee3(
struct zb67573ef41*zf24083af1c,uint8_t count);uint32_t zd3ebf43594(struct zb67573ef41*zf24083af1c,uint8_t count);
uint32_t z507a1af07b(struct zb67573ef41*zf24083af1c,uint8_t count,bool*z059d0babaa);struct zb76bf3e611{uint8_t*
z99d100e6ed;uint8_t z9a01099768;};void z8671bdb0b7(struct zb76bf3e611*z8ab80f1355,uint8_t*z99d100e6ed,uint8_t 
z9a01099768);void zd0bb34864a(struct zb76bf3e611*z8ab80f1355,uint16_t z272d53e6a2);void z9ca5833747(struct zb76bf3e611*
z8ab80f1355,uint16_t z272d53e6a2);bool zd4d38c4135(const struct zb76bf3e611*z8ab80f1355,uint16_t z272d53e6a2);void 
z8644bc3e61(struct zb76bf3e611*z8ab80f1355);struct z4d335faab1{uint8_t z99d100e6ed[(0x812+5503-0x1d81)];};struct 
z2991aa66f2{uint8_t z99d100e6ed[(0x560+2280-0xe40)];};struct z2991aa66f2 z1b82a670fc(const struct z4d335faab1*key,const 
void*data,uint16_t data_size);void z844f2a9dbe(const struct z4d335faab1*key,const void*zd5753f6c49,uint16_t z65c78f7747,
void*z2f95e13be5,uint16_t ze12ce6b9ca);uint64_t z38e71292f7(const struct z2991aa66f2*value);static inline uint16_t 
zcddc7faa45(uint16_t z2bf3f1cf4d){uint16_t zacea26b15c;uint8_t*z99d100e6ed=(uint8_t*)&zacea26b15c;z99d100e6ed[
(0x225+3494-0xfcb)]=z2bf3f1cf4d>>(0x60+8111-0x2007);z99d100e6ed[(0x192d+1665-0x1fad)]=z2bf3f1cf4d&(0x94c+4638-0x1a6b);
return zacea26b15c;}static inline uint16_t z020f7db9be(uint16_t zacea26b15c){uint8_t*z99d100e6ed=(uint8_t*)&zacea26b15c;
return(((uint16_t)(z99d100e6ed[(0x917+4996-0x1c9b)]))<<(0x1760+3757-0x2605))|z99d100e6ed[(0x74f+1538-0xd50)];}
#endif
#ifndef zcff52f35cb
#define zcff52f35cb
#ifndef z8e1516dce7
#define z8e1516dce7
#include <stdint.h>
#include <stdbool.h>
#include "angaza/config.h"
struct z1b13cb8355{uint8_t*data;uint16_t za97986366b;uint16_t z1b0920160b;uint16_t zfe9100a4d5;};void z6786d67f82(struct
 z1b13cb8355*zf4cb8b6d85,void*z99d100e6ed,uint16_t za97986366b,uint16_t z1b0920160b);static inline uint16_t ze22d465f94(
const struct z1b13cb8355*z74e6656378){return z74e6656378->z1b0920160b;}static inline const uint8_t*z624613859f(const 
struct z1b13cb8355*z74e6656378){return z74e6656378->data;}static inline uint16_t z16a1c88212(const struct z1b13cb8355*
z74e6656378){return z74e6656378->z1b0920160b;}static inline void z8906624378(struct z1b13cb8355*z74e6656378,uint16_t 
zfe9100a4d5){ANGAZA_ASSERT(zfe9100a4d5<=z74e6656378->z1b0920160b,
"\x70\x6f\x73\x69\x74\x69\x6f\x6e\x20\x6f\x75\x74\x20\x6f\x66\x20\x72\x61\x6e\x67\x65");z74e6656378->zfe9100a4d5=
zfe9100a4d5;}void z065a26b842(struct z1b13cb8355*z74e6656378,bool z2271b701d3);void z365bf70760(struct z1b13cb8355*
zf4cb8b6d85,uint8_t data,uint8_t z20a76dd807);bool z640f640f9e(struct z1b13cb8355*z74e6656378);uint8_t za73424de57(
struct z1b13cb8355*zf4cb8b6d85,uint8_t z20a76dd807);uint16_t zf2f51e5f3e(struct z1b13cb8355*zf4cb8b6d85,uint16_t 
z20a76dd807);struct zb67573ef41{const char*zdddcb7b2a7;uint16_t za97986366b;uint16_t z1b0920160b;uint16_t zfe9100a4d5;};
void z64165e61c2(struct zb67573ef41*zf24083af1c,const char*zdddcb7b2a7,uint16_t z1b0920160b);uint16_t zb8218113d3(const 
struct zb67573ef41*zf24083af1c);uint16_t z2e20d85074(const struct zb67573ef41*zf24083af1c);uint16_t zc2036ed302(const 
struct zb67573ef41*zf24083af1c);uint8_t zfe57514e4c(struct zb67573ef41*zf24083af1c,uint8_t count);uint16_t zc0ebd1fee3(
struct zb67573ef41*zf24083af1c,uint8_t count);uint32_t zd3ebf43594(struct zb67573ef41*zf24083af1c,uint8_t count);
uint32_t z507a1af07b(struct zb67573ef41*zf24083af1c,uint8_t count,bool*z059d0babaa);struct zb76bf3e611{uint8_t*
z99d100e6ed;uint8_t z9a01099768;};void z8671bdb0b7(struct zb76bf3e611*z8ab80f1355,uint8_t*z99d100e6ed,uint8_t 
z9a01099768);void zd0bb34864a(struct zb76bf3e611*z8ab80f1355,uint16_t z272d53e6a2);void z9ca5833747(struct zb76bf3e611*
z8ab80f1355,uint16_t z272d53e6a2);bool zd4d38c4135(const struct zb76bf3e611*z8ab80f1355,uint16_t z272d53e6a2);void 
z8644bc3e61(struct zb76bf3e611*z8ab80f1355);struct z4d335faab1{uint8_t z99d100e6ed[(0x3a7+6887-0x1e7e)];};struct 
z2991aa66f2{uint8_t z99d100e6ed[(0x1435+1159-0x18b4)];};struct z2991aa66f2 z1b82a670fc(const struct z4d335faab1*key,
const void*data,uint16_t data_size);void z844f2a9dbe(const struct z4d335faab1*key,const void*zd5753f6c49,uint16_t 
z65c78f7747,void*z2f95e13be5,uint16_t ze12ce6b9ca);uint64_t z38e71292f7(const struct z2991aa66f2*value);static inline 
uint16_t zcddc7faa45(uint16_t z2bf3f1cf4d){uint16_t zacea26b15c;uint8_t*z99d100e6ed=(uint8_t*)&zacea26b15c;z99d100e6ed[
(0x217b+650-0x2405)]=z2bf3f1cf4d>>(0x9a9+5320-0x1e69);z99d100e6ed[(0xb32+1623-0x1188)]=z2bf3f1cf4d&(0x1745+4058-0x2620);
return zacea26b15c;}static inline uint16_t z020f7db9be(uint16_t zacea26b15c){uint8_t*z99d100e6ed=(uint8_t*)&zacea26b15c;
return(((uint16_t)(z99d100e6ed[(0x1029+4372-0x213d)]))<<(0x3cd+9009-0x26f6))|z99d100e6ed[(0xa3c+6869-0x2510)];}
#endif
#ifndef __ANGAZA__CONFIG_DEFAULTS_H__
#define __ANGAZA__CONFIG_DEFAULTS_H__
#include "angaza_custom_config.h" 
#if defined(__GNUC__)
#define ANGAZA_PACKED_STRUCT struct __attribute__((packed))
#define ANGAZA_PACKED_UNION union __attribute__((packed))
#elif defined(__IAR_SYSTEMS_ICC__)
#define ANGAZA_PACKED_STRUCT __packed struct
#define ANGAZA_PACKED_UNION __packed union
#else
#ifndef ANGAZA_PACKED_STRUCT
#error "Unrecognized compiler. Defaults unavailable. Please define ANGAZA_PACKED_STRUCT."
#endif
#ifndef ANGAZA_PACKED_UNION
#error "Unrecognized compiler. Defaults unavailable. Please define ANGAZA_PACKED_UNION."
#endif
#endif
#ifndef ANGAZA_STATIC_ASSERT
#if __STDC_VERSION__ >= 201112L
#define ANGAZA_STATIC_ASSERT(b, m) _Static_assert(b, m)
#else
#define ANGAZA_STATIC_ASSERT(b, m)
#endif
#endif
#ifndef ANGAZA_ASSERT
#ifdef ANGAZA_USE_DEFAULT_ASSERT 
#include <assert.h>
#define ANGAZA_ASSERT(b, m) assert(b)
#else
#define ANGAZA_ASSERT(b, m)
#endif
#endif
#define ANGAZA_SECONDS_IN_HOUR (0x1399+3843-0x148c)
#define ANGAZA_HOURS_IN_DAY (0xa4d+3958-0x19ab)
#define ANGAZA_SECONDS_IN_DAY (ANGAZA_SECONDS_IN_HOUR * ANGAZA_HOURS_IN_DAY)
#ifndef ANGAZA_DEFAULT_LOW_CREDIT_THRESHOLD
#define ANGAZA_DEFAULT_LOW_CREDIT_THRESHOLD ((0xfb5+2053-0x17b8) * ANGAZA_SECONDS_IN_DAY)
#endif
#ifndef ANGAZA_LIBRARY_INCLUDE_KEYPAD
#define ANGAZA_LIBRARY_INCLUDE_KEYPAD (0xf57+1837-0x1683) 
#endif
#ifndef ANGAZA_LIBRARY_INCLUDE_CABLE
#define ANGAZA_LIBRARY_INCLUDE_CABLE (0x8e7+505-0xadf)
#endif
#ifndef ANGAZA_LIBRARY_INCLUDE_IR
#define ANGAZA_LIBRARY_INCLUDE_IR (0x5f9+504-0x7f1)
#endif
#ifndef ANGAZA_KEYCODE_PROTOCOL
#define ANGAZA_KEYCODE_PROTOCOL ANGAZA_KEYCODE_PROTOCOL_SMALL
#endif
#ifndef ANGAZA_DEFAULT_KEYCODE_START_CHAR
#if ANGAZA_KEYCODE_PROTOCOL==ANGAZA_KEYCODE_PROTOCOL_SMALL
#define ANGAZA_DEFAULT_KEYCODE_START_CHAR ((char)(0x573+6854-0x2004))
#else
#define ANGAZA_DEFAULT_KEYCODE_START_CHAR ((char)(0x3fc+6778-0x1e4c))
#endif
#endif
#ifndef ANGAZA_DEFAULT_KEYCODE_END_CHAR
#if ANGAZA_KEYCODE_PROTOCOL==ANGAZA_KEYCODE_PROTOCOL_SMALL
#define ANGAZA_DEFAULT_KEYCODE_END_CHAR ((char)(0x15c7+2758-0x206c))
#else
#define ANGAZA_DEFAULT_KEYCODE_END_CHAR ((char)(0x27d+6535-0x1be1))
#endif
#endif
#ifndef ANGAZA_DEFAULT_KEYCODE_ALPHABET
#if ANGAZA_KEYCODE_PROTOCOL==ANGAZA_KEYCODE_PROTOCOL_SMALL
#define ANGAZA_DEFAULT_KEYCODE_ALPHABET "\x31\x32\x33\x34" 
#else
#define ANGAZA_DEFAULT_KEYCODE_ALPHABET "\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39"
#endif
#endif
#ifndef ANGAZA_DEFAULT_KEYCODE_TIMEOUT
#define ANGAZA_DEFAULT_KEYCODE_TIMEOUT (0xadc+3690-0x1936)
#endif
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
extern const struct z4d335faab1 z6d5a43b8b0;extern const struct z4d335faab1 zd11d3d22f1;extern const uint32_t 
zdb7c7920ef;void z298f1a3407(void);static inline void z1a20bd9908(void){}uint32_t zfbd8489fdf(void);struct z4d335faab1 
z08cb6f63d6(void);void za2fa47d1c8(uint32_t z7f789751c5,const struct z4d335faab1*z23dd9c5ec7);static inline uint16_t 
zccf927d73f(void){return(uint16_t)ANGAZA_PAYG_FIRMWARE_ID<<(0xdef+4386-0x1f09)|MANUFACTURER_PROD_FIRMWARE_ID;}
#endif
struct za4b28ee7b9{uint8_t z99d100e6ed[(0x1ceb+1637-0x234b)];};enum payg_nv_block_id{zf8055f3fc9=(0x1f30+1577-0x2559),
z44fc441733=(0x22d1+519-0x24d7),z5d07ee0179=(0x1895+706-0x1b55),z708da52d20=(0x1ab9+2772-0x258a),z1153d8fc37=
(0xd21+2086-0x1543),z0ae15748f0=(0x1958+2147-0x21b6),z9a1be04e05=(0x1b6b+2930-0x26d7),z96747f25f4=(0xbb+630-0x32a),
z77158136eb=(0xdf7+2728-0x1897),zff4ce0d5d8=(0x5ea+6741-0x2036),zee1b728de3=(0xca1+1197-0x1144),z5432539b70=
(0x434+797-0x746),za63eaf1e19=(0x1870+1871-0x1fb3),z54c8b36582=(0x15bd+159-0x164f),z95d833a190=(0x168c+1810-0x1d90),
zf054aab66f=(0x782+4180-0x17c7),};bool z9066c6d9e0(enum payg_nv_block_id z2a31d25b5c,void*data,const uint8_t data_size);
void z88df969180(enum payg_nv_block_id block_id,const void*data,const uint8_t data_size);struct payg_nv_block 
z453fb2f328(const enum payg_nv_block_id block_id,const struct za4b28ee7b9*data);struct z2991aa66f2 z2e8ff023b4(const 
struct payg_nv_block*block);
#endif
#include "angaza/config.h"
#include <string.h>
static ANGAZA_PACKED_STRUCT{struct z4d335faab1 z23dd9c5ec7;uint32_t z7f789751c5;}zfe17c7b0b1;const struct z4d335faab1 
z6d5a43b8b0={{(0x7eb+3787-0x16b6),(0x1c72+682-0x1f1c),(0x134+2457-0xacd),(0x1303+4666-0x253d),(0x9b4+2137-0x120d),
(0xf07+5154-0x2329),(0x704+4884-0x1a18),(0x6a+5265-0x14fb),(0x783+6276-0x2007),(0xc0+1691-0x75b),(0x900+7260-0x255c),
(0x44f+5359-0x193e),(0x1678+1159-0x1aff),(0x921+525-0xb2e),(0x380+4358-0x1486),(0xec3+200-0xf8b)}};const struct 
z4d335faab1 zd11d3d22f1={{(0x76f+5382-0x1b76),(0x21b7+1496-0x2690),(0x12b9+3136-0x1dfa),(0x17a6+2742-0x215d),
(0x152+4133-0x1078),(0x670+2938-0x10eb),(0x3f1+8387-0x23b5),(0xfef+4329-0x1fd9),(0x1b9d+2242-0x2360),
(0x179d+1711-0x1d4d),(0x1f0c+1424-0x239d),(0x830+2133-0xf86),(0x1168+4228-0x20ed),(0x66a+4167-0x15b2),(0x7e6+1362-0xc39)
,(0x704+5873-0x1cf6)}};const uint32_t zdb7c7920ef=4294967295;ANGAZA_STATIC_ASSERT(sizeof(zfe17c7b0b1)%sizeof(struct 
za4b28ee7b9)==(0x2205+925-0x25a2),"struct size not a multiple of block size");void z298f1a3407(void){memcpy(zfe17c7b0b1.
z23dd9c5ec7.z99d100e6ed,zd11d3d22f1.z99d100e6ed,sizeof(zfe17c7b0b1.z23dd9c5ec7.z99d100e6ed));zfe17c7b0b1.z7f789751c5=
zdb7c7920ef;z9066c6d9e0(zf8055f3fc9,&zfe17c7b0b1,sizeof(zfe17c7b0b1));}uint32_t zfbd8489fdf(void){return zfe17c7b0b1.
z7f789751c5;}struct z4d335faab1 z08cb6f63d6(void){return zfe17c7b0b1.z23dd9c5ec7;}void za2fa47d1c8(const uint32_t 
z7f789751c5,const struct z4d335faab1*z23dd9c5ec7){zfe17c7b0b1.z7f789751c5=z7f789751c5;zfe17c7b0b1.z23dd9c5ec7=*
z23dd9c5ec7;z88df969180(zf8055f3fc9,&zfe17c7b0b1,sizeof(zfe17c7b0b1));}
