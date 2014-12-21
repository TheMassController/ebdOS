//Malloc reentrant 
#include "malloc.h"
#include "reentrantMutex.h"

ReentrantMutex* mallocMutex = NULL;

void __malloc_lock (struct _reent *reent ){ 
    lockReentrantMutexBlocking(mallocMutex);
} 

void __malloc_unlock (struct _reent *reent ){ 
    releaseReentrantMutex(mallocMutex);
} 

