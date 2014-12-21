#ifndef REENTRANTMUTEX_H
#define REENTRANTMUTEX_H

#include "threadsafeCalls.h"
#include "mutex.h"

//Just a wrapper around the "real" mutex. If the process has or locks the mutex, the counter is increased. The mutex will be released if the counter is zero again.

struct ReentrantMutex{
    Mutex* mutex;
    unsigned value;
};

typedef struct ReentrantMutex ReentrantMutex;

void lockReentrantMutexBlocking(ReentrantMutex* mutex);
int lockReentrantMutexNoBlock(ReentrantMutex* mutex);
int lockReentrantMutexBlockWait(ReentrantMutex* mutex, unsigned msWaitTime);
void releaseReentrantMutex(ReentrantMutex* mutex);

ReentrantMutex* createReentrantMutex(void);
void deleteReentrantMutex(ReentrantMutex* mutex);
#endif //REENTRANTMUTEX_H
