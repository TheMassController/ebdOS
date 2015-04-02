//Handles the threadsafe calls and the waiting state
#ifndef LOCKOBJECT_H
#define LOCKOBJECT_H

#include "process.h" 
#define MAXWAITTIME 0xFFFFFFFF

struct LockObject{
    unsigned lock;
    unsigned maxLockVal;
    struct Process* processWaitingQueueIncrease; //Processes waiting for the object being increased
    struct Process* processWaitingQueueDecrease; //Processes waiting for the object being decreased
};

//LockObject
void __initLockObject(struct LockObject* object, int maxval);
void __cleanupLockObject(struct LockObject* object);

int __increaseLockObjectBlock(struct LockObject* object);
int __decreaseLockObjectBlock(struct LockObject* object);
int __increaseLockObjectNoBlock(struct LockObject* object);
int __decreaseLockObjectNoBlock(struct LockObject* object);
int __increaseLockObjectBlockTimeout(struct LockObject* object, unsigned msTimeout);
int __decreaseLockObjectBlockTimeout(struct LockObject* object, unsigned msTimeout);
int __getLockVal(struct LockObject* object);
int __getLockMaxVal(struct LockObject* object);
int __LockIsMaxVal(struct LockObject* object);
int __LockIsMinVal(struct LockObject* object);
#endif //LOCKOBJECT_H
