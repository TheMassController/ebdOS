#include "process.h"
#include "stdlib.h"
#include "sysCalls.h"
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

static struct Semaphore readyKQItemsSem;
static struct Semaphore existingKQItemsSem;
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
    initSemaphore(&readyKQItemsSem, MAXTOTALPROCESSES);
    initSemaphore(&existingKQItemsSem, MAXTOTALPROCESSES);
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

int processNewProcess(struct NewProcess* newProc){
    return __createNewProcess(newProc->mPid, newProc->stacklen, newProc->name, newProc->procFunc, newProc->param, newProc->priority);
}

void popAndProcessItem(void){
    if (currentProcess->pid != 1){
        return;
    }
    decreaseSemaphoreBlocking(&readyKQItemsSem);
    lockMutexBlocking(&kQListProtectionMutex);
    struct KernelQueueItem* item = kQIListHead;
    kQIListHead = kQIListHead->nextItem;
    releaseMutex(&(kQListProtectionMutex));
    releaseSemaphore(&existingKQItemsSem, 0);
    switch(item->itemtype){
        case newprocess:
            item->retCode = processNewProcess((struct NewProcess*)item->item);
            break;
        default:
            break;
    }
    releaseBinarySemaphore(&(item->responseWaiter));
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
        return 2;
    }
    increaseSemaphoreBlocking(&(readyKQItemsSem));
    takeBinarySemaphore(&(item->responseWaiter), MAXWAITTIME);
    return item->retCode;
}

int createAndProcessKernelCall(void* item, enum KQITEMTYPE itemtype){
    takeSemaphore(&(existingKQItemsSem), MAXWAITTIME);
    takeMutex(&kQListProtectionMutex, MAXWAITTIME);
    struct KernelQueueItem* kQItem = NULL;
    for (int i = 0; i < MAXTOTALPROCESSES; ++i){
        if (kernelQueueItemPool[i].item == NULL){
            kQItem = &kernelQueueItemPool[i];
        }
    }
#ifdef DEBUG
    if (kQItem == NULL)UARTprintf("existingKQItemsSem and kernelQueueItemPool are out of sync!\r\n");
#endif
    if(kQItem == NULL) {
        releaseMutex(&kQListProtectionMutex);
        return 2;
    }
    kQItem->item = item;
    releaseMutex(&kQListProtectionMutex);

    kQItem->itemtype = itemtype;
    int retCode = pushItem(kQItem);
    releaseBinarySemaphore(&(kQItem->responseWaiter));
    kQItem->nextItem = NULL;
    kQItem->item = NULL;

    releaseSemaphore(&existingKQItemsSem, MAXWAITTIME);
    return retCode;
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
    newProc->procFunc = procFunc;
    releaseMutex(&newProcessPoolMut);
    newProc->stacklen = stacklen;
    if (strlen(name) > 20){
        memcpy(name, newProc->name, 20);
        newProc->name[20] = 0;
    } else {
        strcpy(name, newProc->name);
    }
    newProc->mPid = currentProcess->pid;
    newProc->param = param;
    newProc->priority = priority;
    int retCode = createAndProcessKernelCall(newProc, newprocess);
    releaseSemaphore(&newProcessPoolSem, MAXWAITTIME);
    return retCode;
}

//void deleteCurrentProcess(){
//    takeSemaphore(&deleteProcessPoolSem, MAXWAITTIME);
//    takeMutex(&deleteProcessPoolMut, MAXWAITTIME);
//    for (int i = 0; i < DEFKQPOOLSIZE; ++i
//}
