//Malloc reentrant
#include "malloc.h"
#include "reentrantMutex.h"

struct ReentrantMutex mallocMutex;

#define UNUSED(x) (void)(x) //To suppress compiler warning

void __malloc_lock (struct _reent *reent ){
    UNUSED(reent);
    lockReentrantMutex(&(mallocMutex));
}

void __malloc_unlock (struct _reent *reent ){
    UNUSED(reent);
    unlockReentrantMutex(&(mallocMutex));
}

