/*
 * IGNORE THIS FILE
 *
 * This file is used by the Angaza library packaging process *only* to verify
 * that the library compiles and links in its packaged form. Its use is not
 * necessary for the library to function. It should not be included in your
 * build.
 *
 * IGNORE THIS FILE
 */

#include <angaza/angaza.h>
// the minimum set of functions that must be defined in order to build:

enum prod_feedback_error prod_feedback_handle_state(enum payg_state new_state)
{
    return PROD_FEEDBACK_ERROR_NONE;
}

void prod_ir_override_enable(bool level)
{
}
   
// The routine is called by PAYG library, update by GLP 
/*
enum prod_mainloop_error prod_mainloop_request_processing(void)
{
    payg_all_process(0);
    return PROD_MAINLOOP_ERROR_NONE;
}
*/

/*
enum prod_timcmp_error prod_timcmp_start(uint16_t duration_us)
{
    return PROD_TIMCMP_ERROR_NONE;
}

enum prod_timcmp_error prod_timcmp_stop(void)
{
    return PROD_TIMCMP_ERROR_NONE;
}

enum prod_timcmp_error prod_timcmp_get_microseconds_elapsed(uint16_t* elapsed_us)
{
    return PROD_TIMCMP_ERROR_NONE;
}
*/

/*
enum prod_nv_error prod_nv_write(const struct payg_nv_block* blocks, uint8_t count)
{
    return PROD_NV_ERROR_NONE;
}

enum prod_nv_error prod_nv_read(const uint8_t block_id, struct payg_nv_block* block)
{
    return PROD_NV_ERROR_NONE;
}
*/
/*
enum prod_feedback_error prod_feedback_start(enum prod_feedback_script script)
{
    return PROD_FEEDBACK_ERROR_NONE;
}

void prod_feedback_handle_state_change(void)
{
}
*/
/*
int main(void)
{
    struct prod_keypad_key key = {PROD_KEYPAD_KEY_TYPE_CHAR, {'x'}};

    payg_interrupts_keypad_handle_key(key);
}
*/
