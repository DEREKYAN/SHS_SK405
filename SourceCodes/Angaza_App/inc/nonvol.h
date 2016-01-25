#ifndef __ANGAZA_NONVOL_H__
#define __ANGAZA_NONVOL_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "angaza.h"


/** Define the number of non-volatile blocks
 */
#define NUM_NONVOL_BLOCKS   (ANGAZA_PAYG_NV_BLOCK_ID_MAX + 1)

/** RAM resident copy of non-volatile storage blocks
 *
 *  This copy is used to replicate all values into new flash pages
 *  as new flash pages are initialized, before the old flash page is erased
 */
extern struct payg_nv_block nonvol_block_content [NUM_NONVOL_BLOCKS];


/** Initialize the nonvol implementation
 */
void            nonvol_init           (void);


/** Update one non-volatile block
 *
 * \param  block  Points to the block to be updated in non-volatile storage
 */
void            nonvol_update_block   (const struct payg_nv_block * block);


/** Erase non-volatile (flash) pages that had been deferred until now
 *
 *  The deferral is done because flash erases take a long time and may perturb
 *  normal real-time operation. We therefore do flash erases when real-time activity
 *  is quiescent.
 *
 */
void            nonvol_deferred_erase (void);


#endif
