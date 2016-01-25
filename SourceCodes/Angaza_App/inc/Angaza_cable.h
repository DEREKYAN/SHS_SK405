#ifndef __ANGAZA_CABLE_H__
#define __ANGAZA_CABLE_H__

#include <stdint.h>

#define CONST_4_HOURS_COUNTER            14400u     //4 hours base on second 
#define CABLE_TIME_MAX                   36720000u  // 255*4*3600

extern void Initial_Cable_Data(void);
extern uint8_t cable_send_buf[20] ;

#endif