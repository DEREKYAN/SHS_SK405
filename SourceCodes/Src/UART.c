#include "UART.h"
#include "ADC.h"
#include "Fuel.h"
#include "Mobile.h"
#include "Events.h"
#include "radio.h"
#include "UI.h"
#include "nv.h"
#include "PV.h"
#include "Light.h"
#include "SKBridgePAYG.h"
#include "record.h"
#include <core_cmFunc.h>
#include "Angaza_cable.h"
#include <stdio.h>
#include <stdlib.h>
// UART send + receive buffer variables

#define UART_IDLE_MS                    10000
uchar UART_output_standby_counter = 0;
static volatile uchar uart_rx_step = 0;
static volatile bool UART_Active = FALSE;                                       // flag is set active when buffered UART message is transmitting
static volatile uchar send_buffer[UART_BUFFER_SIZE_TX];		                // messages are buffered here, and then added to UDAT register to send
static volatile uchar tx_buffer_send = 0;					// location in buffer where messages are sent from
static volatile uchar tx_buffer_enter = 0;					// location in buffer where messages are added to
static volatile uchar receive_buffer[UART_BUFFER_SIZE_RX];	                // received messages are buffered here
static volatile uchar rx_buffer_index = 0;					// location of the next open spot in the rx buffer
static u16 uart_rx_idle_counter = 0;
static void  send_hours_number(uint h);
static void glp_command(void);
static void handle_command(uchar command_type);
GLP_bool flag_uart_output_start = GLP_FALSE;
void SoftReset(void); 
extern void payg_all_deinit(void);
/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/
/**
  * @brief  This function handles USART1 TX, RX interrupter.
  * @param  None
  * @retval None
  */
       
void USART1_IRQHandler(void)            
{
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET){
      	receive_buffer[rx_buffer_index] = USART_ReceiveData(USART1);;				// save receive register to buffer
	rx_buffer_index++;										// increment buffer
	rx_buffer_index &= UART_RX_MASK;                                        // test for overflow
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);         
    }
  
    if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET){
 	if (tx_buffer_send != tx_buffer_enter) {				// if buffer still has more characters
            USART_SendData(USART1,send_buffer[tx_buffer_send]);		// add next buffered character to send register
            tx_buffer_send++;										// increment buffer
            tx_buffer_send &= UART_TX_MASK;	
	} else {												// else all buffered messages have been sent
            USART_ITConfig(USART1, USART_IT_TXE, DISABLE);              // clear transmit interrupt to end tx
              UART_Active = FALSE;
	}
    }   
}

// Get UART sending status 
bool get_UART_Active(void)
{
    return UART_Active;
}

// Start to send data by uart, enable uart TX interrupt 
void UART_TX_SLEEP_STOP(uchar t)
{
    __disable_interrupt();
 
    tx_buffer_enter = tx_buffer_send; 
    send_buffer[tx_buffer_enter] = t;
    tx_buffer_enter++;									// increment size of buffer
    tx_buffer_enter &= UART_TX_MASK;	   
 
    if(UART_Active == FALSE)
    {
        if(tx_buffer_send != tx_buffer_enter)
        {
            UART_Active = TRUE;
            USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
         }
    }
    __enable_interrupt();   
  
}

// Receive UART data 
void UART_TX(uchar data)
{
    __disable_interrupt();
    send_buffer[tx_buffer_enter] = data;
    tx_buffer_enter++;									// increment size of buffer
    tx_buffer_enter &= UART_TX_MASK;					// rollover buffer to protect from overflow

    if(UART_Active == FALSE)
    {
        if(tx_buffer_send != tx_buffer_enter)
        {
            UART_Active = TRUE;
            USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
         }
    }
    __enable_interrupt();    
 }
// Send number char 
void Send_Char(uchar letter)
{
     UART_TX('0' + letter);	
     UART_TX(' ');
}


void send_int_number(int snumber)
{
    UART_TX(get_bat_in_out(snumber));
    Send_Number(abs(snumber));
  
}

// This function receives a one to five digit number, parses it into the send buffer in ascii, and initiates transmit
// Called everywhere
void Send_Number(uint number) {
  if (number > 9999)											// is it a 5 digit number

   UART_TX('0' + ((number / 10000) % BASE_TEN));	// enter 10000 digit
  if (number > 999)											// is it a 4 digit number

    UART_TX('0' + ((number / 1000) % BASE_TEN));	// enter 1000 digit
  if (number > 99)
    UART_TX('0' + ((number / 100) % BASE_TEN));

  if (number > 9)
    UART_TX('0' + ((number / 10) % BASE_TEN));


    UART_TX('0' + (number % BASE_TEN));
    UART_TX(' ');

}

