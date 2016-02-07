#include "kernMaintenanceQueue.h"   // Contains the function defenitions, contains #include process.h
#include "kernelPredefined.h"       // Contains the def of MAXTOTALPROCESSES
// System headers
#include <stdlib.h>

#define PROCESSBUFSIZE MAXTOTALPROCESSES+1

static struct Process* procQueueStart;
static struct Process* procQueueEnd;

static struct Process* processBuf[PROCESSBUFSIZE];
static int processReadPos;
static int processWritePos;

void kernRetQueuePush(struct Process* procPtr){
    if (procPtr == NULL) return;
    procPtr->nextProcess = NULL;
    if (procQueueStart == NULL){
        procQueueStart = procPtr;
        procQueueEnd = procPtr;
    } else {
        procQueueEnd->nextProcess = procPtr;
        procQueueEnd = procPtr;
    }
}

void kernRetQueueAddList(struct Process* procPtr){
    if (procPtr == NULL) return;
    if (procQueueStart == NULL){
        procQueueStart = procPtr;
        procQueueEnd = procPtr;
        while(procQueueEnd->nextProcess != NULL){
           procQueueEnd = procQueueEnd->nextProcess;
        }
    } else {
        procQueueEnd->nextProcess = procPtr;
        procQueueEnd = procPtr;
        while(procQueueEnd->nextProcess != NULL){
           procQueueEnd = procQueueEnd->nextProcess;
        }
    }
}

struct Process* kernRetQueuePop(void){
    struct Process* retProc = NULL;
    if (procQueueStart != NULL){
        retProc = procQueueStart;
        procQueueStart = procQueueStart->nextProcess;
        retProc->nextProcess = NULL;
        if (retProc == procQueueEnd){
            procQueueEnd = NULL;
        }
    }
    return retProc;
}

struct Process* kernRetQueueEmpty(void){
    struct Process* retProc = procQueueStart;
    procQueueStart = NULL;
    procQueueEnd = NULL;
    return retProc;
}

void passProcessToKernel(struct Process* const proc){
    proc->nextProcess = NULL;
    processWritePos = (processWritePos + 1) % (PROCESSBUFSIZE);
    processBuf[processWritePos] = proc;
}

struct Process* kernelBufferGetProcess(void){
   if (processReadPos == processWritePos) return NULL;
    processReadPos = (processReadPos + 1) % (PROCESSBUFSIZE);
    return processBuf[processReadPos];
}

int KernelProcessBufferIsEmpty(void){
    if (processReadPos == processWritePos) return 1;
    return 0;
}
