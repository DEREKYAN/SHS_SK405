#include "MCU.h"
#include "PV.h"
#include "Events.h"
#include "ADC.h"
#include "Mobile.h"
#include "Fuel.h"
#include "UI.h" // to avoid UI flash during 5V 10mA scenario
#include "UART.h"
#include "radio.h"
#include "nv.h"
#include "record.h"

static void Handle_PV_Condition(void);
static void Handle_PV_Fault(uchar time_PV_fault_step);
static void Handle_BATTERY_OV(void);  
static void Handle_PV_ON(void);
static void Handle_Charge_OC(void);
static void Handle_Reverse_SCP(void);
static void Handle_PVON_Process(void);                      // process PV ON sate 
static void Handle_PV_CV(void);
static void Handle_PV_OV(void);
static void Handle_CV_Process(void);
static void Handle_PV_BATTERY_FULL(void);
static void Send_PV_UART_Message(uchar select);
static void Handle_0V_Charge(void);

//static uchar pv_state = PV_OFF;			// variable value -- PV status 
uchar pv_state = PV_OFF;			// variable value -- PV status 
static uint fault_reset_timer = 0;		// fault time counter, 15 second, clear PV fault automatically 

static bool pv_cv_flag_backup = FALSE;		// CV status backup for CV counter 
static bool flag_battery_full_backup =FALSE;	// Full fuel backup for battery full counter
// Second event for PV time counter

void event_second_pv(void)
{
    static uchar battery_full_second = 0;
  
    if(pv_state == PV_CV)
    {   
        inc_uint_counter(&uart_nvram.nvram.unv_cv_charge_time,1*SPEED_UP_NUMBER);
        if(!pv_cv_flag_backup)
        {
            if(!flag_14_handler_status.data_bit.flag_CV_charging)
            {   
              if(inc_event_counter(&uart_nvram.nvram.unv_cv_charging))    
              flag_14_handler_status.data_bit.flag_CV_charging =1;
            }     
            pv_cv_flag_backup = TRUE;
        }
    }
    else
    {
        pv_cv_flag_backup = FALSE;
        if(adc_ave.ave_i_charging >= CHARGE_RATE_5)
        {
          inc_uint_counter(&uart_nvram.nvram.unv_charge_level_5_time,1*SPEED_UP_NUMBER);
        }
        else if(adc_ave.ave_i_charging>= CHARGE_RATE_4)
        {
          inc_uint_counter(&uart_nvram.nvram.unv_charge_level_4_time,1*SPEED_UP_NUMBER);
        }
        else if(adc_ave.ave_i_charging >= CHARGE_RATE_3)
        {
          inc_uint_counter(&uart_nvram.nvram.unv_charge_level_3_time,1*SPEED_UP_NUMBER);
        }
        else if(adc_ave.ave_i_charging >= CHARGE_RATE_2)
        {
          inc_uint_counter(&uart_nvram.nvram.unv_charge_level_2_time,1*SPEED_UP_NUMBER);
        }
        else if(adc_ave.ave_i_charging > 0)
        {
          inc_uint_counter(&uart_nvram.nvram.unv_charge_level_1_time,1*SPEED_UP_NUMBER);
        }        
    }
    
    if(pv_state == PV_BATTERY_FULL)
    {
        ++battery_full_second;
        if((!flag_battery_full_backup) && (battery_full_second>10))
        {
            inc_event_counter(&uart_nvram.nvram.unv_full_battery);
            flag_battery_full_backup = TRUE;
        }
    }
    else
    {
        flag_battery_full_backup = FALSE;
        battery_full_second = 0;
    }
}

// PV function 
void Handle_PV(void) 
{ 
    switch(pv_state)
    {
      case PV_OFF:
      Handle_PV_Condition();  		
      break;
    
      case PV_FAULT:
      Handle_PV_Fault(1);  
      break;
    
      case PV_BATTERY_FULL:
      Handle_PV_BATTERY_FULL();
      break;    
    
      case PV_0V_Charge:
      Handle_0V_Charge();
      break;
    
      case PV_ON:
      Handle_PV_ON();
      break;
    
      case PV_CV:
      Handle_PV_CV();
      break;
    
      default:
        
      break;    
    }
    Handler_PV_Port();
}


