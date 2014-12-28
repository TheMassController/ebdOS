#ifndef KERNELQUEUE_H
#define KERNELQUEUE_h

#include "process.h"
#include "semaphore.h"
#include "mutex.h"

enum KQITEMTYPE
{
    newprocess,
    deleteprocess,
   addsleeper
};

struct KernelQueueItem{
    enum KQITEMTYPE itemtype;
    void* item;  
    struct KernelQueueItem* nextItem;
};

struct KernelQueue{
    Semaphore* existingItems;
    Semaphore* readyItems;
    Mutex* listProtectionMutex;
    struct KernelQueueItem* firstItem;
};

struct NewProcess{
    unsigned mPid;
    unsigned long stacklen;
    char* name;
    void (*procFunc)(void*);
    void* param;
    char priority;
};

struct DeleteProcess{
    struct Process* processToDelete;
};

struct AddSleeper{
    struct Process* proc;
    unsigned sleepTicks;
    unsigned overflows;
};

struct KernelQueueItem* __popItem(void);
void __addSleeper(struct Process* process, unsigned sleepTicks, unsigned overflows);
void createProcess(unsigned long stacklen, char* name, void (*procFunc)(void*), void* param, char priority);
void __deleteProcess(struct Process* processToDelete);
#endif //KERNELQUEUE_h