// This function receives a string, parses it into the send buffer, and initiates transmit
// Called everywhere
void Send_Message(uchar *string) {
  char byte;
  while(byte = *string++)										// while another character in message
  UART_TX(byte);
}

// Get uart receiver data 
bool get_uart_char(uchar *ch)
{
  bool rx_flag;
 
  static uchar buffer_last = 0;
   rx_flag = FALSE;
   __disable_interrupt();
  if(buffer_last != rx_buffer_index)
  {
     *ch = receive_buffer[buffer_last];
     buffer_last++;												// increment buffer
     buffer_last &= UART_RX_MASK;
     rx_flag = TRUE;
     
     UART_TX(*ch);
  }
  __enable_interrupt();

  return rx_flag;		
}


bool get_uart_command_idle(void)
{
      bool flag_uart_com_idle = TRUE;
      if(uart_rx_step != 0)
      {
          flag_uart_com_idle =  FALSE;         
      }
      return flag_uart_com_idle;
}
                
// This function responds to received to the first UART character received by triggering an action or saving subsequent UART data
// Called by main
/*
static void glp_command_menu(void)
{
//  Send_Message("\nGLP command:b,p,u,t,f,l,e,r,o\n ");
  Send_Message("CMD:");
}
*/

static void glp_command(void)
{
  Send_Message("\nglp_com:");	
}

void UART_Handle_Rx_Data(void) 
{
  uchar ch;
  static uchar ch_command;
 // return ;      // Derek add for test 20151030
  ++uart_rx_idle_counter;
  if(get_uart_char(&ch))
  {
    uart_rx_idle_counter = 0;
    ++uart_rx_step;
    switch(uart_rx_step)
    {
      case 1:
        if(ch != 'g')
        {
          uart_rx_step = 0;
          if(ch == '@')
          {
                ++UART_output_standby_counter;
                Send_Message("\n@@@@:\n");
          }
          else if( ch == '#')
          {
            Send_Message("\n#:Full fuel\n");
              set_fuel_max();
          }
          else if( ch == '$')
          {
            Send_Message("\n$:Low fuel\n");
              Set_Low_Fuel();
          }
          else if( ch == '%')
          {
            Send_Message("\n%:Empty fuel\n");
              Set_fuel_empty();
          }
        }
      break;
      
       case 2:
        if(ch != 'l')
        uart_rx_step = 0;
      break;     

       case 3:
      if(ch != 'p')
        uart_rx_step = 0;
      break;        
 
       case 4:
      if(ch != '-')
        uart_rx_step = 0;
      break;         

       case 5:
      if(ch != 'c')
        uart_rx_step = 0;
      break;               

       case 6:
      if(ch != 'o')
        uart_rx_step = 0;
      break;           

      case 7:
      if(ch != 'm')
        uart_rx_step = 0;
      break;     
      
      case 8:
      if(ch != ':')
      uart_rx_step = 0;
      else
      {  
//          glp_command_menu();
          glp_command();

      }
      break;
        
      case 9:
     {
       ch_command = ch;
       switch(ch_command)
       {
          case 'b':
          Send_Message("Bootload? y and press key or n");
           break;

#ifdef CLEAR_VERSION   
          case 'p':
//          Send_Message("\nClear PAYG y/n \n");
          Send_Message("P");
          break;           
           
#endif           
           
           
/*           
          case 'p':
//          Send_Message("\nClear PAYG y/n \n");
          Send_Message("P");
          break;
          
          case 'u':
//          Send_Message("\nClear UART y/n \n");
          Send_Message("U");
          break;
*/      
/*           
          case 't':
//          Send_Message("\nClear TRIM y/n \n");
          Send_Message("T");
          break;
*/           
 /*           
          case 'f':
//          Send_Message("\nSet full fuel y/n \n");
          Send_Message("F");
          break;
          
          case 'l':
//          Send_Message("\nSet low fuel y/n \n");
          Send_Message("L");
          break;
          
          case 'e':
//          Send_Message("\nSet empty fuel y/n \n");
          Send_Message("E");        
          break;
          
          case 'o':
//          Send_Message("\nExit command y/n \n");
          Send_Message("C");
          break;
          
          case 'r':
//          Send_Message("\nReset y/n \n");  
          Send_Message("R");          
          break;
*/          
          default:
             uart_rx_step = 8;
            break;
       }
 
     }
      break;
      
    case 10:
    if(ch == 'y')
    {
        uart_rx_step = 8;
        handle_command(ch_command);
        Send_Message("\nDone");
//        glp_command_menu();
//        glp_command();           
    }
    else if(ch == 'n')
    {
        uart_rx_step = 8;
/*        
        Send_Message("\nUndo");
        if(ch !='o')
        {
//          glp_command_menu();
          glp_command(); 
        }
*/        
    }
    else
    {
      uart_rx_step = 9;
    }
    break;
       
      default:
      uart_rx_step = 8;
      break;
      
    }
  }
  if(uart_rx_idle_counter > UART_IDLE_MS)      // 5 second add by 5mS.
  {
     uart_rx_step = 0;
     uart_rx_idle_counter = 0;
  }
}

