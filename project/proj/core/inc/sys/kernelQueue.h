#ifndef KERNELQUEUE_H
#define KERNELQUEUE_h

/**
    RETCODES:
    0: sucess
    2: unknown error
**/

struct KernelQueueItem* __popItem(void);
int createProcess(unsigned long stacklen, char* name, void (*procFunc)(void*), void* param, char priority);
int __deleteProcess(struct Process* processToDelete);
#endif //KERNELQUEUE_h
