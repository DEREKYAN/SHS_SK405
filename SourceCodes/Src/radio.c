#include "Fuel.h"
#include "ADC.h"
#include "UI.h"
#include "UART.h"
#include "PV.h"
#include "Events.h"
#include "Mobile.h"
#include "radio.h"
#include "Mcu.h"
#include "nv.h"
#include "record.h"

static uchar radio_status = RADIO_OFF;

static uint8_t FM_button_backup = 0;


bool Is_FM_Idle(void)
{
    if(radio_status == RADIO_OFF)
    return TRUE;
    return FALSE;
}

uchar get_radio_status(void)
{
#ifdef SKJ
   return radio_status;
#else
   return 0;
#endif
   
}

void handler_FM_button(void)
{
    static bool FM_button_pressed = FALSE;
    if(FM_button_backup == GetFMButton())
    {
        if(FM_button_backup == 0)
        {
            if(!FM_button_pressed)
            {
                FM_button_pressed = TRUE;
                ++radio_status;
                if(radio_status > RADIO_ON_3)
                {
                     radio_status = 0; 
                     DisableFM();
                }
                else
                {
                    EnableFM();
                }
            }
        }
        else
        {
           FM_button_pressed = FALSE;
        }
    }
    else
    {
        FM_button_backup = GetFMButton();
    }
  
}
// EOF
