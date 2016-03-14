#ifndef MUTEX_H
#define MUTEX_H
/**
 * @author Jacko Dirks
 * @file mutex.h
 * Userside implementation of mutex: these functions are supposed to be used by the enduser
 */
#include "futex.h"

struct Mutex{
    struct Futex fut;
    struct ProcessContext* ownerContext;
};

/**
 * @brief Initializes the mutex to an unlocked state
 * @param mutex A pointer to the mutex you want to initialize
 * @return 0 if everything went OK, else an ERRNO. See kernel/inc/sysFutex for more details
 */
int initMutex(struct Mutex* mutex);

/**
 * @brief Destroys the mutex. If the retval is non zero, the mutex is still intact.
 * @param mutex A pointer to the mutex.
 * @return 0 if everything went OK, else an ERRNO. See kernel/inc/sysFutex for more details
 */
int destroyMutex(struct Mutex* mutex);

/**
 * @brief Locks the mutex, blocks until the mutex is locked.
 * @param mutex
 * @return 0 if everything went OK, else an ERRNO. EDEADLK if the mutex was already locked by callee. See kernel/inc/sysFutex for more details
*/
int lockMutex(struct Mutex* mutex);

/**
 * @brief tries to lock the mutex, returns immediately
 * @param mutex
 * @return 0 if it was locked, EBUSY if it was already locked, EDEADLK if the mutex was already locked by callee.
 */
int tryLockMutex(struct Mutex* mutex);

/**
 * @brief unlocks the mutex, but only if it was locked by the callee
 * @param mutex
 * @return 0 if everything went ok, EPERM if callee was not owner. See kernel/inc/sysFutex for additional errors.
 */
int unlockMutex(struct Mutex* mutex);

#endif //MUTEX_H
