/** Interface to a high-precision timer on this MCU.
 *
 * *To be implemented in product firmware by the manufacturer (you).*
 *
 * Used by PAYG code to time input and output signals. Necessary only if
 * support for, e.g., cable or IR inputs are defined.
 *
 * Relevant interrupts:
 *
 * - payg_interrupts_timcmp_handle_elapsed()
 *
 * See documentation in payg_interrupts.h.
 */

#ifndef __ANGAZA__PROD_TIMCMP_H__
#define __ANGAZA__PROD_TIMCMP_H__

#include <stdint.h>

/** Error status of a high-precision timer routine.
 */
enum prod_timcmp_error
{
    /** The invocation was successful; no error occurred.
     */
    PROD_TIMCMP_ERROR_NONE,

    /** The specified duration is unsupported (e.g., it is too long).
     */
    PROD_TIMCMP_ERROR_DURATION_UNSUPPORTED,

    /** The timer is not started, and is required for this operation.
     */
    PROD_TIMCMP_ERROR_NOT_STARTED,
};

/** Start or restart the high-precision timer.
 *
 * The timer measures elapsed time in microseconds starting when this function
 * is called. The timer invokes the prod_timcmp_handle_elapsed() callback after
 * the specified duration has elapsed. The timer must stop naturally after the
 * duration elapses and the callback is invoked. Timer error must be less than
 * 10%.
 *
 * The prod_timcmp_get_microseconds_elapsed() routine may be used to read the
 * current elapsed time while the timer is running. If this start routine is
 * called while the timer is running, it is restarted.
 *
 * The timer need not support durations larger than 8000 us.
 *
 * Valid status codes:
 *
 * - PROD_TIMCMP_ERROR_NONE
 * - PROD_TIMCMP_ERROR_DURATION_UNSUPPORTED
 *
 * \warning May be called at interrupt time.
 * \warning Must complete in 10 us or less.
 * \param duration_us duration in microseconds
 * \return a valid status code
 */
enum prod_timcmp_error prod_timcmp_start(uint16_t duration_us);

/** Stop the high-precision timer.
 *
 * The callback must not not be invoked after this function returns (unless the
 * timer is restarted).
 *
 * Valid status codes:
 *
 * - PROD_TIMCMP_ERROR_NONE
 *
 * \warning May be called at interrupt time.
 * \return a valid status code
 */
enum prod_timcmp_error prod_timcmp_stop(void);

/** Read the time elapsed thus far.
 *
 * Valid status codes:
 *
 * - PROD_TIMCMP_ERROR_NONE
 * - PROD_TIMCMP_ERROR_NOT_STARTED
 *
 * \warning May be called at interrupt time.
 * \param elapsed_us out parameter to be filled with the microseconds elapsed
 * \return a valid status code
 */
enum prod_timcmp_error prod_timcmp_get_microseconds_elapsed(uint16_t* elapsed_us);

#endif
