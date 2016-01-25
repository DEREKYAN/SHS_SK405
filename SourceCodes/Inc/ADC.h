#ifndef ADC_H
#define ADC_H
#include "Config.h"
#include "main.h"

struct AVG_ADC_Struct
{
  u16 V_Charge;               
  u16 avg_vbatt_5mS;
  u16 vkey;
  u16 avg_i_charge;
  u16 avg_imobile;
  u16 avg_v_charge;
};


struct ADC_RESULT_STRUCT
{
    u16 battery_adc;
    u16 uc_adc;  
    u16 PVfb_adc;
    u16 USBfb_adc;
    u16 Lightfb_adc;
    u16 key_adc;
    u16 charging_adc;
    u16 load_adc;
    u16 v_vdd;
    u16 v_PVfb;
    u16 v_USBfb;
    u16 v_lihgtfb;
    int i_charging;
    int i_discharging;
    int i_battery;
    u16 discharging_adc_offset;
    GLP_bool Flag_Charing_Discharge;              // 0 is charging, and is charing 
};

struct ADC_SUM_STRUCT
{
    u16 sum_v_battery;
    u16 sum_v_PVfb;
    u16 sum_v_USBfb;  
    uint sum_v_lihgtfb;
    int sum_i_battery;  
};

struct ADC_AVE_AVERAGE
{
    u16 ave_v_battery;
    u16 ave_v_PVfb;
    u16 ave_v_USBfb;  
    u16 ave_v_lihgtfb;
    int ave_i_battery;  
    int ave_i_load;
    int ave_i_charging;
    uchar counter;
    uchar pv_measuere_counter;
    uchar flag_disable_PV;
   
};

#define MIN_CURRENT                             30

#define START_BATTERY_VOLTAGE			3300	// Default initial battery voltage 

#define UC_ADC                                  ADC_Channel_0
#define PVFB_ADC        	                ADC_Channel_7		// ADC7 - PA7
#define LINGH_ADC       			ADC_Channel_9		// ADC9 - PB1
#define USB_ADC 				ADC_Channel_8		// ADC8 - PB0
#define KEY_ADC                                 ADC_Channel_4           // ADC4 - PA4

#define	VCHRG						  ADC_Channel_0		// ADC0 - PA0
#define VBATT							23		// how are we measuring this?
#define VKEY              ADC_Channel_4           // ADC4 - PA4

#define IMOBILE						ADC_Channel_8		// ADC8 - PB0
#define ILIGHT						ADC_Channel_9		// ADC9 - PB1
#define VREFINT           ADC_Channel_17          // ADC17 - Vrefint
#define VEXTREF           ADC_Channel_5           // ADC17 - Vrefint

#define AVG_ILIGHT                50              
#define AVG_IMOBILE               51   
#define AVG_VC                    52

#define ILIGHT_AVG_SAMPLES				10		// samples, for average ilight
#define VREFINT_AVG_SAMPLES       10
#define ADC_AVG_SAMPLES           4
#define STOP_ADC_SAMPLES          10
#define I_AVG_SAMPLE              10
#define AVG_ICHRG						      14		// ADC variable - Average of ICHRG
#define AVG_ICHRG_CTRL					  15		// ADC variable - Average of ICHRG
#define AVG_IBATT						      16		// ADC variable - Average of IBATT

#define CHARG_CURRENT_OFFSET_MA   30              // ADC charging current offset when Ichrg<300mA

extern s16 avg_ibattery;          // Variable signed average battery current
extern bool ave_ilight_update;    // Flag ADC sample for light control

extern struct ADC_RESULT_STRUCT adc_result;
extern struct ADC_SUM_STRUCT adc_sum;
extern struct ADC_AVE_AVERAGE adc_ave;

void Run_ADC_Samples();             // Run ADC samples
void ADC_Vrefint_TRIM(void);      // ADC for trim 
uchar get_bat_in_out(int snum);       // Get sign of battery current ('+','-',' ')
uint Sample_ADC(uint channel);    // Get ADC sample value
void stop_adc_samples(void);      // ADC sample process function @sleep & hibernation
void set_max_charge_rate(u16 data);   // Set maximux charging current
void set_vrefint_mv(u16 vref);        // Set internal reference voltage (mV)
void Initial_ADC_Offset(void);
void stop_delay(uint t);
void Handle_short_protect(void);

#endif
// EOF
