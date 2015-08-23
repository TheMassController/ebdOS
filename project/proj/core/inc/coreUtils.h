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
 * @return 0 if we are not, nonzero if we are in an interrupt.
 */
int isInSVCInterrupt(void);

/* @brief Fills the section in between startPtr and endPtr with zeros. Inclusive start, exclusive end.
 *
 * There are no alignment requirements, other that byte-alignment offcourse (minimum addressable). 
 * @param startPtr The pointer that points to the first address, the data behind this address is also set to zero
 * @param endPtr The pointer that points to the last address, the data behind this address is not set to zero
 */
void zeroFillSection(void* startPtr, void* endPtr);

/**
 * @brief Increments an integer threadsafe.
 * This function guarantees that the value of integer will not pass maxval if only this function is used to increase the value.
 * If the given integer was already at maxval or higher when this function started the value is unchanged and -1 is returned.
 * This function will refuse to operate on an integer smaller then zero and always return -1 when one is passed
 * @param unsPtr A pointer to the integer which's value you want to change
 * @param maxval The maximumval, this function will never increase the derefered unsPtr to beyond this value
 * @return The value of the derefed unsPtr at the point where this function was done operating or -1
 */
int incrIntegerTSMax(int* intPtr, int maxval);

/**
 * @brief Decrements an integer threadsafe.
 * This function guarantees that the value of unsPtr will not drop below zero (and subsequently wrap around) if only this function is used.
 * If given integer was already zero or less, then this function will return -1;
 * @param unsPtr A pointer to an integer which's value you want to change.
 * @return The value of the derefed unsPtr at the point where this function was done operating or -1
 */
int decrIntegerTSMax(int* unsPtr);
#endif //COREUTILS_H
