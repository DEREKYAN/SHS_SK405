
#ifndef z44e6f70797
#define z44e6f70797
#include "angaza/config.h"
#include "angaza/payg_all.h"
#ifndef z20fbe47bb0
#define z20fbe47bb0
#include "angaza/config.h"
#if ANGAZA_LIBRARY_INCLUDE_KEYPAD == (0x164b+1128-0x1ab2)
#ifndef z42141cb1d4
#define z42141cb1d4
#include "angaza/config.h"
#if ANGAZA_LIBRARY_INCLUDE_KEYPAD == (0xa08+651-0xc92)
#include "angaza/prod_keypad.h"
#include <stdbool.h>
#include <stdint.h>
#define zbeb91cc9c2      (0x4f8+1053-0x895)
#define z1c4a635f01      (ANGAZA_SECONDS_IN_DAY / zbeb91cc9c2)
bool z9622a3c53f(const struct prod_keypad_key za033d43345,const struct prod_keypad_key z0f144c2120);void zad72251a8f(
uint32_t seconds_elapsed);bool zfb2d3e813b(void);void ze5ef1b9d78(void);
#define z3bc7e19dec (0x1a2a+3134-0x2628)
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
z8644bc3e61(struct zb76bf3e611*z8ab80f1355);struct z4d335faab1{uint8_t z99d100e6ed[(0x2ac+8155-0x2277)];};struct 
z2991aa66f2{uint8_t z99d100e6ed[(0x553+6625-0x1f2c)];};struct z2991aa66f2 z1b82a670fc(const struct z4d335faab1*key,const
 void*data,uint16_t data_size);void z844f2a9dbe(const struct z4d335faab1*key,const void*zd5753f6c49,uint16_t z65c78f7747
,void*z2f95e13be5,uint16_t ze12ce6b9ca);uint64_t z38e71292f7(const struct z2991aa66f2*value);static inline uint16_t 
zcddc7faa45(uint16_t z2bf3f1cf4d){uint16_t zacea26b15c;uint8_t*z99d100e6ed=(uint8_t*)&zacea26b15c;z99d100e6ed[
(0x3d5+1793-0xad6)]=z2bf3f1cf4d>>(0xdc9+2659-0x1824);z99d100e6ed[(0x153d+3850-0x2446)]=z2bf3f1cf4d&(0x3d3+1139-0x747);
return zacea26b15c;}static inline uint16_t z020f7db9be(uint16_t zacea26b15c){uint8_t*z99d100e6ed=(uint8_t*)&zacea26b15c;
return(((uint16_t)(z99d100e6ed[(0xf6f+1116-0x13cb)]))<<(0xe35+6206-0x266b))|z99d100e6ed[(0xc58+4021-0x1c0c)];}
#endif
#include <stdint.h>
#define zd1ad6c043e (0xda7+4987-0x2114)
#if ANGAZA_KEYCODE_PROTOCOL == ANGAZA_KEYCODE_PROTOCOL_SMALL
#define z36794d7643 (0x516+1012-0x8fa) 
#define zb020bccb17 (0x1f3d+1190-0x2365)
#define z241f89364d (0x60a+3963-0x1506)
#define z69858c6f9a zd1ad6c043e
#elif ANGAZA_KEYCODE_PROTOCOL == ANGAZA_KEYCODE_PROTOCOL_FULL
#define z36794d7643 (0x10d+3822-0xfeb) 
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
zdcc0276c3d{z310d54e49d=(0x637+7553-0x23b8),zb907c3d280=(0x60b+1841-0xd3b),zc9eb6225dc=(0x1082+499-0x1273),};enum 
zd2763f3828{zb361beff3a=(0xe23+4336-0x1f13),};void z35c1733bb2(const char*z51da0e89f4);bool zdec0c1ec14(const struct 
z85a0b1642b*zf2e84cdb22,struct z1a6b085d9b*z2a9b90236b);enum z767fe83ae2 zde5081fac6(const struct z1a6b085d9b*
z353bbb6e99);enum z767fe83ae2 z65599d88a1(const struct z85a0b1642b*zf2e84cdb22);uint16_t z1b796fa841(const struct 
z1a6b085d9b*z353bbb6e99,const struct z4d335faab1*key);enum zecace3a34a{zced3ef152a=(0xebc+3238-0x1b62),zfa4cac4da2=
(0x14e5+798-0x1802),z633c30fac4=(0x1c87+1130-0x20ef),};struct z47f37bd326{uint32_t zd4c4f8e622;};struct z8c6396fe6f{
uint32_t zd4c4f8e622;};enum z9c0ec497d1{z50c63eedff=(0x180+7843-0x2023),ze21914623f=(0x127d+466-0x144e),za107c4bc60=
(0xf40+5580-0x250a),};struct z399cda6a12{enum z9c0ec497d1 z9450b175e4;};union z267fd60ff8{struct z47f37bd326 z269cf6a29d
;struct z8c6396fe6f zc2cfbc11ee;struct z399cda6a12 zf701e2f996;};struct z3824fbc5c6{enum zecace3a34a type;uint16_t 
z83996b1809;union z267fd60ff8 z3c07c7db94;};enum zfc0ad122e4{zd7605648d8=(0xca0+5868-0x238c),za6436d61e3=
(0x145c+4302-0x2529),z4cf363935d=(0x107d+543-0x129a),z894b013606=(0x227+5691-0x185f),};struct z63041a2022{uint32_t 
ze1404276fc[(0xbfa+298-0xd20)];uint32_t z7f789751c5;};enum zf690a1e111{z3738536ed0=(0x11a6+4910-0x24d4),za0f14efb8e=
(0x64b+2209-0xeeb),};struct z532a30d60e{enum zf690a1e111 z25d1355136;};union zaec9cceef5{struct z63041a2022 z94356f2885;
struct z532a30d60e zb4dba8d32d;};struct z3cad09ffa6{enum zfc0ad122e4 type;union zaec9cceef5 z3c07c7db94;};enum 
z7d78ff9667{zeb7e21a12f,z57d3ac7de5,};union z0d5377e298{struct z3824fbc5c6 zb8be3299c1;struct z3cad09ffa6 zc579cab8a3;};
struct za13546c0c6{enum z7d78ff9667 zc0cb64693d;union z0d5377e298 z923f1b0559;uint32_t z07c829a062;};void zc82f30b4cc(
const char*z51da0e89f4);enum z767fe83ae2 z478f868641(const struct z85a0b1642b*zf2e84cdb22);bool z0faee65746(struct 
z85a0b1642b*zf2e84cdb22,struct za13546c0c6*z2a9b90236b);bool zffb40663dd(struct z85a0b1642b*zf2e84cdb22,struct 
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
#ifndef z49a5de43aa
#define z49a5de43aa
#include "angaza/payg_state.h"
#include <stdint.h>
#define za7423ec1fe UINT32_MAX
enum z099cdaadc3{z72b9663dad=(0x579+7604-0x232d),z8fdca155d8=(0x2372+635-0x25ec)<<(0xc6c+2139-0x14c7),z7f1bc901db=
(0x19f1+2448-0x2380)<<(0x13eb+469-0x15bf),z71febcb1cf=(0xfaa+5946-0x26e3)<<(0x15d9+2053-0x1ddc),z9b6e971db5=
(0x6+7498-0x1d4f)<<(0xee2+5203-0x2332),};void z19716f30d8(void);uint32_t zce8b058870(uint32_t seconds_elapsed);void 
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
z8644bc3e61(struct zb76bf3e611*z8ab80f1355);struct z4d335faab1{uint8_t z99d100e6ed[(0x171b+3880-0x2633)];};struct 
z2991aa66f2{uint8_t z99d100e6ed[(0x13f8+482-0x15d2)];};struct z2991aa66f2 z1b82a670fc(const struct z4d335faab1*key,const
 void*data,uint16_t data_size);void z844f2a9dbe(const struct z4d335faab1*key,const void*zd5753f6c49,uint16_t z65c78f7747
,void*z2f95e13be5,uint16_t ze12ce6b9ca);uint64_t z38e71292f7(const struct z2991aa66f2*value);static inline uint16_t 
zcddc7faa45(uint16_t z2bf3f1cf4d){uint16_t zacea26b15c;uint8_t*z99d100e6ed=(uint8_t*)&zacea26b15c;z99d100e6ed[
(0x1260+2703-0x1cef)]=z2bf3f1cf4d>>(0x772+7161-0x2363);z99d100e6ed[(0x1727+1382-0x1c8c)]=z2bf3f1cf4d&(0x1b5+7074-0x1c58)
;return zacea26b15c;}static inline uint16_t z020f7db9be(uint16_t zacea26b15c){uint8_t*z99d100e6ed=(uint8_t*)&zacea26b15c
;return(((uint16_t)(z99d100e6ed[(0x9dc+4526-0x1b8a)]))<<(0x1ebf+1842-0x25e9))|z99d100e6ed[(0x345+1132-0x7b0)];}
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
z8644bc3e61(struct zb76bf3e611*z8ab80f1355);struct z4d335faab1{uint8_t z99d100e6ed[(0x47b+4984-0x17e3)];};struct 
z2991aa66f2{uint8_t z99d100e6ed[(0xc40+2087-0x145f)];};struct z2991aa66f2 z1b82a670fc(const struct z4d335faab1*key,const
 void*data,uint16_t data_size);void z844f2a9dbe(const struct z4d335faab1*key,const void*zd5753f6c49,uint16_t z65c78f7747
,void*z2f95e13be5,uint16_t ze12ce6b9ca);uint64_t z38e71292f7(const struct z2991aa66f2*value);static inline uint16_t 
zcddc7faa45(uint16_t z2bf3f1cf4d){uint16_t zacea26b15c;uint8_t*z99d100e6ed=(uint8_t*)&zacea26b15c;z99d100e6ed[
(0x829+3554-0x160b)]=z2bf3f1cf4d>>(0x8e6+998-0xcc4);z99d100e6ed[(0xe06+3918-0x1d53)]=z2bf3f1cf4d&(0x17c7+73-0x1711);
return zacea26b15c;}static inline uint16_t z020f7db9be(uint16_t zacea26b15c){uint8_t*z99d100e6ed=(uint8_t*)&zacea26b15c;
return(((uint16_t)(z99d100e6ed[(0x1ebb+1146-0x2335)]))<<(0xcf6+2299-0x15e9))|z99d100e6ed[(0x8d4+756-0xbc7)];}
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
#define ANGAZA_SECONDS_IN_HOUR (0x161a+5957-0x1f4f)
#define ANGAZA_HOURS_IN_DAY (0x3c1+3845-0x12ae)
#define ANGAZA_SECONDS_IN_DAY (ANGAZA_SECONDS_IN_HOUR * ANGAZA_HOURS_IN_DAY)
#ifndef ANGAZA_DEFAULT_LOW_CREDIT_THRESHOLD
#define ANGAZA_DEFAULT_LOW_CREDIT_THRESHOLD ((0x1d37+1884-0x2491) * ANGAZA_SECONDS_IN_DAY)
#endif
#ifndef ANGAZA_LIBRARY_INCLUDE_KEYPAD
#define ANGAZA_LIBRARY_INCLUDE_KEYPAD (0x43+2028-0x82e) 
#endif
#ifndef ANGAZA_LIBRARY_INCLUDE_CABLE
#define ANGAZA_LIBRARY_INCLUDE_CABLE (0xe22+3047-0x1a08)
#endif
#ifndef ANGAZA_LIBRARY_INCLUDE_IR
#define ANGAZA_LIBRARY_INCLUDE_IR (0x1a44+2494-0x2402)
#endif
#ifndef ANGAZA_KEYCODE_PROTOCOL
#define ANGAZA_KEYCODE_PROTOCOL ANGAZA_KEYCODE_PROTOCOL_SMALL
#endif
#ifndef ANGAZA_DEFAULT_KEYCODE_START_CHAR
#if ANGAZA_KEYCODE_PROTOCOL==ANGAZA_KEYCODE_PROTOCOL_SMALL
#define ANGAZA_DEFAULT_KEYCODE_START_CHAR ((char)(0x14a+3874-0x1037))
#else
#define ANGAZA_DEFAULT_KEYCODE_START_CHAR ((char)(0xd31+5493-0x227c))
#endif
#endif
#ifndef ANGAZA_DEFAULT_KEYCODE_END_CHAR
#if ANGAZA_KEYCODE_PROTOCOL==ANGAZA_KEYCODE_PROTOCOL_SMALL
#define ANGAZA_DEFAULT_KEYCODE_END_CHAR ((char)(0x8a2+224-0x961))
#else
#define ANGAZA_DEFAULT_KEYCODE_END_CHAR ((char)(0xa83+490-0xc4a))
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
#define ANGAZA_DEFAULT_KEYCODE_TIMEOUT (0x21fb+237-0x22d8)
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
zccf927d73f(void){return(uint16_t)ANGAZA_PAYG_FIRMWARE_ID<<(0xa84+4280-0x1b34)|MANUFACTURER_PROD_FIRMWARE_ID;}
#endif
struct za4b28ee7b9{uint8_t z99d100e6ed[(0x11e9+4444-0x2340)];};enum payg_nv_block_id{zf8055f3fc9=(0xd64+2561-0x1765),
z44fc441733=(0xb02+6757-0x2566),z5d07ee0179=(0x1817+1505-0x1df6),z708da52d20=(0x8d3+925-0xc6d),z1153d8fc37=
(0x193a+452-0x1afa),z0ae15748f0=(0x1b2f+2052-0x232e),z9a1be04e05=(0x82+3418-0xdd6),z96747f25f4=(0x394+2863-0xebc),
z77158136eb=(0x1e57+15-0x1e5e),zff4ce0d5d8=(0xdc6+2126-0x160b),zee1b728de3=(0x6d+4360-0x116b),z5432539b70=
(0x130b+1094-0x1746),za63eaf1e19=(0x66b+455-0x826),z54c8b36582=(0x810+2733-0x12b0),z95d833a190=(0x786+7730-0x25aa),
zf054aab66f=(0xeba+937-0x1254),};bool z9066c6d9e0(enum payg_nv_block_id z2a31d25b5c,void*data,const uint8_t data_size);
void z88df969180(enum payg_nv_block_id block_id,const void*data,const uint8_t data_size);struct payg_nv_block 
z453fb2f328(const enum payg_nv_block_id block_id,const struct za4b28ee7b9*data);struct z2991aa66f2 z2e8ff023b4(const 
struct payg_nv_block*block);
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
z8644bc3e61(struct zb76bf3e611*z8ab80f1355);struct z4d335faab1{uint8_t z99d100e6ed[(0x1cab+1041-0x20ac)];};struct 
z2991aa66f2{uint8_t z99d100e6ed[(0x521+279-0x630)];};struct z2991aa66f2 z1b82a670fc(const struct z4d335faab1*key,const 
void*data,uint16_t data_size);void z844f2a9dbe(const struct z4d335faab1*key,const void*zd5753f6c49,uint16_t z65c78f7747,
void*z2f95e13be5,uint16_t ze12ce6b9ca);uint64_t z38e71292f7(const struct z2991aa66f2*value);static inline uint16_t 
zcddc7faa45(uint16_t z2bf3f1cf4d){uint16_t zacea26b15c;uint8_t*z99d100e6ed=(uint8_t*)&zacea26b15c;z99d100e6ed[
(0x91d+5070-0x1ceb)]=z2bf3f1cf4d>>(0x11cd+729-0x149e);z99d100e6ed[(0x891+5333-0x1d65)]=z2bf3f1cf4d&(0x174d+3086-0x225c);
return zacea26b15c;}static inline uint16_t z020f7db9be(uint16_t zacea26b15c){uint8_t*z99d100e6ed=(uint8_t*)&zacea26b15c;
return(((uint16_t)(z99d100e6ed[(0xbd7+2163-0x144a)]))<<(0x364+3534-0x112a))|z99d100e6ed[(0x9bf+3127-0x15f5)];}
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
#define ANGAZA_SECONDS_IN_HOUR (0x1416+8005-0x254b)
#define ANGAZA_HOURS_IN_DAY (0x1820+929-0x1ba9)
#define ANGAZA_SECONDS_IN_DAY (ANGAZA_SECONDS_IN_HOUR * ANGAZA_HOURS_IN_DAY)
#ifndef ANGAZA_DEFAULT_LOW_CREDIT_THRESHOLD
#define ANGAZA_DEFAULT_LOW_CREDIT_THRESHOLD ((0x5d9+702-0x895) * ANGAZA_SECONDS_IN_DAY)
#endif
#ifndef ANGAZA_LIBRARY_INCLUDE_KEYPAD
#define ANGAZA_LIBRARY_INCLUDE_KEYPAD (0x1551+1988-0x1d14) 
#endif
#ifndef ANGAZA_LIBRARY_INCLUDE_CABLE
#define ANGAZA_LIBRARY_INCLUDE_CABLE (0x75+5118-0x1472)
#endif
#ifndef ANGAZA_LIBRARY_INCLUDE_IR
#define ANGAZA_LIBRARY_INCLUDE_IR (0x312+5240-0x178a)
#endif
#ifndef ANGAZA_KEYCODE_PROTOCOL
#define ANGAZA_KEYCODE_PROTOCOL ANGAZA_KEYCODE_PROTOCOL_SMALL
#endif
#ifndef ANGAZA_DEFAULT_KEYCODE_START_CHAR
#if ANGAZA_KEYCODE_PROTOCOL==ANGAZA_KEYCODE_PROTOCOL_SMALL
#define ANGAZA_DEFAULT_KEYCODE_START_CHAR ((char)(0x6c3+4059-0x1669))
#else
#define ANGAZA_DEFAULT_KEYCODE_START_CHAR ((char)(0x900+972-0xca2))
#endif
#endif
#ifndef ANGAZA_DEFAULT_KEYCODE_END_CHAR
#if ANGAZA_KEYCODE_PROTOCOL==ANGAZA_KEYCODE_PROTOCOL_SMALL
#define ANGAZA_DEFAULT_KEYCODE_END_CHAR ((char)(0x10f7+233-0x11bf))
#else
#define ANGAZA_DEFAULT_KEYCODE_END_CHAR ((char)(0x2564+204-0x260d))
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
#define ANGAZA_DEFAULT_KEYCODE_TIMEOUT (0x1352+2211-0x1be5)
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
zccf927d73f(void){return(uint16_t)ANGAZA_PAYG_FIRMWARE_ID<<(0x6e7+8104-0x2687)|MANUFACTURER_PROD_FIRMWARE_ID;}
#endif
#include "angaza/prod_feedback.h"
#include "angaza/prod_mainloop.h"
#include "angaza/config.h"
#include <stdint.h>
static ANGAZA_PACKED_STRUCT{ANGAZA_PACKED_STRUCT{uint32_t z23813d6ea2;uint8_t zba5bd4ecd7;}zc3cc0e9c9c;
ANGAZA_PACKED_STRUCT{uint32_t z23813d6ea2;uint8_t zba5bd4ecd7;}z0a41adac56;ANGAZA_PACKED_STRUCT{uint32_t z23813d6ea2;
uint8_t zba5bd4ecd7;}z07446c68d7;ANGAZA_PACKED_STRUCT{uint32_t zf91a2a8548;uint8_t zba5bd4ecd7;}z59106bd282;bool 
z20cc2cfc99;uint32_t z0dbff6f384;}zfe17c7b0b1;void z19716f30d8(void){zfe17c7b0b1.zc3cc0e9c9c.z23813d6ea2=
(0x93b+4701-0x1b98);zfe17c7b0b1.z0a41adac56.z23813d6ea2=(0x5aa+1799-0xcb1);zfe17c7b0b1.z07446c68d7.z23813d6ea2=
(0xfc5+1638-0x162b);zfe17c7b0b1.z59106bd282.zf91a2a8548=ANGAZA_DEFAULT_LOW_CREDIT_THRESHOLD;zfe17c7b0b1.z20cc2cfc99=true
;zfe17c7b0b1.z0dbff6f384=payg_all_uptime();z9066c6d9e0(z1153d8fc37,&zfe17c7b0b1.zc3cc0e9c9c,sizeof(zfe17c7b0b1.
zc3cc0e9c9c)*(0x302+6480-0x1c4e));}uint32_t zce8b058870(uint32_t seconds_elapsed){if(payg_all_uptime()-zfe17c7b0b1.
z0dbff6f384>=ANGAZA_SECONDS_IN_HOUR||zfe17c7b0b1.z20cc2cfc99){z63e7a0706a();}if(zfe17c7b0b1.z20cc2cfc99){zfe17c7b0b1.
z20cc2cfc99=false;prod_feedback_handle_state_change();}return(0xb3+8787-0x22f7);}bool payg_state_is_enabled(void){switch
(payg_state_get_current()){case PAYG_STATE_ENABLED_UNLOCKED:case PAYG_STATE_ENABLED:case 
PAYG_STATE_ENABLED_NEAR_DISABLED:return true;case PAYG_STATE_DISABLED:return false;default:ANGAZA_ASSERT(false,
"encountered invalid PAYG state");return false;};}enum payg_state payg_state_get_current(void){if(zfe17c7b0b1.
z07446c68d7.z23813d6ea2==za7423ec1fe||(zfbd8489fdf()==4294967295)){return PAYG_STATE_ENABLED_UNLOCKED;}else if(
zfe17c7b0b1.z07446c68d7.z23813d6ea2>zfe17c7b0b1.z0a41adac56.z23813d6ea2){if(zfe17c7b0b1.z07446c68d7.z23813d6ea2<
zfe17c7b0b1.z0a41adac56.z23813d6ea2+zfe17c7b0b1.z59106bd282.zf91a2a8548){return PAYG_STATE_ENABLED_NEAR_DISABLED;}else{
return PAYG_STATE_ENABLED;}}else{return PAYG_STATE_DISABLED;}}void payg_state_consume_credit(const uint32_t amount){
zd5e58eefc1(z7f1bc901db,amount,z7f1bc901db,z72b9663dad);}void z7439e6a5fc(uint32_t amount){zfe17c7b0b1.z59106bd282.
zf91a2a8548=amount;}void zd5e58eefc1(enum z099cdaadc3 za033d43345,uint32_t amount,enum z099cdaadc3 z8f2c15d999,enum 
z099cdaadc3 z5af16b8ab3){const enum payg_state z25340f2af0=payg_state_get_current();const uint32_t z96773b27d5=
zfe17c7b0b1.z0a41adac56.z23813d6ea2>zfe17c7b0b1.z07446c68d7.z23813d6ea2?zfe17c7b0b1.z0a41adac56.z23813d6ea2:zfe17c7b0b1.
z07446c68d7.z23813d6ea2;const uint32_t zbae6f569ca=amount+((z8f2c15d999&z8fdca155d8)?zfe17c7b0b1.zc3cc0e9c9c.z23813d6ea2
:(0xfbf+852-0x1313))+((z8f2c15d999&z7f1bc901db)?zfe17c7b0b1.z0a41adac56.z23813d6ea2:(0x968+7103-0x2527))+((z8f2c15d999&
z71febcb1cf)?zfe17c7b0b1.z07446c68d7.z23813d6ea2:(0xec3+2420-0x1837))+((z8f2c15d999&z9b6e971db5)?z96773b27d5:
(0x1497+3081-0x20a0))-((z5af16b8ab3&z8fdca155d8)?zfe17c7b0b1.zc3cc0e9c9c.z23813d6ea2:(0x836+1989-0xffb))-((z5af16b8ab3&
z7f1bc901db)?zfe17c7b0b1.z0a41adac56.z23813d6ea2:(0x1555+3239-0x21fc))-((z5af16b8ab3&z71febcb1cf)?zfe17c7b0b1.
z07446c68d7.z23813d6ea2:(0xa09+4961-0x1d6a))-((z5af16b8ab3&z9b6e971db5)?z96773b27d5:(0x1e5d+1922-0x25df));if(za033d43345
&z8fdca155d8){zfe17c7b0b1.zc3cc0e9c9c.z23813d6ea2=zbae6f569ca;}if(za033d43345&z7f1bc901db){zfe17c7b0b1.z0a41adac56.
z23813d6ea2=zbae6f569ca;}if(za033d43345&z71febcb1cf){zfe17c7b0b1.z07446c68d7.z23813d6ea2=zbae6f569ca;}const enum 
payg_state zfbaa18e2a4=payg_state_get_current();if(z25340f2af0!=zfbaa18e2a4){zfe17c7b0b1.z20cc2cfc99=true;
prod_mainloop_request_processing();}}void z63e7a0706a(void){z88df969180(z1153d8fc37,&zfe17c7b0b1.zc3cc0e9c9c,sizeof(
zfe17c7b0b1.zc3cc0e9c9c)*(0x3d0+5544-0x1974));zfe17c7b0b1.z0dbff6f384=payg_all_uptime();}uint32_t zab8da285b3(void){
return zfe17c7b0b1.zc3cc0e9c9c.z23813d6ea2;}uint32_t z7194c8b5d7(void){return zfe17c7b0b1.z0a41adac56.z23813d6ea2;}
uint32_t zc0772fcd35(void){return zfe17c7b0b1.z07446c68d7.z23813d6ea2;}
