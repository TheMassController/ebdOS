//Handles the threadsafe calls and the waiting state
#ifndef THREADSAFECALLS_H
#define THREADSAFECALLS_H

#include "process.h" 

struct SingleLockObject{
    unsigned lock;
    struct Process* processWaitingQueue;
};

struct MultiLockObject{
    unsigned lock;
    unsigned maxLockVal;
    struct Process* processWaitingQueueIncrease; //Processes waiting for the object being increased
    struct Process* processWaitingQueueDecrease; //Processes waiting for the object being decreased
};

typedef struct SingleLockObject SingleLockObject;
typedef struct MultiLockObject MultiLockObject;

//SingleLockObject
void __initSingleLockObject(SingleLockObject* object);
void __cleanupSingleLockObject(SingleLockObject* object);

int __lockObjectNoblock(SingleLockObject* object);
void __lockObjectBlock(SingleLockObject* object);
int __lockObjectBlockTimeout(SingleLockObject* object, unsigned msTimeout);
void __releaseObject(SingleLockObject* object);
int __singleLockObjectIsLocked(SingleLockObject* object);

//MultiLockObject
void __initMultiLockObject(MultiLockObject* object, int maxval);
void __cleanupMultiLockObject(MultiLockObject* object);

int __increaseMultiLockObjectBlock(MultiLockObject* object);
int __decreaseMultiLockObjectBlock(MultiLockObject* object);
int __increaseMultiLockObjectNoBlock(MultiLockObject* object);
int __decreaseMultiLockObjectNoBlock(MultiLockObject* object);
int __increaseMultiLockObjectBlockTimeout(MultiLockObject* object, unsigned msTimeout);
int __decreaseMultiLockObjectBlockTimeout(MultiLockObject* object, unsigned msTimeout);
int __getMultiLockVal(MultiLockObject* object);
int __getMultiLockMaxVal(MultiLockObject* object);
//TODO semaphore functions
#endif //THREADSAFECALLS_H
