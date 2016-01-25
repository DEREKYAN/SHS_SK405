#include "Config.h"

// Mobile Constants
#define MOBILE_MANUAL_OFF					0		// Manual off state (via button hold)
#define MOBILE_OFF						1		// Regular off state
#define MOBILE_FAULT						2		// 15 second short protection state
#define MOBILE_ON						3		// USB ports output 5V

#define MOBILE_MINIMUM_CURRENT      20    // Minimum light current 20mA
//#define SD_5V_THRESHOLD						2500		// Battery current 2500mA
#define MOBILE_SHORT_THRESHOLD                                  3000

#define MOBILE_FAULT_TIME                                       750u            // 750*20mS=15S
#define CONST_3DAY                                              (uint)(225*24*60*60/100)

#define MOBILE_IDLE_THESHOLD                                    (u16)31u
#define MOBILE_LOAD_THESHOLD                                    (u16)250u
extern uint USB_heavy_load_time;
extern uint USB_light_load_time;
extern uchar mobile_idle_time;
extern uchar Mobile_State;

void Handle_Mobile(void);
void Set_Mobile_State(uchar set_state);
uchar Get_Mobile_State(void);
bool Is_Mobile_Enabled(void);
bool Is_Mobile_Idle(void);

void handler_alive_time_second(void);
void event_second_user(void);
void set_usb_ocp(u16 data);
void set_usb_port_off_counter(u16 data);
void add_uart_no_usage(s16 no_usage_second);
//void event_second_mobile(void);
void event_second_load(void);

// EOF
