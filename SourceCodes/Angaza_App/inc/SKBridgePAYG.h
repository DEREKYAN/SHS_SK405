#ifndef __SKBRIDGEPAYG_H__
#define __SKBRIDGEPAYG_H__

typedef enum{
        CREDIT_EANBLE = 0,
        CREDIT_UNLOCK = 1,
	CREDIT_DISABLE= 2,
	CREDIT_NEAR_DISABLE= 3,
}CREDIT_TYTE;

extern uint32_t time_near_disable;

CREDIT_TYTE get_credit_status(void);
void payg_near_disable_display(uint32_t t);
void handl_payg_all_process(void);
bool get_flag_req_pay_process();

#define TIME_DISPLAY_NEAR_DISABLE   2*60*60
#endif
