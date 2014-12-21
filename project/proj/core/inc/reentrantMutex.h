#ifndef REENTRANTMUTEX_H
#define REENTRANTMUTEX_H

#include "threadsafeCalls.h"
#include "binaryMutex.h"

struct ReentrantMutex{
    MultiLockObject* multiLockObject;
    BinaryMutex* mutex;
    unsigned ownerPid;
};

typedef struct ReentrantMutex ReentrantMutex;

void lockReentrantMutexBlocking(ReentrantMutex* mutex);
int lockReentrantMutexNoBlock(ReentrantMutex* mutex);
int lockMutexBlockWait(ReentrantMutex* mutex, unsigned msWaitTime);
void releaseReentrantMutex(ReentrantMutex* mutex);

ReentrantMutex* createMutex(ReentrantMutex* mutex);
void deleteReentrantMutex(ReentrantMutex* mutex);
#endif //REENTRANTMUTEX_H
