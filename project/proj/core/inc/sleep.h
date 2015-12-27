#ifndef SLEEP_H
#define SLEEP_H
/**
 * @author Jacko Dirks
 * @file sleep.h
 * All user side sleep functions.
 */

/**
 * @brief The SleepRequest struct is passed on to the kernel. All fields can be used in combination with eachother
 */
struct SleepRequest {
    unsigned refTime;   /**< The reference time: the 0 point of sleeping */
    unsigned uSec;      /**< The amount of microseconds the process sleeps */
    unsigned mSec;      /**< The amount of milliseconds the process sleeps */
    unsigned sec;       /**< The amount of seconds the process sleeps */
};

/**
 * @brief Makes the current process sleep for at least the amount of time as set in the sleepRequest struct.
 * The reftime is set by this function.
 * @param sleepRequest The sleepRequest struct containing all information about the sleep duration.
 * @return -1 if interrupted. Errno will be set.
 */
int sleep(struct SleepRequest* sleepReq);

/**
 * @brief Makes the current process sleep for at least the amount of microseconds given
 * @param uSec The sleeptime in microseconds.
 * @return -1 if interrupted. Errno will be set.
 */
int sleepUS(unsigned uSec);

/**
 * @brief Makes the current process sleep for at least the amount of milliseconds given
 * @param mSec The sleeptime in microseconds.
 * @return -1 if interrupted. Errno will be set.
 */
int sleepMS(unsigned mSec);

/**
 * @brief Makes the current process sleep for at least the amount of seconds given
 * @param sec The sleeptime in seconds.
 * @return -1 if interrupted. Errno will be set.
 */
int sleepS(unsigned sec);
#endif //SLEEP_H
