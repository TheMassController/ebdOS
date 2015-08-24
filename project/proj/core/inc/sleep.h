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
 * @brief Get the current value of the system timer (probably Wide Timer 0/A)
 * @return The value at the moment of reading
 */
unsigned getCurrentSytemTimerValue(void);

/**
 * @brief Makes the current process sleep for at least the amount of time as set in the sleepRequest struct.
 * The reftime is set by this function.
 * @param sleepRequest The sleepRequest struct containing all information about the sleep duration.
 */
void sleep(struct SleepRequest* sleepReq);

/**
 * @brief Makes the current process sleep for at least the amount of microseconds given
 * @param uSec The sleeptime in microseconds.
 */
void uSleep(unsigned uSec);

/**
 * @brief Makes the current process sleep for at least the amount of milliseconds given
 * @param mSec The sleeptime in microseconds.
 */
void mSleep(unsigned mSec);

/**
 * @brief Makes the current process sleep for at least the amount of seconds given
 * @param sec The sleeptime in seconds.
 */
void sSleep(unsigned sec);

//TODO old stuff, destroy
void sleepMS(unsigned ms);
void sleepS(unsigned seconds);
#endif //SLEEP_H
