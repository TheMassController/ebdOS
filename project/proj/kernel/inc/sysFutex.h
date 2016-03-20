/**
 * @brief The kernelspace side of the futex implementation. Uses the managed mutex.
 * @author Jacko Dirks
 * This is a kernel build-in: the kernel supports futex, as opposed to it being a module.
 *
 * This module will NEVER TOUCH ATOMICVAL. The change of value in atomicval and its initialization should all happen in userspace
 *
 * The kernel should call the functions defined here and usually place the returnvals of the functions in the retval variable of the callee process.
 */

#include "futex.h"
#include "process.h"

/**
 * @brief Initialize a new Futex
 * @param fut The futex, as presented by userspace, that is being initialized
 * @return 0 if everything was ok, the lockID field of the futex struct will be set. ERRNO if not:
 * ENOLCK if out of locks
 * EINVAL if there was a problem with the parameter
 */
int sysInitFutex(struct Futex* fut, struct Process* proc);

/**
 * @brief Puts the process in a wait state, but only if atomicVal of the futex struct <= 0
 * @param fut The futex, as presented by userspace, that is being initialized
 * @return 0 if everything was ok, this is the case where there were no bounces: a bounce is an error.
 * EAGAIN if the value of the lock was > 0, do not forward this error to the callee
 * EINVAL if the fut param was incorrect
 *
 * The only reason why a bounce is defined as an error is so that the kernel will put the callee process back into the readyqueue. EAGAIN should not be forwarded to the callee process.
 * If the retval is nonzero, reactivate the process. If not the managedLockModule has taken care of it
 */
int sysFutexWait(struct Futex* fut, struct Process* proc);

/**
 * @brief Releases a single process from the futex if there was one
 * @param fut The futex from which a process is released
 * @param procPtr A released process or NULL in case of error or no processes to release
 * @return if there was no error 0, else:
 * EINVAL if there was a problem with fut
 */
int sysFutexPost(struct Futex* fut, struct Process** procPtr);

/**
 * @brief Releases the resources allocated to this futex
 * @param Fut the released futex
 * @return 0 if everything was ok. Else:
 * EINVAL if there was a problem with fut
 * EDEADLK if the lock could not be released because processes were waiting for it. The lock will not be released in this case
 */
int sysDestroyFutex(struct Futex* fut);
