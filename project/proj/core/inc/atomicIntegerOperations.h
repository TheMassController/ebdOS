#ifndef ATOMICINTEGEROPERATIONS_H
#define ATOMICINTEGEROPERATIONS_H
/**
 * @file atomicIntegerOperations.h
 * @author Jacko Dirks
 * @brief Provides threadsafe integer operations. Useful in, for example, spinlocks.
 */

/**
 * @brief Increments an integer threadsafe, using a max value.
 * This function guarantees that the value of integer will not pass maxval if only this function is used to increase the value.
 * If the given integer was already at maxval or higher when this function started the value is unchanged and -1 is returned.
 * This function will refuse to operate on an integer smaller then zero.
 * @param intPtr A pointer to the integer which's value you want to change
 * @param maxval The maximumval, this function will never increase the derefered intPtr to beyond this value
 * @return The value of the derefed intPtr at the point where this function was done operating or -1
 */
int atomicIncreaseIntWithMax(int* intPtr, const int maxval);
/**
 * @brief Decrements an integer threadsafe, with 0 as lower limit
 * This function guarantees that the value of intPtr will not drop below zero (and subsequently wrap around) if only this function is used.
 * If given integer was already zero or less, then this function will return -1.
 * This function guarantees that the integer is usable afterwards with the incrIntegerTSMax function
 * @param intPtr A pointer to an integer which's value you want to change.
 * @return The value of the derefed intPtr at the point where this function was done operating or -1
 */
int atomicDecreaseIntWithMax(int* intPtr);

/**
 * @brief Increments an integer threadsafe.
 * Does not provide any protection against overflows. The returnvalue is the value as written by this function
 * @param intPtr A pointer to the integer which's value you want to increment.
 * @return the written value.
 */
int atomicIncreaseInt(int* intPtr);
/**
 * @brief Decrements an integer threadsafe.
 * Does not provide any protection against overflows. The returnvalue is the value as written by this function
 * @param intPtr A pointer to the integer which's value you want to decrement.
 * @return the written value.
 */
int atomicDecreaseInt(int* intPtr);

/**
 * @brief Sets an integer threadsafe, but only if the current value matches the expected one.
 * @param intPtr A pointer to the integer which's value you want to set.
 * @param newval The value that you want to write to *intPtr
 * @param expCurVal The newval is only written if *intPtr == expCurVal
 * @return 0 if the value was not written, 1 if it was.
 */
int atomicSetInt(int* intPtr, const int newval, const int expCurVal);
#endif //ATOMICINTEGEROPERATIONS_H
