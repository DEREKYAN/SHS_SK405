#ifndef _CONFIG_H
#define _CONFIG_H

#include "stm32f0xx.h"
#include "Board.h"
#define MCU_TYPE	MCU_TYPE_STM32F030


typedef enum {FALSE = 0, TRUE = !FALSE} bool;
typedef unsigned int uint;
typedef unsigned char		uchar;
typedef unsigned short int  u16;
typedef short int  s16;
#define USE_DEBUG       1


#endif
// EOF