void Handler_PV_Port(void)
{
  if(adc_ave.flag_disable_PV !=1)
  {  
//    pv_state = PV_ON;           // Add for test     
    switch(pv_state)
    {
      static uchar pv_on_delay;           // Add for delay 11.23
      case PV_OFF:
      ClrChrg0vPin();                     // PA5 low
      SetChrgCtrlPin();                   // PA1 high
      pv_on_delay = 0;
      break;
    
      case PV_FAULT:
      ClrChrg0vPin();                     // PA5 low
      SetChrgCtrlPin();                   // PA1 high   
      pv_on_delay = 0;
      break;
    
      case PV_BATTERY_FULL:
      ClrChrg0vPin();                     // PA5 low
      SetChrgCtrlPin();                   // PA1 high    
      break;    
    
      case PV_0V_Charge:
      ClrChrg0vPin();                     // PA5 low
      ClrChrgCtrlPin();                   // PA1 output low
      break;
    
      case PV_ON:
      if(pv_on_delay <5)
      {
        ++pv_on_delay;
      }
      else
      {  
        SetChrg0vPin();                     // PA5 output high  
        
        ClrChrgCtrlPin();                   // PA1 output low
      }
      break;
    
      case PV_CV:
      if(pv_on_delay <5)
      {
        ++pv_on_delay;
      }
      else
      {  
        ClrChrg0vPin();                     // PA5 low
        ClrChrgCtrlPin();                   // PA1 output low
      }
      break;
        
      default:
      break;
    }
  }  
}

// Set PV new status 
void set_PV_status(uchar new_status)
{
     pv_state = new_status;
}

/////////////////////////////////////////////////////////////////////////
static void Handle_PV_BATTERY_FULL(void)
{
    Handle_BATTERY_OV();
    if((adc_ave.ave_v_battery <= BATTERY_EXIT_CV) || ( get_fuel_mAH() < MAX_FUEL))
    {
        if(adc_ave.ave_v_PVfb >= adc_ave.ave_v_battery)
        {
            pv_state = PV_ON;
        }
        else
        {
            pv_state = PV_OFF; 
        }
    }
}

/////////////////////////////////////////////////////////////////////////
static void Handle_PV_CV(void)
{
    Handle_BATTERY_OV();                        // Exceeds 3.7V 40MS
    Handle_PV_OV();                             // PV exceeds 8.5V 
    Handle_Charge_OC();                         // Charging current exceed 2.5A 
    Handle_CV_Process();
}

//Handle CV charging
static void Handle_CV_Process(void)
{
    static uchar time_CV_remove = 0;
    static uchar time_exit_CV = 0;
    static uchar time_battery_full_persist = 0;
    if(pv_state == PV_FAULT)
      return;

    if(adc_ave.ave_i_charging == 0)
    {
          ++time_CV_remove;
          if(time_CV_remove>120)
          {
            time_CV_remove = 0;
            pv_state = PV_OFF; 
            Send_PV_UART_Message(1);
          }        
      }
      else
      {
          time_CV_remove = 0;
      } 
      
      if(adc_ave.ave_v_battery <= BATTERY_EXIT_CV)
      {
          ++time_exit_CV;
          if(time_exit_CV >= EXIT_CV_TIME_PERSISSTENCE)
          {
              time_exit_CV = 0;
              pv_state = PV_ON; 
          }
      }
      else
      {
          time_exit_CV = 0;
      }
      
      if(adc_ave.ave_v_battery >= VOLTAGE_BATTERY_FULL )
      {
        ++time_battery_full_persist;
        if(time_battery_full_persist >= TIME_BATTERY_FULL_PERSIST)
        {
            time_battery_full_persist = 0;
            Send_PV_UART_Message(5);
            set_fuel_max();
            pv_state = PV_BATTERY_FULL; 
            if(!flag_14_handler_status.data_bit.flag_full_battery)
            {   
              if(inc_event_counter(&uart_nvram.nvram.unv_full_battery))       
              flag_14_handler_status.data_bit.flag_full_battery =1;
            }              
        }        
      }
      else
      {
          time_battery_full_persist = 0;
      }     
}

