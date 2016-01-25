#include "prod_diag.h"
#include <stdint.h>
#include <stdbool.h>
#include "Angaza_cable.h"
#include <string.h>


//extern void Send_Message(uint8_t *string);
//extern void Send_Number(uint32_t number);

/** Retrieve diagnostic data with the given priority, if any.
 *
 * This function enables diagnostic data, such as battery voltage or product
 * usage information, to be transferred back through a PAYG communication
 * channel. This interface is designed to allow different amounts of
 * information to be transferred through channels with different bandwidth
 * limits. When data is needed, the PAYG library will request blocks of data in
 * order of their importance, starting with priority 0 as most important.
 *
 * For example, if product code stores the battery voltage, the number of
 * seconds the product has been used on a low light setting, and the number of
 * seconds on a high light setting, it might provide the battery voltage as
 * two-byte value at priority 0 and the low and high usage numbers as four-byte
 * values at priorities 1 and 2 respectively. Calling prod_diag_get_data(0,
rror prod_diag_get_data(
    uint16_t priority,
    uint16_t* data_size,
    void* buffer,
    uint16_t buffer_size)
{
    return PROD_DIAG_ERROR_NO_DATA_AT_PRIORITY;
}

void prod_cable_set_tx_pin(bool level)
{
  
} * ...) would result in the two-byte voltage data copied into the specified
 * buffer, and PROD_DIAG_ERROR_NONE returned. Specifying a priority for which
 * product code does not have data defined, e.g., prod_diag_get_data(4, ...),
 * would result in PROD_DIAG_NO_DATA_AT_PRIORITY returned.
 *
 * Data should have consecutive priorities. If no data exists at priority 12,
 * for example, then no data should be exist at priorities values larger (lower
 * importance) than 12.
 *
 * Valid status codes:
 *
 * - PROD_DIAG_ERROR_NONE
 * - PROD_DIAG_ERROR_NO_DATA_AT_PRIORITY
 * - PROD_DIAG_ERROR_BUFFER_TOO_SMALL
 *
 * \note Never called at interrupt time.
 * \param priority priority of the data to be retrieved
 * \param data_size pointer to variable into which data size should be copied
 * \param buffer pointer to buffer into which data should be copied
 * \param buffer_size size of the buffer provided
 * \return an appropriate error code
 */

enum prod_diag_error prod_diag_get_data(
    uint16_t priority,
    uint16_t* data_size,
    void* buffer,
    uint16_t buffer_size)
{
    // this firmware only provides the priority-zero data block;
    // if the PAYG library requests a different data block, return an error
    if(priority > 0)
    {
        return PROD_DIAG_ERROR_NO_DATA_AT_PRIORITY;
    }

    // inform the library of the size of this data block
    *data_size = sizeof(cable_send_buf);                                               // Add for test 
    // if the library's buffer is too small, return an error
    if(buffer_size < *data_size)
    {
        return PROD_DIAG_ERROR_BUFFER_TOO_SMALL;
    }

    // prepare usage data and copy it to the library
    Initial_Cable_Data();
    memcpy(buffer, cable_send_buf, *data_size);    
   
    return PROD_DIAG_ERROR_NONE;
}