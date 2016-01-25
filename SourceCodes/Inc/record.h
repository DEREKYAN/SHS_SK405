#ifndef __RECORD_H
#define __RECORD_H
#include "Config.h"
#include "record.h"

union u_recond_nv
{
  struct
  {
      u16 unv_pv_bat_ov;                // 2
      u16 unv_pv_fwd_ocp;               // 2+2=4
      u16 unv_pv_rev_ocp;               // 4+2= 6
      u16 unv_pv_inp_ov;                // 6+2 = 8
      u16 unv_USB_ocp;                  // 8+2 = 10
      u16 unv_light_scp;                // 10+2=12
      u16 unv_any_fault;                // 12+2 = 14
      u16 unv_low_battery;              // 14+2 = 16
      u16 unv_slope_low_battery;        // 16+2 = 18
      u16 unv_voltage_low_battery;      // 18+2 = 20
      u16 unv_empty_battery;            // 20+2 = 22
      u16 unv_cv_charging;              // 22+2 = 24
      u16 unv_full_battery;             // 24+2 = 26
      u16 unv_manually_turn_off;        // 26+2 = 28
      u16 unv_usb_port_off;             // 28+2 = 30
      u16 unv_button_press;             // 30+2 = 32
      uint unv_inventory_time;          // 32+4 = 36
      uint unv_working_life_time;       // 36+4 = 38
      u16 unv_max_rate;                 // 38+2 = 40
      uint unv_cv_charge_time;          // 40+4 = 44
      uint unv_charge_level_1_time;     // 44 + 4= 48
      uint unv_charge_level_2_time;     // 48 + 4= 52
      uint unv_charge_level_3_time;     // 52 + 4= 56
      uint unv_charge_level_4_time;     // 56 + 4 = 60
      uint unv_charge_level_5_time;     // 60 + 4 = 64      
      uint unv_low_battery_discharge_time;    // 64+4 = 68
 
      uint unv_discharge_level_1_time;  // 68 + 4 = 72          
      uint unv_discharge_level_2_time;  // 72 +4 = 76
      uint unv_discharge_level_3_time;  // 76 + 4 = 80     
      uint unv_discharge_level_4_time;  // 80 + 4 =8 4    
      uint unv_discharge_level_5_time;  // 84 + 4 = 88
      uint unv_discharge_level_6_time;  // 88 + 4 = 92     
      u16 unv_BCM_low_fuel_mAH;              // 92 + 2 = 94
      u16 unv_BCM_empty_fuel_mAH;            // 94 + 2 = 96
      u16 unv_low_bat_flag;                // 96 + 2 = 98    
      u16 unv_checksum;                      // 98 + 2 = 100  
      
  }nvram;
  
  uint nvram_buff[25];              // 25*4 = 24
  
};

extern union u_recond_nv uart_nvram;

#define RECORD_START_FLASH_ADDRESS      0x08007800              // PAGE 28
#define RECORD_END_FLASH_ADDRESS        0x08007C00              // PAGE 
//bool set_record_data(void);
void save_data_to_NV(void);
void read_data_from_NV(void);    
void save_record_data(void);
void event_second_record(u16 t);
void set_req_record_at_empty_fuel(void);

#endif 
// EOF
