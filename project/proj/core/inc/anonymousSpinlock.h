#ifndef ANONYMOUSSPINLOCK_H
#define ANONYMOUSSPINLOCK_H

#include "kernel/inc/process.h"
#include "sysCalls.h"

/**
 * @file anonymousSpinlock.h
 * @author Jacko Dirks
 *
 * This file specifies the anonymousAnonymousSpinlock interface.
 * The anonymousSpinlock is an unmanaged lockobject which does not provide any guarantees about order.
 * There is no owner: anyone can unlock a locked spinlock. It is usable inside an interrupt
 */

/**
 * The anonymousSpinlock struct. Its only possible values are 0 and 1, 1 is locked.
 */
struct AnonymousSpinlock {
    int value;
};

/**
 * @brief Initializes the anonymousSpinlock. Requires the pointer to point to an existing memory location.
 * It is advisable to destroy every anonymousSpinlock created by this function with the destroyAnonymousSpinlock function.
 * It is allowed to skip this function and manually make sure the struct location is all zero.
 * @param anonymousSpinlock The anonymousSpinlock we want tot initialize
 * @return 0 if everything was ok, nonzero if not.
 */
int initAnonymousSpinlock(struct AnonymousSpinlock* anonymousSpinlock);

/**
 * @brief Destroys the anonymousSpinlock.
 *
 * If this function is called while the anonymousSpinlock is in a locked state it trows an error.
 * @param anonymousSpinlock The anonymousSpinlock we want to destroy.
 * @return 0 if everything was ok, nonzero if not.
 */
int destroyAnonymousSpinlock(struct AnonymousSpinlock* anonymousSpinlock);

/**
 * @brief Locks the anonymousSpinlock
 * This function only returns when the anonymousSpinlock is locked or after a fatal error.
 * @return 0 if everything was ok, nonzero if not
 */
int lockAnonymousSpinlock(struct AnonymousSpinlock* anonymousSpinlock);

/**
 * @brief Tries to lock the anonymousSpinlock, returns immeaditaly
 * This function tries once and then returns
 * @return 0 if locked, nonzero if not
 */
int tryLockAnonymousSpinlock(struct AnonymousSpinlock* anonymousSpinlock);

/**
 * @brief Releases the anonymousSpinlock.
 * If the calling process was not the owner, then nothing happens.
 * @return 0 if everything was ok, nonzero if not.
 */
int unlockAnonymousSpinlock(struct AnonymousSpinlock* anonymousSpinlock);
#endif //ANONYMOUSSPINLOCK_H
