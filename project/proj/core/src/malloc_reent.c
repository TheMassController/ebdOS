//Malloc reentrant 
#include "malloc.h"
#include "reentrantMutex.h"

struct ReentrantMutex mallocMutex;
volatile int initialized = 0;

#define UNUSED(x) (void)(x) //To suppress compiler warning

void __malloc_lock (struct _reent *reent ){ 
    if (!initialized) return; 
    UNUSED(reent);
    lockReentrantMutexBlocking(&(mallocMutex));
} 

void __malloc_unlock (struct _reent *reent ){ 
    if (!initialized) return;
    UNUSED(reent);
    releaseReentrantMutex(&(mallocMutex));
} 

