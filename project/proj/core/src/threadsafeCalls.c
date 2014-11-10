#include "threadsafeCalls.h" 
#include "process.h"
#include "supervisorCall.h"
#include "sleep.h"

extern struct Process* currentProcess;

//Returns 1 if successful
unsigned __lockMutex(void* addr);
void __unlockMutex(void* addr);

int __lockObjectNoblock(void* object){
    return __lockMutex(object);
}

void __lockObjectBlock(void* object){
   while(!__lockMutex(object)){
        currentProcess->blockAddress = object;
        currentProcess->state |= STATE_WAIT;
        CALLSUPERVISOR(SVC_reschedule);
    } 
     //TODO maybe implement a way to increase the priority of the process that holds this mutex, if the prio of the current process is higher
}

int __lockObjectBlockTimeout(void* object, unsigned timeout){
     if (!__lockObjectNoblock(object)){
        currentProcess->blockAddress = object;
        currentProcess->state |= STATE_WAIT;
        sleepMS(timeout);
    }
    return __lockObjectNoblock(object);
}

void __releaseObject(void* object){
    __unlockMutex(object);
    //TODO notify kernel
}
