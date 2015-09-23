#ifndef SYSSLEEP_H
#define SYSSLEEP_H
/**
 * @author Jacko Dirks
 * @file sysSleep.h
 * This is the kernel side of orinary sleeping. The compination synchronization/sleep is handled elsewhere.
 * This sleep subsystem depends on the system timer, the one that changes every microsecond.
 * An internal interrupt and a specific SVC call is used to communicate processes that have awoken back to the scheduler.
 * This module is tightly coupled with the SVC.
 */

#include "process.h"
#include "sleep.h"

struct SleepingProcessStruct{
    struct Process* process;
    struct SleepingProcessStruct* nextPtr;
    unsigned overflows;
    unsigned sleepUntil;
};

// Depricated
void __sleepMSDelayBlock(unsigned ms);

/**
 * @brief Adds a process to the sleep module
 * @param Proc A pointer to the process you want to add.
 * @param sleepRequest The full sleep request. This thing is processed, so the sleepingProcessStruct does not have to be set.
 * @return NULL if the process was successfully added, proc if not, because sleep time was already expired
 * @warning Calling this function from interrupt causes crash
 * @warning Calling this function unprivileged causes MPU error
 */
struct Process* addSleeper(struct Process* proc, struct SleepRequest* sleepRequest);

/**
 * @brief removes a process from the sleep module.
 * The process is only removed, not passed on to the SVC
 * @param proc The process that is removed from the sleep module
 * @return NULL if the process was not found, the same process pointer as the first param else.
 * @warning Calling this function from interrupt causes crash
 * @warning Calling this function unprivileged causes MPU error
 */
struct Process* removeSleeper(struct Process* proc);

/**
 * @brief Handles the overflow of the system timer.
 * The overflow is handled internally after which a list of processes that is now ready to be added to the scheduler is returned.
 * @return A list of processes that is now ready to be handled
 * @warning Calling this function from anything other then the SVC may cause unintended bahviour.
 * @warning Calling this function unprivileged causes MPU error
 */
struct Process* sleepHandleSysTimerOverflow(void);


#endif //SYSSLEEP_H
