#include <stdlib.h>
#include <string.h>
#include "Fuel.h"
#include "ADC.h"
#include "UI.h"
#include "UART.h"
#include "PV.h"
#include "Events.h"
#include "Mobile.h"
#include "radio.h"
#include "nv.h"
#include "record.h"

static u16 bcm_ma_accumulation;
static uint bcm_discharging_counter;
static uchar BCM_step = 0;
static uchar uart_fuel_level = 6;          // 0 = empty, 1 = low, 2 = level 1, 3 = level2
                                           // 4 = level 3, 5 = level 4, 6 = level 5

static s16 fuel_level;				// Fuel gauge value, units(mAH)
static u16 fuel_empty;                          // The threshold fuel gauge of empty fuel, units(mAH)
static u16 fuel_low;				// The threshold fuel gauge of low fuel, units(mAH)	
static u16 fuel_level2;				// The threshold fuel gauge of level 2 fuel, units(mAH)
static u16 fuel_level3;				// The threshold fuel gauge of level 3 fuel, units(mAH)
static u16 fuel_level4;				// The threshold fuel gauge of level 4 fuel, units(mAH)
static u16 fuel_level5;				// The threshold fuel gauge of level 5 fuel, units(mAH)

static u16 fuel_MAX;				// Maximum Fuel gauge, units(mAH)
//static uint fuel_in_count = 0;                  // charging current counter base on 5MS
//static uint fuel_out_count = 0;                 // discharging current count base on 5MS
static int fuel_out_in_count = 0;                 // discharging current count base on 5MS

static int fuel_count = 0;			// singed fuel counter (include in,out)
static int fuel_Left = 0;			// It is less than 1mAH in 15 second, so it is left  	

static uchar boolean_flags = 0;			// all boolean flags in this module are stored here to save on RAM

//u16 voltage_low_bat_counter = 0;	        // slope Low battery counter 11.23

static u16 last_fuel_gage[SLOPE_VALUES];/* = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}*/;
static u16 last_voltage[SLOPE_VALUES];/* =   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}*/;
static u16 intervals = 0;			// step of slope detection 

static void slope_detect_low_fuel(s16 fg);
static void clear_fuel_counter(void);

static void Clear_Flag(char mask);
static void Set_Flag(char mask);
static void BCM_handler(int fuel_count);
// Get low fuel threshold, units:mAH

u16 get_fuel_low(void)
{
    return fuel_low;
}
// Get level 2 fuel threshold, units:mAH
u16 get_fuel_level2(void)
{
    return fuel_level2;
}
// Get level 3 fuel threshold, units:mAH
u16 get_fuel_level3(void)
{
    return fuel_level3;
}
// Get level 4 fuel threshold, units:mAH
u16 get_fuel_level4(void)
{
    return fuel_level4;
}
// Get level 5 fuel threshold, units:mAH
u16 get_fuel_level5(void)
{
    return fuel_level5;
}

/*
void set_PN_data(uchar new_pn)
{
    PN_data = new_pn;
}*/
// Initial Fuel gauge and product number to the variable of RMM 
void init_fuel_const(void)
{
#ifdef  SINGLE
        // 2750mAH battery capacity
        fuel_empty = 2u;	// 0mAh
        fuel_low = 750u;	// 5hours * 70mAh + 50mAh spare = 400mAh/0.05mAh 
        fuel_level2 = 1200u;	// 6000*0.20
        fuel_level3 = 2400u;	// 6000*0.40
        fuel_level4 = 3600u;	// 6000*0.60
        fuel_level5 = 4800u;	// 6000*0.80
        fuel_MAX = 5802u;	// 6000*0.967
        fuel_level =  4980u;	// FUEL_STARTING 6000*0.83;               
#endif
#ifdef  BOUBLE
        // 2750mAH battery capacity
        fuel_empty = 2u;	// 0mAh
        fuel_low = 750u;	// 5hours * 70mAh + 50mAh spare = 400mAh/0.05mAh 
        fuel_level2 = 2400u;	// 12000*0.20
        fuel_level3 = 4800u;	// 12000*0.40
        fuel_level4 = 7200u;	// 12000*0.60
        fuel_level5 = 9600u;	// 12000*0.80
        fuel_MAX = 11604u;	// 12000*0.967
        fuel_level =  9960u;	// FUEL_STARTING 12000*0.83;               
#endif        
}
// pre-set fuel gauge, units(mAH)
void set_fuel_mAH(s16 data)
{
    fuel_level = data;
}

