#ifndef __ANGAZA__PROD_DIAG_H__
#define __ANGAZA__PROD_DIAG_H__

#include <stdint.h>

/** Error status of a diagnostic-data routine.  PAYG library uses this status
 * to determine if diagnostic data was successfully retrieved by
 * prod_diag_get_data() and is valid to send back over PAYG communications.
 */
enum prod_diag_error
{
    /** The invocation was successful; no error occurred.
     */
    PROD_DIAG_ERROR_NONE,

    /** No data exists at the specified priority.
     */
    PROD_DIAG_ERROR_NO_DATA_AT_PRIORITY,

    /** Too small a buffer was provided for the data.
     */
    PROD_DIAG_ERROR_BUFFER_TOO_SMALL,
};

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
 * ...) would result in the two-byte voltage data copied into the specified
 * buffer, and PROD_DIAG_ERROR_NONE returned. Specifying a priority for which
 * product code does not have data defined, e.g., prod_diag_get_data(4, ...),
 * would result in PROD_DIAG_NO_DATA_AT_PRIORITY returned.
 *
 * Data should have consecutive priorities. If no data exists at priority 12,
 * for example, then no data should be exist at priorities values larger (lower
 * importance) than 12.
 *
 * \par Example Scenario:\n
 * (For reference only.  Actual implementation will differ based on product)
 * -# Product has two pieces of 'diagnostic' data (battery voltage and
 *  runtime of product)
 * -# Priorities for these are set to '0' (battery) and '1' (runtime)
 * -# PAYG library is sending a data message back through the cable, and
 *  requests the data in order of priority ('0' first, then '1')
 *
 *   - @code
 *   // (inside PAYG library)
 *      uint16_t cur_priority = 0;
 *      prod_diag_error pd_error = PROD_DIAG_ERROR_NONE;
 *      do {
 *          // will return "PROD_DIAG_ERROR_NONE" while cur_priority is 0 or 1.
 *          // diagnostic data 'buffer' is data that will be stored in PAYG message reply.
 *          pd_error = prod_diag_get_data(
 *          cur_priority,
 *          data_size,
 *          buffer,
 *          buffer_size)
 *
 *          // 'priority' is an index to designate different pieces of diagnostic data to transfer over PAYG.
 *          cur_priority++;
 *      } while(pd_error == PROD_DIAG_ERROR_NONE);
 *      @endcode
 *    - @code
 *    // (inside product code, example definition of prod_diag_get_data())
 *   enum prod_diag_error prod_diag_get_data(
 *       uint16_t priority,
 *      uint16_t* data_size,
 *      void* buffer,
 *      uint16_t buffer_size)
 *  {
 *    struct big_product_data{
 *          uint32_t a;
 *          uint32_t b;
 *          uint32_t c;
 *          uint32_t d;
 *          uint32_t e;
 *      }data_page_zero; // 160 bit data block (priority '0')
 *      data_page_zero.a = 0xa1a1a1a1;
 *      data_page_zero.b = 0xb2b2b2b2;
 *      data_page_zero.c = 0xc3c3c3c3;
 *      data_page_zero.d = 0xd4d4d4d4;
 *      data_page_zero.e = 0xe5e5e5e5;
 *
 *      int16_t data_page_one = get_runtime_data(); // (priority '1')
 *
 *      // this product returns data no larger than this struct size.
 *      if(buffer_size < sizeof(struct big_product_data))
 *      {
 *          *data_size = sizeof(struct big_product_data);
 *          return PROD_DIAG_ERROR_BUFFER_TOO_SMALL;
 *      }
 *
 *      // Provide the 'priority level'/page of data requested by PAYG library.
 *      switch(priority)
 *      {
 *          // populate first page of data.
 *          case 0:
 *              *(struct big_product_data*)buffer = data_page_zero;
 *              *data_size = sizeof(struct big_product_data);
 *              break;
 *
 *          // populate buffer with 'runtime data'
 *          case 1:
 *              *(signed int*)buffer = data_page_one;
 *              *data_size = sizeof(int16_t);
 *              break;
 *
 *          // this product only has two 'pages' or 'priorities' of data
 *          default:
 *              return PROD_DIAG_ERROR_NO_DATA_AT_PRIORITY;
 *      }
 *      // `PROD_DIAG_ERROR_NONE` indicates to the PAYG library that the
 *      // data in `buffer` is OK to report.
 *      return PROD_DIAG_ERROR_NONE;
 *  }
 *  @endcode
 *
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
    uint16_t buffer_size);

#endif
