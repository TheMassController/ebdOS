/**
 * @brief A module that unifies a wait-like subsystem
 * @author Jacko Dirks
 *
 * There are many situations in which you want to wait for x time or event y and stop waiting if one of both happens.
 * This module handles the waiting part of this equation. It manages a system timer which works in the same way as the sleep timer.
 * If a process is added, it is added in combination with a remove function, this function should remove the process from the queue of the actual thing it is waiting for.
 * There is also a way to remove a process from this subsystem.
 *
 * A thing to take into consideration is that a process exists in two places if this module is used, which might lead to the process being added to the scheduler twice and other forms of nastiness.
 * This module is very prone to race conditions, is the point. Therefore the remove function called is required to either remove the process from the module and return it or return NULL.
 * The remove function shall not return anything else.
 * This module also never touches the state of the process.
 *
 * This module manages its own timer, the waitTimer. Its inner workings are very alike to the sleep timer.
 */

#include "process.h"
#include "core/inc/sleep.h"

/**
 * @brief Adds a process to the wait queue
 * @param remove The function that is called with the given process as param whenvever its timer expires
 * @param proc The process that needs to wait
 * @param sleepReq The sleep request struct
 * @return 0 if everything went ok
 *  ETIMEDOUT if the timer had already ran out
 */
int addWaiter(struct Process*(*remove)(struct Process*), struct Process* proc, struct SleepRequest* sleepReq);

/**
 * @brief Removes a waiter from this module
 * @param proc The process you want to remove
 * @return 0 if everything was ok
 *  EINVAL if the requested process was not found
 * @warning If EINVAL is returned, the kernel might already be done for.
 */
int removeWaiter(struct Process* proc);

/**
 * @brief Should be called whenever the Managed Lock timer finishes
 */
struct Process* waitTimerTimeout(void);

/**
 *@brief Should be called whenever the system timer overflows
 */
struct Process* waitTimerSysTimerOverflow(void);
