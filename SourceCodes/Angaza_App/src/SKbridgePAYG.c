#include "prod_feedback.h"
#include "SKBridgePAYG.h"
#include <angaza/angaza.h>
#include "stm32f0xx_gpio.h"
static CREDIT_TYTE credit_status;
static bool flag_req_pay_process = false;
uint32_t time_near_disable = 0;

CREDIT_TYTE get_credit_status(void)
{
  enum payg_state new_state = payg_state_get_current();

  switch (new_state)
  {
    case PAYG_STATE_DISABLED:
      credit_status = CREDIT_DISABLE;
    break;

    case PAYG_STATE_ENABLED_NEAR_DISABLED:
      credit_status = CREDIT_NEAR_DISABLE; 
    break;

    case PAYG_STATE_ENABLED:
      credit_status = CREDIT_EANBLE;
    break;
    case PAYG_STATE_ENABLED_UNLOCKED:
      credit_status = CREDIT_UNLOCK;
    break;
  }
  return credit_status;
}


void payg_near_disable_display(uint32_t t)
{

    static enum payg_state backup_status;
    enum payg_state new_state = payg_state_get_current();
    if(new_state == PAYG_STATE_ENABLED_NEAR_DISABLED)
    {
        time_near_disable += t;
        if((time_near_disable >= TIME_DISPLAY_NEAR_DISABLE) || (backup_status >= PAYG_STATE_ENABLED) )
        {
          time_near_disable = 0;
          pay_ng_indication();
//          start_near_disable_display();
        }
    }
    else
    {
        time_near_disable = 0;
    }
    backup_status = new_state;
}

enum prod_mainloop_error prod_mainloop_request_processing(void)
{
    flag_req_pay_process = true;
    return PROD_MAINLOOP_ERROR_NONE;
}

void handl_payg_all_process(void)
{
    if(flag_req_pay_process)
    {
      flag_req_pay_process = false;
      payg_all_process(0);
    }
}
      
bool get_flag_req_pay_process(void)
{
        return flag_req_pay_process;
}
  
void prod_cable_set_tx_pin(bool level)
{
  if(level)
  {
    GPIO_SetBits(GPIOF, GPIO_Pin_0);
  }
  else
  {  
    GPIO_ResetBits(GPIOF, GPIO_Pin_0);
  }
//  GPIO_WriteBit(GPIOF, GPIO_Pin_0, level);
}


bool prod_cable_get_rx_pin()
{
     bool flag_rx;
    if(Bit_RESET == GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_1))
    {
        flag_rx = false;
      
    }
    else
    {
        flag_rx = true;
    }
    return flag_rx;
 //  return GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_1);
}      