#ifndef QUEUE_H
#define QUEUE_H

#include "mutex.h"

//The Queue. A queue is of undefined size and can only be written to or from when holding the mutex
//It is a double linked list and it operates on void*. 

struct QueueItem{
    void* data;
    struct QueueItem* nextItem;
    struct QueueItem* previousItem;
};

typedef struct QueueItem QueueItem;

struct Queue{
    QueueItem* firstItem;
    QueueItem* lastItem;
    unsigned size;
    Mutex* mutex;
};

typedef struct Queue Queue;

Queue* createQueue(void);
void deleteQueue(Queue* queue);

int pushToQueue(Queue* queue, void* item);
int pushToQueueNoblock(Queue* queue, void* item);
int pushToQueueBlockTimeout(Queue* queue, void* item, unsigned timeout);
void* popFromQueue(Queue* queue);
int getQueueLen(Queue* queue);


#endif //QUEUE_H
