//Queue source code
#include "queue.h" 
#include "stdlib.h"

Queue* createQueue(void){
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) return NULL;
    queue->mutex = createMutex();
    if (queue->mutex == NULL){
        free(queue);
        return NULL;
    }
    queue->firstItem = NULL;
    queue->lastItem = NULL;
    return queue;
}

void deleteQueue(Queue* queue){
    //First: pop everything from the queue
    //Then: delete mutex
    //And at the very end: delete the qeue itself
    //TODO implement
}

int pushToQueue(Queue* queue, void* item){
    QueueItem* queueItem = (QueueItem*)malloc(sizeof(QueueItem)); 
    queueItem->data = item;
    if (item == NULL) return 0;
    lockMutexBlocking(queue->mutex);   
    queueItem->nextItem = queue->firstItem;
    queue->firstItem->previousItem = queueItem;
    queue->firstItem = queueItem;
    releaseMutex(queue->mutex);
    return 1;
}
