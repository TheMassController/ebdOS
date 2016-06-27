#ifndef SYSSLEEP_H
#define SYSSLEEP_H
/**
 * @author Jacko Dirks
 * @file sysSleep.h
 * This is the kernel side of ordinary sleeping. The combination synchronization(mutexing)/sleep is handled elsewhere.
 * This sleep subsystem depends on the system timer, the one that changes every microsecond.
 * An internal interrupt and a specific SVC call is used to communicate processes that have awoken back to the scheduler.
 * This module is tightly coupled with the SVC.
 */

#include "core/inc/sleep.h"          // Contains sleepRequest struct
#include "process.h"        // Contains process struct

/**
 * @brief Adds a process to the sleep module
 * @param Proc A pointer to the process you want to add.
 * @param sleepRequest The full sleep request. This thing is processed, so the sleepingProcessStruct does not have to be set.
 * @return A list of processes that is done sleeping.
 * @warning Calling this function from interrupt causes crash
 * @warning Calling this function unprivileged causes MPU error
 */
struct Process* addSleeper(struct Process* proc, const struct SleepRequest* sleepRequest);

/**
 * @brief removes a process from the sleep module.
 * Call refreshSleepList during runtime. It is assumed that the sleeper is in the list.
 * @param proc The process that is removed from the sleep module
 * @return A list of processes, including those who are done sleeping and the removed one.
 * @warning Calling this function from interrupt causes crash
 * @warning Calling this function unprivileged causes MPU error
 */
struct Process* removeSleeper(struct Process* proc);

/**
 * @brief Refreshes sleeplist, resets the interrupt, returns the list of processes that are done.
 * @return A linkedlist of processes whose sleeping times have passed.
 */
struct Process* refreshSleeplist(void);

/**
 * @brief Handles the overflow of the system timer.
 * The overflow is handled internally after which a list of processes that is now ready to be added to the scheduler is returned.
 * @return A list of processes that is now ready to be handled
 * @warning Calling this function from anything other then the SVC may cause unintended bahviour.
 * @warning Calling this function unprivileged causes MPU error
 */
struct Process* sleepHandleSysTimerOverflow(void);


#endif //SYSSLEEP_H
