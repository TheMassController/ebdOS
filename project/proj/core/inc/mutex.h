#ifndef MUTEX_H
#define MUTEX_H
//Mutex functions
//A mutex is locked to its owner: only the owner can release it
#include "threadsafeCalls.h" 

struct Mutex{
    SingleLockObject* singleLockObject;
    unsigned ownerPid;
    struct Mutex* nextMutex;
};

typedef struct Mutex Mutex;

#define lockMutex lockMutexBlocking
void lockMutexBlocking(Mutex* mutex);

//Returns 1 if successfull, 0 if not
int lockMutexBlockWait(Mutex* mutex, unsigned msWaitTime);

//Returns 1 if successfull, 0 if not
int lockMutexNoBlock(Mutex* mutex);

void releaseMutex(Mutex* mutex);

Mutex* createMutex(void);

void deleteMutex(Mutex* mutex);

//Binary mutex functions

#endif //MUTEX_H