// Get fuel gauge, units(mAH)
s16 get_fuel_mAH(void)
{
    return fuel_level;
}
// Set fuel gauge counter to maximum value 
void set_fuel_max(void)
{
    fuel_level = fuel_MAX;
 //   fuel_in_count = 0; 
 //   fuel_out_count = 0;
    fuel_out_in_count = 0;
    fuel_count = 0;
    Clear_Flag((LOW_FUEL_MASK | EMPTY_FUEL_MASK));
}
// Set empty fuel 
void Set_fuel_empty(void)
{

    clear_fuel_counter();  

    if(!Is_Empty_Fuel())
    {
    	Set_Flag(EMPTY_FUEL_MASK);				// bypasses voltage based logic
        Clear_Flag(LOW_FUEL_MASK);				// bypasses voltage based logic 
        set_red_led_blink_conter();
        set_req_record_at_empty_fuel();
        
        if(BCM_step == BCM_MEASUER_EMPTY)
        {
          if(bcm_ma_accumulation > uart_nvram.nvram.unv_BCM_empty_fuel_mAH)
          {
            uart_nvram.nvram.unv_BCM_empty_fuel_mAH = bcm_ma_accumulation;
          }
              BCM_step = BCM_MEASURE_OVER;
        }        
    }
}

static void clear_fuel_counter(void)
{
    fuel_level = 0;           // Derek;
    fuel_out_in_count = 0;
    fuel_count = 0;  
}

// Set low fuel 
void Set_Low_Fuel(void) 
{
    fuel_level = fuel_low-1;        //Derek 
    Set_Flag(LOW_FUEL_MASK);				// bypasses voltage based logic
    Clear_Flag(EMPTY_FUEL_MASK);			// bypasses voltage based logic
    if(BCM_step == BCM_MEASUER_LOW)
    {
      if(bcm_ma_accumulation > uart_nvram.nvram.unv_BCM_low_fuel_mAH)
      {
        uart_nvram.nvram.unv_BCM_low_fuel_mAH = bcm_ma_accumulation;
      }            
      BCM_step = BCM_MEASUER_EMPTY;
//      Send_Message("\nEND BCM_LOW\n");                
  }      
}
// Accumulate fuel gauge once per 5 millisecond 
void handler_fuel(void)
{
    static u16 fuel_5mS_count = 3000;
    static u16 keep_low_empty_count = 0;

    fuel_out_in_count += adc_ave.ave_i_battery;
    ++fuel_5mS_count;
    if(fuel_5mS_count>=3000)            // 15 second
    {
        fuel_5mS_count = 0;
        handler_fuel_level();
    }    
    
    if(adc_ave.ave_v_battery <=V_EMPTY_THESHOLD)	// low voltage, trigger empty fuel 
    {
        if(!Is_Empty_Fuel())
        {
          ++keep_low_empty_count;
          if(keep_low_empty_count>200)                        // 1 second
          {
            Set_fuel_empty();
            if(!flag_14_handler_status.data_bit.flag_empty_battery_trigger)
            {   
              if(inc_event_counter(&uart_nvram.nvram.unv_empty_battery))       
              flag_14_handler_status.data_bit.flag_empty_battery_trigger =1;
            }            
          }
        }
        clear_fuel_counter();         

    }
    else if(adc_ave.ave_v_battery <= V_LOW_FUEL_THESHOLD)	// low voltage, trigger low fuel 	
    {
      if(fuel_level > fuel_low )
      {
          ++keep_low_empty_count;
          if(keep_low_empty_count>200)                  // 1 second
        {
          Set_Low_Fuel();          

          if((get_user_set_flag() == CONST_NV_USED) && (!flag_14_handler_status.data_bit.flag_voltage_trigger_low))
          {   
              inc_event_counter(&uart_nvram.nvram.unv_voltage_low_battery);
              flag_14_handler_status.data_bit.flag_voltage_trigger_low =1;
          }            
            
          uart_nvram.nvram.unv_low_bat_flag = 2;               // voltage triggered
        }
      }
    }
    else
    {
        keep_low_empty_count = 0;
    }
    
    //	convert fuel gauge to fuel level
    if(Is_Empty_Fuel())
    {
        uart_fuel_level = 0;
    }
    else if(Is_Low_Fuel())
    {
        uart_fuel_level = 1;
    }
    else if(Get_Fuel_Level() > LEVEL_5)
    {
        uart_fuel_level = 6;
    }
    else if(Get_Fuel_Level() > LEVEL_4)
    {
        uart_fuel_level = 5;
    }
     else if(Get_Fuel_Level() > LEVEL_3)
    {
        uart_fuel_level = 4;
    }   
     else if(Get_Fuel_Level() > LEVEL_2)
    {
        uart_fuel_level = 3;
    }         
    else
    {
        uart_fuel_level = 2;
    }
}
// Get uart level to print message by UART

