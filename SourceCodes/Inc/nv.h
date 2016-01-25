#ifndef __NV_H
#define __NV_H

#include "types.h"
#define CONST_NV_USED           1
#define CONST_NV_UNUSED         0u

#define TYPE_WATCHDOG_RESET     (u16)1
#define TYPE_LOW_VOL_RESET      (u16)2
#define TYPE_POWER_ON_RESET     (u16)3
#define TYPE_SOFTWARE_RESET     (u16)4

extern u16 watchdong_reset_counter ;
extern u16 low_bat_reset_counter;
extern u16 power_on_reset_counter;

uchar* get_flash_SN(void);
u16 get_nv_date(void);
u16 get_nv_vref(void);
void set_nv_vref(u16 vref);
void set_nv_date(u16 date);
void init_nv_flash(void);
void set_nv_trim_flag(void);
void nv_read_int32(uint address,uint *buf, uchar inumbertoread);
bool trim_uart_rx_handler(void);
bool extern_ver_trim(void);
uchar get_trim_status(void);
u16 get_reboot_counter(void);
u16 nv_get_halfword(uint address);
void handler_reboot_counter(u16 type);
u16 get_user_set_flag(void);
void write_nv_user_set_flag(void);

#endif
// EOF
