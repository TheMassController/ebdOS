#ifndef SYSTEMCLOCKMANAGEMENT_H
#define SYSTEMCLOCKMANAGEMENT_H
/**
 * @file systemClockManagement.h
 * @author Jacko Dirks
 * @brief Manages the main system clock.
 *
 * This is the main timer for the system. It increments evey microsecond and gives out a pulse to the supervisor when it interrupts.
 */

#define EBD_SYSCLOCKMAXVAL 4294967295

/**
 * @brief Returns the current value of the system clock
 * @return The current value of the system clock
 */
unsigned getSystemClockValue(void);

/*
 * These are two interrupthandlers
 */
void systemTimerInterrupt(void);
void sleepTimerInterrupt(void);

#endif //SYSTEMCLOCKMANAGEMENT_H
