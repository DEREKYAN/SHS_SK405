#include "Config.h"
#include "UI.h"

//extern uchar PN_Name[] = "SK321 ";

#define BCM_FULL                5
#define BCM_MEASUER_LOW         4
#define BCM_MEASUER_EMPTY       3
#define BCM_MEASURE_END         2
#define BCM_MEASURE_OVER        0


#define FUEL_COUNT_CONST                (15*4*60*200/FUEL_UP_NUMBER)       // Const diviver to get mAH, 4*60 is hours diviver, 200*15 is total sum of 200*15 average current
#define V_EMPTY_THESHOLD                2700                   // Empty fuel threshold voltage 2700mV
#define V_LOW_FUEL_THESHOLD             2800                    //Low fuel threshold voltage 2800mV


#define LOW_FUEL_FG             0     // get low fuel with fuel accumulate way
#define LOW_FUEL_SLOP           1     // get low fuel with slope detect way
#define LOW_FUEL_VOLTAGE        2     // low fuel is triggered by low fuel threshold voltage 

#define EMPTY_FUEL_FG           0     // get empty fuel with fuel accumulate way
#define EMPTY_FUEL_VOLTAGE      1     // empty fuel is triggered by empty fuel threshold voltage

#define SLOPE_VALUES						85	    // total size of slope array
#define MIN_VALUES_TO_ENABLE_SLOPE			24		// 6 minute minimum of steady current

#define IBATT_PERCENT_MUL_PLUS				6		// 6/5 = 120% of measured current
#define IBATT_PERCENT_MUL_MINUS				4		// 4/5 = 80% of measured current
#define IBATT_PERCENT_DIV					5		// divisor for above constants

#define SLOPE_MAH_THRESHOLD					40		// 40mAh 

#define LOW_FUEL_MASK						0x40	// 01000000
#define EMPTY_FUEL_MASK						0x80	// 10000000		

#define EMPTY_FUEL							0	// 0mAh
#define LEVEL_LOW							400u	// 5hours * 70mAh + 50mAh spare = 400mAh/0.05mAh 
#define LEVEL_2								550u	// 2750*0.20
#define LEVEL_3								1100u	// 2750*0.40
//#define HALF_FUEL							1375u	// 2750*0.50
#define HALF_FUEL							1500u	// 3000*0.50
#define LEVEL_4								1650u	// 2750*0.60
#define LEVEL_5								2200u	// 2750*0.80
#define FUEL_STARTING						        2282u	// 2750*0.83
#define FUEL_EIGHTY_FIVE					        2338u	// 2750*0.85

#define FUEL_NINETY							2475u	// 2750*0.90
#define FUEL_NINETY_TWO						        2530u	// 2750*0.92
#define MAX_FUEL							2640u	// 2750*0.967

#define BATTERY_3000MA          1
extern u16 voltage_low_bat_counter;	        // slope Low battery counter 11.23
extern u16 BCM_low_fuel_mAH;
extern u16 BCM_empty_fuel_mAH;

s16 get_fuel_mAH(void);
void set_fuel_max(void);
void init_fuel_const(void);
void handler_fuel(void);
void handler_fuel_level(void);
void clear_slope_detect(void);
void Set_fuel_empty(void);
void Set_Low_Fuel(void); 
uchar get_empty_bat_flag(void);
void Clear_Fuel_Gage_And_Voltage(void);

u16 get_fuel_level2(void);
u16 get_fuel_level3(void);
u16 get_fuel_level4(void);
u16 get_fuel_level5(void);
u16 get_fuel_low(void);
//extern uchar PN_Name[] = "SK312 ";

void set_PN_data(uchar new_pn);

void Clear_Fuel_Gage_And_Voltage(void);
void Set_Low_Fuel(void);
void Set_Empty_Fuel(void);
bool Is_Low_Fuel(void);
bool Is_Empty_Fuel(void);
uint Get_Fuel_Level(void);
uchar get_uart_fuel_level(void);
void set_low_bat_counter(u16 data);
void set_empty_bat_counter(u16 data);
void set_low_bat_flag(uchar data);
void set_empty_bat_flag(uchar data);

// EOF
