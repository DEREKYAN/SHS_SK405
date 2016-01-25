#include "Config.h"
#include "main.h"

#define CONST_HOUR_COUNTER            3600u   // Const diviver from sencond to hour.
#define UART_BUFFER_SIZE_TX				    128
#define UART_BUFFER_SIZE_RX				    32
#define UART_RX_MASK					        (UART_BUFFER_SIZE_RX-1)
#define UART_TX_MASK					        (UART_BUFFER_SIZE_TX-1)
#define BASE_TEN						          10

extern uchar UART_output_standby_counter;
extern GLP_bool flag_uart_output_start;


//#define LOOP_PROTECT					        10000u

// UART Functions
bool Is_UART_Active(void);
void UART_Clear_Serial_Unlock(void);
void Disable_UART_Setup(void);
void Send_Zero(void);
void Send_Number(uint number);
void send_int_number(int snumber);
void Send_Message(uchar *string);
void UART_Handle_Tx_Data(void);
void UART_Handle_Rx_Data(void);
void UART_TX(uchar data);
void Send_Char(uchar letter);
void UART_Send_Sequence(uchar uart_counter);

bool get_uart_char(uchar *ch);
void UART_TX_SLEEP_STOP(uchar t);
bool get_UART_Active(void);
bool get_uart_command_idle(void);

// EOF
