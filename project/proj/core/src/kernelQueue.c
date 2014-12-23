#include "process.h"
#include "stdlib.h"
#include "kernelQueue.h"

struct KernelQueue* kernelQueue = NULL;

void pushItem(struct KernelQueueItem* item){
    lockMutexBlocking(kernelQueue->listProtectionMutex);
    struct KernelQueueItem* searchItem = kernelQueue->firstItem;
    if (searchItem != NULL) for(; searchItem->nextItem != NULL; searchItem = searchItem->nextItem);
    searchItem->nextItem = item;
    releaseMutex(kernelQueue->listProtectionMutex);
    increaseSemaphoreBlocking(kernelQueue->readyItems);
}

