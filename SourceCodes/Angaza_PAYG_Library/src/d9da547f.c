
#include "angaza/config.h"
struct za9e60239b0{char z2e7cf56789;};
#if ANGAZA_LIBRARY_INCLUDE_IR
#include <stdbool.h>
#include <stdint.h>
#include "angaza/prod_ir.h"
#include "angaza/prod_timcmp.h"
#include "angaza/prod_keypad.h"
#include "angaza/payg_interrupts.h"
#define z66d554b5a8 0.3  
static const uint32_t za086ca76b3=(uint32_t)((0x14a0+6726-0x1d52)*(1.0-z66d554b5a8));static const uint32_t z8688665d28=(
uint32_t)((0x1e5c+4691-0x1f1b)*(1.0+z66d554b5a8));static const uint32_t zc457fbe462=(uint32_t)((0x23c2+2122-0x2342)*(1.0
-z66d554b5a8));static const uint32_t za42b74ec95=(uint32_t)((0x1598+4537-0x1e87)*(1.0+z66d554b5a8));static const 
uint32_t z777693d0f7=(uint32_t)((0xdfa+2409-0x1533)*(1.0-z66d554b5a8));static const uint32_t zc10c41f36d=(uint32_t)(
(0x19ff+1981-0x1f8c)*(1.0+z66d554b5a8));static const uint32_t z698fcd6a5d=(uint32_t)((0xddd+113-0xc1e)*(1.0-z66d554b5a8)
);static const uint32_t z8288c39ca8=(uint32_t)((0x41f+2786-0xcd1)*(1.0+z66d554b5a8));static const uint32_t z110f7e4e79=(
uint32_t)((0x881+3478-0xf7d)*(1.0-z66d554b5a8));static const uint32_t z5130c0a6ec=(uint32_t)((0x7c5+1939-0x8be)*(1.0+
z66d554b5a8));typedef ANGAZA_PACKED_STRUCT{uint8_t z6fc70a6db1;uint8_t z2a1f7293a3;uint8_t z87d72c00a0;uint8_t 
z0500377483;}z75653bf5bf;static volatile z75653bf5bf z0c0d314b43;static volatile uint32_t zd28a347ca3=
(0x985+7284-0x25f9);typedef enum{z30dfdc2394,zae77cdb2a8,z32e22b83bd,zb5073a9860,z3feb0cd6fa,zc0646f0829}ze8e175adc9;
static ze8e175adc9 z0361775943=z30dfdc2394;static bool z72c0aa4c8c=false;static uint32_t zf387a08021=(0x417+4895-0x1736)
;static void ze44ab4d028(){prod_ir_override_enable(false);z72c0aa4c8c=true;zf387a08021=(0x1e64+1491-0x2437);
prod_timcmp_start(10000);}static void z6cfaba4497(){prod_ir_override_enable(true);z72c0aa4c8c=false;zf387a08021=
(0x73d+6951-0x2264);}static void zb489e39cc1(void){zd28a347ca3=(0x13cb+2336-0x1ceb);}static void z931027b99a(int 
z190ca54686){uint32_t zc5c688262a;struct prod_keypad_key key;zc5c688262a=zd28a347ca3>>(0x12e4+539-0x14fc);if(zc5c688262a
>=sizeof(z0c0d314b43)){zb489e39cc1();}else{*(((uint8_t*)&z0c0d314b43)+zc5c688262a)=(*(((uint8_t*)&z0c0d314b43)+
zc5c688262a)>>(0x1085+4495-0x2213))|(z190ca54686<<(0x1601+1557-0x1c0f));zd28a347ca3++;if(zd28a347ca3==(sizeof(
z75653bf5bf)*(0x1935+1781-0x2022))){const uint8_t z88c7ad2622=~z0c0d314b43.z0500377483;if((z0c0d314b43.z6fc70a6db1==
(0xdcf+2936-0x1947))&&(z0c0d314b43.z2a1f7293a3==(uint8_t)(0x8fd+7911-0x26e5))&&(z0c0d314b43.z87d72c00a0==z88c7ad2622)){
switch(z0c0d314b43.z87d72c00a0){case(0xa10+5196-0x1e0a):key.value.character=((char)(0x1571+4197-0x25a6));break;case
(0xd2b+3980-0x1ca1):key.value.character=((char)(0xb70+6277-0x23c4));break;case(0x8e8+320-0xa0f):key.value.character=
((char)(0x12e1+430-0x145d));break;case(0x4bd+5800-0x1b58):key.value.character=((char)(0x2197+89-0x21bd));break;case
(0xf66+5746-0x25cc):key.value.character=((char)(0x1ed7+1181-0x2340));break;case(0x68f+6310-0x1f1d):key.value.character=
((char)(0x10b3+3716-0x1f02));break;case(0x223+8973-0x24d2):key.value.character=((char)(0xeb8+3883-0x1dad));break;case
(0xdab+3596-0x1baf):key.value.character=((char)(0x190a+3414-0x2629));break;case(0x1f8d+69-0x1fb6):key.value.character=
((char)(0x17a0+4003-0x270b));break;case(0x1d35+106-0x1d45):key.value.character=((char)(0x758+4878-0x1a2d));break;case
(0x182f+1042-0x1bff):key.value.character=((char)(0x120+7615-0x1eb5));break;case(0x6dd+8099-0x2636):key.value.character=
((char)(0xad6+2125-0x1300));break;default:key.value.character=((char)(0xcd5+115-0xd09));break;}if(key.value.character!=
((char)(0x16e9+736-0x198a))){key.type=PROD_KEYPAD_KEY_TYPE_CHAR;payg_interrupts_keypad_handle_key(key);}}zb489e39cc1();}
}}void z72eb06ad63(void){if(z72c0aa4c8c){zf387a08021=(0xb90+2327-0x14a7);prod_timcmp_start(10000);}}void 
payg_interrupts_timcmp_handle_elapsed(void){zf387a08021+=10000;if(z0361775943!=z30dfdc2394){z0361775943=z30dfdc2394;
zb489e39cc1();}if(zf387a08021>=8000000){z0361775943=z30dfdc2394;z6cfaba4497();zb489e39cc1();}else{prod_timcmp_start(
10000);}}void payg_interrupts_ir_handle_rx_edge(bool rx_pin_level){uint16_t elapsed_us=(0x10cd+1297-0x15de);bool 
z889f1fa557;if(z72c0aa4c8c){prod_timcmp_get_microseconds_elapsed(&elapsed_us);z72eb06ad63();}else{ze44ab4d028();}if(
rx_pin_level){z889f1fa557=false;}else{z889f1fa557=true;}switch(z0361775943){case z30dfdc2394:if(z889f1fa557){z0361775943
=zae77cdb2a8;}zb489e39cc1();break;case zae77cdb2a8:if(!z889f1fa557){if(elapsed_us>=(0x211a+1461-0x22e7)){z0361775943=
z32e22b83bd;}else{z0361775943=z30dfdc2394;}}break;case z32e22b83bd:if(z889f1fa557){if((elapsed_us>=za086ca76b3)&&(
elapsed_us<=z8688665d28)){z0361775943=zb5073a9860;}else if((elapsed_us>=zc457fbe462)&&(elapsed_us<=za42b74ec95)){
z0361775943=zc0646f0829;}else{z0361775943=zae77cdb2a8;zb489e39cc1();}}break;case zb5073a9860:if(!z889f1fa557){if((
elapsed_us>=z777693d0f7)&&(elapsed_us<=zc10c41f36d)){z0361775943=z3feb0cd6fa;}else{if(elapsed_us>za086ca76b3){
z0361775943=z32e22b83bd;}else{z0361775943=z30dfdc2394;}zb489e39cc1();}}break;case z3feb0cd6fa:if(z889f1fa557){if((
elapsed_us>=z698fcd6a5d)&&(elapsed_us<=z8288c39ca8)){z931027b99a((0x1498+1123-0x18fb));if(zd28a347ca3==(0x196+77-0x1e3))
{z0361775943=zc0646f0829;}else{z0361775943=zb5073a9860;}}else if((elapsed_us>=z110f7e4e79)&&(elapsed_us<=z5130c0a6ec)){
z931027b99a((0x1dd1+1659-0x244b));if(zd28a347ca3==(0x3+144-0x93)){z0361775943=zc0646f0829;}else{z0361775943=zb5073a9860;
}}else{z0361775943=zae77cdb2a8;zb489e39cc1();}}break;case zc0646f0829:if(!z889f1fa557){z0361775943=z30dfdc2394;
zb489e39cc1();}break;}}
#endif

