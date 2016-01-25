#include "nonvol.h"
#include <stdbool.h>
#include "stm32f0xx.h"
#include "string.h"
#include "angaza.h"


/*******************************************************************
 * Implementation Notes:
 *
 * The primary design goal in using Flash for non-volatile storage
 * is to provide more than a 10 year lifetime, with frequent
 * backup for the passage of time, and resiliency amidst Flash errors.
 *
 * Each Flash page is 1024 bytes.  Two flash pages at the end of
 * chip's flash are dedicated to non-volatile storage.
 *
 * Each block written to Flash takes 8 bytes.
 * Data is written to Flash sequentially.  As a Flash page is filled,
 * all data blocks are written to another page.  Then the previous full page
 * is erased.  In this way, the non-volatile data is double-buffered until
 * its integrity is verified on a new flash page.
 *
 * After every write to Flash, the data is read back in order to verify that
 * it was written to Flash correctly.  If a write ever fails,
 * the data is rewritten into the next Flash location until it
 * is read back correctly.
 *
 * Upon reading Flash data, the internal checksum
 * is checked to ensure that the Flash maintained its
 * integrity.  If the checksum is ever bad, that Flash data is ignored.
 *
 * At startup, the active flash page is scanned for all valid blocks.
 * The valid blocks last written to Flash are selected as the most current
 * value for each block id.  These valid blocks are stored in the RAM
 * resident cache, nonvol_block_content, during normal operation.  The cache
 * is used for several purposes, including returning current values immediately
 * rather than re-searching Flash, eliminating redundant writes to Flash if
 * block data has not changed, and writing all block values into a new Flash
 * page when the current Flash page is exhausted.
 *
 * The STM32Fxx data sheet specifies Flash endurance of 1000 cycles
 * and data retention of 20 years.  We can therefore estimate how many
 * block writes we can reliably make:
 *
 *      Blocks written to each page = (1024 bytes / 8 bytes per block) - 8 permanent blocks = 120 blocks
 *
 *      2 Flash pages * 1000 erase cycles per page * 120 blocks = 240,000 reliable writes
 *
 * In order to estimate the lifetime of the device, we can make the
 * following calculation:  assuming one block write every hour to store the passage of time,
 * and 12 block writes per day of all generic PAYG data:
 *
 *      Each day, the following amount of data is written to Flash:
 *
 *          Time data retention:      24 writes
 *
 *          Generic PAYG data:        12 writes
 *                                    ---------
 *              Writes per day:       36 writes
 *
 * So, we can estimate the total operational use of the device
 * before Flash failure at:
 *
 *          240,000 writes / 36 writes per day = 6666 days = 18 years
 */

/** Flash page size in bytes
 */
#define FLASH_PAGE_SIZE 1024


/** Number of Flash pages
 */
#define FLASH_PAGE_COUNT 32


/** RAM resident copy of non-volatile storage blocks
 *
 *  This copy is used to replicate all values into new flash pages
 *  as new flash pages are initialized, before the old flash page is erased
 */
struct payg_nv_block nonvol_block_content[NUM_NONVOL_BLOCKS];


/** Number of blocks in each Flash page
 */
#define NUM_BLOCKS_IN_FLASH_PAGE (FLASH_PAGE_SIZE/ANGAZA_PAYG_NV_BLOCK_SIZE)


/** An erased block
 */
static const struct payg_nv_block nonvol_block_erased = {{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}};


/** The index of the current page (0 or 1)
 */
static uint8_t nonvol_current_page_index = 0;


/** Index + 1 of a page whose erase is deferred
 */
static uint8_t deferred_erase_page = 0;


/** Address of each flash page
 */
// Version for 16KB image
static const uint8_t *page_address[] =
{
	((uint8_t *)FLASH_BASE) + ((FLASH_PAGE_COUNT - 4) * FLASH_PAGE_SIZE),
	((uint8_t *)FLASH_BASE) + ((FLASH_PAGE_COUNT - 3) * FLASH_PAGE_SIZE)
};


/** The index of the next available writable slot in each flash page
 */
static uint8_t next_avail_index[sizeof(page_address)/sizeof(page_address[0])] = {0, 0};


/** Find the next writable block index in a flash page
 *
 * \param  The address of the flash page
 * \return The next writable block index
 */
static uint8_t find_next_avail_index (uint8_t *page_address)
{
	int i;

	for (i=NUM_BLOCKS_IN_FLASH_PAGE - 1; i >= 0; i--)
	{
		if (memcmp(page_address + (i*ANGAZA_PAYG_NV_BLOCK_SIZE), (void *)&nonvol_block_erased, ANGAZA_PAYG_NV_BLOCK_SIZE) != 0)
		{
			return (uint8_t)i+1;
		}
	}
	return 0;
}


/** Read the latest value of all flash blocks into nonvol_block_content
 */
static void read_nonvol_data (void)
{
	int                    i;
	int                    index;
	struct payg_nv_block  *flash_ptr;
	bool                   valid[NUM_NONVOL_BLOCKS];

	for (i=0; i<NUM_NONVOL_BLOCKS; i++)
	{
		valid[i] = false;
	}

	for (i=next_avail_index[nonvol_current_page_index]-1;
		 i >= 0;
		 i--)
	{
	    flash_ptr = (struct payg_nv_block *)(page_address[nonvol_current_page_index]
	                          	            + (i * ANGAZA_PAYG_NV_BLOCK_SIZE));

	    /** Is the given block valid, based on its internal checksum and block id?
	     */
	    if (payg_nv_block_is_valid(flash_ptr))
	    {
			index = payg_nv_block_id(flash_ptr);

			if ((index < NUM_NONVOL_BLOCKS)
					&& !valid[index])
			{
				memcpy (&nonvol_block_content[index], (void *)flash_ptr, ANGAZA_PAYG_NV_BLOCK_SIZE);
				valid[index] = true;
			}
	    }
	}
}


