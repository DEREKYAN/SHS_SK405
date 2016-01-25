
#include "angaza/config.h"
#if ANGAZA_LIBRARY_INCLUDE_KEYPAD
#include "angaza/payg_all.h"
#include "angaza/prod_mainloop.h"
#include "angaza/prod_feedback.h"
#ifndef z42141cb1d4
#define z42141cb1d4
#include "angaza/config.h"
#if ANGAZA_LIBRARY_INCLUDE_KEYPAD == (0xc5+1937-0x855)
#include "angaza/prod_keypad.h"
#include <stdbool.h>
#include <stdint.h>
#define zbeb91cc9c2      (0x68b+5650-0x1c1d)
#define z1c4a635f01      (ANGAZA_SECONDS_IN_DAY / zbeb91cc9c2)
bool z9622a3c53f(const struct prod_keypad_key za033d43345,const struct prod_keypad_key z0f144c2120);void zad72251a8f(
uint32_t seconds_elapsed);bool zfb2d3e813b(void);void ze5ef1b9d78(void);
#define z3bc7e19dec (0x83+8274-0x2095)
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
enum z099cdaadc3{z72b9663dad=(0x825+1414-0xdab),z8fdca155d8=(0x1a23+2954-0x25ac)<<(0x189f+812-0x1bcb),z7f1bc901db=
(0x2c1+3504-0x1070)<<(0x788+5697-0x1dc8),z71febcb1cf=(0x14a8+1345-0x19e8)<<(0x148c+2417-0x1dfb),z9b6e971db5=
(0x804+5960-0x1f4b)<<(0x17b9+237-0x18a3),};void z19716f30d8(void);uint32_t zce8b058870(uint32_t seconds_elapsed);void 
z7439e6a5fc(uint32_t amount);void zd5e58eefc1(enum z099cdaadc3 za033d43345,uint32_t amount,enum z099cdaadc3 z8f2c15d999,
enum z099cdaadc3 z5af16b8ab3);void z63e7a0706a(void);uint32_t zab8da285b3(void);uint32_t z7194c8b5d7(void);uint32_t 
zc0772fcd35(void);static inline void z3afd043833(void){z63e7a0706a();}
#endif
static struct{z1986c2d6a8 zd504fcbb7b;struct z85a0b1642b zf54199ecde;bool z0711df5181;uint32_t za89822972e;}z275cc0818e;
bool z9622a3c53f(const struct prod_keypad_key za033d43345,const struct prod_keypad_key z0f144c2120){ANGAZA_ASSERT(
za033d43345.type==PROD_KEYPAD_KEY_TYPE_CHAR,
"\x69\x6e\x76\x61\x6c\x69\x64\x20\x6b\x65\x79\x70\x61\x64\x20\x6b\x65\x79\x20\x74\x79\x70\x65");ANGAZA_ASSERT(
z0f144c2120.type==PROD_KEYPAD_KEY_TYPE_CHAR,
"\x69\x6e\x76\x61\x6c\x69\x64\x20\x6b\x65\x79\x70\x61\x64\x20\x6b\x65\x79\x20\x74\x79\x70\x65");return za033d43345.value
.character==z0f144c2120.value.character;}void zad72251a8f(uint32_t seconds_elapsed){if((z275cc0818e.za89822972e+
seconds_elapsed)>=ANGAZA_SECONDS_IN_DAY){z275cc0818e.za89822972e=ANGAZA_SECONDS_IN_DAY;}else{z275cc0818e.za89822972e+=
seconds_elapsed;}}bool zfb2d3e813b(void){
#ifndef ANGAZA_KEYCODE_NOT_RATE_LIMITED
return(z275cc0818e.za89822972e<z1c4a635f01);
#else
return false;
#endif
}void ze5ef1b9d78(void){if(z275cc0818e.za89822972e>=z1c4a635f01){z275cc0818e.za89822972e-=z1c4a635f01;}}void zaadd37bee4
(struct z85a0b1642b*zf2e84cdb22,const char*z9e974f8831){zf2e84cdb22->z1b0920160b=(0x97a+1401-0xef3);for(uint32_t i=
(0x4f6+3499-0x12a1);z9e974f8831[i]!='\0';++i){ANGAZA_ASSERT(i<z3bc7e19dec,
"\x74\x6f\x6f\x20\x6d\x61\x6e\x79\x20\x6b\x65\x79\x73\x20\x66\x6f\x72\x20\x66\x72\x61\x6d\x65");const struct 
prod_keypad_key key={PROD_KEYPAD_KEY_TYPE_CHAR,{z9e974f8831[i]}};zf2e84cdb22->z9e974f8831[i]=key;++zf2e84cdb22->
z1b0920160b;}}struct z85a0b1642b zf3c4dde316(const char*z9e974f8831){struct z85a0b1642b zf2e84cdb22;zaadd37bee4(&
zf2e84cdb22,z9e974f8831);return zf2e84cdb22;}void z30522e9f22(const struct z85a0b1642b*zf2e84cdb22,char*zdddcb7b2a7){for
(uint8_t i=(0xc11+1513-0x11fa);i<zf2e84cdb22->z1b0920160b;++i){ANGAZA_ASSERT(zf2e84cdb22->z9e974f8831[i].type==
PROD_KEYPAD_KEY_TYPE_CHAR,"\x6e\x6f\x74\x20\x61\x20\x63\x68\x61\x72\x2d\x74\x79\x70\x65\x20\x6b\x65\x79");zdddcb7b2a7[i]
=zf2e84cdb22->z9e974f8831[i].value.character;}}void z482d238b89(const z1986c2d6a8 zd504fcbb7b){z275cc0818e.za89822972e=
(0x15f+5110-0x1555);z275cc0818e.zd504fcbb7b=zd504fcbb7b;z5bd3d5702a();}void zd0b62f0f62(void){}uint32_t zd0c16cb767(
uint32_t seconds_elapsed){zad72251a8f(seconds_elapsed);return z4f0ebd829a(seconds_elapsed);}void z5bd3d5702a(void){
z275cc0818e.zf54199ecde.z1b0920160b=(0x1cd6+724-0x1faa);z275cc0818e.z0711df5181=false;}void z99650ea82c(const struct 
prod_keypad_key key){if(z275cc0818e.zf54199ecde.z1b0920160b<z3bc7e19dec){z275cc0818e.zf54199ecde.z9e974f8831[z275cc0818e
.zf54199ecde.z1b0920160b++]=key;}else{z275cc0818e.z0711df5181=true;}}void ze9c19e4038(void){if(z275cc0818e.zf54199ecde.
z1b0920160b>(0xc70+250-0xd6a)&&!z275cc0818e.z0711df5181){(*z275cc0818e.zd504fcbb7b)(&z275cc0818e.zf54199ecde);}else{
prod_feedback_start(PROD_FEEDBACK_SCRIPT_MESSAGE_REJECTED);}ze5ef1b9d78();z5bd3d5702a();}static struct{struct 
prod_keypad_key z516d003588;struct prod_keypad_key z70b0dce271;uint8_t z5f135a6a92;bool z60c93a0a2b;uint32_t zddb59d138e
;}ze1505bc248;void z93277c0ade(const struct prod_keypad_key z516d003588,const struct prod_keypad_key z70b0dce271,uint8_t
 z5f135a6a92){ze1505bc248.z516d003588=z516d003588;ze1505bc248.z70b0dce271=z70b0dce271;ze1505bc248.z5f135a6a92=
z5f135a6a92;zc607ae7036();}bool z1d423bd097(void){if(ze1505bc248.z5f135a6a92==zbd92582e81){return false;}return(
z275cc0818e.zf54199ecde.z1b0920160b>=ze1505bc248.z5f135a6a92);}void zc607ae7036(){ze1505bc248.z60c93a0a2b=false;}
uint32_t z4f0ebd829a(uint32_t seconds_elapsed){if(ze1505bc248.z60c93a0a2b){if(ze1505bc248.zddb59d138e==UINT32_MAX){
ze1505bc248.zddb59d138e=payg_all_uptime();}uint32_t zed3f589b15=payg_all_uptime()-ze1505bc248.zddb59d138e;if(zed3f589b15
>ANGAZA_DEFAULT_KEYCODE_TIMEOUT){zc607ae7036();z5bd3d5702a();}}return ze1505bc248.z60c93a0a2b?(0x12b+3562-0xf14):
(0x1066+4609-0x21e7);}void zb85ab16ded(const struct prod_keypad_key key){ze1505bc248.zddb59d138e=UINT32_MAX;
prod_mainloop_request_processing();if(zfb2d3e813b()){prod_feedback_start(PROD_FEEDBACK_SCRIPT_KEY_REJECTED);}else if(
z9622a3c53f(key,ze1505bc248.z516d003588)){prod_feedback_start(PROD_FEEDBACK_SCRIPT_KEY_ACCEPTED);ze1505bc248.z60c93a0a2b
=true;z5bd3d5702a();}else if(ze1505bc248.z60c93a0a2b){prod_feedback_start(PROD_FEEDBACK_SCRIPT_KEY_ACCEPTED);if(
z9622a3c53f(key,ze1505bc248.z70b0dce271)){zc607ae7036();ze9c19e4038();}else{z99650ea82c(key);if(z1d423bd097()){
zc607ae7036();ze9c19e4038();}}}else{prod_feedback_start(PROD_FEEDBACK_SCRIPT_KEY_REJECTED);}}void 
payg_interrupts_keypad_handle_key(const struct prod_keypad_key key){zb85ab16ded(key);}
#endif

