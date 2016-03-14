#include "reentrantMutex.h"
#include "stdlib.h"

void initReentrantMutex(struct ReentrantMutex* mutex){
    initMutex(&(mutex->mutex));
    mutex->value = 0;
}

void cleanupReentrantMutex(struct ReentrantMutex* mutex){
    destroyMutex(&mutex->mutex);
}

void lockReentrantMutexBlocking(struct ReentrantMutex* mutex){
    lockMutex(&mutex->mutex);
    mutex->value++;
}

int lockReentrantMutexNoBlock(struct ReentrantMutex* mutex){
    if (!tryLockMutex(&mutex->mutex)){
        return 0;
    }
    mutex->value++;
    return 1;
}
//FIXME
void releaseReentrantMutex(struct ReentrantMutex* mutex){
    if(mutex->value > 0) mutex->value--;
    if (mutex->value == 0){
        unlockMutex(&mutex->mutex);
    }
}