static void handle_command(uchar command_type)
{
  switch(command_type)
  {
    case 'b':
    Send_Message("\nBootload? y/n\n");
    payg_all_deinit();  
    SoftReset();  
    break;

#ifdef CLEAR_VERSION  
    case 'p':
    FLASH_Unlock();
    {
        FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);  
        FLASH_ErasePage(0x08007000);  
        FLASH_ErasePage(0x08007400);
    } 
    FLASH_Lock();   
    break;
#endif    
    
    
/*
    case 'r':
    SoftReset();  
    break;
    
    case 'p':
    FLASH_Unlock();
    {
        FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);  
        FLASH_ErasePage(0x08007000);  
        FLASH_ErasePage(0x08007400);
    } 
    FLASH_Lock();      
  
//    Send_Message("\nClear PAYG y/n \n");
    break;
      
    case 'u':
    FLASH_Unlock();
    {
        FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);  
        FLASH_ErasePage(0x08007800);
    } 
    FLASH_Lock();      
      
//    Send_Message("\nClear UART y/n \n");
    break;
*/          
/* 
  case 't':
//      Send_Message("\nClear TRIM derek\n");    
    FLASH_Unlock(); 
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);  
    {
      FLASH_ErasePage(0x08007C00);
    } 
    FLASH_Lock();  
    break;
 */   
 /*           
    case 'f':
//    Send_Message("\nset full fuel y/n \n");
    set_fuel_max();
    break;
                    
    case 'l':
    Set_Low_Fuel();
//    Send_Message("\nset low fuel y/n \n");
    break;
          
    case 'e':
    Set_fuel_empty();
//    Send_Message("\nset empty fuel y/n \n");
    break;

    case 'o':
    uart_rx_step = 0;
    break;    
*/    
    default:
    
    break;
  }  
}

void SoftReset(void) 
{ 
  __set_MSP(*(__IO uint32_t*)  0x08000000);  
  NVIC_SystemReset();// 
}

