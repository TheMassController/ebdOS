#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"    // Contains the declaration of struct Process

/**
 * @file scheduler.h
 * @author Jacko Dirks
 *
 * This file defines the functions available to the SVC interrupt and the rest of the world to communicate with the scheduler.
 * Non-priviliged processes cannot call these functions at all without hitting the MPU.
 * Privileged processes can call some and some will silently fail.
 * Interrupts can call all, but this might result in undefined behaviour and some in silent failure. Only the SVC interrupt can call all functions safely.
 * See the warnings in the function descriptions.
 * The idea is that a process generates an SVC interrupt if it wants to interact with the scheduler, for example because it wants to fall asleep or it wants to yield.
 *
 * The scheduler also interacts with the systick and the pendSV.
 * The systick is set by the scheduler and the interrupt is catched in the scheduler.
 * The pendSV is an interrupt which is triggered to do the actual context switch.
 * The scheduler is (and should be) the only one to ever trigger the pendSV.
 * Its starting point resides in @see contextSwitcher.S and it uses some of the functions defined here.
 *
 * Currently the scheduler is completely round robin, the priorities are ignored.
 */

/**
 * @brief Initializes the scheduler by setting the global context to given currentProcess and accepting the idleProcess
 * @param currentProc The current process at the very start of the OS. Usually the kernel.
 * @param idleProd The idle process, this process runs when no other process runs.
 * @warning If this process runs twice it crashes the OS.
 */
void initScheduler(struct Process* idleProc, struct Process* currentProc);

/**
 * @brief Get the current length of the timeslice in ms. This function can be called by any function.
 * @return Length of timeslice in ms.
 * @warning This value is only guaranteed to be correct when this function is called from the SVC.
 */
unsigned getTimeSlice(void);

/**
 * @brief Get the maximal timeslice length in ms.
 * @return The maximal timeslice length in ms.
 * @warning This function will cause a segfault if called from unprivileged mode.
 */
unsigned getMaxTimeSlice(void);

/**
 * @brief Set the current length of the timeslice in ms.
 * @return The value that is set as the new timeslice.
 * @warning If this function is not called from SVC interrupt it silently fails.
 */
unsigned setTimeSlice(unsigned newSlice);

/**
 * @brief Adds a process to the scheduler, thus allowing it to get timeslices.
 * @param proc A pointer to the process you want to add.
 * @warning If this function is not called from SVC interrupt it silently fails.
 */
void addProcessToScheduler(struct Process* proc);

/**
 * @brief Removes a process from the scheduler, thus preventing it from getting timeslices again.
 * If this is the current active process then this function will trigger a context switch.
 * @param proc A pointer to the process you want to remove.
 * @warning If this function is not called from SVC interrupt it silently fails.
 */
void removeProcessFromScheduler(struct Process* proc);

/**
 * @brief Tests if given process is currently in the scheduler.
 * @param proc A pointer to the process this request is about.
 * @return 1 if the process is on the scheduler, 0 if it is not.
 * @warning This value is only guaranteed to be correct when this function is called from the SVC.
 * @warning This function will cause a segfault if called from unprivileged mode.
 */
int processInScheduler(struct Process* proc);

/**
 * @brief Forces a reschedule without waiting for the systick.
 * @warning If this function is not called from SVC interrupt it silently fails.
 */
void preemptCurrentProcess(void);

/**
 * @brief Gets the pointer to the process that is currently active.
 * @return The pointer to the currently active process
 * @warning This value is only guaranteed to be correct when this function is called from the SVC.
 * @warning This function will cause a segfault if called from unprivileged mode.
 */
struct Process* getCurrentProcess(void);

/**
 * @brief Pops the current process from the scheduler and returns a pointer to it.
 * This function will trigger a context switch
 * @return The pointer to the currently active process
 * @warning If this function is not called from SVC interrupt it always returns NULL
 */
struct Process* popCurrentProcess(void);

/**
 * @brief Returns the process that, under the current circumstances, will be the next process to get a timeslice.
 * The next process can be the same as the current process, for example when there are no other processes.
 * @return The process that, under the current circumstances, will get the next timeslice.
 */
struct Process* getNextActiveProcess(void);

/**
 * @brief Changes the global context, which is everything except the registers
 * Use this function with care: when not used as init or in conjunction with a register swap processes lose their context and all sorts of nasty things can start happening.
 * This function also changes the systick setup, if applicable.
 * @param newProcPtr The global context will be switched to the context related to this process pointer
 * @warning This function will not swap registers
 */
void changeGlobalContext(struct Process* newProcPtr);
#endif // SCHEDULER_H
