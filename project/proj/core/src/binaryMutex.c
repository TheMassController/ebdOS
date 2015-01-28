//The actual mutex functions
#include "binaryMutex.h"
#include "stdlib.h"
#include "process.h"
#include "threadsafeCalls.h" 
#include "asmUtils.h"

extern struct Process* currentProcess;

void initBinaryMutex(struct BinaryMutex* mutex){
    __initSingleLockObject(&(mutex->singleLockObject));
}

void uninitBinaryMutex(struct BinaryMutex* mutex){
    __cleanupSingleLockObject(&(mutex->singleLockObject));
}

void lockBinaryMutexBlocking(struct BinaryMutex* mutex){
    if (isInInterrupt()) return; 
    __lockObjectBlock(&(mutex->singleLockObject));
}

int lockBinaryMutexNoBlock(struct BinaryMutex* mutex){
    return __lockObjectNoblock(&(mutex->singleLockObject));
}

//Ret: 0 if failed
int lockBinaryMutexBlockWait(struct BinaryMutex* mutex, unsigned msWaitTime){
    if (isInInterrupt()) return 0; 
    return __lockObjectBlockTimeout(&(mutex->singleLockObject), msWaitTime);
}

void releaseBinaryMutex(struct BinaryMutex* mutex){
    __releaseObject(&(mutex->singleLockObject)); 
}

