
#include "angaza/config.h"
#if ANGAZA_LIBRARY_INCLUDE_CABLE
#ifndef zf5004d0e5e
#define zf5004d0e5e
#include "angaza/config.h"
#if ANGAZA_LIBRARY_INCLUDE_CABLE == (0x192b+764-0x1c26)
#include <stdint.h>
#include <stdbool.h>
ANGAZA_PACKED_STRUCT z1f8a0a75ab{uint8_t z99d100e6ed[(0x874+2720-0x12f4)];};typedef void(*zfd35925452)(const struct 
z1f8a0a75ab*);void z4be94fd883(zfd35925452 zd504fcbb7b);void zdf28f0f36a(const struct z1f8a0a75ab*z96b01d3a5a);bool 
zaa9068e83c();
#endif
#endif
#include "angaza/angaza.h"
#include <string.h>
static const uint16_t z9f60b1cefd=(0xd88+5367-0x2180);static const uint16_t z31d265aa28=(0x980+2083-0x117b);static const
 uint16_t z71c0170b3f=(0x47c+9281-0x24d5);static const uint16_t zbd94344361=(0x19ad+5731-0x18a0);static const uint16_t 
z2542b98052=(0x134c+4639-0x2183);static const uint16_t z99fd2cec85=(0x918+2671-0x12bf);static const uint16_t zddb44fe0f5
=(0x1d7a+1130-0x1f8c);static const uint16_t zd441effb3b=sizeof(struct z1f8a0a75ab)*(0x22f5+569-0x2526)+
(0xb57+3218-0x17e8);static struct{zfd35925452 zfe3dbf2c77;uint16_t z91c1d3d929;bool zb2c2a67b96;uint16_t zb433cbfc04;
uint16_t zbe68665ec8;struct z1f8a0a75ab z23666be448;}zfe17c7b0b1;void z4be94fd883(const zfd35925452 zd504fcbb7b){
zfe17c7b0b1.zfe3dbf2c77=zd504fcbb7b;zfe17c7b0b1.z91c1d3d929=(0x81b+7438-0x2529);zfe17c7b0b1.zb2c2a67b96=false;
zfe17c7b0b1.zb433cbfc04=zd441effb3b;zfe17c7b0b1.zbe68665ec8=(0x692+6384-0x1f82);}void zdf28f0f36a(const struct 
z1f8a0a75ab*z96b01d3a5a){zfe17c7b0b1.z23666be448=*z96b01d3a5a;zfe17c7b0b1.zb433cbfc04=(0xbc8+5706-0x2212);zfe17c7b0b1.
zbe68665ec8=(0x82c+7553-0x25ad);prod_cable_set_tx_pin(false);}bool zaa9068e83c(){return zfe17c7b0b1.zb433cbfc04<
zd441effb3b;}static void z832aace6d0(const bool z190ca54686){const uint8_t za19c24c0db=zfe17c7b0b1.z91c1d3d929/
(0xa0f+5323-0x1ed2);zfe17c7b0b1.z23666be448.z99d100e6ed[za19c24c0db]<<=(0x74a+4611-0x194c);zfe17c7b0b1.z23666be448.
z99d100e6ed[za19c24c0db]|=z190ca54686;++zfe17c7b0b1.z91c1d3d929;if(zfe17c7b0b1.z91c1d3d929==sizeof(struct z1f8a0a75ab)*
(0x5af+1583-0xbd6)){(*zfe17c7b0b1.zfe3dbf2c77)(&zfe17c7b0b1.z23666be448);zfe17c7b0b1.z91c1d3d929=(0x11e4+1912-0x195c);}}
static bool z0653eeae8a(){bool zc593da7e75;if(zfe17c7b0b1.zb433cbfc04==zd441effb3b-(0x863+3001-0x141b)){zc593da7e75=true
;}else{const uint8_t za19c24c0db=zfe17c7b0b1.zb433cbfc04/(0x11a1+4603-0x2394);zc593da7e75=zfe17c7b0b1.z23666be448.
z99d100e6ed[za19c24c0db]>>(0x1071+4858-0x2364);zfe17c7b0b1.z23666be448.z99d100e6ed[za19c24c0db]<<=(0x328+6288-0x1bb7);}
++zfe17c7b0b1.zb433cbfc04;return zc593da7e75;}void payg_interrupts_cable_handle_rx_edge(void){if(zaa9068e83c()){return;}
const bool level=prod_cable_get_rx_pin();if(level&&!zfe17c7b0b1.zb2c2a67b96){prod_timcmp_start(z9f60b1cefd);}else if(
zfe17c7b0b1.zb2c2a67b96&&!level){uint16_t duration_us;prod_timcmp_get_microseconds_elapsed(&duration_us);z832aace6d0(
duration_us>z31d265aa28);prod_timcmp_start(z71c0170b3f);}zfe17c7b0b1.zb2c2a67b96=level;}void 
payg_interrupts_timcmp_handle_elapsed(void){if(!zaa9068e83c()){if(zfe17c7b0b1.z91c1d3d929>(0x1979+497-0x1b6a)){
zfe17c7b0b1.z91c1d3d929=(0x840+7601-0x25f1);prod_timcmp_start(zbd94344361);}prod_cable_set_tx_pin(false);}else if(
zfe17c7b0b1.zbe68665ec8<(0x593+798-0x8b0)){++zfe17c7b0b1.zbe68665ec8;prod_cable_set_tx_pin(false);prod_timcmp_start(
z2542b98052);}else if(zfe17c7b0b1.zb433cbfc04==zd441effb3b){prod_cable_set_tx_pin(false);prod_timcmp_stop();}else if(
zfe17c7b0b1.zbe68665ec8%(0x25a1+275-0x26b2)==(0x1331+1502-0x190f)){++zfe17c7b0b1.zbe68665ec8;prod_cable_set_tx_pin(true)
;const uint16_t duration_us=z0653eeae8a()?zddb44fe0f5:z99fd2cec85;prod_timcmp_start(duration_us);}else{++zfe17c7b0b1.
zbe68665ec8;prod_cable_set_tx_pin(false);prod_timcmp_start(z2542b98052);}}
#endif

