#include "reentrantMutex.h"
#include "stdlib.h"

ReentrantMutex* createReentrantMutex(void){
    ReentrantMutex* mutex = (ReentrantMutex*)malloc(sizeof(ReentrantMutex));
    if (mutex == NULL) return NULL;
    mutex->multiLockObject = __createMultiLockObject(4294967295);
    if (mutex->multiLockObject == NULL){
        free(mutex);
        return NULL;
    }   
    mutex->mutex = createBinaryMutex();
    if (mutex->mutex == NULL){
        free(mutex->multiLockObject);
    }
    mutex->ownerPid = 0;
    return mutex;
}

void deleteReentrantMutex(ReentrantMutex* mutex){
    __deleteMultiLockObject(mutex->multiLockObject);
    free(mutex);
}
