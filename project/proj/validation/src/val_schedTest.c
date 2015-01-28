#include "validation.h"
#include "process.h" 
#include "sleep.h"
#include "stdlib.h" 
#include "uartstdio.h" 
#include "string.h" 
#include "semaphore.h"
#include "mutex.h"
#include "binaryMutex.h"

extern struct Process* currentProcess;

struct SleepTimeStruct{
    unsigned runTimeMS;
    char* name;
};

struct LockStruct{
    unsigned sleepMS;
    struct Semaphore semaphore;
    struct Mutex mutex;
};

void sleepTestProcess(void* sleepTimeStruct){
    struct SleepTimeStruct* intel = (struct SleepTimeStruct*)sleepTimeStruct;
    unsigned sleepTime = 0;
    unsigned wakeTime = 0;
    while(1){
        UARTprintf("Process %s, which runs every %d ms, has just ran. Time since last run: %u\r\n",intel->name, intel->runTimeMS, sleepTime - wakeTime);
        sleepTime = getCurrentSleepTimerValue();
        sleepMS(intel->runTimeMS);
        wakeTime = getCurrentSleepTimerValue();
    }
    free(intel->name);
    free(sleepTimeStruct);
}

void lockTestProcess(void* lockStruct){
    while(1){
        struct LockStruct* intel = lockStruct;
        increaseSemaphoreBlocking(&(intel->semaphore));
        UARTprintf("%s increased the semaphore! SemVal: %d\r\n", currentProcess->name, getSemaphoreCurrentVal(&(intel->semaphore)));
        lockMutexBlocking(&(intel->mutex)); 
        UARTprintf("%s got the mutex!\r\n", currentProcess->name);
        sleepMS(intel->sleepMS); 
        releaseMutex(&(intel->mutex));
        UARTprintf("%s released the mutex!\r\n", currentProcess->name);
        decreaseSemaphoreBlocking(&(intel->semaphore));
        UARTprintf("%s decreased the semaphore! SemVal: %d\r\n", currentProcess->name, getSemaphoreCurrentVal(&(intel->semaphore))); 
        sleepMS(intel->sleepMS); 
    }
}

void testLocking(void){
    struct LockStruct* lockStruct = malloc(sizeof(struct LockStruct));
    initSemaphore(&(lockStruct->semaphore),2);
    initMutex(&(lockStruct->mutex));
    lockStruct->sleepMS = 500;     
    __createNewProcess(0, 256, "lockProcHigh", &lockTestProcess, lockStruct, 3);
    __createNewProcess(0, 256, "lockProcMed", &lockTestProcess, lockStruct, 2);
    __createNewProcess(0, 256, "lockProcLow", &lockTestProcess, lockStruct, 1);
}

void testSleep(void){
    //Spawn three processes: 1 sec, 10 sec, 30 sec
    struct SleepTimeStruct* structs[3];
    //The first one
    structs[0] = (struct SleepTimeStruct*)malloc(sizeof(struct SleepTimeStruct));
    structs[0]->name = (char*)malloc(strlen("timeoutProc1s")+1);
    strcpy(structs[0]->name,"timeoutProc1s");
    structs[0]->runTimeMS = 1000;
    if (__createNewProcess(0, 256, "timeoutProc1s", &sleepTestProcess, structs[0], 2) == 2){
        UARTprintf("Could not create process timeoutProc1s\r\n");         
    }
    structs[1] = (struct SleepTimeStruct*)malloc(sizeof(struct SleepTimeStruct));
    structs[1]->name = (char*)malloc(strlen("timeoutProc10s")+1);
    strcpy(structs[1]->name,"timeoutProc10s");
    structs[1]->runTimeMS = 10000;
    if (__createNewProcess(0, 256, "timeoutProc10s", &sleepTestProcess, structs[1], 1) == 2){
        UARTprintf("Could not create process timeoutProc10s\r\n");
    }
    structs[2] = (struct SleepTimeStruct*)malloc(sizeof(struct SleepTimeStruct));
    structs[2]->name = (char*)malloc(strlen("timeoutProc30s")+1);
    strcpy(structs[2]->name,"timeoutProc30s");
    structs[2]->runTimeMS = 30000;
    if(__createNewProcess(0, 256, "timeoutProc30s", &sleepTestProcess, structs[2], 2) == 2){
        UARTprintf("Could not create process timeoutProc30s\r\n");
    }
}

void BinMutFunc(void* binMut){
    struct BinaryMutex* binaryMutex = binMut;
    while(1){
        int i = lockBinaryMutexBlockWait(binaryMutex, 2000);
        if (!i){
            UARTprintf("Noes! :(\r\n");
        } else {
            UARTprintf("Yay! :)\r\n");
        }
    }
}

void testSleepAndMutex(void){
    struct BinaryMutex* binaryMutex = malloc(sizeof(struct BinaryMutex));
    initBinaryMutex(binaryMutex);
    if (binaryMutex == NULL){
        UARTprintf("FAILURE\r\n");
        return;
    }
    if(__createNewProcess(0, 1024, "BinaryMutexTestProc", &BinMutFunc, binaryMutex, 4) == 2){
        UARTprintf("FAILURE\r\n");
    }    
}



int testScheduler(void){
    //testSleep();
    //testLocking();
    testSleepAndMutex();
    UARTprintf("Test prepared\r\n");
    return 1;
}

