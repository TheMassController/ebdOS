#ifndef SEMPAHORE_H
#define SEMAPHORE_H
/**
 * @author Jacko Dirks
 * @file semaphore.h
 * Userside implementation of semaphore: these functions are supposed to be used by the enduser.
 */

#include "futex.h"
#include "sleep.h"

struct Semaphore {
    struct Futex fut;
};

/**
 * @brief Initializes the semaphore to the given value
 * @param semaphore A pointer to the mutex you want to initialize
 * @param value The initial value of the given semaphore
 * @return 0 if everything went OK, else an ERRNO. See kernel/inc/sysFutex for more details
 * @warning Initializing a semaphore twice leads to a resource leak
 */
int initSemaphore(struct Semaphore* semaphore, int value);

/**
 * @brief Destroys the semaphore. If the retval is non zero, the semaphore is left untouched.
 * @param mutex A pointer to the semaphore.
 * @return 0 if everything went OK, else an ERRNO. See kernel/inc/sysFutex for more details
 */
int destroySemaphore(struct Semaphore* semaphore);

/**
 * @brief Increments the semaphore by one
 * @param semaphore the semaphore you want to increment
 * @return 0 if everything went OK, else an ERRNO. See kernel/inc/sysFutex for more details
 */
int semaphorePost(struct Semaphore* semaphore);

/**
 * @brief Decrements the semaphore, blocking if the currentval is zero or lower.
 * @param semaphore The semaphore you want to decrement
 * @return 0 if everything went OK, you now have a resource. If the return value is nonzero an error has occured. See kernel/inc/sysFutex for details.
 */
int semaphoreWait(struct Semaphore* semaphore);

/**
 * @brief Tries to decrement the semaphore, returns immidiately.
 * @param semaphore The semaphore you want to decrement.
 * @return 0 if a resource was available, it is now claimed. EBUSY if there was no resource available. Errors are possible, see kernel/inc/sysFutex.
 */
int semaphoreTryWait(struct Semaphore* semaphore);

/**
 * @brief Tries to decrement the semaphore, waiting at most the given time until returning.
 * @param semaphore The semaphore you want to decrement.
 * @param sleepReq The specfication of how long you want to block at most.
 * @return 0 if a resource was claimed. ETIMEDOUT if the specified time passed. Errors are possible, see kernel/inc/sysFutex.
 */
int semaphoreWaitTimeout(struct Semaphore* restrict semaphore, struct SleepRequest* restrict sleepReq);

/**
 * @brief gets the current value of the semaphore. This function cannot fail unless pointed to a wrong location. It might return rubbish if used on an uninitialized function.
 * @param semaphore The semaphore you want to know the value of
 * @return The current value of the semaphore
 */
int semaphoreGetValue(struct Semaphore* semaphore);
#endif //SEMPAHORE_H
