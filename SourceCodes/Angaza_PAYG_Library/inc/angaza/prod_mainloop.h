#ifndef __ANGAZA__PROD_MAINLOOP_H__
#define __ANGAZA__PROD_MAINLOOP_H__

/** Error status of a given event-queue function call.
 */
enum prod_mainloop_error
{
    /** The invocation was successful; no error occurred.
     */
    PROD_MAINLOOP_ERROR_NONE,
};

/** Ask the product main loop to call payg_all_process() as soon as possible.
 *
 * This function is typically used by interrupt handlers to schedule larger
 * blocks of work to run outside interrupt time. After this function is called,
 * the product main loop should call payg_all_process() within 20 ms. The
 * callback *must not* be serviced synchronously: in the other words,
 * prod_mainloop_request_processing() must not itself call payg_all_process(),
 * since the latter must never be called at interrupt time.
 * /par Example Scenario:
 * (For reference only.  Actual implementation will vary based on product.)
 * -# The PAYG library receives and processes a complete PAYG message (via a sequence of interrupts)
 * -# The PAYG library now requires a longer period of time ('idle time') to fully process the PAYG message
 * -# The PAYG library calls `prod_mainloop_request_processing()` to indicate this need for processor time
 * -# The product firmware sets a flag to indicate that `payg_all_process()` should be called as soon as possible
 *      - @code
 *      // (inside product firmware, inside prod_mainloop_request_processing()
 *      prod_mainloop_request_processing()
 *      {
 *          // set a flag that will be handled in the main loop
 *          set_payg_process_needed_global_flag();
 *          return PROD_MAINLOOP_ERROR_NONE;
 *      }
 *
 *      // (inside product firmware, inside main/executive loop)
 *      if (payg_process_needed_global_flag)
 *      {
 *          // immediately call payg_all_process if the flag is set
 *          payg_all_process();
 *      }
 *      @endcode
 *
 * This function must always succeed and return PROD_MAINLOOP_ERROR_NONE.
 *
 * \warning May be called at interrupt time.
 * \return an appropriate error code
 */
enum prod_mainloop_error prod_mainloop_request_processing(void);

#endif
