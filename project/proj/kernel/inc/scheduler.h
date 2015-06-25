#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"    // Contains the declaration of struct Process

/* @file scheduler.h
 * @author Jacko Dirks
 *
 * This file defines the functions available to the SVC interrupt and the rest of the world to communicate with the scheduler.
 * Non-priviliged processes cannot call these functions at all without hitting the MPU.
 * Privileged processes can call some and some will silently fail.
 * Interrupts can call all, but this might result in undefined behaviour. Only the SVC interrupt can call all functions safely.
 *
 * The idea is that a process generates an SVC interrupt if it wants to interact with the scheduler, for example because it wants to fall asleep or it wants to yield.
 *
 * The size of the timeslice needs to be written to the systick timer. The systick timer can only contain 24 bit, and thus this is the maxlength of the timeslice.
 * The slice is get and set in MS. The maxlength depends on the clock source.
 * @see setup.c to find out which clock source is used by the systick timer.
 *
 * Currently the scheduler is completely round robin, the priorities are ignored.
 */

/* @brief Get the current length of the timeslice in ms. This function can be called by any function.
 * @return Length of timeslice in ms.
 * @warning This value is only guaranteed to be correct when this function is called from the SVC.
 */
unsigned getTimeSlice(void);

/* @brief Get the maximal timeslice length.
 * @return The maximal timeslice length.
 * @warning This function will cause a segfault if called from unprivileged mode.
 */
unsigned getMaxTimeSlice(void);

/* @brief Set the current length of the timeslice in ms.
 * @return The value that is set as the new timeslice.
 * @warning If this function is not called from an interrupt it silently fails. If the interrupt is not SVC then undefined behaviour might happen.
 */
unsigned setTimeSlice(unsigned newSlice);

/* @brief Adds a process to the scheduler, thus allowing it to get timeslices.
 * @param proc A pointer to the process you want to add.
 * @warning If this function is not called from an interrupt it silently fails. If the interrupt is not SVC then undefined behaviour might happen.
 */
void addProcessToScheduler(struct Process* proc);

/* @brief Removes a process from the scheduler, thus preventing it from getting timeslices again.
 *
 * If this is the current active process then this function will trigger a context switch.
 * @param proc A pointer to the process you want to remove.
 * @return 0 if the process was not on the scheduler, nonzero else.
 * @warning If this function is not called from an interrupt it silently fails. If the interrupt is not SVC then undefined behaviour might happen.
 */
int removeProcessFromScheduler(struct Process* proc);

/* @brief Tests if given process is currently in the scheduler.
 * @param proc A pointer to the process this request is about.
 * @return 1 if the process is on the scheduler, 0 if it is not.
 * @warning This value is only guaranteed to be correct when this function is called from the SVC.
 * @warning This function will cause a segfault if called from unprivileged mode.
 */
int processInScheduler(struct Process* proc);

/* @brief Forces a reschedule without waiting for the systick.
 * @warning If this function is not called from an interrupt it silently fails. If the interrupt is not SVC then undefined behaviour might happen.
 */
void premptCurrentProcess(void);

#endif // SCHEDULER_H
