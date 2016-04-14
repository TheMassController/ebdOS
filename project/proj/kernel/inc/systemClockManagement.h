#ifndef SYSTEMCLOCKMANAGEMENT_H
#define SYSTEMCLOCKMANAGEMENT_H
/**
 * @file systemClockManagement.h
 * @author Jacko Dirks
 * @brief Manages the main system clocks.
 *
 * This also handles the main timer for the system. It increments evey microsecond and gives out a pulse to the supervisor when it interrupts.
 */

#include <stdint.h>

#define EBD_SYSCLOCKMAXVAL 4294967295

/**
 * @brief Returns the current value of the system clock
 * @return The current value of the system clock
 */
uint32_t getSystemClockValue(void);

/**
 * @brief enables, sets and loads a given half of a given wide timer with the given values
 * Assumes that all interrupts are already setup
 * @param enable 0 if the timer should be disabled
 * @param ulBase The address of the wide timer
 * @param ulTimer The side of the timer
 * @param lValue the value that will be loaded into the timer, but only if enable != 0
 * @param mValue the match value that will be set in the timer, but only if enable != 0
 */
void setHalfWTimerInterrupt(int enable, unsigned long ulBase, unsigned long ulTimer, unsigned long lValue, unsigned long mValue);

/*
 * These are two interrupthandlers
 */
void systemTimerInterrupt(void);
void sleepTimerInterrupt(void);

#endif //SYSTEMCLOCKMANAGEMENT_H
