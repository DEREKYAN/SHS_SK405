#ifndef __PV_H__
#define __PV_H__
#include "Config.h"

extern uchar pv_state;
void set_PV_status(uchar new_status);
uchar Get_PV_Status(void);
void event_second_pv(void);


#define PV_MAX_CONNECT_VOLTAGE                  8500u                           // 8.5V
#define PV_MIN_CONNECT_VOLTAGE                  3800u                           // 3.8V
#define TIME_MAX_PV_COUNT                       1500u                           // 1500/10MS = 15S

#define EXIT_0V_CHARGE_VOLTAGE                  2500u                           // Battery voltage 2.5V 
#define BATTERY_MAX_VOLTAGE                     3700u                           // Battery voltage 3.7V 
#define MAX_CHARGING_CURRENT                    2500u                           // Max charging current 2.5A

#define REVERSE_SCP_HIGH                        2500u                           // PV RSC 2.5V
#define REVERSE_SCP_LOW                         700u                            // PV RSC 0.7V

#define BATTERY_ON_TO_CV_HIGHT                  3600u                            // battery voltage 3.6V
#define BATTERY_ON_TO_CV_LOW                    3550u                            // battery voltage 3.55V
#define BATTERY_EXIT_CV                         3400u                            // battery voltage 3.4V

#define VOLTAGE_BATTERY_FULL                    3600u                           // battery voltage 3.6V
#define TIME_BATTERY_FULL_PERSIST               25u                             // 250MS

#define ON_TO_CV_TIME_PERSISTENCE               50u                              // 500Ms
#define EXIT_CV_TIME_PERSISSTENCE               50u                              // 500MS

//#define V_CHG_OFFSET                            200u                             // 200mV
#define V_CHG_OFFSET                            0u                             // 200mV

#define PV_OFF					        0                       // PV State
#define PV_FAULT				        1                       // PV State
#define PV_BATTERY_FULL                                 2                       // PV State    
#define PV_0V_Charge                                    3                       // PV State
#define PV_ON					        4                       // PV State
#define PV_CV                                           5                       // PV State

#define CHARGE_RATE_2					121u	   // Units mA	        
#define CHARGE_RATE_3					241u		        
#define CHARGE_RATE_4					362u		        
#define CHARGE_RATE_5					452u		        
#define CHARGE_HYSTERESIS			30u		        



void Handle_PV(void);
void Disconnect_PV(void);
bool Is_Regulation_Transition(void);
bool Is_Charging(void);
bool Is_Charge_Fault(void);
bool Is_PV_Regulation_Active(void);
void Set_Full_Charge(bool status);
bool Is_Full_Charge(void);
void Increment_Recalibrate_IBatt_Timer(void);
void Zero_Recalibrate_IBatt_Timer(void);

bool Is_PV_CV(void);
bool Is_charging_idle();
void set_pv_bat_ov(u16 data);
void set_pv_fwd_ocp(u16 data);
void set_pv_inp_ov(u16 data);
void set_cv_charging_counter(u16 data);
void set_full_bat_counter(u16 data);
void set_cv_charge_time(uint data);
void set_pv_rev_ocp(u16 data);
void Handler_PV_Port(void);
#endif
// EOF
