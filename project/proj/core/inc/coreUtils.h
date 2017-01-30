#ifndef COREUTILS_H
#define COREUTILS_H
/* @file coreUtils.h
 * @author Jacko Dirks
 *
 * Provides common utility functions. Many have been written in assembly.
 */

/* @brief returns only after an interrupt has happened.
 *
 * The idea is that there is nothing to do in thread mode until after the next interrupt, so we suspend the thread mode.
 * When an interrupt happens, this interrupt is handled first and directly after this function returns.
 */
void waitForInterrupt(void);

/* @brief Checks whether or not we are currently in handler mode
 * @return 0 if we are not, nonzero if we are in an interrupt.
 */
int isInInterrupt(void);

/* @brief Checks wether or not the current interrupt is SVC interrupt.
 *
 * This function will also return false if the CPU is not in an interrupt at all, you do not need to check isInInterrupt first
 * @return 0 if we are not, nonzero if we are in the Supervisor Call interrupt.
 */
int isInSVCInterrupt(void);
#endif //COREUTILS_H
