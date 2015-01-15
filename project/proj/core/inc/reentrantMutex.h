#ifndef REENTRANTMUTEX_H
#define REENTRANTMUTEX_H

#include "threadsafeCalls.h"
#include "mutex.h"

//Just a wrapper around the "real" mutex. If the process has or locks the mutex, the counter is increased. The mutex will be released if the counter is zero again.

struct ReentrantMutex{
    struct Mutex mutex;
    unsigned value;
};

void lockReentrantMutexBlocking(struct ReentrantMutex* mutex);
int lockReentrantMutexNoBlock(struct ReentrantMutex* mutex);
int lockReentrantMutexBlockWait(struct ReentrantMutex* mutex, unsigned msWaitTime);
void releaseReentrantMutex(struct ReentrantMutex* mutex);

struct ReentrantMutex* createReentrantMutex(void);
void deleteReentrantMutex(struct ReentrantMutex* mutex);
#endif //REENTRANTMUTEX_H
