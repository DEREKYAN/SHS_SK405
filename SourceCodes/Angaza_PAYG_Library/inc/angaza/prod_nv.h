/** \file
 * Product firmware functions providing access to NVRAM for the PAYG library.
 *
 * The PAYG library requires a mechanism to write an arbitrary number (less than
 * ANGAZA_PAYG_NV_BLOCK_ID_MAX) of payg_nv_block structures to NV memory.
 * It also requires a mechanism to read these blocks back.
 * prod_nv_write() and prod_nv_read() are product-specific functions written
 * by the product manufacturer to provide for these requirements.
 *
 * Please see AppNote "PAYG Library prod_nv" for more details.
 */

#ifndef __ANGAZA__PROD_NV_H__
#define __ANGAZA__PROD_NV_H__

#include <stdint.h>
#include "angaza/payg_nv_block.h"

/** Error status of a given nonvolatile-storage function call.
 */
enum prod_nv_error
{
    /** The invocation was successful; no error occurred.
     */
    PROD_NV_ERROR_NONE,

    /** The specified data block was not found in nonvolatile storage.
     */
    PROD_NV_ERROR_BLOCK_NOT_FOUND,
};

/** Write new versions of the specified blocks to nonvolatile storage.
 *
 * The prod_nv module provides a primitive mechanism for storing small
 * fixed-size blocks of data in nonvolatile storage. Each block has an id.
 * Repeatedly writing a block with the same id can be thought of as repeatedly
 * overwriting that block, since only the most recent version of a given block
 * can ever be read. There is a low limit to the number of possible block ids:
 * specifically, ANGAZA_PAYG_NV_BLOCK_ID_MAX + 1.
 *
 * This function allows multiple blocks to be written at once: the `blocks`
 * parameter points to an array of one or more blocks to write. The length of
 * this array is provided by the `count` parameter.
 *
 * This interface must provide a minimum endurance of 100000 (one hundred
 * thousand) total writes, summed across all blocks, plus additional write
 * volume caused through payg_all_deinit(), if any. If the underlying flash
 * hardware provides, for example, 1024-byte pages with a minimum endurance of
 * 1000 erase cycles per page, the endurance requirements for this interface
 * can be achieved by spreading the writes across two pages. One page would
 * normally be sufficient for endurance alone, but least two pages are *always*
 * recommended given typical flash storage---on which an entire page must be
 * erased at once---to prevent data corruption due to power loss while a page
 * is being erased.
 *
 * The blocks written will never be invalid, i.e., payg_nv_block_is_valid()
 * will never return false for any block in the `blocks` array. If an invalid
 * block *is* written, that indicates a library bug; that condition may
 * therefore be asserted.
 *
 * \par Example Scenario:\n
 * (For reference only.  Actual implementation will differ based on product)
 * -# Product internally writes one block of NVRAM at a time
 * -# In implementation of prod_nv_write, product firmware loops through
 *    its internal NVRAM write function ('nonvol_update_block' in this example)
 *    - @code
 *      enum prod_nv_error prod_nv_write(const struct payg_nv_block* blocks, uint8_t count)
 *      {
 *          int i;
 *
 *          // Write each block to NV storage
 *          for (i=0; i<count; i++)
 *          {
 *              nonvol_update_block (blocks);
 *
 *              blocks++;
 *          }
 *          //must return PROD_NV_ERROR_NONE
 *          return PROD_NV_ERROR_NONE;
 *      }
 *      @endcode
 *
 * Valid status codes:
 *
 * - PROD_NV_ERROR_NONE
 *
 * \note Never called at interrupt time.
 * \param blocks array of one or more blocks to write
 * \param count number of blocks to write, i.e., length of the blocks array
 * \return a valid status code
 */
enum prod_nv_error prod_nv_write(const struct payg_nv_block* blocks, uint8_t count);

/** Attempt to read the most recent version of the specified block.
 *
 * If no uncorrupted version of the specified block is found,
 * PROD_NV_ERROR_BLOCK_NOT_FOUND must be returned.
 *
 * Valid status codes:
 *
 * - PROD_NV_ERROR_NONE
 * - PROD_NV_ERROR_BLOCK_NOT_FOUND
 *
 * \par Example Scenario:\n
 * (For reference only.  Actual implementation will differ based on product)
 * -# Product implementation of prod_nv_read checks validity of data read
 * -# Validity check functions are provided by firmware library (see payg_nv.h)
 * -# If the data is correct, copy it into RAM.
 *     - @code
 *      enum prod_nv_error prod_nv_read(uint8_t block_id, struct payg_nv_block* block)
 *      {
 *          // If the RAM resident copy of the NV storage block is valid,
 *          // then return that block.  A block is valid if the internal checksum
 *          // is valid and the block id is correct
 *          if (payg_nv_block_is_valid(&nonvol_block_content[block_id])
 *                  && (payg_nv_block_id(&nonvol_block_content[block_id]) == block_id))
 *          {
 *              memcpy((void *)block, &nonvol_block_content[block_id], ANGAZA_PAYG_NV_BLOCK_SIZE);
 *
 *              return PROD_NV_ERROR_NONE;
 *          }
 *
 *          return PROD_NV_ERROR_BLOCK_NOT_FOUND;
 *      }
 *      @endcode
 *
 * \note Never called at interrupt time.
 * \param data out parameter to fill with the data read; never NULL
 * \return a valid prod_nv_error status code
 */
enum prod_nv_error prod_nv_read(uint8_t block_id, struct payg_nv_block* block);

#endif
