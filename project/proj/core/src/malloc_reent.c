//Malloc reentrant 
#include "malloc.h"
#include "reentrantMutex.h"

ReentrantMutex* mallocMutex = NULL;

void __malloc_lock (struct _reent *reent ){ 
    if (mallocMutex == NULL) return;
    lockReentrantMutexBlocking(mallocMutex);
} 

void __malloc_unlock (struct _reent *reent ){ 
    if (mallocMutex == NULL) return;
    releaseReentrantMutex(mallocMutex);
} 