/** Erase a flash page
 *
 * \param   The flash page index
 * \return  void
 */
static void erase_page(uint8_t page_index)
{
	FLASH_Unlock();
        FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);  
	FLASH_ErasePage((uint32_t)page_address[page_index]);
	FLASH_Lock();

	next_avail_index[page_index] = 0;
}


/** Initialize the nonvol implementation
 */
void nonvol_init   (void)
{
	next_avail_index[0] = find_next_avail_index((uint8_t *)page_address[0]);
	next_avail_index[1] = find_next_avail_index((uint8_t *)page_address[1]);

	// Most recently written page will have highest index
	if (next_avail_index[1] > next_avail_index[0])
	{
		// Second page is latest
		nonvol_current_page_index = 1;
	}

	read_nonvol_data();

	// Ensure that other page is erased
	if (next_avail_index[(nonvol_current_page_index + 1) % 2] != 0)
	{
		erase_page((nonvol_current_page_index + 1) % 2);
	}
}


/** Write one flash block at the next available location in the current flash page.
 *
 *  Takes the block data from the RAM cache in nonvol_block_content
 *
 * \param  The block index to write to flash
 * \return True if the block was correctly written and verified, otherwise false
 */
static bool write_one_block (int index)
{
	uint16_t *data_ptr;
	uint16_t *flash_ptr;
	bool      valid = false;
	int       i;

	data_ptr  = (uint16_t *)&nonvol_block_content[index];

	flash_ptr = (uint16_t *)(page_address[nonvol_current_page_index]
	            + (next_avail_index[nonvol_current_page_index]
	                  * ANGAZA_PAYG_NV_BLOCK_SIZE));

	FLASH_Unlock();
        FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);
	for (i=0; i<ANGAZA_PAYG_NV_BLOCK_SIZE/sizeof(uint16_t); i++)
	{
        FLASH_ProgramHalfWord((uint32_t)(flash_ptr+i), *(data_ptr+i));
	}
	FLASH_Lock();

	// Verify the data written to make sure it matches
	if (memcmp((void *)flash_ptr, (void *)data_ptr, ANGAZA_PAYG_NV_BLOCK_SIZE) == 0)
	{
		valid = true;
	}

	next_avail_index[nonvol_current_page_index]++;

	return valid;
}


/** Switch to a new flash page
 */
static void swap_flash_page(void)
{
	int  i;
	bool valid;

	// Clear any pending deferred erase if we have wrapped around,
	// since we cannot wait any longer
	nonvol_deferred_erase();

	// Advance to the new flash page
	nonvol_current_page_index = (nonvol_current_page_index + 1) % 2;

	// Copy the current value of all blocks onto the new page
	for (i=0; i<NUM_NONVOL_BLOCKS; i++)
	{
	    if (payg_nv_block_is_valid(&nonvol_block_content[i])
	    		&& (payg_nv_block_id(&nonvol_block_content[i]) == i))
	    {
			valid = false;

			while (!valid
					&& (next_avail_index[nonvol_current_page_index] < NUM_BLOCKS_IN_FLASH_PAGE))
			{
				valid = write_one_block(i);
			}
	    }
	}

	// Defer erasing old page until a quiescent period in order not to perturb realtime
	deferred_erase_page = ((nonvol_current_page_index + 1) % 2) + 1;
}


/** Erase a non-volatile (flash) page that had been deferred until now
 *
 *  The deferral is done because flash erases take a long time and may perturb
 *  normal real-time operation. We therefore do flash erases when real-time activity
 *  is quiescent.
 *
 */
void  nonvol_deferred_erase(void)
{
	if (deferred_erase_page != 0)
	{
		erase_page(deferred_erase_page-1);
		deferred_erase_page = 0;
	}
}


/** Update one non-volatile block
 *
 *  If the block data differs from that in the RAM cache, nonvol_block_content,
 *  then the cache is updated and the block is written to flash.  However, if the block
 *  data has not changed compared to the RAM cache, then the flash write is skipped.
 *
 * \param  block  Points to the block to be updated in non-volatile storage
 */
void nonvol_update_block (const struct payg_nv_block *block)
{
	bool     valid;
	uint8_t  block_index;

	// Get the block index
	block_index = payg_nv_block_id(block);

	if (block_index <= ANGAZA_PAYG_NV_BLOCK_ID_MAX)
	{
		// Only write the block if the content has changed from that in flash
		if (memcmp((void *)block, &nonvol_block_content[block_index], ANGAZA_PAYG_NV_BLOCK_SIZE) != 0)
		{
			// Copy the block to RAM resident array
			memcpy(&nonvol_block_content[block_index], (void *)block, ANGAZA_PAYG_NV_BLOCK_SIZE);

			valid = false;

			// Write the new data to flash until it is correct;
			// ie., try to circumvent any flash write errors
			while (!valid)
			{
				if (next_avail_index[nonvol_current_page_index] < NUM_BLOCKS_IN_FLASH_PAGE)
				{
					valid = write_one_block(block_index);
				}
				else
				{
					// Swap flash page, which will write all block values to the new page
					swap_flash_page();
					valid = true;
				}
			}
		}
	}
}