uchar get_uart_fuel_level(void)
{
    return uart_fuel_level;
}

// calculate fuel gauge after 15 second accumulation 

static void BCM_handler(int fuel_count)
{
    int bcm_fuel_count;
          
    bcm_fuel_count = fuel_count;
    
    switch(BCM_step)
    {
      case BCM_FULL:
      if((bcm_fuel_count >0) || (pv_state >= PV_ON))
      {
          bcm_ma_accumulation = 0;
          bcm_discharging_counter = 0;
      }
      else if(bcm_fuel_count < 0)
      {
            BCM_step = BCM_MEASUER_LOW;
//            Send_Message("\nStart BCM\n");
      }
      break;
      
      case BCM_MEASUER_LOW:
      case BCM_MEASUER_EMPTY:  
       if((bcm_fuel_count >0) || (pv_state >= PV_ON))
      {
          bcm_ma_accumulation = 0;
          bcm_discharging_counter = 0;
          BCM_step = BCM_MEASURE_OVER;
//          Send_Message("\nEND BCM\n");
      }
      else if(bcm_fuel_count < 0)
      {
          bcm_discharging_counter -=bcm_fuel_count;
          bcm_ma_accumulation +=bcm_discharging_counter/FUEL_COUNT_CONST;
          bcm_discharging_counter %= FUEL_COUNT_CONST;
          if(bcm_ma_accumulation >30000)               // Don't overflower 
          {
              BCM_step = BCM_MEASURE_OVER;
          }
 /*         
          else if(Is_Low_Fuel())
          {
              if(BCM_step == BCM_MEASUER_LOW)
              {
                if(bcm_ma_accumulation > uart_nvram.nvram.unv_BCM_low_fuel_mAH)
                {
                  uart_nvram.nvram.unv_BCM_low_fuel_mAH = bcm_ma_accumulation;
                }            
                BCM_step = BCM_MEASUER_EMPTY;
//                Send_Message("\nEND BCM_LOW\n");                
              }
          }
*/          
      }
      break;
      
      case BCM_MEASURE_OVER:
      bcm_ma_accumulation = 0;
      bcm_discharging_counter = 0;    
      if(pv_state == PV_CV)
      {
          BCM_step = BCM_FULL;
      }
      
      break;
      
      default:
      BCM_step = BCM_MEASURE_OVER;
      break;

      
    }  
}

