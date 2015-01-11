//Malloc reentrant 
#include "malloc.h"
#include "reentrantMutex.h"

struct ReentrantMutex* mallocMutex = NULL;

#define UNUSED(x) (void)(x) //To suppress compiler warning

void __malloc_lock (struct _reent *reent ){ 
    UNUSED(reent);
    if (mallocMutex == NULL) return;
    lockReentrantMutexBlocking(mallocMutex);
} 

void __malloc_unlock (struct _reent *reent ){ 
    UNUSED(reent);
    if (mallocMutex == NULL) return;
    releaseReentrantMutex(mallocMutex);
} 

