
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
z8644bc3e61(struct zb76bf3e611*z8ab80f1355);struct z4d335faab1{uint8_t z99d100e6ed[(0x25a+6487-0x1ba1)];};struct 
z2991aa66f2{uint8_t z99d100e6ed[(0x1346+4079-0x232d)];};struct z2991aa66f2 z1b82a670fc(const struct z4d335faab1*key,
const void*data,uint16_t data_size);void z844f2a9dbe(const struct z4d335faab1*key,const void*zd5753f6c49,uint16_t 
z65c78f7747,void*z2f95e13be5,uint16_t ze12ce6b9ca);uint64_t z38e71292f7(const struct z2991aa66f2*value);static inline 
uint16_t zcddc7faa45(uint16_t z2bf3f1cf4d){uint16_t zacea26b15c;uint8_t*z99d100e6ed=(uint8_t*)&zacea26b15c;z99d100e6ed[
(0xd0+2965-0xc65)]=z2bf3f1cf4d>>(0x1392+880-0x16fa);z99d100e6ed[(0x7b+9101-0x2407)]=z2bf3f1cf4d&(0x142f+4591-0x251f);
return zacea26b15c;}static inline uint16_t z020f7db9be(uint16_t zacea26b15c){uint8_t*z99d100e6ed=(uint8_t*)&zacea26b15c;
return(((uint16_t)(z99d100e6ed[(0xef2+3637-0x1d27)]))<<(0x138d+1098-0x17cf))|z99d100e6ed[(0x13ea+3201-0x206a)];}
#endif
#ifndef z82dde3c77c
#define z82dde3c77c
#include <stdint.h>
void z8d129b6c5f(uint8_t*zf8fb9a3323,const uint8_t*zfe2103ff66,const uint32_t z06cbb123e5,const uint8_t*key);
#endif
#include "angaza/config.h"
#include <string.h>
void z6786d67f82(struct z1b13cb8355*z74e6656378,void*z99d100e6ed,uint16_t za97986366b,uint16_t z1b0920160b){
ANGAZA_ASSERT(za97986366b>=z1b0920160b,
"\x73\x74\x72\x65\x61\x6d\x20\x6c\x65\x6e\x67\x74\x68\x20\x65\x78\x63\x65\x65\x64\x73\x20\x63\x61\x70\x61\x63\x69\x74\x79"
);z74e6656378->data=z99d100e6ed;z74e6656378->za97986366b=za97986366b;z74e6656378->z1b0920160b=z1b0920160b;z74e6656378->
zfe9100a4d5=(0x563+4776-0x180b);}void z065a26b842(struct z1b13cb8355*z74e6656378,bool z2271b701d3){ANGAZA_ASSERT(
z74e6656378->zfe9100a4d5<z74e6656378->za97986366b,
"\x61\x74\x74\x65\x6d\x70\x74\x20\x74\x6f\x20\x6f\x76\x65\x72\x66\x6c\x6f\x77\x20\x62\x69\x74\x73\x74\x72\x65\x61\x6d");
const uint16_t z1dad715afb=z74e6656378->zfe9100a4d5>>(0x1bdd+2507-0x25a5);const uint8_t z60e8b6f748=(z1dad715afb+
(0xf75+1576-0x159c))*(0x1251+3604-0x205d)-z74e6656378->zfe9100a4d5-(0x25c+5296-0x170b);const uint8_t z2563c758c3=
z74e6656378->data[z1dad715afb];z74e6656378->data[z1dad715afb]=(((z2563c758c3>>z60e8b6f748)&(0x1553+3594-0x225f))|
z2271b701d3)<<z60e8b6f748;++z74e6656378->zfe9100a4d5;if(z74e6656378->zfe9100a4d5>z74e6656378->z1b0920160b){ANGAZA_ASSERT
(z74e6656378->zfe9100a4d5==z74e6656378->z1b0920160b+(0xac1+2873-0x15f9),
"\x73\x74\x72\x65\x61\x6d\x20\x70\x6f\x73\x69\x74\x69\x6f\x6e\x20\x69\x6e\x76\x61\x72\x69\x61\x6e\x74\x20\x66\x61\x69\x6c\x65\x64"
);++z74e6656378->z1b0920160b;}}void z365bf70760(struct z1b13cb8355*z74e6656378,uint8_t z2271b701d3,uint8_t z20a76dd807){
ANGAZA_ASSERT(z20a76dd807<=(0x1a8b+1366-0x1fd9),
"\x6d\x6f\x72\x65\x20\x74\x68\x61\x6e\x20\x38\x20\x62\x69\x74\x73\x20\x70\x75\x73\x68\x65\x64\x20\x66\x72\x6f\x6d\x20\x75\x69\x6e\x74\x38"
);for(uint8_t i=(0x425+7831-0x22bc);i<z20a76dd807;++i){const uint8_t z190ca54686=(z2271b701d3>>(z20a76dd807-
(0xc53+4299-0x1d1d)))&(0x95c+7061-0x24f0);z065a26b842(z74e6656378,z190ca54686);z2271b701d3<<=(0x745+1109-0xb99);}}bool 
z640f640f9e(struct z1b13cb8355*z74e6656378){ANGAZA_ASSERT(z74e6656378->zfe9100a4d5<z74e6656378->z1b0920160b,
"\x61\x74\x74\x65\x6d\x70\x74\x20\x74\x6f\x20\x6f\x76\x65\x72\x66\x6c\x6f\x77\x20\x62\x69\x74\x73\x74\x72\x65\x61\x6d");
const uint16_t z1dad715afb=z74e6656378->zfe9100a4d5>>(0x364+1299-0x874);const uint8_t z60e8b6f748=(z1dad715afb+
(0x2269+449-0x2429))*(0x1bdf+1184-0x2077)-z74e6656378->zfe9100a4d5-(0x42d+6641-0x1e1d);const uint8_t z2563c758c3=
z74e6656378->data[z1dad715afb];++z74e6656378->zfe9100a4d5;return(z2563c758c3>>z60e8b6f748)&(0x19b2+3036-0x258d);}uint8_t
 za73424de57(struct z1b13cb8355*z74e6656378,uint8_t z20a76dd807){ANGAZA_ASSERT(z20a76dd807<=(0x13c8+2559-0x1dbf),
"\x6d\x6f\x72\x65\x20\x74\x68\x61\x6e\x20\x38\x20\x62\x69\x74\x73\x20\x70\x75\x6c\x6c\x65\x64\x20\x66\x72\x6f\x6d\x20\x75\x69\x6e\x74\x38"
);uint8_t z8f8fb8f533=(0x1cc+8662-0x23a2);for(uint8_t i=(0x598+6849-0x2059);i<z20a76dd807;++i){z8f8fb8f533=(z8f8fb8f533
<<(0xd59+5492-0x22cc))|z640f640f9e(z74e6656378);}return z8f8fb8f533;}uint16_t zf2f51e5f3e(struct z1b13cb8355*z74e6656378
,uint16_t z20a76dd807){ANGAZA_ASSERT(z20a76dd807<=(0xcf0+6124-0x24cc),
"\x6d\x6f\x72\x65\x20\x74\x68\x61\x6e\x20\x38\x20\x62\x69\x74\x73\x20\x70\x75\x73\x68\x65\x64\x20\x66\x72\x6f\x6d\x20\x75\x69\x6e\x74\x38"
);uint8_t zae043bfcc4=z20a76dd807>(0x770+1893-0xecd)?(0xfcf+3494-0x1d6d):z20a76dd807;uint8_t z4633129668=z20a76dd807>
(0xd31+5918-0x2447)?z20a76dd807-(0xef1+4076-0x1ed5):(0x1fb1+800-0x22d1);uint16_t z8f8fb8f533=(0x83b+4456-0x19a3);
z8f8fb8f533=za73424de57(z74e6656378,zae043bfcc4);z8f8fb8f533<<=z4633129668;z8f8fb8f533|=za73424de57(z74e6656378,
z4633129668);return z8f8fb8f533;}static uint32_t z5b5daa8dab(const char*zdddcb7b2a7,const uint8_t count){uint32_t value=
(0xe99+2668-0x1905);for(uint8_t i=(0x5f8+6903-0x20ef);i<count;++i){ANGAZA_ASSERT(((char)(0x79+2250-0x913))<=zdddcb7b2a7[
i]&&zdddcb7b2a7[i]<=((char)(0x1c74+2241-0x24fc)),
"\x63\x68\x61\x72\x20\x6e\x6f\x74\x20\x61\x6e\x20\x41\x53\x43\x49\x49\x20\x64\x69\x67\x69\x74");value=value*
(0xe3b+339-0xf84)+zdddcb7b2a7[i]-((char)(0x13d4+113-0x1415));}return value;}void z64165e61c2(struct zb67573ef41*
zf24083af1c,const char*zdddcb7b2a7,uint16_t z1b0920160b){zf24083af1c->zdddcb7b2a7=zdddcb7b2a7;zf24083af1c->z1b0920160b=
z1b0920160b;zf24083af1c->zfe9100a4d5=(0x856+1509-0xe3b);}uint16_t zb8218113d3(const struct zb67573ef41*zf24083af1c){
return zf24083af1c->z1b0920160b;}uint16_t z2e20d85074(const struct zb67573ef41*zf24083af1c){return zf24083af1c->
zfe9100a4d5;}uint16_t zc2036ed302(const struct zb67573ef41*zf24083af1c){return zf24083af1c->z1b0920160b-zf24083af1c->
zfe9100a4d5;}uint8_t zfe57514e4c(struct zb67573ef41*zf24083af1c,const uint8_t count){return(uint8_t)zd3ebf43594(
zf24083af1c,count);}uint16_t zc0ebd1fee3(struct zb67573ef41*zf24083af1c,const uint8_t count){return(uint16_t)zd3ebf43594
(zf24083af1c,count);}uint32_t zd3ebf43594(struct zb67573ef41*zf24083af1c,const uint8_t count){ANGAZA_ASSERT(zf24083af1c
->zfe9100a4d5+count<=zf24083af1c->z1b0920160b,
"\x74\x6f\x6f\x20\x6d\x61\x6e\x79\x20\x64\x69\x67\x69\x74\x73\x20\x70\x75\x6c\x6c\x65\x64");const uint32_t value=
z5b5daa8dab(zf24083af1c->zdddcb7b2a7+zf24083af1c->zfe9100a4d5,count);zf24083af1c->zfe9100a4d5+=count;return value;}
uint32_t z507a1af07b(struct zb67573ef41*zf24083af1c,uint8_t count,bool*z059d0babaa){if(*z059d0babaa||zc2036ed302(
zf24083af1c)<count){*z059d0babaa=true;return UINT32_MAX;}else{return zd3ebf43594(zf24083af1c,count);}}struct z2d464e12aa
{uint8_t za19c24c0db;uint8_t z70f37c2eba;};static struct z2d464e12aa z3686cdccc0(const struct zb76bf3e611*z8ab80f1355,
uint16_t z272d53e6a2){ANGAZA_ASSERT(z272d53e6a2<((uint16_t)z8ab80f1355->z9a01099768)*(0x1e41+1954-0x25db),
"\x65\x6c\x65\x6d\x65\x6e\x74\x20\x64\x6f\x65\x73\x20\x6e\x6f\x74\x20\x66\x69\x74\x20\x69\x6e\x20\x62\x69\x74\x73\x65\x74"
);struct z2d464e12aa za8bcadb700;za8bcadb700.za19c24c0db=z272d53e6a2>>(0xafc+16-0xb09);za8bcadb700.z70f37c2eba=
z272d53e6a2-za8bcadb700.za19c24c0db*(0xfaf+4271-0x2056);return za8bcadb700;}void z8671bdb0b7(struct zb76bf3e611*
z8ab80f1355,uint8_t*z99d100e6ed,uint8_t z9a01099768){z8ab80f1355->z99d100e6ed=z99d100e6ed;z8ab80f1355->z9a01099768=
z9a01099768;}void zd0bb34864a(struct zb76bf3e611*z8ab80f1355,uint16_t z272d53e6a2){const struct z2d464e12aa za8bcadb700=
z3686cdccc0(z8ab80f1355,z272d53e6a2);z8ab80f1355->z99d100e6ed[za8bcadb700.za19c24c0db]|=(0x6ef+1888-0xe4e)<<za8bcadb700.
z70f37c2eba;}void z9ca5833747(struct zb76bf3e611*z8ab80f1355,uint16_t z272d53e6a2){const struct z2d464e12aa za8bcadb700=
z3686cdccc0(z8ab80f1355,z272d53e6a2);z8ab80f1355->z99d100e6ed[za8bcadb700.za19c24c0db]&=~((0x35d+5251-0x17df)<<
za8bcadb700.z70f37c2eba);}bool zd4d38c4135(const struct zb76bf3e611*z8ab80f1355,uint16_t z272d53e6a2){const struct 
z2d464e12aa za8bcadb700=z3686cdccc0(z8ab80f1355,z272d53e6a2);return z8ab80f1355->z99d100e6ed[za8bcadb700.za19c24c0db]&(
(0x410+8683-0x25fa)<<za8bcadb700.z70f37c2eba);}void z8644bc3e61(struct zb76bf3e611*z8ab80f1355){memset(z8ab80f1355->
z99d100e6ed,(0x1ef1+946-0x22a3),z8ab80f1355->z9a01099768);}
#define z1818f36505(z28b7268651) \
  (((uint64_t)((z28b7268651)[(0x18b6+2201-0x214f)])      ) | \
   ((uint64_t)((z28b7268651)[(0xccb+5979-0x2425)]) <<  (0x12bc+3993-0x224d)) | \
   ((uint64_t)((z28b7268651)[(0xa99+38-0xabd)]) << (0x1b61+575-0x1d90)) | \
   ((uint64_t)((z28b7268651)[(0x1137+2400-0x1a94)]) << (0xb83+2427-0x14e6)) | \
   ((uint64_t)((z28b7268651)[(0x14ff+2610-0x1f2d)]) << (0x60f+2550-0xfe5)) | \
   ((uint64_t)((z28b7268651)[(0x20b7+1564-0x26ce)]) << (0xa1+5407-0x1598)) | \
   ((uint64_t)((z28b7268651)[(0xada+1095-0xf1b)]) << (0x10bd+3093-0x1ca2)) | \
   ((uint64_t)((z28b7268651)[(0x404+6278-0x1c83)]) << (0xd76+5385-0x2247)))