/////////////////////////////////////////////////////////////////////////
static void Handle_PV_ON(void)
{
    Handle_BATTERY_OV();                        // Exceeds 3.7V 40MS
    Handle_Reverse_SCP();                       // Reverse short protect 
    Handle_Charge_OC();                         // Charging current exceed 2.5A   
    Handle_PVON_Process();                      // process PV ON sate 
}

//Hand CV charging 
static void Handle_PVON_Process(void)                      // process PV ON sate 
{
    static uchar time_PV_remove = 0;
    static uchar time_CV_enter = 0;
    if(pv_state == PV_FAULT)
      return;
    
      if((adc_ave.ave_v_PVfb < REVERSE_SCP_LOW) || (adc_ave.ave_i_charging == 0))
      {
          ++time_PV_remove;
          if(time_PV_remove>120)
          {
            time_PV_remove = 0;
            pv_state = PV_OFF; 
            Send_PV_UART_Message(11);
          }        
      }
      else
      {
          time_PV_remove = 0;
      }
   
      if(adc_ave.ave_v_battery >= BATTERY_ON_TO_CV_LOW)
      {
              ++time_CV_enter;
              if(time_CV_enter > ON_TO_CV_TIME_PERSISTENCE)
              {
                pv_state = PV_CV; 
                Send_PV_UART_Message(12);
                time_CV_enter = 0;
              }
      }
      else
      {
          time_CV_enter = 0;
      }
      
      if(adc_ave.ave_v_battery >= BATTERY_ON_TO_CV_HIGHT)
      {
              pv_state = PV_CV; 
              Send_PV_UART_Message(12);
              time_CV_enter = 0;
      }  
      
      Handle_PV_OV();
}


// Detect PV over voltage 
static void Handle_PV_OV(void)
{
    if(adc_ave.ave_v_PVfb>= PV_MAX_CONNECT_VOLTAGE)
    {
        pv_state = PV_FAULT;
        inc_usi_counter(&uart_nvram.nvram.unv_pv_inp_ov);
        Send_PV_UART_Message(7);
    }
}

//Detect PV reverse short proctect   
static void Handle_Reverse_SCP(void)
{
  static uchar time_reverse_scp = 0;
    if((adc_ave.ave_v_PVfb > REVERSE_SCP_LOW ) && (adc_ave.ave_v_PVfb < REVERSE_SCP_HIGH))
    {
        ++time_reverse_scp;
        if(time_reverse_scp>4)                          // >40MS
        {  
          pv_state = PV_FAULT;
          Send_PV_UART_Message(10); 
          
          inc_usi_counter(&uart_nvram.nvram.unv_pv_rev_ocp);
        }
    }
    else
    {
        time_reverse_scp = 0; 
    }
      
}
  
//Detect charging over current fault 
static void Handle_Charge_OC(void)
{
    if(adc_ave.ave_i_charging > MAX_CHARGING_CURRENT)
    {
        pv_state = PV_FAULT;
        Send_PV_UART_Message(6);     
        inc_usi_counter(&uart_nvram.nvram.unv_pv_fwd_ocp);
    }
}        
//Handle is 
static void Handle_BATTERY_OV(void)         
{
  static uchar time_battery_OV = 0;
  
  if(adc_ave.ave_v_battery > BATTERY_MAX_VOLTAGE)
  {
      if(time_battery_OV <= 4)
      {
        if(time_battery_OV ==4)
        {
          pv_state = PV_FAULT;
          Send_PV_UART_Message(2);
          inc_usi_counter(&uart_nvram.nvram.unv_pv_bat_ov);
        }
          ++time_battery_OV;
      }
  }
  else
  {
      time_battery_OV = 0;
  }         
}         
         
