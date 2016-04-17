#ifndef SYSMANAGEDLOCK_h
#define SYSMANAGEDLOCK_h
/**
 * @author Jacko Dirks
 * @file sysManagedLock.h
 * This is the system side of the inter-thread or inter-process non-busy lock handling: the sempahore and the mutex.
 * On the kernelside this is called a managed lock. This file is purely management of the managed lock objects, it cannot behave like an actual mutex/semaphore handler.
 * A process can wait for a mutex for a limited time or infinitely.
 * The process of handing the mutex to the next process is FIFO and therefore fair:
 * under the presumption that every process will eventually let go of a mutex, every process will eventually get the mutex.
 * All functions defined here should only be called by the kernel:
 * calling by interrupt might lead to undefined behaviour, calls by non-kenernel should lead to sergfault.
 *
 * Before a managed lock can be used it needs to be requested from this module.
 *
 * There is also a timer related to this kernel module, it works about the same as the sleep module timer.
 */
#include "sysSleep.h"
#include "abstrSysSleepStructs.h"

/**
 * @brief Allocates a manged lock
 * @param lockId The location an id for the object will be written to. Invalid if retval != 0
 * @param owner The original owner/creator of the lock. Used to free all locks of a killed/ended process
 * @return 0 if everything was ok, ERRNO val if it was not:
 * -ENOLCK if out of locks
 */
int allocateManagedLock(size_t* lockId, uintptr_t owner);

/**
 * @brief Releases an allocated lock. Will refuse if processes were waiting for it
 * @param lockId The lock you want to release
 * @return 0 if everything was ok, EINVAL if lock was not found, EDEADLK if there were still processes waiting for the lock (the lock will not be released).
 *
 * Locks are not bound to their owner: any process can release them.
 */
int freeManagedLock(size_t lockId);

/**
 * @brief Tries to release all locks allocated to the specified owner. Cannot fail
 * @param owner The process whose resources are reaped
 * @return 0
 */
int freeManagedLockByOwner(uintptr_t owner);

/**
 * @brief Adds a process to the waiting list of the managed object refered to by lockId
 * @param lockId The id of the lock whos waiting list the process will be added to
 * @param proc The process that is added to the waiting list
 * @return 0 if everything was ok, EINVAL if lockId is invalid
 */
int waitForManagedLock(size_t lockId, struct Process* proc);

/**
 * @brief removes one process from the waiting list of the managed lock object refered to by lockID
 * @param lockId The id of the lock whos waiting list refered to
 * @param procReady a pointer that will be set to the process that is released. NULL if there was no process
 * @return 0 if everything was ok (the situation where there was no process waiting is also counted as ok), EINVAL if lockId is invalid
 */
int releaseManagedLock(size_t lockId, struct Process** procReady);

/**
 * @brief Removes the specified process from the specified lock
 * @param lockId The id of the lock whos waiting list refered to
 * @param proc The proc that will be removed from the waitinglist of the refered lock
 * @return 0 if everything was ok, EINVAL if lockId is invalid, EAGAIN if proc was not waiting for given lock.
 */
int removeProcessFromManagedLock(size_t lockId, struct Process* proc);

/**
 * The following functions are related to the sleep/wait combination
 */

/**
 * @brief Sets up a process to wait for a specified lock for at most the specified amount of time
 * @param lockId the ID of the lock the process is going to wait for
 * @param proc The process that is going to wait with a timeout
 * @param slpReq A sleeping struct to indicate how long the timeout is
 * @return 0 if everything was ok
 *      EINVAL if lockId is invalid
 *      ETIMEDOUT The timer had already ran out, the process is not added to the module
 */
int timedWaitForManagedLock(size_t lockId, struct Process* proc, struct SleepRequest* slpStr);

/**
 * @brief Should be called whenever the Managed Lock timer finishes
 */
struct Process* timedManagedLockTimeout(void);

/**
 *@brief Should be called whenever the system timer overflows
 */
struct Process* timedManagedLockSysTimerOverflow(void);

#endif //SYSMANAGEDLOCK_h
