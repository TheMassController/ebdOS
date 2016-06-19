/**
 * @file futex.h
 * @author Jacko Dirks
 *
 * The declaration of the userspace side of the futex. Futex is the used implementation for mutexing and semaphores.
 * Futex is still one abstraction too low and should not be used by the user.
 * The user should use mutex or sempahore (or spinlock).
 *
 * A futex is not grabable when it is zero or lower, but will still be decreased.
 * Any process trying to grab a futex that cannot be grabbed anymore will block, either for a limited amount of time or forever.
 * Because the locking meganism is dependend on the managed lock, the locking queue is round robin: first come, first serve.
 *
 * Available is defined as the atomic val of the Futex being > 0. If it is lower then zero, any post call will block or be rejected, dependend on the called function.
 */
#ifndef FUTEX_H
#define FUTEX_H

#include <stddef.h>

#include "sleep.h"

struct Futex {
    int atomicVal;
    size_t lockId;
};

/**
 * @brief Initializes a futex to the given value
 * @param fut A pointer to the futex struct that will be initialized
 * @param value The initial value of the futex
 * @return 0 if everything went OK, else an ERRNO. See kernel/inc/sysFutex for more details
 */
int initFutex(struct Futex* fut, int value);

/**
 * @brief Destroys a futex, releasing the managed lock that was allocated
 * @param fut A pointer to the futex struct that will be de-initialized
 * @return 0 if everything went OK, else an ERRNO. See kernel/inc/sysFutex for more details
 */
int destroyFutex(struct Futex* fut);

/**
 * @brief increases the amount of resources with one.
 * @param fut The futex struct.
 * @return 0 if everything went OK, else an ERRNO. See kernel/inc/sysFutex for more details
 */
int futexPost(struct Futex* fut);

/**
 * @brief requests one more resource from the futex, blocks if none available.
 * @param fut The futex struct from whom a resource is requested
 * @return 0 if everything went OK, else an ERRNO. See kernel/inc/sysFutex for more details
 */
int futexWait(struct Futex* fut);

/**
 * @brief Requests one resource from the futex, returns immediately
 * @param fut The futex struct
 * @return 0 if everything went OK and a resource was available, EBUSY if there were no resources available.
 */
int futexTryWait(struct Futex* fut);

/**
 * @brief Requests one resource from the mutex, blocks for at most the given amount of time if no resources are available right now.
 * @param fut The futex struct
 * @param sleepReq A struct indicating the max wait time.
 * @return 0 if everything went OK, ETIMEDOUT if the mutex was not available in the specified amount of time, other ERRNOs are also possible. See kernel/inc/sysFutex.h for more details
 */
int futexWaitTimeout(struct Futex* restrict fut, struct SleepRequest* restrict sleepReq);

/**
 * @brief gets the current value of the futex. This function cannot fail unless pointed to a wrong location. It will return rubbish if used on an uninitialized function.
 * @param fut The futex you want to know the value of
 * @return The current value of the futex
 */
int futexGetValue(struct Futex* fut);
#endif //FUTEX_H
