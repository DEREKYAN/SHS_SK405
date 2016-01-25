#include "Angaza_cable.h"
#include "prod_diag.h"
#include "Fuel.h"
#include "record.h"
#include "nv.h"
#include "pv.h"

uint8_t cable_send_buf[20] ;
const uint8_t COMPRESS_TABLE_A[15] = {0u, 1u, 2u, 3u, 5u, 7u, 10u, 14u, 20u, 28u, 40u, 56u, 79u, 111u, 156u};

static uint8_t get_compress_A_low(uint16_t n);
static uint8_t get_compress_A_high(uint16_t n);
static uint8_t get_counter_8bit(uint16_t n);               // for D6
static uint8_t get_counter_4bit(uint16_t m, uint16_t n);    
static uint8_t get_cable_type_fuel(uint16_t f);
static uint8_t get_cable_time(uint32_t t);
void Initial_Cable_Data(void)
{
    uint16_t f;
    f = get_fuel_mAH();
    cable_send_buf[0] = get_cable_type_fuel(f);
    cable_send_buf[1] = get_compress_A_high(uart_nvram.nvram.unv_pv_bat_ov) +  get_compress_A_low(uart_nvram.nvram.unv_pv_fwd_ocp);
    cable_send_buf[2] = get_compress_A_high(uart_nvram.nvram.unv_pv_rev_ocp) +  get_compress_A_low(uart_nvram.nvram.unv_pv_inp_ov);
    cable_send_buf[3] = get_compress_A_high(uart_nvram.nvram.unv_USB_ocp) +  get_compress_A_low(uart_nvram.nvram.unv_any_fault);   
    cable_send_buf[4] = get_counter_8bit(uart_nvram.nvram.unv_low_battery);
    cable_send_buf[5] = get_compress_A_high(uart_nvram.nvram.unv_slope_low_battery) +  get_compress_A_low(uart_nvram.nvram.unv_voltage_low_battery);
    cable_send_buf[6] = get_counter_8bit(uart_nvram.nvram.unv_empty_battery);
    cable_send_buf[7] = get_counter_8bit(uart_nvram.nvram.unv_cv_charging);
    cable_send_buf[8] = get_counter_4bit(watchdong_reset_counter,low_bat_reset_counter);      
    cable_send_buf[9] = get_counter_4bit(power_on_reset_counter,uart_nvram.nvram.unv_manually_turn_off);          
    cable_send_buf[10] = get_compress_A_high(uart_nvram.nvram.unv_usb_port_off);
 
    cable_send_buf[11] = get_cable_time(uart_nvram.nvram.unv_low_battery_discharge_time);  
    cable_send_buf[12] = get_cable_time(uart_nvram.nvram.unv_discharge_level_1_time);
    cable_send_buf[13] = get_cable_time(uart_nvram.nvram.unv_discharge_level_2_time);      
    cable_send_buf[14] = get_cable_time(uart_nvram.nvram.unv_discharge_level_3_time);  
    
    cable_send_buf[15] = get_cable_time(uart_nvram.nvram.unv_discharge_level_4_time);
    cable_send_buf[16] = get_cable_time(uart_nvram.nvram.unv_discharge_level_5_time);
    cable_send_buf[17] = get_cable_time(uart_nvram.nvram.unv_discharge_level_6_time);   
    cable_send_buf[18] = get_cable_type_fuel(uart_nvram.nvram.unv_BCM_empty_fuel_mAH);
    cable_send_buf[19] = CABLE_VERSION;
    if(uart_nvram.nvram.unv_max_rate > 2000)
      cable_send_buf[19] +=1;
}



static uint8_t get_cable_time(uint32_t t)
{
    uint8_t r;
    if(t > CABLE_TIME_MAX)
      t = CABLE_TIME_MAX;
    r = t/CONST_4_HOURS_COUNTER;
    return r;
}

static uint8_t get_cable_type_fuel(uint16_t f)
{
    uint8_t r;
    if(f>4000)
       f = 4000;
    r = (255 * f)/4000;
    return r;
}


static uint8_t get_compress_A_high(uint16_t n)
{
  uint8_t t;
  t = get_compress_A_low(n);
  t *= 0x10;
  return t;
}

static uint8_t get_compress_A_low(uint16_t n)
{
    uint8_t r;
    for(r = 0; r<=15; r++)
    if(n<=COMPRESS_TABLE_A[r])
      break;
    return r;
}



static uint8_t get_counter_8bit(uint16_t n)               // for D6
{
    uint8_t r;
    if(n>= 255)
      n = 255;
        r = n;
    return r;
}



static uint8_t get_counter_4bit(uint16_t m, uint16_t n)               
{
    uint8_t r;
    if(m>15)
      m = 15;
    if(n>15)
      n = 15;
        r = m*0x10 + n;    
    return r;  
}




