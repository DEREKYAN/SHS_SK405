#include "Config.h"
//Light Constants:
/*
#define LIGHT_OFF					0
#define LIGHT_FAULT					1
#define LIGHT_LOW					2
#define LIGHT_NORMAL				        3
*/

enum LIGHT_STATUS_TYPE
{
    LIGHT_OFF, 
    LIGHT_MANUAL_OFF,
    LIGHT_FAULT,
    LIGHT_LOW,
    LIGHT_NORMAL,
};

extern enum LIGHT_STATUS_TYPE Light_State;

//#define SD_12V_REPETITION			8
//#define SD_12V_PERSISTENCE			4		// >4 consecutive ADC readings
//#define SD_12V_THRESHOLD_M			4		// 4/10 ~ 0.464V / 1.16V ratio
//#define SD_12V_THRESHOLD_D			10		// 4/10 ~ 0.464V / 1.16V ratio

#define LIGHT_12V_SHORT_THRESHOLD                   8200            // 8.2V protect 
#define LIGHT_8V5_SHORT_THRESHOLD                   5600            // 5.6 protect 
/*
#define _Port_12V_Low_Batt()		(PORT_PTDD_PTDD3 = 0)
#define _Port_12V_Normal()			(PORT_PTDD_PTDD3 = 1)
#define _Port_12V_Off()				(PORT_PTDD_PTDD2 = 0)
#define _Port_12V_On()				(PORT_PTDD_PTDD2 = 1)
*/
void Light_Init(void);
void Light_Port_Off(void);
void Light_Port_Low(void);
void Light_Port_Hight(void);

void Handle_Light(void);
void Handle_Light_Short(void);
uchar Get_Light_State(void);
bool Is_Light_Enabled(void);

// EOF
