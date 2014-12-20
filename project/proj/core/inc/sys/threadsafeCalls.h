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
SingleLockObject* __createSingleLockObject(void);
void __deleteSingleLockObject(SingleLockObject* object);

int __lockObjectNoblock(SingleLockObject* object);
void __lockObjectBlock(SingleLockObject* object);
int __lockObjectBlockTimeout(SingleLockObject* object, unsigned timeout);
void __releaseObject(SingleLockObject* object);
int __singleLockObjectIsLocked(SingleLockObject* object);

//MultiLockObject
MultiLockObject* __createMultiLockObject(unsigned maxval);
void __deleteMultiLockObject(MultiLockObject* object);
void __increaseMultiLockObjectBlock(MultiLockObject* object);
void __decreaseMultiLockObjectBlock(MultiLockObject* object);
int __increaseMultiLockObjectNoBlock(MultiLockObject* object);
int __decreaseMultiLockObjectNoBlock(MultiLockObject* object);
int __increaseMultiLockObjectBlockTimeout(MultiLockObject* object);
int __decreaseMultiLockObjectBlockTimeout(MultiLockObject* object);
unsigned __getMultiLockVal(MultiLockObject* object);
unsigned __getMultiLockMaxVal(MultiLockObject* object);
//TODO semaphore functions
#endif //THREADSAFECALLS_H
