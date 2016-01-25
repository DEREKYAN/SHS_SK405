#include "Config.h"
#include "main.h"

#define DGBUG           1
#define PN 		"SK405 "
#define CABLE_VERSION   2*0
//#define EN_PROTECTION           1             // Release must enable
#define VERSION         "V0.0 "		//always leave a space at the end here
#define SPEED_UP_NUMBER         1
#define FUEL_UP_NUMBER          1

#define SPEED_UP_CALIBRATION    1
//#define DEBUG_LSI_CALIBRATION   1 
//#define CLEAR_VERSION         1
//#define DEBUG_PORT              1
#define ANGAZA                  1
#define SING_BATTERY_PACK       1

#ifdef  SING_BATTERY_PACK
#define SINGLE           1
#else
#define BOUBLE           1
#endif

#define UI_PERSISTENCE_MAX_LEVEL	        160
#define UI_PERSISTENCE_ON_LEVEL		        120
#define UI_PERSISTENCE_INIT		        115
#define UI_PERSISTENCE_OFF_LEVEL	        40
#define UI_PERSISTENCE_MIN_LEVEL	        1

#define BLINK_DUTY			        2
#define BLINK_PERIOD			        2000	                	// on for 10ms every 5000ms

void Handle_UI(void);
void TurnOff_UI(void); 
void Clear_Red_LED_Blink_Timer(void);
void red_led_blink(void);
void set_red_led_blink_conter(void);
void TurnOn_UI(void);
void Handler_Credit_UI_Event(void);
GLP_bool Is_PV_idle(void);
void reflash_fuel_LED_bar(void);

// EOF