void UART_Send_Sequence(uchar uart_counter) {
//  return;                       // Derek add for test 20151030
  if(uart_rx_step != 0) return;
  switch (uart_counter) 
  {
    case 1:											
    Send_Message("\n");										//2
    Send_Message("A ");
    Send_Number(adc_result.key_adc);
    Send_Number(adc_ave.ave_v_battery);
    Send_Number(adc_ave.ave_v_PVfb);
    Send_Number(adc_ave.ave_v_USBfb);
    Send_Number(adc_ave.ave_v_lihgtfb);                     
    Send_Number(Light_State);
    Send_Number(Get_Mobile_State());        // 0=off, 1= manual off,2 = fault, 3= on
    Send_Number(pv_state);           // 0=off, 1= fault, 2 = battery full, 3 = 0V charge, 4= PV_ON, 5= PV_CV                           

    if(UART_output_standby_counter !=0)
    {
        flag_uart_output_start = GLP_TRUE;
    }
    else
    {
        flag_uart_output_start = GLP_FALSE;
    }
                     
    break;
    case 2:
    Send_Message("B ");
    Send_Number(adc_result.discharging_adc_offset);
    Send_Number(adc_result.load_adc);
    Send_Number(adc_result.charging_adc);  
    send_int_number(adc_ave.ave_i_battery);
    send_int_number(adc_ave.ave_i_load);                          
    send_int_number(adc_ave.ave_i_charging);
    Send_Number(get_fuel_mAH());           //  0-max fuel
    break;
                        
    case 3:     
    Send_Message("C ");
    Send_Number(uart_nvram.nvram.unv_pv_bat_ov);
    Send_Number(uart_nvram.nvram.unv_pv_fwd_ocp);
    Send_Number(uart_nvram.nvram.unv_pv_rev_ocp);
    Send_Number(uart_nvram.nvram.unv_pv_inp_ov);
    Send_Number(uart_nvram.nvram.unv_USB_ocp);
    Send_Number(uart_nvram.nvram.unv_light_scp);
    Send_Number(uart_nvram.nvram.unv_any_fault);
    break;
                       
    case 4:
    Send_Message("D ");
    Send_Number(uart_nvram.nvram.unv_low_battery);
    Send_Number(uart_nvram.nvram.unv_slope_low_battery);             // 11.23
    Send_Number(uart_nvram.nvram.unv_voltage_low_battery);             // 11.23
    Send_Number(uart_nvram.nvram.unv_low_bat_flag);             
    Send_Number(uart_nvram.nvram.unv_empty_battery);            
    Send_Number(uart_nvram.nvram.unv_cv_charging);
    Send_Number(uart_nvram.nvram.unv_full_battery);                       
    break;                 
                  
    case 5:
    Send_Message("E ");
    Send_Number(watchdong_reset_counter);
    Send_Number(low_bat_reset_counter);
    Send_Number(power_on_reset_counter);

    Send_Number(uart_nvram.nvram.unv_manually_turn_off);
    Send_Number(uart_nvram.nvram.unv_usb_port_off);
    Send_Number(get_trim_status());      
    Send_Number((uint)get_credit_status());
    Send_Number(uart_nvram.nvram.unv_button_press);
                  
    break;

    case 6:
    Send_Message("F ");
    Send_Number(get_user_set_flag());
    send_hours_number(uart_nvram.nvram.unv_inventory_time);
    send_hours_number(uart_nvram.nvram.unv_working_life_time);
//    Send_Number(uart_nvram.nvram.unv_working_life_time%CONST_HOUR_COUNTER);
                         
    break;

    case 7:
    Send_Message("G ");
    Send_Number(uart_nvram.nvram.unv_max_rate);            
    send_hours_number(uart_nvram.nvram.unv_cv_charge_time);
    send_hours_number(uart_nvram.nvram.unv_charge_level_1_time);
    send_hours_number(uart_nvram.nvram.unv_charge_level_2_time);
    send_hours_number(uart_nvram.nvram.unv_charge_level_3_time);
    send_hours_number(uart_nvram.nvram.unv_charge_level_4_time);                
    send_hours_number(uart_nvram.nvram.unv_charge_level_5_time); 
          
    break;

    case 8:
    Send_Message("H ");
                
    send_hours_number(uart_nvram.nvram.unv_low_battery_discharge_time);
    send_hours_number(uart_nvram.nvram.unv_discharge_level_1_time);     
    send_hours_number(uart_nvram.nvram.unv_discharge_level_2_time);                     
    send_hours_number(uart_nvram.nvram.unv_discharge_level_3_time);                
    send_hours_number(uart_nvram.nvram.unv_discharge_level_4_time);     
    send_hours_number(uart_nvram.nvram.unv_discharge_level_5_time);                     
    send_hours_number(uart_nvram.nvram.unv_discharge_level_6_time);                            
      
    Send_Number(uart_nvram.nvram.unv_BCM_low_fuel_mAH);
    Send_Number(uart_nvram.nvram.unv_BCM_empty_fuel_mAH);
                
    break;
                
    case 9:
    Send_Message("I ");
    Send_Number(get_uart_fuel_level());
    {
        static u16 uart_flast_erase_times;  
        uart_flast_erase_times = *(__IO u16 *)(RECORD_END_FLASH_ADDRESS -2); 
        if(uart_flast_erase_times == 0xFFFF)
        {
            uart_flast_erase_times = 0;
        } 
        Send_Number(uart_flast_erase_times);
    }
                
    Send_Number(get_nv_vref());
    Send_Message(PN);
    Send_Message(VERSION);
                
    Send_Message(get_flash_SN());
    UART_TX(' ');
    Send_Number(get_nv_date());            
    break;     
    
    default:
    break;
  }
}

// send time counter (units: hours)
static void  send_hours_number(uint h)
{
    uint n;
    n = h/CONST_HOUR_COUNTER;
    Send_Number(n);
}

// EOF
