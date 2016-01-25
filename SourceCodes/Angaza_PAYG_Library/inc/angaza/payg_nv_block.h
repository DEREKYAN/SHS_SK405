/**\file PAYG NV block-based interface, for cross-platform nonvolatile storage.
 *
 * PAYG NV block-based interface, for storing PAYG state information and
 * any additional product/usage information that will be logged to Angaza
 * via PAYG messages.  These are utility functions to check the validity
 * of a given block of data, and to check the internal "Angaza PAYG NV Block ID" (
 * which is always less than `PAYG_NV_BLOCK_ID_MAX`) of a given block of data.
 * The product firmware uses these functions when processing PAYG-related NV read/writes.
 *
 * The payg_nv_block structure and functions are used to support `prod_nv_read()` and `prod_nv_write()` in `prod_nv.h`.
 * Those prod_nv_* functions are implemented by *product* firmware to read and write instances of the payg_nv_block struct:
 *
 *  1. The prod_nv_read() function is called by the library to read a block with a particular id. Its implementation will usually need to determine the id of blocks that it then reads from flash. 
 *  2. The `payg_nv_block_id()` function allows your prod_nv implementation to extract the id from a block.
 *  3. The `prod_nv_read()` function will usually need to know whether a block it has read from flash is "valid" or not.
 *  4. The `payg_nv_block_is_valid()` function allows your prod_nv implementation to determine whether a block is valid or corrupted.
 *
 * The functions in this file are used to support `prod_nv_read()` and `prod_nv_write()`
 * in prod_nv.h.
 *
 * Please see AppNote "PAYG Library prod_nv" for more details.
 **/

#ifndef __ANGAZA__PAYG_NV_BLOCK_H__
#define __ANGAZA__PAYG_NV_BLOCK_H__

#include <stdint.h>
#include <stdbool.h>
#include "angaza/config.h"

/** block size in bytes
 */
#define ANGAZA_PAYG_NV_BLOCK_SIZE 8
/** 16 possible chunks/block IDs
 */
#define ANGAZA_PAYG_NV_BLOCK_ID_MAX 15

/** Data read from or to be written to nonvolatile storage.
 */
ANGAZA_PACKED_STRUCT payg_nv_block
{
    /** Opaque fixed-size block of data.
     */
    uint8_t data[ANGAZA_PAYG_NV_BLOCK_SIZE];
};

/** Get the id number of a given block.
 *
 * This information may be used by the product's implementation of the `prod_nv.h` nonvolatile storage interface
 * to determine which blocks of data are the same and which are different.  For example, when copying data from a
 * full flash page to a new page, the product implementation (written by manufacturer) will copy only the most
 * recent block written with a given id.
 *
 * \par Example Scenario:\n
 * (For reference only.  Actual implementation will differ based on product)
 * -# Product is copying PAYG NV data to a new flash page
 * -# Product iterates through the available blocks in current page
 * -# Product copies the blocks in the same order to the new flash page
 *     - @code
 *  bool valid;
 *  // Copy the current value of all blocks onto the new page
 *  for (i=0; i<NUM_NONVOL_BLOCKS; i++)
 *  {
 *      // loop through the blocks in the current page, checking if they
 *      // are valid, and ensuring that the block ID is copied in order
 *      if (payg_nv_block_is_valid(&nonvol_block_content[i])
 *              && (payg_nv_block_id(&nonvol_block_content[i]) == i))
 *      {
 *          valid = false;
 *
 *          while (!valid
 *                  && (next_avail_index[nonvol_current_page_index] < NUM_BLOCKS_IN_FLASH_PAGE))
 *          {
 *              //product-specific code to write to flash.
 *              valid = write_one_block(i);
 *          }
 *      }
 *  }
 *  @endcode
 *
 * \return payg_nv_block_id, between 0 and PAYG_NV_BLOCK_ID_MAX
 */
uint8_t payg_nv_block_id(const struct payg_nv_block* block);

/** Is the given block valid, based on its internal checksum?
 *
 * This information may be used by the product's implementation of the prod_nv.h nonvolatile storage 
 * interface to determine whether a block written in flash is in fact stored correctly. For example, 
 * when reading the most recent block written for a given id, product code must ignore sections of flash 
 * that appear to be invalid blocks.
 *
 * \par Example Scenario:\n
 * (For reference only.  Actual implementation will differ based on product)
 * -# Product checks if a given block ID is valid/passes checksum
 * -# If block is valid, product atempts to read from the block
 *     - @code
 *      // Obtain pointer to location of current PAYG_NV block
 *      flash_ptr = (struct payg_nv_block *)(page_address(nv_current_page_index)
 *                     + (ANGAZA_PAYG_NV_BLOCK_SIZE));
 *
 *      // Is the given block valid, based on its internal checksum and block id?
 *      if (payg_nv_block_is_valid(flash_ptr))
 *      {
 *           index = payg_nv_block_id(flash_ptr);
 *
 *          if ((index < NUM_NONVOL_BLOCKS)
 *                  && !valid[index])
 *          {
 *              // copy PAYG_NV data into RAM resident copy
 *              memcpy (&nonvol_block_content[index], (void *)flash_ptr, ANGAZA_PAYG_NV_BLOCK_SIZE);
 *              valid[index] = true;
 *          }
 *      }
 *      @endcode
 *
 * \return true iff the checksum of block is valid
 */
bool payg_nv_block_is_valid(const struct payg_nv_block* block);

#endif
