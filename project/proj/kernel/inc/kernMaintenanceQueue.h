#ifndef KERNMAINTENANCEQUEUE_H
#define KERNMAINTENANCEQUEUE_H

#include "process.h"

/**
 * @file kernMaintenanceQueue.h
 * @author Jacko Dirks
 * @brief Supports the Supervisor in holding track of all processes that need maintenaince
 * @warning All functions defined here can only be called by the supervisor. In any other case they will silently fail.
 */

/**
 * @brief Add a process to the processQueue. It will be added to the end of it.
 * @param procPtr The pointer to the process you want to add. If this pointer is NULL, nothing happens
 * @warning If this function is called by anything other then the supervisor it will silently fail
 */
void kernQueue_push(struct Process* procPtr);

/**
 * @brief Pop a process from the kernelQueue. It will be popped from the top.
 * @return The popped Process pointer or NULL if there was none
 * @warning If this function is called by anything other then the supervisor it will silently fail
 */
struct Process* kernQueue_pop(void);

#endif //KERNMAINTENANCEQUEUE_H
