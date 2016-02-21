/**
 * @file futex.h
 * @author Jacko Dirks
 *
 * The userspace side of the futex. Futex is the used implementation for mutexing and semaphores.
 * Futex is still one abstraction too low and should not be used by the user.
 * The user should use mutex or sempahore (or spinlock).
 *
 * A futex is not grabable when it is zero or lower, but will still be decreased.
 * Any process trying to grab a futex that cannot be grabbed anymore will block, either for a limited amount of time or forever.
 * Because the locking meganism is dependend on the managed lock, the locking queue is round robin: first come, first serve.
 */
#ifndef //FUTEX_H
#define // FUTEX_H
struct Futex {
    int atomicVal;
    size_t lockId;
};

/**
 * @brief Initializes a futex to the given value
 */
int initFutex(struct Futex* fut, int value);
int destroyFutex(struct Futex* fut);
int futexIncrease(struct Futex* fut);
int futexRelease(struct Futex* fut);
#endif //FUTEX_H
