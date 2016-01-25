
#ifndef z82dde3c77c
#define z82dde3c77c
#include <stdint.h>
void z8d129b6c5f(uint8_t*zf8fb9a3323,const uint8_t*zfe2103ff66,const uint32_t z06cbb123e5,const uint8_t*key);
#endif
#include <stdio.h>
#include <string.h>
typedef uint64_t z28e85b1a3d;typedef uint32_t ze4a28528c7;typedef uint8_t z5dc59fe0a7;static z28e85b1a3d z56ecdabb1f;
static z28e85b1a3d z486298ebd8;static z28e85b1a3d zd52e3fbbfc;static z28e85b1a3d zf1102ff605;
#define z2cb2364f68(z29178363a1,b) (z28e85b1a3d)( ((z29178363a1) << (b)) | ( (z29178363a1) >> ((0xa78+6405-0x233d) - (b)\
)) )
#define zf578721fe3(z28b7268651, z652bf6efae)         \
    (z28b7268651)[(0x169+2558-0xb67)] = (z5dc59fe0a7)((z652bf6efae)      ); (z28b7268651)[(0x5a3+7296-0x2222)] = (\
z5dc59fe0a7)((z652bf6efae) >>  (0x219d+627-0x2408)); \
    (z28b7268651)[(0x588+1149-0xa03)] = (z5dc59fe0a7)((z652bf6efae) >> (0xfd0+5206-0x2416)); (z28b7268651)[\
(0x310+9146-0x26c7)] = (z5dc59fe0a7)((z652bf6efae) >> (0xc19+6622-0x25df));
#define z0f993793b4(z28b7268651, z652bf6efae)         \
  zf578721fe3((z28b7268651),     (ze4a28528c7)((z652bf6efae)      ));   \
  zf578721fe3((z28b7268651) + (0x133a+3521-0x20f7), (ze4a28528c7)((z652bf6efae) >> (0x179b+731-0x1a56)));
#define z1818f36505(z28b7268651) \
  (((z28e85b1a3d)((z28b7268651)[(0x20cd+530-0x22df)])      ) | \
   ((z28e85b1a3d)((z28b7268651)[(0x1e53+989-0x222f)]) <<  (0x1c14+2528-0x25ec)) | \
   ((z28e85b1a3d)((z28b7268651)[(0xeda+2645-0x192d)]) << (0x112a+1677-0x17a7)) | \
   ((z28e85b1a3d)((z28b7268651)[(0x559+8128-0x2516)]) << (0x1239+255-0x1320)) | \
   ((z28e85b1a3d)((z28b7268651)[(0x34b+954-0x701)]) << (0x22d7+212-0x238b)) | \
   ((z28e85b1a3d)((z28b7268651)[(0x898+2659-0x12f6)]) << (0x889+5508-0x1de5)) | \
   ((z28e85b1a3d)((z28b7268651)[(0xb9f+3808-0x1a79)]) << (0x1455+435-0x15d8)) | \
   ((z28e85b1a3d)((z28b7268651)[(0xd5f+5613-0x2345)]) << (0xc87+2964-0x17e3)))
static void zcb7f579bf1(void){do{z56ecdabb1f+=z486298ebd8;z486298ebd8=z2cb2364f68(z486298ebd8,(0x1069+3165-0x1cb9));
z486298ebd8^=z56ecdabb1f;z56ecdabb1f=z2cb2364f68(z56ecdabb1f,(0x22b6+634-0x2510));zd52e3fbbfc+=zf1102ff605;zf1102ff605=
z2cb2364f68(zf1102ff605,(0x1e50+1599-0x247f));zf1102ff605^=zd52e3fbbfc;z56ecdabb1f+=zf1102ff605;zf1102ff605=z2cb2364f68(
zf1102ff605,(0x3d+4357-0x112d));zf1102ff605^=z56ecdabb1f;zd52e3fbbfc+=z486298ebd8;z486298ebd8=z2cb2364f68(z486298ebd8,
(0xd44+2106-0x156d));z486298ebd8^=zd52e3fbbfc;zd52e3fbbfc=z2cb2364f68(zd52e3fbbfc,(0x7a2+6725-0x21c7));}while(
(0xd42+4540-0x1efe));}void z8d129b6c5f(uint8_t*zf8fb9a3323,const uint8_t*zfe2103ff66,const uint32_t z06cbb123e5,const 
uint8_t*z324491a3e3){const z5dc59fe0a7*z70b0dce271=zfe2103ff66+z06cbb123e5-(z06cbb123e5%sizeof(z28e85b1a3d));const int 
z11ac23e795=z06cbb123e5&(0x1045+1748-0x1712);z28e85b1a3d b=((z28e85b1a3d)z06cbb123e5)<<(0x1474+2654-0x1e9a);z56ecdabb1f=
0x736f6d6570736575ULL;z486298ebd8=0x646f72616e646f6dULL;zd52e3fbbfc=0x6c7967656e657261ULL;zf1102ff605=
0x7465646279746573ULL;const z28e85b1a3d z6a0b0fafcf=z1818f36505(z324491a3e3);const z28e85b1a3d z3981d7efaa=z1818f36505(
z324491a3e3+(0xd27+3210-0x19a9));zf1102ff605^=z3981d7efaa;zd52e3fbbfc^=z6a0b0fafcf;z486298ebd8^=z3981d7efaa;z56ecdabb1f
^=z6a0b0fafcf;for(;zfe2103ff66!=z70b0dce271;zfe2103ff66+=(0x49c+2919-0xffb)){const z28e85b1a3d m=z1818f36505(zfe2103ff66
);zf1102ff605^=m;zcb7f579bf1();zcb7f579bf1();z56ecdabb1f^=m;}switch(z11ac23e795){case(0x13ed+886-0x175c):b|=((
z28e85b1a3d)zfe2103ff66[(0x56b+4070-0x154b)])<<(0x1dd5+2237-0x2662);case(0x971+4150-0x19a1):b|=((z28e85b1a3d)zfe2103ff66
[(0x2c+8078-0x1fb5)])<<(0x88c+3669-0x16b9);case(0x735+2469-0x10d5):b|=((z28e85b1a3d)zfe2103ff66[(0x1688+953-0x1a3d)])<<
(0x143f+3095-0x2036);case(0x17eb+3361-0x2508):b|=((z28e85b1a3d)zfe2103ff66[(0x21+3038-0xbfc)])<<(0x5cc+2273-0xe95);case
(0x7b6+3680-0x1613):b|=((z28e85b1a3d)zfe2103ff66[(0x109b+680-0x1341)])<<(0xb5+4530-0x1257);case(0x46c+3939-0x13cd):b|=((
z28e85b1a3d)zfe2103ff66[(0xfa8+3346-0x1cb9)])<<(0x1175+2391-0x1ac4);case(0x16c9+2535-0x20af):b|=((z28e85b1a3d)
zfe2103ff66[(0x125d+638-0x14db)]);break;case(0x857+738-0xb39):break;}zf1102ff605^=b;zcb7f579bf1();zcb7f579bf1();
z56ecdabb1f^=b;zd52e3fbbfc^=(0x1738+1264-0x1b29);zcb7f579bf1();zcb7f579bf1();zcb7f579bf1();zcb7f579bf1();b=z56ecdabb1f^
z486298ebd8^zd52e3fbbfc^zf1102ff605;z0f993793b4(zf8fb9a3323,b);}