void handler_fuel_level(void)
{  

      fuel_count =  fuel_out_in_count;
      fuel_out_in_count = 0;
//      fuel_in_count = 0;
//      fuel_out_count = 0;
      BCM_handler(fuel_count);
      fuel_count += fuel_Left;
      fuel_level += fuel_count/FUEL_COUNT_CONST;
      fuel_Left = fuel_count%FUEL_COUNT_CONST;  

      if(fuel_level > fuel_MAX)
      {
          set_fuel_max();			// Accumulate fuel gauge to maximum 
      }
      else if(fuel_level <= 0)
      {
        clear_fuel_counter();      

      }
      else if(adc_ave.ave_v_battery < 2700)          // 
      {
          if(fuel_level > fuel_empty)         // Derek
            fuel_level = fuel_empty;
      }
      else if(fuel_level <= fuel_empty)
      {
        
      }
      else if((fuel_level < fuel_low) && (fuel_level >= fuel_empty))
      {
          Clear_Flag(EMPTY_FUEL_MASK);			// bypasses voltage based logic
          
          if(!Is_Low_Fuel())
          {
              Set_Flag(LOW_FUEL_MASK);			// Low fuel is triggered by accumulate of fuel gauge
              if((get_user_set_flag() == CONST_NV_USED) && (!flag_14_handler_status.data_bit.flag_fuel_computed_low))
              {   
                inc_usi_counter(&uart_nvram.nvram.unv_low_battery);
                flag_14_handler_status.data_bit.flag_fuel_computed_low =1;
              }
              uart_nvram.nvram.unv_low_bat_flag = 0;               		
          }
      }
      else
      {
          Clear_Flag((LOW_FUEL_MASK | EMPTY_FUEL_MASK ));			// Clear low, empty fuel flag when fuel gauge isn't low or empty fuel	
      }
      slope_detect_low_fuel(fuel_level);		// detect low fuel with slope solution

}
// detect low fuel with slope solution
static void slope_detect_low_fuel(s16 fg)
{
  
  static u16 last_ibatt = 0;
  u16 current_ibatt;
  s16 s_current_ibatt = adc_ave.ave_i_battery;	
  u16 current_voltage = adc_ave.ave_v_battery;
  
   if(Is_Low_Fuel() || Is_Empty_Fuel())
  {
      Clear_Fuel_Gage_And_Voltage();		// don't run slope detect in low and empty fule status
      return;
  } 

  if(fg > HALF_FUEL)				// don't run slope detect when fuel gauge is more than half
  {
      Clear_Fuel_Gage_And_Voltage();
      return;
  }

  if(s_current_ibatt >= -100)	
  {
//      Send_Message("\n SLOPE I+/- RESET\n");	// don't run slope detect while discharging current is less than 100mA
      Clear_Fuel_Gage_And_Voltage();    
      return;
  }
  
  current_ibatt =  -s_current_ibatt;
  
  if ((current_ibatt > ((last_ibatt*IBATT_PERCENT_MUL_PLUS)/IBATT_PERCENT_DIV)) || (current_ibatt < ((last_ibatt*IBATT_PERCENT_MUL_MINUS)/IBATT_PERCENT_DIV))) 
  {  
//      Send_Message("\n SLOPE current error RESET\n");		// renew slope detect when discahrging current change more than +/10%
      Clear_Fuel_Gage_And_Voltage();
      last_ibatt = current_ibatt;
      return;
  }
  last_ibatt = current_ibatt;

  if(intervals < MIN_VALUES_TO_ENABLE_SLOPE)
  {
    ++intervals;			// Count time that hold on discharging current 
//    Send_Message("\n SLOPE hold:");
//    Send_Number(intervals);
//    Send_Message("\n");
    return;
  }
  {
    uchar x = 0;
    u16 fuel_delta = 0;
    uchar count = 0;
    for (x=SLOPE_VALUES-1;x>0;x--) 
    {					// first, update our array
	last_fuel_gage[x] = last_fuel_gage[x-1];	// Matrix of voltage and fuel gauge
	last_voltage[x] = last_voltage[x-1];		
    }	
    last_fuel_gage[0] = fg;
    last_voltage[0] = current_voltage;
    
    while ((fuel_delta < SLOPE_MAH_THRESHOLD) && (count < SLOPE_VALUES)) 
    {	// now count and sum fuel increments until we reach 20mAh
	count++;
	if (last_fuel_gage[count] > fuel_level)
	fuel_delta = last_fuel_gage[count] - fuel_level;
    }
    
    if (fuel_delta < SLOPE_MAH_THRESHOLD) 
    {
//        Send_Message("\nSlope fuel delta:");	// Fuel gage change less then threshold, don't delect low fuel 
//	Send_Number(fuel_delta);
//	Send_Message("\n");
        return;
    } 
    else if (last_voltage[count] > current_voltage) 
    {			// test threshold here
        u16 voltage_delta = (last_voltage[count] - current_voltage);				// added compensation here
 /*
        Send_Message("SV");
	Send_Number(voltage_delta);
        Send_Message("FU");
	Send_Number(fuel_delta);
        Send_Message("CU");
	Send_Number(count);
	Send_Message("\n");  
*/        
	if ((voltage_delta *40) >= (fuel_delta*14)) 
        {
            Set_Low_Fuel();			// low fuel is triggered when rate of fall voltage is more than 16mV/40mAH
            if((get_user_set_flag() == CONST_NV_USED) && (!flag_14_handler_status.data_bit.flag_slope_computed_low))
            {   
                flag_14_handler_status.data_bit.flag_slope_computed_low = 1;
                inc_event_counter(&uart_nvram.nvram.unv_slope_low_battery);
            }
            uart_nvram.nvram.unv_low_bat_flag = 1;               	// voltage triggered
	} 
  /*          
        else 
        {
          Send_Message("\nSLOPE:NONE V:");
          Send_Number(last_voltage[count]);
          Send_Message(" Guel:");
          Send_Number(last_fuel_gage[count]);
          Send_Message("\n");
       
	}
*/  
    }
/*    
    else
    {     
         Send_Message("\nlast_voltage:");
         Send_Number(last_voltage[count]);
         Send_Message(" Array number:");
         Send_Number(count) ;
         Send_Message("\n");
    }
*/    
  }
}  
  

