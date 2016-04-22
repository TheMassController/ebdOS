#ifndef REENTRANTMUTEX_H
#define REENTRANTMUTEX_H
/**
 * @brief Implements the reentrant mutex
 *
 * There are no good reasons to use this: either use the semaphore or the non reentrant mutex. But Newlib requests it, sooo
 * Everytime you lock it and you are already the owner an internal counter increases. When you unlock it, the same counter decreases. If the counter hits zero, the r-tex is actually unlocked.
 *
 * DO NOT USE THIS.
 * @warning Operations on an unintialized state might lead to undefined behaviour
 * @author Jacko Dirks
 * @file reentrantMutex.h
 */

#include "futex.h"
#include "sleep.h"

struct ReentrantMutex{
    struct Futex fut;
    unsigned value;
    struct ProcessContext* ownerContext;
};

/**
 * @brief Blocks until the reentrant mutex is obtained, increases reentrant counter if already obtained.
 * @param mutex The pointer to the reentrant mutex that is being blocked
 * @return 0 if everything is ok, EINVAL if given r-tex is invalid
 */
int lockReentrantMutex(struct ReentrantMutex* mutex);

/**
 * @brief Tries once to lock the given reentrant mutex, returns immidiately. If the r-tex was already owned by the process, the counter is increased
 * @param mutex The pointer to the reentrant mutex that is being blocked
 * @return 0 if everything is ok, EINVAL if given r-tex in invalid
 */
int tryLockReentrantMutex(struct ReentrantMutex* mutex);

/**
 * @brief Tries to lock the given reentrant mutex for the given amount of time. If the r-tex was already owned by the process, the counter is increased
 * @param mutex The pointer to the reentrant mutex that is being blocked
 * @return 0 if everything is ok, EINVAL if given r-tex is invalid, ETIMEDOUT if timed out
 */
int lockReentrantMutexTimeout(struct ReentrantMutex* restrict mutex, struct SleepRequest* restrict sleepReq);

/**
 * @brief Decreases the counter of the r-tex, releasing the r-tex if counter hits zero.
 * @param mutex The pointer to the reentrant mutex that is being blocked
 * @return 0 if everything is ok, EINVAL if given r-tex is invalid, EPERM if you are not the owner
 */
int unlockReentrantMutex(struct ReentrantMutex* mutex);


/**
 * @brief Initializes the r-tex to an unlocked state
 * @param mutex A pointer to the r-tex you want to initialize
 * @return 0 if everything went OK, ENOLOCK if out of managed lock resources.
 */
int initReentrantMutex(struct ReentrantMutex* mutex);

/**
 * @brief Releases the resources related to given r-tex. Always call this at the end of the lifecycle.
 * @param mutex A pointer to the r-tex you want to unintialize
 * @return 0 if everything went OK, EINVAL if the futex was invalid
 */
int destroyReentrantMutex(struct ReentrantMutex* mutex);
#endif //REENTRANTMUTEX_H
