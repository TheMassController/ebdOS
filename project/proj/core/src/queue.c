//Queue source code

//Just reference, this file is marked for deletion
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

//void deleteQueue(Queue* queue){
    //First: pop everything from the queue
    //Then: delete mutex
    //And at the very end: delete the qeue itself
    //TODO implement
//}

//ONLY CALL THIS FUNCTION WHEN THE MUTEX IS LOCKED!!!
void __addToQeue(Queue* queue, QueueItem* item){
    if (queue->firstItem == NULL){
        queue->firstItem = item;
        queue->lastItem = item;
        item->previousItem = NULL;
    }else{
        queue->firstItem->previousItem = item;
        queue->firstItem = item;
    }
}

//ONLY CALL THIS FUNCTION WHEN THE MUTEX IS LOCKED!!!
QueueItem* __popFromQueue(Queue* queue){
    if (queue->lastItem == NULL) return NULL;
    QueueItem* item = queue->lastItem;    
    if (queue->firstItem == queue->lastItem){
        queue->firstItem = NULL;
        queue->lastItem = NULL;
    } else {
        queue->lastItem = queue->lastItem->previousItem;
    }
    return item;
}

int pushToQueue(Queue* queue, void* item){
    QueueItem* queueItem = (QueueItem*)malloc(sizeof(QueueItem)); 
    queueItem->data = item;
    if (item == NULL) return 0;
    lockMutexBlocking(queue->mutex);
    __addToQeue(queue, queueItem);
    releaseMutex(queue->mutex);
    return 1;
}

void* popFromQueue(Queue* queue){
    lockMutexBlocking(queue->mutex);
    QueueItem* item = __popFromQueue(queue); 
    releaseMutex(queue->mutex);
    void* object = item->data;
    free(item);
    return object; 
}
