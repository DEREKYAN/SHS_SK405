
#ifndef z44e6f70797
#define z44e6f70797
#include "angaza/config.h"
#include "angaza/payg_all.h"
#ifndef z20fbe47bb0
#define z20fbe47bb0
#include "angaza/config.h"
#if ANGAZA_LIBRARY_INCLUDE_KEYPAD == (0xad8+5258-0x1f61)
#ifndef z42141cb1d4
#define z42141cb1d4
#include "angaza/config.h"
#if ANGAZA_LIBRARY_INCLUDE_KEYPAD == (0xe2a+1864-0x1571)
#include "angaza/prod_keypad.h"
#include <stdbool.h>
#include <stdint.h>
#define zbeb91cc9c2      (0x784+1690-0xd9e)
#define z1c4a635f01      (ANGAZA_SECONDS_IN_DAY / zbeb91cc9c2)
bool z9622a3c53f(const struct prod_keypad_key za033d43345,const struct prod_keypad_key z0f144c2120);void zad72251a8f(
uint32_t seconds_elapsed);bool zfb2d3e813b(void);void ze5ef1b9d78(void);
#define z3bc7e19dec (0x1059+2262-0x18ef)
#define zbd92582e81 UINT8_MAX
ANGAZA_PACKED_STRUCT z85a0b1642b{struct prod_keypad_key z9e974f8831[z3bc7e19dec];uint8_t z1b0920160b;};void zaadd37bee4(
struct z85a0b1642b*zf2e84cdb22,const char*z9e974f8831);struct z85a0b1642b zf3c4dde316(const char*z9e974f8831);void 
z30522e9f22(const struct z85a0b1642b*zf2e84cdb22,char*zdddcb7b2a7);typedef void(*z1986c2d6a8)(const struct z85a0b1642b*)
;void z482d238b89(const z1986c2d6a8 zd504fcbb7b);void zd0b62f0f62(void);uint32_t zd0c16cb767(uint32_t seconds_elapsed);
void z5bd3d5702a(void);void z99650ea82c(const struct prod_keypad_key key);void ze9c19e4038(void);void z93277c0ade(const 
struct prod_keypad_key z516d003588,const struct prod_keypad_key z70b0dce271,uint8_t z5f135a6a92);void zc607ae7036();
uint32_t z4f0ebd829a(uint32_t seconds_elapsed);void zb85ab16ded(const struct prod_keypad_key ze7d076848a);
#endif
#endif
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
z8644bc3e61(struct zb76bf3e611*z8ab80f1355);struct z4d335faab1{uint8_t z99d100e6ed[(0xb5+435-0x258)];};struct 
z2991aa66f2{uint8_t z99d100e6ed[(0x710+253-0x805)];};struct z2991aa66f2 z1b82a670fc(const struct z4d335faab1*key,const 
void*data,uint16_t data_size);void z844f2a9dbe(const struct z4d335faab1*key,const void*zd5753f6c49,uint16_t z65c78f7747,
void*z2f95e13be5,uint16_t ze12ce6b9ca);uint64_t z38e71292f7(const struct z2991aa66f2*value);static inline uint16_t 
zcddc7faa45(uint16_t z2bf3f1cf4d){uint16_t zacea26b15c;uint8_t*z99d100e6ed=(uint8_t*)&zacea26b15c;z99d100e6ed[
(0x1f92+1608-0x25da)]=z2bf3f1cf4d>>(0x839+1975-0xfe8);z99d100e6ed[(0x76f+4842-0x1a58)]=z2bf3f1cf4d&(0x1ecf+59-0x1e0b);
return zacea26b15c;}static inline uint16_t z020f7db9be(uint16_t zacea26b15c){uint8_t*z99d100e6ed=(uint8_t*)&zacea26b15c;
return(((uint16_t)(z99d100e6ed[(0xa8a+4544-0x1c4a)]))<<(0x5ed+2572-0xff1))|z99d100e6ed[(0x1a90+1608-0x20d7)];}
#endif
#include <stdint.h>
#define zd1ad6c043e (0x1b99+824-0x1ec3)
#if ANGAZA_KEYCODE_PROTOCOL == ANGAZA_KEYCODE_PROTOCOL_SMALL
#define z36794d7643 (0x4fd+4708-0x1751) 
#define zb020bccb17 (0x17b4+2790-0x221c)
#define z241f89364d (0x2c7+3714-0x10ca)
#define z69858c6f9a zd1ad6c043e
#elif ANGAZA_KEYCODE_PROTOCOL == ANGAZA_KEYCODE_PROTOCOL_FULL
#define z36794d7643 (0x25c+2417-0xbbd) 
#define z69858c6f9a zbd92582e81
#endif
enum z767fe83ae2{zf4c8d94422,z68d73e1aa7,z36b1aab054,zc71a48595e,};typedef enum z767fe83ae2(*z22f4f76219)(const struct 
z85a0b1642b*zf2e84cdb22);typedef void(*z9f5ffe457f)(const char*z51da0e89f4);void z27149b95f9(z22f4f76219 z35115b1365,
z9f5ffe457f ze0fc91c083,const char*z51da0e89f4);void zb0394eb662(void);void z5d6ee32217(const struct z85a0b1642b*
zf2e84cdb22);uint32_t zb6c3c68640(uint32_t seconds_elapsed);
#define z47ed6e9661 UINT16_MAX
ANGAZA_PACKED_STRUCT zf15f212fd1{uint8_t z0516684022;uint8_t zbc5656605b;};ANGAZA_PACKED_STRUCT zea9bc2f484{uint16_t 
z261242ee55;};ANGAZA_PACKED_UNION z4925e90716{struct zf15f212fd1 zb8be3299c1;struct zea9bc2f484 z588eb6c6f8;};
ANGAZA_PACKED_STRUCT z1a6b085d9b{uint8_t z83996b1809;union z4925e90716 z3c07c7db94;uint16_t z07c829a062;};enum 
zdcc0276c3d{z310d54e49d=(0x513+396-0x69f),zb907c3d280=(0x16b9+1002-0x1aa2),zc9eb6225dc=(0x5f8+8019-0x2549),};enum 
zd2763f3828{zb361beff3a=(0xbd1+2777-0x16aa),};void z35c1733bb2(const char*z51da0e89f4);bool zdec0c1ec14(const struct 
z85a0b1642b*zf2e84cdb22,struct z1a6b085d9b*z2a9b90236b);enum z767fe83ae2 zde5081fac6(const struct z1a6b085d9b*
z353bbb6e99);enum z767fe83ae2 z65599d88a1(const struct z85a0b1642b*zf2e84cdb22);uint16_t z1b796fa841(const struct 
z1a6b085d9b*z353bbb6e99,const struct z4d335faab1*key);enum zecace3a34a{zced3ef152a=(0xf60+2502-0x1926),zfa4cac4da2=
(0x496+171-0x540),z633c30fac4=(0x1763+4013-0x270e),};struct z47f37bd326{uint32_t zd4c4f8e622;};struct z8c6396fe6f{
uint32_t zd4c4f8e622;};enum z9c0ec497d1{z50c63eedff=(0xa40+2761-0x1509),ze21914623f=(0x1f9f+1178-0x2438),za107c4bc60=
(0x9e7+6566-0x238b),};struct z399cda6a12{enum z9c0ec497d1 z9450b175e4;};union z267fd60ff8{struct z47f37bd326 z269cf6a29d
;struct z8c6396fe6f zc2cfbc11ee;struct z399cda6a12 zf701e2f996;};struct z3824fbc5c6{enum zecace3a34a type;uint16_t 
z83996b1809;union z267fd60ff8 z3c07c7db94;};enum zfc0ad122e4{zd7605648d8=(0x781+2149-0xfe6),za6436d61e3=
(0x7bb+6645-0x21af),z4cf363935d=(0x1a46+2344-0x236c),z894b013606=(0x998+6634-0x237f),};struct z63041a2022{uint32_t 
ze1404276fc[(0x920+4128-0x193c)];uint32_t z7f789751c5;};enum zf690a1e111{z3738536ed0=(0x2f5+4934-0x163b),za0f14efb8e=
(0x1a30+2466-0x23d1),};struct z532a30d60e{enum zf690a1e111 z25d1355136;};union zaec9cceef5{struct z63041a2022 
z94356f2885;struct z532a30d60e zb4dba8d32d;};struct z3cad09ffa6{enum zfc0ad122e4 type;union zaec9cceef5 z3c07c7db94;};
enum z7d78ff9667{zeb7e21a12f,z57d3ac7de5,};union z0d5377e298{struct z3824fbc5c6 zb8be3299c1;struct z3cad09ffa6 
zc579cab8a3;};struct za13546c0c6{enum z7d78ff9667 zc0cb64693d;union z0d5377e298 z923f1b0559;uint32_t z07c829a062;};void 
zc82f30b4cc(const char*z51da0e89f4);enum z767fe83ae2 z478f868641(const struct z85a0b1642b*zf2e84cdb22);bool z0faee65746(
struct z85a0b1642b*zf2e84cdb22,struct za13546c0c6*z2a9b90236b);bool zffb40663dd(struct z85a0b1642b*zf2e84cdb22,struct 
za13546c0c6*z2a9b90236b);bool z69ea42bac0(struct z85a0b1642b*zf2e84cdb22,struct za13546c0c6*z2a9b90236b);enum 
z767fe83ae2 z99ab94ac7c(const struct z85a0b1642b*zf2e84cdb22,const struct za13546c0c6*z353bbb6e99);enum z767fe83ae2 
z3dbf69f9b2(const struct z3824fbc5c6*z353bbb6e99);enum z767fe83ae2 zc6ec253e52(const struct z3cad09ffa6*z353bbb6e99);
void ze0c6dc580c(struct z85a0b1642b*zf24083af1c);uint32_t z211be7c7d7(const struct z85a0b1642b*zf2e84cdb22,const struct 
z4d335faab1*key);bool z8ca3c13b26(const uint16_t z83996b1809);bool z320c52bc2a(const uint16_t z83996b1809,const bool 
z918f243ede);bool zdd280310a3(const uint16_t z83996b1809,const bool zc072325e69);void zc8588a29a9(void);
#endif
#endif
struct z28f13284db{
#if ANGAZA_LIBRARY_INCLUDE_KEYPAD
z22f4f76219 z35115b1365;z9f5ffe457f z20f1f63336;uint8_t z5f135a6a92;char z6f0cf0bf11;char zf930334ec1;const char*
za6fa5f8372;
#endif
};void za74b95daa3(const struct z28f13284db*z062d4060f6);
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
z8644bc3e61(struct zb76bf3e611*z8ab80f1355);struct z4d335faab1{uint8_t z99d100e6ed[(0x1e23+417-0x1fb4)];};struct 
z2991aa66f2{uint8_t z99d100e6ed[(0x988+2146-0x11e2)];};struct z2991aa66f2 z1b82a670fc(const struct z4d335faab1*key,const
 void*data,uint16_t data_size);void z844f2a9dbe(const struct z4d335faab1*key,const void*zd5753f6c49,uint16_t z65c78f7747
,void*z2f95e13be5,uint16_t ze12ce6b9ca);uint64_t z38e71292f7(const struct z2991aa66f2*value);static inline uint16_t 
zcddc7faa45(uint16_t z2bf3f1cf4d){uint16_t zacea26b15c;uint8_t*z99d100e6ed=(uint8_t*)&zacea26b15c;z99d100e6ed[
(0x22d+64-0x26d)]=z2bf3f1cf4d>>(0x13a3+3331-0x209e);z99d100e6ed[(0x1c57+1355-0x21a1)]=z2bf3f1cf4d&(0x67d+7712-0x239e);
return zacea26b15c;}static inline uint16_t z020f7db9be(uint16_t zacea26b15c){uint8_t*z99d100e6ed=(uint8_t*)&zacea26b15c;
return(((uint16_t)(z99d100e6ed[(0x943+7309-0x25d0)]))<<(0xf3+6839-0x1ba2))|z99d100e6ed[(0x16df+1966-0x1e8c)];}
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
#define ANGAZA_SECONDS_IN_HOUR (0xfaf+5901-0x18ac)
#define ANGAZA_HOURS_IN_DAY (0x1cc0+1695-0x2347)
#define ANGAZA_SECONDS_IN_DAY (ANGAZA_SECONDS_IN_HOUR * ANGAZA_HOURS_IN_DAY)
#ifndef ANGAZA_DEFAULT_LOW_CREDIT_THRESHOLD
#define ANGAZA_DEFAULT_LOW_CREDIT_THRESHOLD ((0x2c9+2851-0xdea) * ANGAZA_SECONDS_IN_DAY)
#endif
#ifndef ANGAZA_LIBRARY_INCLUDE_KEYPAD
#define ANGAZA_LIBRARY_INCLUDE_KEYPAD (0xd18+2203-0x15b2) 
#endif
#ifndef ANGAZA_LIBRARY_INCLUDE_CABLE
#define ANGAZA_LIBRARY_INCLUDE_CABLE (0x13fd+1484-0x19c8)
#endif
#ifndef ANGAZA_LIBRARY_INCLUDE_IR
#define ANGAZA_LIBRARY_INCLUDE_IR (0x645+3845-0x154a)
#endif
#ifndef ANGAZA_KEYCODE_PROTOCOL
#define ANGAZA_KEYCODE_PROTOCOL ANGAZA_KEYCODE_PROTOCOL_SMALL
#endif
#ifndef ANGAZA_DEFAULT_KEYCODE_START_CHAR
#if ANGAZA_KEYCODE_PROTOCOL==ANGAZA_KEYCODE_PROTOCOL_SMALL
#define ANGAZA_DEFAULT_KEYCODE_START_CHAR ((char)(0xb4a+973-0xee2))
#else
#define ANGAZA_DEFAULT_KEYCODE_START_CHAR ((char)(0xcfb+2084-0x14f5))
#endif
#endif
#ifndef ANGAZA_DEFAULT_KEYCODE_END_CHAR
#if ANGAZA_KEYCODE_PROTOCOL==ANGAZA_KEYCODE_PROTOCOL_SMALL
#define ANGAZA_DEFAULT_KEYCODE_END_CHAR ((char)(0x12b3+1173-0x1727))
#else
#define ANGAZA_DEFAULT_KEYCODE_END_CHAR ((char)(0x5c3+5676-0x1bcc))
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
#define ANGAZA_DEFAULT_KEYCODE_TIMEOUT (0x69+4951-0x13b0)
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
zccf927d73f(void){return(uint16_t)ANGAZA_PAYG_FIRMWARE_ID<<(0xc3b+1302-0x1149)|MANUFACTURER_PROD_FIRMWARE_ID;}
#endif
#ifndef z8270679e93
#define z8270679e93
#include "angaza/config.h"
#if ANGAZA_LIBRARY_INCLUDE_CABLE == (0x161c+808-0x1943)
#ifndef zf5004d0e5e
#define zf5004d0e5e
#include "angaza/config.h"
#if ANGAZA_LIBRARY_INCLUDE_CABLE == (0x966+6395-0x2260)
#include <stdint.h>
#include <stdbool.h>
ANGAZA_PACKED_STRUCT z1f8a0a75ab{uint8_t z99d100e6ed[(0x10c4+304-0x11d4)];};typedef void(*zfd35925452)(const struct 
z1f8a0a75ab*);void z4be94fd883(zfd35925452 zd504fcbb7b);void zdf28f0f36a(const struct z1f8a0a75ab*z96b01d3a5a);bool 
zaa9068e83c();
#endif
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
z8644bc3e61(struct zb76bf3e611*z8ab80f1355);struct z4d335faab1{uint8_t z99d100e6ed[(0x3dc+7925-0x22c1)];};struct 
z2991aa66f2{uint8_t z99d100e6ed[(0x27c+8247-0x22ab)];};struct z2991aa66f2 z1b82a670fc(const struct z4d335faab1*key,const
 void*data,uint16_t data_size);void z844f2a9dbe(const struct z4d335faab1*key,const void*zd5753f6c49,uint16_t z65c78f7747
,void*z2f95e13be5,uint16_t ze12ce6b9ca);uint64_t z38e71292f7(const struct z2991aa66f2*value);static inline uint16_t 
zcddc7faa45(uint16_t z2bf3f1cf4d){uint16_t zacea26b15c;uint8_t*z99d100e6ed=(uint8_t*)&zacea26b15c;z99d100e6ed[
(0xaf8+5480-0x2060)]=z2bf3f1cf4d>>(0x6a0+5717-0x1ced);z99d100e6ed[(0x50a+7233-0x214a)]=z2bf3f1cf4d&(0x1f66+261-0x1f6c);
return zacea26b15c;}static inline uint16_t z020f7db9be(uint16_t zacea26b15c){uint8_t*z99d100e6ed=(uint8_t*)&zacea26b15c;
return(((uint16_t)(z99d100e6ed[(0x3f5+1588-0xa29)]))<<(0x51a+8602-0x26ac))|z99d100e6ed[(0xb01+4886-0x1e16)];}
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
#define ANGAZA_SECONDS_IN_HOUR (0x1a94+6625-0x2665)
#define ANGAZA_HOURS_IN_DAY (0x721+7534-0x2477)
#define ANGAZA_SECONDS_IN_DAY (ANGAZA_SECONDS_IN_HOUR * ANGAZA_HOURS_IN_DAY)
#ifndef ANGAZA_DEFAULT_LOW_CREDIT_THRESHOLD
#define ANGAZA_DEFAULT_LOW_CREDIT_THRESHOLD ((0x847+3695-0x16b4) * ANGAZA_SECONDS_IN_DAY)
#endif
#ifndef ANGAZA_LIBRARY_INCLUDE_KEYPAD
#define ANGAZA_LIBRARY_INCLUDE_KEYPAD (0x6bd+7608-0x2474) 
#endif
#ifndef ANGAZA_LIBRARY_INCLUDE_CABLE
#define ANGAZA_LIBRARY_INCLUDE_CABLE (0x16a+9029-0x24ae)
#endif
#ifndef ANGAZA_LIBRARY_INCLUDE_IR
#define ANGAZA_LIBRARY_INCLUDE_IR (0x1c96+556-0x1ec2)
#endif
#ifndef ANGAZA_KEYCODE_PROTOCOL
#define ANGAZA_KEYCODE_PROTOCOL ANGAZA_KEYCODE_PROTOCOL_SMALL
#endif
#ifndef ANGAZA_DEFAULT_KEYCODE_START_CHAR
#if ANGAZA_KEYCODE_PROTOCOL==ANGAZA_KEYCODE_PROTOCOL_SMALL
#define ANGAZA_DEFAULT_KEYCODE_START_CHAR ((char)(0x177a+1452-0x1cf1))
#else
#define ANGAZA_DEFAULT_KEYCODE_START_CHAR ((char)(0xcd1+5198-0x20f5))
#endif
#endif
#ifndef ANGAZA_DEFAULT_KEYCODE_END_CHAR
#if ANGAZA_KEYCODE_PROTOCOL==ANGAZA_KEYCODE_PROTOCOL_SMALL
#define ANGAZA_DEFAULT_KEYCODE_END_CHAR ((char)(0x1a08+2670-0x2455))
#else
#define ANGAZA_DEFAULT_KEYCODE_END_CHAR ((char)(0x6c2+3805-0x157c))
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
#define ANGAZA_DEFAULT_KEYCODE_TIMEOUT (0xb37+2694-0x15ad)
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
zccf927d73f(void){return(uint16_t)ANGAZA_PAYG_FIRMWARE_ID<<(0xcbf+2589-0x16d4)|MANUFACTURER_PROD_FIRMWARE_ID;}
#endif
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
z8644bc3e61(struct zb76bf3e611*z8ab80f1355);struct z4d335faab1{uint8_t z99d100e6ed[(0x1fa+1210-0x6a4)];};struct 
z2991aa66f2{uint8_t z99d100e6ed[(0x2f3+6947-0x1e0e)];};struct z2991aa66f2 z1b82a670fc(const struct z4d335faab1*key,const
 void*data,uint16_t data_size);void z844f2a9dbe(const struct z4d335faab1*key,const void*zd5753f6c49,uint16_t z65c78f7747
,void*z2f95e13be5,uint16_t ze12ce6b9ca);uint64_t z38e71292f7(const struct z2991aa66f2*value);static inline uint16_t 
zcddc7faa45(uint16_t z2bf3f1cf4d){uint16_t zacea26b15c;uint8_t*z99d100e6ed=(uint8_t*)&zacea26b15c;z99d100e6ed[
(0x37b+5147-0x1796)]=z2bf3f1cf4d>>(0x12ef+3357-0x2004);z99d100e6ed[(0xc0d+4412-0x1d48)]=z2bf3f1cf4d&(0x1857+1633-0x1db9)
;return zacea26b15c;}static inline uint16_t z020f7db9be(uint16_t zacea26b15c){uint8_t*z99d100e6ed=(uint8_t*)&zacea26b15c
;return(((uint16_t)(z99d100e6ed[(0x114c+3885-0x2079)]))<<(0x126a+1346-0x17a4))|z99d100e6ed[(0x1426+4444-0x2581)];}
#endif
#include <stdint.h>
#include <stdbool.h>
#define zc2470f70ad UINT16_MAX
enum z6d3ea90808{zc6756cf9fe=-(0x10ec+912-0x1477),zbe59c74657=-(0x370+4420-0x14b1),zdd619174a7=-(0xe69+4781-0x2115),
z8743b8143a=(0x160+4198-0x11c5),zd601da1af2=(0xcf0+2912-0x184d),z916a881d3d=(0x3d+262-0x13e),z35df456492=
(0x421+4123-0x1435),z5fa629cfdf=(0x424+3242-0x10c5),zb328cc315b=-(0xc9+4794-0x1375),z1e15291ff6=-(0x568+4027-0x151d),
z03f0288307=-(0xb80+6337-0x243d),z0b2877b28a=-(0x886+4807-0x1b4b),z81a3db4175=(0xfc0+2191-0x184f),z5397dac104=
(0x243c+676-0x26de),z6339bdc9a6=(0xdc6+533-0xfd7),za16f097bc2=(0xf81+5747-0x25ee),zafb3d7f0ef=(0x450+4750-0x16d2)};enum 
zb00f9e49da{z3f6ff71297=(0x1300+46-0x132e),ze33805dc35=(0x54c+5046-0x1901),za5ead2f585=(0x1054+3258-0x1d0c),z8bf421480c=
(0xa89+7202-0x26a8),z7d78f82406=(0x13a3+1298-0x18b1),z4c65ee2b8e=(0x1a64+3123-0x2692),z26a109a3fc=(0x871+1308-0xd87),
z6f767ce41f=(0x16f0+3889-0x261a),z2654e14acd=(0x374+8876-0x2618),z650ea4efe6=(0xf19+1685-0x15a5),};ANGAZA_PACKED_STRUCT 
z8d75aaacd3{uint8_t zf98a522941;uint8_t z2d65a69612;uint32_t zd292382187;};ANGAZA_PACKED_STRUCT zcb9ae164ff{uint8_t 
zd03e3f3ea2;uint8_t ze198a604d6;uint8_t zf033d0a7a9;uint8_t z8e18bc6407;uint8_t z9615ede57e;};ANGAZA_PACKED_STRUCT 
z468294f62a{uint8_t zb657806209[(0x1548+3159-0x218a)];};ANGAZA_PACKED_STRUCT z241b5aff13{int8_t z44fd34d036;uint16_t 
zec20cf7fba;uint16_t z03b9deb8ed;uint8_t zb657806209[(0x90a+2620-0x1336)];};ANGAZA_PACKED_STRUCT zeeade73912{uint8_t 
data[(0x164+6633-0x1b38)];};ANGAZA_PACKED_STRUCT ze8b46b7fd3{struct zcb9ae164ff z95346f4fd2;struct zcb9ae164ff 
zb283a18c67;uint8_t zb657806209[(0x142+8723-0x234a)];};ANGAZA_PACKED_STRUCT z0108bf0e58{uint16_t z83996b1809;struct 
z8d75aaacd3 zf0f1223c32[(0x1acc+1282-0x1fcb)];uint8_t zb657806209[(0x15d1+281-0x16e9)];};ANGAZA_PACKED_STRUCT 
zcb498b42dc{bool z6c43cdc604;uint8_t zb657806209[(0x102d+5283-0x24bc)];};ANGAZA_PACKED_STRUCT z115d482bb6{uint32_t 
z7f789751c5;struct z4d335faab1 z23dd9c5ec7;uint8_t zb657806209[(0xb07+2877-0x1643)];};ANGAZA_PACKED_STRUCT zc5b468ab2b{
uint8_t z45949a12d6;uint8_t zb657806209[(0xae9+3032-0x16ad)];};ANGAZA_PACKED_STRUCT z50cb51c182{uint8_t zb657806209[
(0xa10+4980-0x1d6f)];};enum zdb43a3069b{zd03757bfc9=(0xd03+460-0xecf),z769468a62a=(0x54b+1297-0xa5b),};
ANGAZA_PACKED_STRUCT z9831eeb6a3{uint16_t zce335549f0;uint32_t z7f789751c5;uint32_t zc33a66378d;uint32_t z4e2a4054e0;
uint32_t zd65751a3a0;uint8_t ze9d8dd7565;uint16_t z6bec759684;};ANGAZA_PACKED_STRUCT z2230094cb2{uint16_t zce335549f0;
uint32_t z7f789751c5;struct zcb9ae164ff z95346f4fd2;uint8_t flags;struct zcb9ae164ff zb283a18c67;uint8_t ze9d8dd7565;
uint16_t z6bec759684;uint8_t zb657806209[(0x1214+2017-0x19f4)];};ANGAZA_PACKED_STRUCT za5f68613de{uint8_t z53ab876a75;
uint8_t zb657806209[(0x10f8+2301-0x19e2)];};enum zcbc3bfd665{z60c5940d1b=(0x1a+6137-0x1810),z9b95e903e2=
(0x15e7+2680-0x1ff8),};ANGAZA_PACKED_STRUCT z9672d1c9fc{uint8_t version;uint8_t data[(0x127d+1303-0x1780)];};
ANGAZA_PACKED_UNION z3f6992bda9{struct z468294f62a z4e8e7946af;struct z241b5aff13 zfb31b25acb;struct zeeade73912 
z6a4de9dd1d;struct ze8b46b7fd3 z45fdc63ba2;struct z0108bf0e58 ze109e6e51f;struct z115d482bb6 z0c5694cdbb;struct 
z9831eeb6a3 z68f85eb123;struct z50cb51c182 zad179c5774;struct z2230094cb2 z67db900c2d;struct zeeade73912 zb286a59e0a;
struct za5f68613de z19adc5a428;struct z9672d1c9fc z49ebb13ca4;};ANGAZA_PACKED_STRUCT z646d334194{int8_t zdec3b76f2f;
uint16_t sequence;union z3f6992bda9 z3c07c7db94;struct z2991aa66f2 z07c829a062;};bool z472eda3cf8(const struct 
z646d334194*z353bbb6e99);bool zb8be58c96d(const struct z646d334194*z353bbb6e99,const struct z4d335faab1*key);struct 
z2991aa66f2 z41cddd3e47(const struct z646d334194*z353bbb6e99,const struct z4d335faab1*key);struct z646d334194 
z49beb1bf9a(const struct z1f8a0a75ab*z6058e9283d);struct z1f8a0a75ab ze3a55cd70e(const struct z646d334194*z353bbb6e99);
uint8_t zde6803a11f(const struct zcb9ae164ff*zd6271ddcc8);uint8_t z101a736a21(const struct zcb9ae164ff*zd6271ddcc8);void
 z2027a378b0(void);void zcdf585f407(const struct z1f8a0a75ab*z6058e9283d);bool ze8c77eb4ad(const struct z646d334194*
z353bbb6e99,struct z646d334194*z96b01d3a5a);ANGAZA_STATIC_ASSERT(sizeof(struct zeeade73912)==(0x1147+5586-0x2704),
"\x65\x63\x68\x6f\x20\x72\x65\x71\x75\x65\x73\x74\x20\x62\x6f\x64\x79\x20\x68\x61\x73\x20\x69\x6e\x63\x6f\x72\x72\x65\x63\x74\x20\x73\x69\x7a\x65"
);ANGAZA_STATIC_ASSERT(sizeof(struct z646d334194)==(0x1e1f+642-0x2081),
"\x6d\x65\x73\x73\x61\x67\x65\x20\x73\x74\x72\x75\x63\x74\x20\x68\x61\x73\x20\x69\x6e\x63\x6f\x72\x72\x65\x63\x74\x20\x73\x69\x7a\x65"
);ANGAZA_STATIC_ASSERT(sizeof(((struct z646d334194*)(0x1235+520-0x143d))->zdec3b76f2f)==(0x10+6644-0x1a03),
"\x6d\x65\x73\x73\x61\x67\x65\x20\x74\x79\x70\x65\x20\x66\x69\x65\x6c\x64\x20\x68\x61\x73\x20\x69\x6e\x63\x6f\x72\x72\x65\x63\x74\x20\x73\x69\x7a\x65"
);ANGAZA_STATIC_ASSERT(sizeof(((struct z646d334194*)(0x9d2+5301-0x1e87))->sequence)==(0x6d4+5825-0x1d93),
"\x6d\x65\x73\x73\x61\x67\x65\x20\x73\x65\x71\x75\x65\x6e\x63\x65\x20\x66\x69\x65\x6c\x64\x20\x68\x61\x73\x20\x69\x6e\x63\x6f\x72\x72\x65\x63\x74\x20\x73\x69\x7a\x65"
);ANGAZA_STATIC_ASSERT(sizeof(((struct z646d334194*)(0x1b33+939-0x1ede))->z3c07c7db94)==(0x49f+8121-0x2443),
"\x6d\x65\x73\x73\x61\x67\x65\x20\x62\x6f\x64\x79\x20\x66\x69\x65\x6c\x64\x20\x68\x61\x73\x20\x69\x6e\x63\x6f\x72\x72\x65\x63\x74\x20\x73\x69\x7a\x65"
);ANGAZA_STATIC_ASSERT(sizeof(((struct z646d334194*)(0xbe4+1604-0x1228))->z07c829a062)==(0x583+4962-0x18dd),
"\x6d\x65\x73\x73\x61\x67\x65\x20\x63\x68\x65\x63\x6b\x20\x66\x69\x65\x6c\x64\x20\x68\x61\x73\x20\x69\x6e\x63\x6f\x72\x72\x65\x63\x74\x20\x73\x69\x7a\x65"
);ANGAZA_STATIC_ASSERT(sizeof(struct z1f8a0a75ab)==sizeof(struct z646d334194),
"\x72\x61\x77\x20\x61\x6e\x64\x20\x72\x69\x63\x68\x20\x6d\x65\x73\x73\x61\x67\x65\x20\x73\x74\x72\x75\x63\x74\x20\x73\x69\x7a\x65\x73\x20\x64\x6f\x20\x6e\x6f\x74\x20\x6d\x61\x74\x63\x68"
);
#if zb40ad23cec != zdceebb6c01
#error "little-endian architecture required for cable protocol support"
#endif
#endif
#endif
#ifndef z42141cb1d4
#define z42141cb1d4
#include "angaza/config.h"
#if ANGAZA_LIBRARY_INCLUDE_KEYPAD == (0x8c6+7168-0x24c5)
#include "angaza/prod_keypad.h"
#include <stdbool.h>
#include <stdint.h>
#define zbeb91cc9c2      (0x57f+5814-0x1bb5)
#define z1c4a635f01      (ANGAZA_SECONDS_IN_DAY / zbeb91cc9c2)
bool z9622a3c53f(const struct prod_keypad_key za033d43345,const struct prod_keypad_key z0f144c2120);void zad72251a8f(
uint32_t seconds_elapsed);bool zfb2d3e813b(void);void ze5ef1b9d78(void);
#define z3bc7e19dec (0x543+7131-0x20de)
#define zbd92582e81 UINT8_MAX
ANGAZA_PACKED_STRUCT z85a0b1642b{struct prod_keypad_key z9e974f8831[z3bc7e19dec];uint8_t z1b0920160b;};void zaadd37bee4(
struct z85a0b1642b*zf2e84cdb22,const char*z9e974f8831);struct z85a0b1642b zf3c4dde316(const char*z9e974f8831);void 
z30522e9f22(const struct z85a0b1642b*zf2e84cdb22,char*zdddcb7b2a7);typedef void(*z1986c2d6a8)(const struct z85a0b1642b*)
;void z482d238b89(const z1986c2d6a8 zd504fcbb7b);void zd0b62f0f62(void);uint32_t zd0c16cb767(uint32_t seconds_elapsed);
void z5bd3d5702a(void);void z99650ea82c(const struct prod_keypad_key key);void ze9c19e4038(void);void z93277c0ade(const 
struct prod_keypad_key z516d003588,const struct prod_keypad_key z70b0dce271,uint8_t z5f135a6a92);void zc607ae7036();
uint32_t z4f0ebd829a(uint32_t seconds_elapsed);void zb85ab16ded(const struct prod_keypad_key ze7d076848a);
#endif
#endif
#ifndef z49a5de43aa
#define z49a5de43aa
#include "angaza/payg_state.h"
#include <stdint.h>
#define za7423ec1fe UINT32_MAX
enum z099cdaadc3{z72b9663dad=(0xbea+4855-0x1ee1),z8fdca155d8=(0x397+2081-0xbb7)<<(0x790+7854-0x263e),z7f1bc901db=
(0x4ac+387-0x62e)<<(0xa2a+4510-0x1bc7),z71febcb1cf=(0x44d+7950-0x235a)<<(0x1656+2296-0x1f4c),z9b6e971db5=
(0x1587+2156-0x1df2)<<(0xa12+3202-0x1691),};void z19716f30d8(void);uint32_t zce8b058870(uint32_t seconds_elapsed);void 
z7439e6a5fc(uint32_t amount);void zd5e58eefc1(enum z099cdaadc3 za033d43345,uint32_t amount,enum z099cdaadc3 z8f2c15d999,
enum z099cdaadc3 z5af16b8ab3);void z63e7a0706a(void);uint32_t zab8da285b3(void);uint32_t z7194c8b5d7(void);uint32_t 
zc0772fcd35(void);static inline void z3afd043833(void){z63e7a0706a();}
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
z8644bc3e61(struct zb76bf3e611*z8ab80f1355);struct z4d335faab1{uint8_t z99d100e6ed[(0x549+3522-0x12fb)];};struct 
z2991aa66f2{uint8_t z99d100e6ed[(0x5c2+3151-0x1209)];};struct z2991aa66f2 z1b82a670fc(const struct z4d335faab1*key,const
 void*data,uint16_t data_size);void z844f2a9dbe(const struct z4d335faab1*key,const void*zd5753f6c49,uint16_t z65c78f7747
,void*z2f95e13be5,uint16_t ze12ce6b9ca);uint64_t z38e71292f7(const struct z2991aa66f2*value);static inline uint16_t 
zcddc7faa45(uint16_t z2bf3f1cf4d){uint16_t zacea26b15c;uint8_t*z99d100e6ed=(uint8_t*)&zacea26b15c;z99d100e6ed[
(0x1093+1635-0x16f6)]=z2bf3f1cf4d>>(0xd7d+6298-0x260f);z99d100e6ed[(0xca1+1281-0x11a1)]=z2bf3f1cf4d&(0x142a+3013-0x1ef0)
;return zacea26b15c;}static inline uint16_t z020f7db9be(uint16_t zacea26b15c){uint8_t*z99d100e6ed=(uint8_t*)&zacea26b15c
;return(((uint16_t)(z99d100e6ed[(0xc7+2872-0xbff)]))<<(0x16a9+466-0x1873))|z99d100e6ed[(0x11ed+3944-0x2154)];}
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
z8644bc3e61(struct zb76bf3e611*z8ab80f1355);struct z4d335faab1{uint8_t z99d100e6ed[(0x1db5+1623-0x23fc)];};struct 
z2991aa66f2{uint8_t z99d100e6ed[(0x1aa7+2407-0x2406)];};struct z2991aa66f2 z1b82a670fc(const struct z4d335faab1*key,
const void*data,uint16_t data_size);void z844f2a9dbe(const struct z4d335faab1*key,const void*zd5753f6c49,uint16_t 
z65c78f7747,void*z2f95e13be5,uint16_t ze12ce6b9ca);uint64_t z38e71292f7(const struct z2991aa66f2*value);static inline 
uint16_t zcddc7faa45(uint16_t z2bf3f1cf4d){uint16_t zacea26b15c;uint8_t*z99d100e6ed=(uint8_t*)&zacea26b15c;z99d100e6ed[
(0x7f8+6472-0x2140)]=z2bf3f1cf4d>>(0x2db+1764-0x9b7);z99d100e6ed[(0x1553+47-0x1581)]=z2bf3f1cf4d&(0x928+1370-0xd83);
return zacea26b15c;}static inline uint16_t z020f7db9be(uint16_t zacea26b15c){uint8_t*z99d100e6ed=(uint8_t*)&zacea26b15c;
return(((uint16_t)(z99d100e6ed[(0x221+5672-0x1849)]))<<(0x1765+1255-0x1c44))|z99d100e6ed[(0x176c+2467-0x210e)];}
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
#define ANGAZA_SECONDS_IN_HOUR 3600
#define ANGAZA_HOURS_IN_DAY (0x9c+1344-0x5c4)
#define ANGAZA_SECONDS_IN_DAY (ANGAZA_SECONDS_IN_HOUR * ANGAZA_HOURS_IN_DAY)
#ifndef ANGAZA_DEFAULT_LOW_CREDIT_THRESHOLD
#define ANGAZA_DEFAULT_LOW_CREDIT_THRESHOLD ((0xf21+224-0xfff) * ANGAZA_SECONDS_IN_DAY)
#endif
#ifndef ANGAZA_LIBRARY_INCLUDE_KEYPAD
#define ANGAZA_LIBRARY_INCLUDE_KEYPAD (0xcc6+175-0xd74) 
#endif
#ifndef ANGAZA_LIBRARY_INCLUDE_CABLE
#define ANGAZA_LIBRARY_INCLUDE_CABLE (0x849+370-0x9ba)
#endif
#ifndef ANGAZA_LIBRARY_INCLUDE_IR
#define ANGAZA_LIBRARY_INCLUDE_IR (0xea3+3296-0x1b83)
#endif
#ifndef ANGAZA_KEYCODE_PROTOCOL
#define ANGAZA_KEYCODE_PROTOCOL ANGAZA_KEYCODE_PROTOCOL_SMALL
#endif
#ifndef ANGAZA_DEFAULT_KEYCODE_START_CHAR
#if ANGAZA_KEYCODE_PROTOCOL==ANGAZA_KEYCODE_PROTOCOL_SMALL
#define ANGAZA_DEFAULT_KEYCODE_START_CHAR ((char)(0x1624+1992-0x1db7))
#else
#define ANGAZA_DEFAULT_KEYCODE_START_CHAR ((char)(0x1617+53-0x1622))
#endif
#endif
#ifndef ANGAZA_DEFAULT_KEYCODE_END_CHAR
#if ANGAZA_KEYCODE_PROTOCOL==ANGAZA_KEYCODE_PROTOCOL_SMALL
#define ANGAZA_DEFAULT_KEYCODE_END_CHAR ((char)(0x1504+4103-0x24ea))
#else
#define ANGAZA_DEFAULT_KEYCODE_END_CHAR ((char)(0x108c+2309-0x196e))
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
#define ANGAZA_DEFAULT_KEYCODE_TIMEOUT (0x6dd+6501-0x2032)
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
zccf927d73f(void){return(uint16_t)ANGAZA_PAYG_FIRMWARE_ID<<(0x8a9+2109-0x10de)|MANUFACTURER_PROD_FIRMWARE_ID;}
#endif
struct za4b28ee7b9{uint8_t z99d100e6ed[(0x980+3756-0x1827)];};enum payg_nv_block_id{zf8055f3fc9=(0x131d+94-0x137b),
z44fc441733=(0x13e7+2608-0x1e16),z5d07ee0179=(0xb2d+1168-0xfbb),z708da52d20=(0xfeb+4053-0x1fbd),z1153d8fc37=
(0xc+4741-0x128d),z0ae15748f0=(0x19f6+1719-0x20a8),z9a1be04e05=(0x5cd+1446-0xb6d),z96747f25f4=(0x73b+5583-0x1d03),
z77158136eb=(0x238+5275-0x16cb),zff4ce0d5d8=(0x87d+1245-0xd51),zee1b728de3=(0xa2+2145-0x8f9),z5432539b70=
(0x127a+5180-0x26ab),za63eaf1e19=(0x3ff+2497-0xdb4),z54c8b36582=(0x1b7+4124-0x11c6),z95d833a190=(0x121c+4776-0x24b6),
zf054aab66f=(0x1bf9+222-0x1cc8),};bool z9066c6d9e0(enum payg_nv_block_id z2a31d25b5c,void*data,const uint8_t data_size);
void z88df969180(enum payg_nv_block_id block_id,const void*data,const uint8_t data_size);struct payg_nv_block 
z453fb2f328(const enum payg_nv_block_id block_id,const struct za4b28ee7b9*data);struct z2991aa66f2 z2e8ff023b4(const 
struct payg_nv_block*block);
#endif
#ifndef zf5004d0e5e
#define zf5004d0e5e
#include "angaza/config.h"
#if ANGAZA_LIBRARY_INCLUDE_CABLE == (0xfb6+4873-0x22be)
#include <stdint.h>
#include <stdbool.h>
ANGAZA_PACKED_STRUCT z1f8a0a75ab{uint8_t z99d100e6ed[(0x733+4604-0x190f)];};typedef void(*zfd35925452)(const struct 
z1f8a0a75ab*);void z4be94fd883(zfd35925452 zd504fcbb7b);void zdf28f0f36a(const struct z1f8a0a75ab*z96b01d3a5a);bool 
zaa9068e83c();
#endif
#endif
#include "angaza/angaza.h"
#ifndef ANGAZA_LIBRARY_INCLUDE_KEYPAD
#error "Missing required definition of ANGAZA_LIBRARY_INCLUDE_KEYPAD"
#endif
#ifndef ANGAZA_LIBRARY_INCLUDE_CABLE
#error "Missing required definition of ANGAZA_LIBRARY_INCLUDE_CABLE"
#endif
#ifndef ANGAZA_LIBRARY_INCLUDE_IR
#error "Missing required definition of ANGAZA_LIBRARY_INCLUDE_IR"
#endif
static struct{uint32_t z8352511f86;}zfe17c7b0b1;static uint32_t z19bc2a5bbc(uint32_t za033d43345,uint32_t z0f144c2120){
return za033d43345<z0f144c2120?za033d43345:z0f144c2120;}static const struct z28f13284db zd2b5b17dd8={
#if ANGAZA_LIBRARY_INCLUDE_KEYPAD
#if ANGAZA_KEYCODE_PROTOCOL == ANGAZA_KEYCODE_PROTOCOL_SMALL
z65599d88a1,z35c1733bb2,
#elif ANGAZA_KEYCODE_PROTOCOL == ANGAZA_KEYCODE_PROTOCOL_FULL
z478f868641,zc82f30b4cc,
#else
#error "ANGAZA_KEYCODE_PROTOCOL value unrecognized."
#endif
z69858c6f9a,ANGAZA_DEFAULT_KEYCODE_START_CHAR,ANGAZA_DEFAULT_KEYCODE_END_CHAR,ANGAZA_DEFAULT_KEYCODE_ALPHABET
#endif
};void payg_all_init(void){za74b95daa3(&zd2b5b17dd8);}void za74b95daa3(const struct z28f13284db*z062d4060f6){zfe17c7b0b1
.z8352511f86=(0x1ac8+350-0x1c26);z298f1a3407();z19716f30d8();
#if ANGAZA_LIBRARY_INCLUDE_CABLE
z2027a378b0();z4be94fd883(zcdf585f407);
#endif
#if ANGAZA_LIBRARY_INCLUDE_KEYPAD
const struct prod_keypad_key zb940099ba2={PROD_KEYPAD_KEY_TYPE_CHAR,{z062d4060f6->z6f0cf0bf11}};const struct 
prod_keypad_key zaad215c35c={PROD_KEYPAD_KEY_TYPE_CHAR,{z062d4060f6->zf930334ec1}};z27149b95f9(z062d4060f6->z35115b1365,
z062d4060f6->z20f1f63336,z062d4060f6->za6fa5f8372);z482d238b89(z5d6ee32217);z93277c0ade(zb940099ba2,zaad215c35c,
z062d4060f6->z5f135a6a92);
#endif
prod_mainloop_request_processing();}void payg_all_deinit(void){
#if ANGAZA_LIBRARY_INCLUDE_KEYPAD
zd0b62f0f62();zb0394eb662();
#endif
z3afd043833();z1a20bd9908();}uint32_t payg_all_process(uint32_t seconds_elapsed){zfe17c7b0b1.z8352511f86+=
seconds_elapsed;uint32_t z7e2317ecc4=UINT32_MAX;z7e2317ecc4=z19bc2a5bbc(z7e2317ecc4,zce8b058870(seconds_elapsed));
#if ANGAZA_LIBRARY_INCLUDE_KEYPAD
z7e2317ecc4=z19bc2a5bbc(z7e2317ecc4,zd0c16cb767(seconds_elapsed));z7e2317ecc4=z19bc2a5bbc(z7e2317ecc4,zb6c3c68640(
seconds_elapsed));
#endif
return z7e2317ecc4;}uint32_t payg_all_uptime(void){return zfe17c7b0b1.z8352511f86;}
