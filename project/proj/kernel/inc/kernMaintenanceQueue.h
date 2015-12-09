#ifndef KERNMAINTENANCEQUEUE_H
#define KERNMAINTENANCEQUEUE_H

#include "process.h"

/**
 * @file kernMaintenanceQueue.h
 * @author Jacko Dirks
 * @brief Supports the Supervisor in holding track of all processes that need maintenaince, or are done being maintained
 */

/**
 * @brief Add a process to the processQueue. It will be added to the end of it.
 * @param procPtr The pointer to the process you want to add. If this pointer is NULL, nothing happens
 * @warning If this function is called by anything other then the supervisor it will silently fail
 */
void kernRetQueuePush(struct Process* procPtr);

/**
 * @brief Pop a process from the kernelQueue. It will be popped from the top.
 * @return The popped Process pointer or NULL if there was none
 * @warning If this function is called by anything other then the supervisor it will silently fail
 */
struct Process* kernRetQueuePop(void);

/**
 * @brief get the entire queue (linkedlist) and empty out the internal buffer
 * @return The entire kernelQueue or NULL if there was none
 */
struct Process* kernRetQueueGet(void);

/**
 * @brief Used by the SVC to pass processes to the kernel for handling
 * @param proc The process passed to the kernel for handling
 * @warning Do not call this function when not in Supervisor.
 */
void passProcessToKernel(struct Process* const proc);

/**
 * @brief pops a process from the buffer and returns that process
 * @return NULL if there were no processes, a process if there was a process in the buffer.
 */
struct Process* kernelBufferGetProcess(void);
#endif //KERNMAINTENANCEQUEUE_H
