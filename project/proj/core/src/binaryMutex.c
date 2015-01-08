//The actual mutex functions
#include "binaryMutex.h"
#include "stdlib.h"
#include "process.h"
#include "threadsafeCalls.h" 

BinaryMutex* firstBinaryMutex = NULL;
extern struct Process* currentProcess;

struct BinaryMutex* createBinaryMutex(void){
    struct BinaryMutex* mutex = malloc(sizeof(BinaryMutex));
    if (mutex == NULL) return NULL;
    mutex->lock = 0;
    if (firstBinaryMutex == NULL){
        firstBinaryMutex = mutex;
    } else {
        BinaryMutex* mut;
        for(mut = firstBinaryMutex; mut->nextBinaryMutex == NULL; mut = mut->nextBinaryMutex);
        mut->nextBinaryMutex = mutex;
    }
    return mutex;
}

//void deleteBinaryMutex(BinaryMutex* mutex){
//    //TODO call kernel to delete this mutex. If a resource was still waiting for it, kernel panic or some shit.
//}

void lockBinaryMutex(struct BinaryMutex* mutex){
    //TODO prevent locking when inside an interrupt    
    __lockObjectBlock((void*)mutex);
}

int lockBinaryMutexNoBlock(struct BinaryMutex* mutex){
    //TODO prevent locking when inside an interrupt 
    return __lockObjectNoblock((void*)mutex);
}

int lockBinaryMutexBlockWait(struct BinaryMutex* mutex, unsigned msWaitTime){
    //TODO prevent locking when inside an interrupt 
    return __lockObjectBlockTimeout((void*)mutex, msWaitTime);
}

void releaseBinaryMutex(struct BinaryMutex* mutex){
    __releaseObject((void*)mutex); 
}

