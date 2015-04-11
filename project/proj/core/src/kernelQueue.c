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

//TODO this part is fundamentally broken. The syscall layer should be redesigned and re-implemented

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
    struct Process* callee;
    int retCode;
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
    return __createNewProcess(newProc->mPid, newProc->stacklen, newProc->name, newProc->procFunc, newProc->param, newProc->priority, 0);
}

int processDeleteProcess(struct DeleteProcess* delProc){
    (void)delProc;
    //TODO implement
    return 0;
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
    switch(item->itemtype){
        case newprocess:
            item->retCode = processNewProcess((struct NewProcess*)item->item);
            break;
        case deleteprocess:
            item->retCode = processDeleteProcess((struct DeleteProcess*) item->item);
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
    //Take the objects needed to touch the new process queue
    takeSemaphore(&newProcessPoolSem, MAXWAITTIME);
    takeMutex(&newProcessPoolMut, MAXWAITTIME);
    //Find the correct empty spot to write your data to
    struct NewProcess* newProc = NULL;
    for (int i = 0; i < DEFKQPOOLSIZE; ++i){
        if (newProcessPool[i].procFunc == NULL){
            newProc = &newProcessPool[i];
            break;
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
        memcpy(newProc->name,name, 20);
        newProc->name[20] = 0;
    } else {
        strcpy(newProc->name, name);
    }
    newProc->mPid = currentProcess->pid;
    newProc->param = param;
    newProc->priority = priority;
    int retCode = createAndProcessKernelCall(newProc, newprocess);
    releaseSemaphore(&newProcessPoolSem, MAXWAITTIME);
    return retCode;
}

void exitProcess(int exitCode){
    takeSemaphore(&deleteProcessPoolSem, MAXWAITTIME);
    takeMutex(&deleteProcessPoolMut, MAXWAITTIME);
    struct DeleteProcess* delProc = NULL;
    for (int i = 0; i < DEFKQPOOLSIZE; ++i){
        if (deleteProcessPool[i].processToDelete == NULL){
            delProc = &deleteProcessPool[i];
            break; 
        }
    }
#ifdef DEBUG 
    if (delProc == NULL) UARTprintf("WARNING: semaphore of deleteProcessPool is out of sync\r\n");
#endif
    if (delProc == NULL) {
        //TODO kernelpanic or something: the process cannot run anymore and the KQ is broken.
        //This might be inrecovereble
        //Well maybe just segfault
        return;
    }
    delProc->processToDelete = currentProcess;
    delProc->callee = currentProcess;
    releaseMutex(&deleteProcessPoolMut);
    delProc->retCode = exitCode;
    createAndProcessKernelCall(delProc, deleteprocess);
#ifdef DEBUG
   UARTprintf("We are at a point in exitProcess where we do not want to be\r\n"); 
#endif //DEBUG
}

void processReturn(void){
    exitProcess(0);
}

//void deleteCurrentProcess(){
//    takeSemaphore(&deleteProcessPoolSem, MAXWAITTIME);
//    takeMutex(&deleteProcessPoolMut, MAXWAITTIME);
//    for (int i = 0; i < DEFKQPOOLSIZE; ++i
//}
