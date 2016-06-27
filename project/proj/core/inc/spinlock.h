#ifndef SPINLOCK_H
#define SPINLOCK_H

#include "kernel/inc/process.h"
#include "sysCalls.h"

/**
 * @file spinlock.h
 * @author Jacko Dirks
 *
 * This file specifies the spinlock interface.
 * The spinlock is an unmanaged lockobject which does not provide any guarantees about order.
 * The spinlock has an owner and cannot be used in an interrupt.
 */

/**
 * The spinlock struct. Its only possible values are 0 and 1, 1 is locked.
 */
struct Spinlock {
    int value;
    struct ProcessContext* owner;
};

/**
 * @brief Initializes the spinlock. Requires the pointer to point to an existing memory location.
 * It is advisable to destroy every spinlock created by this function with the destroySpinlock function
 * This function promises to set every field of the spinlock to NULL/0, e.g. a spinlock in the .BSS section does not have to be initialized.
 * @param spinlock The spinlock we want tot initialize
 * @return 0 if everything was ok, nonzero if not.
 */
int initSpinlock(struct Spinlock* spinlock);

/**
 * @brief Destroys the spinlock.
 *
 * If this function is called while the spinlock is in a locked state it trows an error.
 * @param spinlock The spinlock we want to destroy.
 * @return 0 if everything was ok, nonzero if not.
 */
int destroySpinlock(struct Spinlock* spinlock);

/**
 * @brief Locks the spinlock
 * This function only returns when the spinlock is locked or after a fatal error.
 * @return 0 if everything was ok, nonzero if not
 */
int lockSpinlock(struct Spinlock* spinlock);

/**
 * @brief Tries to lock the spinlock, returns immeaditaly
 * This function tries once and then returns
 * @return 0 if locked, nonzero if not
 */
int tryLockSpinlock(struct Spinlock* spinlock);

/**
 * @brief Releases the spinlock.
 * If the calling process was not the owner, then nothing happens.
 * @return 0 if everything was ok, nonzero if not.
 */
int unlockSpinlock(struct Spinlock* spinlock);
#endif //SPINLOCK_H
