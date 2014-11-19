//Malloc reentrant 
#include "malloc.h"
#include "mutex.h"

Mutex* mallocMutex = NULL;

void __malloc_lock (struct _reent *reent ){ 
    lockMutexBlocking(mallocMutex);
} 

void __malloc_unlock (struct _reent *reent ){ 
    releaseMutex(mallocMutex);
} 

