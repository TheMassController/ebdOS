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

/* @brief Fills the section in between startPtr and endPtr with zeros. Inclusive start, exclusive end.
 *
 * There are no alignment requirements, other that byte-alignment offcourse (minimum addressable).
 * @param startPtr The pointer that points to the first address, the data behind this address is also set to zero
 * @param endPtr The pointer that points to the last address, the data behind this address is not set to zero
 */
void zeroFillSection(void* startPtr, void* endPtr);
#endif //COREUTILS_H