///Handle 0V charging 
static void Handle_0V_Charge(void)
{
    if(adc_ave.ave_v_battery > EXIT_0V_CHARGE_VOLTAGE)
    {
      pv_state = PV_ON;
      Send_PV_UART_Message(8);
    }
    Handle_BATTERY_OV();                        // Exceeds 3.7V 40MS
    Handle_Reverse_SCP();                       // Reverse short protect 
}

// This function returns true if the MCU is charging
bool Is_Charging(void) {
  if (pv_state > PV_BATTERY_FULL)    
    return TRUE;
  return FALSE;
}
// Judge whether charging is idle
bool Is_charging_idle(void)
{
    if((pv_state == PV_OFF) || (pv_state == PV_BATTERY_FULL))
      return TRUE;
      return FALSE;
}
// Judge whether PV is CV charging or not 
bool Is_PV_CV(void)
{
    if(pv_state == PV_CV)
      return TRUE;
      return FALSE;
}
// Judge whether PV is fault or not 
bool Is_Charge_Fault(void) {
  if (pv_state == PV_FAULT)
    return TRUE;
  return FALSE;
}
// Judge whether system can charge or not 
static void Handle_PV_Condition(void)
{

    if(adc_ave.ave_v_PVfb >= PV_MAX_CONNECT_VOLTAGE)
    {
        fault_reset_timer = 0;
        pv_state = PV_FAULT;

        inc_usi_counter(&uart_nvram.nvram.unv_pv_inp_ov);
        Send_PV_UART_Message(7);
    }
    else if(adc_ave.ave_v_PVfb >= PV_MIN_CONNECT_VOLTAGE)
    {

        if(adc_ave.ave_v_battery > EXIT_0V_CHARGE_VOLTAGE)
        {
          if(adc_ave.ave_v_battery >= BATTERY_ON_TO_CV_HIGHT)
          {
            pv_state = PV_CV; 
            Send_PV_UART_Message(12);
          }    
          else
          {
            pv_state = PV_ON;
            Send_PV_UART_Message(3);
          }
        }
        else
        {
          pv_state = PV_0V_Charge;
          Send_PV_UART_Message(9);
        }
    }
    else
    {
        pv_state = PV_OFF;
    }
}

// PV fault process 
static void Handle_PV_Fault(uchar time_PV_fault_step)
{
    fault_reset_timer += time_PV_fault_step;
    if(fault_reset_timer > TIME_MAX_PV_COUNT)
    {
        fault_reset_timer =0;
        pv_state = PV_OFF;
    }
}
// Send PV status by UART port 
static void Send_PV_UART_Message(uchar select) {
        Send_Message("\n");
	switch(select) {
        case 1:
             Send_Message("CV END");								          
        break;
          
	case 2:											// END V						
                Send_Message("PEV:");								          
		Send_Number(adc_ave.ave_v_battery);
		break;
	case 3:											// CHARGING
                Send_Message("CHG:");
		Send_Number(adc_ave.ave_v_PVfb);
		break;
	case 5:
                Send_Message("CHD:");					// CHARGED          
		Send_Number(adc_ave.ave_v_battery);
		break;
	case 6:
                Send_Message("PEI:");					// END I          
		Send_Number(adc_ave.ave_v_battery);
		break;
	case 7:
                Send_Message("PH");	// PV HIGH - this display only works if VBAT < 3.48V          
		break;
   
        case 9:
               Send_Message("\nPV 0V CHARG");
               break;
               
        case 10:
              Send_Message("\nPV ROC");
              break;
               
        case 11:
              Send_Message("\nCC END");
              break;
              
        case 12:
              Send_Message("\nPV CV");
              break;
              
        default:
        	break;
          
	}
}

/////////////////////////////////////////////////////////
// EOF