//void clear_slope_detect(void)
//{
// also called by main, when going to sleep
void Clear_Fuel_Gage_And_Voltage(void) {
	uchar x = 0;	
	if (intervals != 0) {
		for (x=0; x<SLOPE_VALUES; x++) {
			last_fuel_gage[x] = 0;
			last_voltage[x] = 0;
		}
		intervals = 0;
	}
}

// This function uses a bit mask to set a 1 bit flag
// Called internally

static void Set_Flag(char mask) {
	boolean_flags |= mask;
}

// This function uses a bit mask to clear a 1 bit flag
// Called internally
static void Clear_Flag(char mask) {
	boolean_flags &= (~mask);
}

// This function uses bit arithmetic to return the state of a 1 bit flag
// Called internally
static bool Test_Flag(char mask) {
	if ((boolean_flags & mask) > 0)
		return TRUE;
	return FALSE;
}
// Test whether low fuel flag is true or not 
bool Is_Low_Fuel(void) {
  return Test_Flag(LOW_FUEL_MASK);		// if low fuel
}
// Test whether empty fuel flag is true or not 
bool Is_Empty_Fuel(void) {
  return Test_Flag(EMPTY_FUEL_MASK);		// if empty fuel
}
// Get fuel gauge, units(mAH)
uint Get_Fuel_Level(void) {
  return fuel_level;
}

// EOF
