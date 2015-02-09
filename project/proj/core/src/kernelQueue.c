#include "process.h"
#include "stdlib.h"
#include "kernelQueue.h"
#include "string.h"
#include "supervisorCall.h"
#include "process.h"
#include "semaphore.h"
#include "mutex.h"
#include "binarySemaphore.h"

#ifdef DEBUG
#include "uartstdio.h"
#endif //DEBUG

extern struct Process* currentProcess;

#define DEFKQPOOLSIZE 5

enum KQITEMTYPE
{
    newprocess,
    deleteprocess,
};

struct KernelQueueItem{
    enum KQITEMTYPE itemtype;
    void* item;
    struct KernelQueueItem* nextItem;
    int retCode;
    struct BinarySemaphore responseWaiter;
};

static struct Semaphore readyKQItems;
static struct Semaphore existingKQItems;
static struct Mutex kQListProtectionMutex;
static struct KernelQueueItem kernelQueueItemPool[MAXTOTALPROCESSES];
static struct KernelQueueItem* kQIListHead = NULL;

struct NewProcess{
    unsigned mPid;
    unsigned long stacklen;
    char name[21];
    void (*procFunc)();
    void* param;
    char priority;
};

struct DeleteProcess{
    struct Process* processToDelete;
};

static struct DeleteProcess deleteProcessPool[DEFKQPOOLSIZE];
static struct Semaphore deleteProcessPoolSem;
static struct Mutex deleteProcessPoolMut;
static struct NewProcess newProcessPool[DEFKQPOOLSIZE];
static struct Semaphore newProcessPoolSem;
static struct Mutex newProcessPoolMut;

void initKernelQueue(void){
    initSemaphore(&readyKQItems, MAXTOTALPROCESSES);
    initSemaphore(&existingKQItems, MAXTOTALPROCESSES);
    initSemaphore(&newProcessPoolSem, DEFKQPOOLSIZE);
    initSemaphore(&deleteProcessPoolSem, DEFKQPOOLSIZE);
    initMutex(&(kQListProtectionMutex));
    initMutex(&newProcessPoolMut);
    initMutex(&deleteProcessPoolMut);
    for (int i = 0; i < MAXTOTALPROCESSES; ++i){
        kernelQueueItemPool[i].item = NULL;
        kernelQueueItemPool[i].nextItem = NULL;
        initBinarySemaphore(&(kernelQueueItemPool[i].responseWaiter));
    }
    for (int i = 0; i < DEFKQPOOLSIZE; ++i){
        newProcessPool[i].procFunc = NULL;
        deleteProcessPool[i].processToDelete = NULL;
    }
}

void popAndProcessItem(void){
    if (currentProcess->pid != 1){
        return;
    }
    lockMutexBlocking(&kQListProtectionMutex);
    struct KernelQueueItem* item = kQIListHead;
    kQListHead = kQListHead->nextItem;
    releaseMutex(&(kQListProtectionMutex));
    releaseSemaphore(&existingKQItems, 0);
    switch(item->itemtype){
        case newprocess:
            processNewProcess((struct NewProcess*)item->item);
            break;
        default:
            break;
    }
    item->item = NULL;
}

int pushItem(struct KernelQueueItem* item){
    lockMutexBlocking(&kQListProtectionMutex);
    struct KernelQueueItem* currentItem = kQIListHead;
    struct KernelQueueItem* prevItem = NULL;
    while(currentItem != NULL){
        prevItem = currentItem;
        currentItem = currentItem->nextItem;
    }
    if (prevItem == NULL){
        kQIListHead = item;
    } else {
        prevItem->nextItem = item;
        item->nextItem = currentItem;
    }
    releaseMutex(&(kQListProtectionMutex));
    if (takeBinarySemaphore(&(item->responseWaiter), 0) == -1){
        releaseSemaphore(&existingKQItems, MAXWAITTIME);
        return 2;
    }
    increaseSemaphoreBlocking(&(readyKQItems));
    takeBinarySemaphore(&(item->responseWaiter), MAXWAITTIME);
    return item->retCode;
}

int createAndProcessKernelCall(void* item, enum KQITEMTYPE itemtype){
    takeSemaphore(&(existingKQItems), MAXWAITTIME);
    //TODO: fix
    takeMutex(&kQListProtectionMutex, MAXWAITTIME);
    for (int i = 0; i < MAXTOTALPROCESSES; ++i){
        if (kernelQueueItemPool[i].item == NULL){
            kernelQueueItemPool[i].item = item;
            kernelQueueItemPool[i].itemtype = itemtype;
            int retCode = pushItem(&kernelQueueItemPool[i]);
            releaseBinarySemaphore(&(kernelQueueItemPool[i].responseWaiter));
            kernelQueueItemPool[i].item = NULL;
            kernelQueueItemPool[i].nextItem = NULL;
            return retCode;
        }
    }
#ifdef DEBUG
    UARTprintf("existingKQItems and kernelQueueItemPool are out of sync!\r\n");
#endif
    return 2;
}

int createProcess(unsigned long stacklen, char* name, void (*procFunc)(), void* param, char priority){
    takeSemaphore(&newProcessPoolSem, MAXWAITTIME);
    takeMutex(&newProcessPoolMut, MAXWAITTIME);
    struct NewProcess* newProc = NULL;
    for (int i = 0; i < DEFKQPOOLSIZE; ++i){
        if (newProcessPool[i].procFunc == NULL){
            newProc = &newProcessPool[i];
        }
    }
#ifdef DEBUG 
    if (newProc == NULL) UARTprintf("WARNING: semaphore of newProcessPool is out of sync\r\n");
#endif
    if (newProc == NULL){
        releaseMutex(&newProcessPoolMut);
        //Do not release the semaphore: there were no free items
        return 2;
    }
    newProc->stacklen = stacklen;
    if (strlen(name) > 20){
        memcpy(name, newProc->name, 20);
        newProc->name[20] = 0;
    } else {
        strcpy(name, newProc->name);
    }
    newProc->mPid = currentProcess->pid;
    newProc->procFunc = procFunc;
    newProc->param = param;
    newProc->priority = priority;
    releaseMutex(&newProcessPoolMut);
    int retCode = createAndProcessKernelCall(newProc, newprocess);
    releaseSemaphore(&newProcessPoolSem, MAXWAITTIME);
    return retCode;
}

//void deleteCurrentProcess(){
//    takeSemaphore(&deleteProcessPoolSem, MAXWAITTIME);
//    takeMutex(&deleteProcessPoolMut, MAXWAITTIME);
//    for (int i = 0; i < DEFKQPOOLSIZE; ++i
//}
