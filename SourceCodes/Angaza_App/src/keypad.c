/** Initialization routine for keypad_4x3_membrane
 * Input key to PAYG library to add new credit  
 *      1 --  F (A)    2 --  B   3 -- C  4 -- D  5 -- E
 */
#include "stdbool.h"
#include "prod_keypad.h"
#include "angaza.h"
#include "angaza/payg_interrupts.h"

void set_keypad_to_credit(uint8_t key_value)
{
  struct prod_keypad_key key;
  bool   valid_key;
  if(IS_PAYG_IDLE())
  {  
    valid_key = true;
    switch (key_value)
    {
      case 1:
      key.value.character = '1';
      break;

      case 2:
      key.value.character = '2';

      break;

      case 3:
     key.value.character = '3';

      break;

      case 4:
     key.value.character = '4';
 
      break;	
      
      case 5:
      key.value.character = '5';
      break;	
      
      default:
      valid_key = false;
      break;
    }
    if (valid_key)
    {
      key.type  = PROD_KEYPAD_KEY_TYPE_CHAR;
      payg_interrupts_keypad_handle_key(key);
    }
  }
}
