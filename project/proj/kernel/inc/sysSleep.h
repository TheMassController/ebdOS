#ifndef SYSSLEEP_H
#define SYSSLEEP_H
/**
 * @author Jacko Dirks
 * @file sysSleep.h
 * This is the kernel side of orinary sleeping. The compination synchronization/sleep is handled elsewhere
 */

#include "process.h"
#include "sleep.h"

struct SleepingProcessStruct{
    struct Process* process;
    struct SleepingProcessStruct* nextPtr;
    unsigned overflows;
    unsigned sleepUntil;
};

void __sleepMSDelayBlock(unsigned ms);

/**
 * @brief Adds a process to the sleep module
 * @param Proc A pointer to the process you want to add.
 * @param sleepRequest The full sleep request. This thing is processed, so the sleepingProcessStruct does not have to be set.
 * @warning Calling this process from interrupt causes crash
 * @warning Calling this process unprivileged causes MPU error
 */
void addSleeper(struct Process* proc, struct SleepRequest* sleepRequest);

/**
 * @brief removes a process from the sleep module.
 * The process is only removed, not passed on to the SVC
 * @param proc The process that is removed from the sleep module
 * @return NULL if the process was not found, the same process pointer as the first param else.
 * @warning Calling this process from interrupt causes crash
 * @warning Calling this process unprivileged causes MPU error
 */
struct Process* removeSleeper(struct Process* proc);


#endif //SYSSLEEP_H
