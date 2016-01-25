#ifndef RADIO_H
#define RADIO_H

#include "types.h"


#define RADIO_OFF               0
#define RADIO_ON_1              1
#define RADIO_ON_2              2
#define RADIO_ON_3              3

uchar get_radio_status(void);
void handler_FM_button(void);
bool Is_FM_Idle(void);
void set_radio_working_time(uint data);

#endif
// EOF
