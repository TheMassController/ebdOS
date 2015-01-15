#ifndef MUTEX_H
#define MUTEX_H
//Mutex functions
//A mutex is locked to its owner: only the owner can release it
#include "threadsafeCalls.h" 

struct Mutex{
    SingleLockObject singleLockObject;
    unsigned ownerPid;
};

void lockMutexBlocking(struct Mutex* mutex);

//Returns 1 if successfull, 0 if not
int lockMutexBlockWait(struct Mutex* mutex, unsigned msWaitTime);

//Returns 1 if successfull, 0 if not
int lockMutexNoBlock(struct Mutex* mutex);

void releaseMutex(struct Mutex* mutex);

void initMutex(struct Mutex* mutex);

void cleanupMutex(struct Mutex* mutex);

//Binary mutex functions

#endif //MUTEX_H