struct z2991aa66f2 z1b82a670fc(const struct z4d335faab1*key,const void*data,uint16_t data_size){struct z2991aa66f2 value
;z8d129b6c5f(value.z99d100e6ed,data,data_size,key->z99d100e6ed);return value;}void z844f2a9dbe(const struct z4d335faab1*
key,const void*zd5753f6c49,uint16_t z65c78f7747,void*z2f95e13be5,uint16_t ze12ce6b9ca){uint8_t z72d9896257[
(0x1d74+535-0x1f86)]={(0x2ea+8680-0x24d2)};ANGAZA_ASSERT(z65c78f7747<=sizeof(z72d9896257)-(0x12e0+3541-0x20b4),
"\x75\x6e\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x20\x73\x65\x65\x64\x20\x73\x69\x7a\x65");memcpy(&z72d9896257[
(0x123c+4174-0x2289)],zd5753f6c49,z65c78f7747);const struct z2991aa66f2 zc151cbd165=z1b82a670fc(key,z72d9896257,
z65c78f7747+(0x1e1+5894-0x18e6));ANGAZA_ASSERT(ze12ce6b9ca<=sizeof(zc151cbd165.z99d100e6ed),
"\x75\x6e\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x20\x6f\x75\x74\x70\x75\x74\x20\x73\x69\x7a\x65");memcpy(z2f95e13be5,
zc151cbd165.z99d100e6ed,ze12ce6b9ca);}uint64_t z38e71292f7(const struct z2991aa66f2*value){return z1818f36505(value->
z99d100e6ed);}
