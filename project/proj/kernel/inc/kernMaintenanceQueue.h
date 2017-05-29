#ifndef KERNMAINTENANCEQUEUE_H
#define KERNMAINTENANCEQUEUE_H

#include "process.h"

/**
 * @file kernMaintenanceQueue.h
 * @author Jacko Dirks
 * @brief Supports the Supervisor in holding track of all processes that need maintenaince, or are done being maintained
 */

/**
 * @brief Sets the returnvalue from the perspective of procPtr and releases the process to the scheduler
 * @param procPtr The process released
 * @param contextRetVal The returnvalue to be set.
 */
void releaseProcessToScheduler(struct Process* procPtr, int contextRetVal);

/**
 * @brief Add a process to the processQueue. It will be added to the end of it.
 * @param procPtr The pointer to the process you want to add. If this pointer is NULL, nothing happens
 * @warning If this function is called by anything other then the supervisor it will silently fail
 */
void kernRetQueuePush(struct Process* procPtr);

/**
 * @brief Add a list of processes to the processQueue. It will be added to the end of it.
 *
 * The singly linked list structure of the Process struct is used. It is safe agains NULL additions.
 * @param procPtr The pointer to the first process you want to add. If this pointer is NULL, nothing happens
 */
void kernRetQueueAddList(struct Process* procPtr);

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
struct Process* kernRetQueueEmpty(void);

/**
 * @brief Used by the SVC to pass processes to the kernel for handling
 * @param proc The process passed to the kernel for handling
 * @warning Do not call this function when not in Supervisor.
 */
void passProcessToKernel(struct Process* const proc);

/**
 * @brief pops a process from the buffer and returns that process
 * @return NULL if there were no processes, a process if there was a process in the buffer.
 * @warning Do not call this function from any other process then Kernel
 */
struct Process* kernelBufferGetProcess(void);

/**
 * @brief Test if the Kernel has any processes left to handle
 * @return 1 if there are processes in the buffer, 0 if there are none
 */
int KernelProcessBufferIsEmpty(void);
#endif //KERNMAINTENANCEQUEUE_H
