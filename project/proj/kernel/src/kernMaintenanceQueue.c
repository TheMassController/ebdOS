#include "kernMaintenanceQueue.h"   // Contains the function defenitions, contains #include process.h
#include "coreUtils.h"              // Contains isInSVCInterrupt
// System headers
#include <stdlib.h>

static struct Process* procQueueStart;
static struct Process* procQueueEnd;

void kernQueue_push(struct Process* procPtr){
    if (procPtr != NULL && isInSVCInterrupt()){
        procPtr->nextProcess = NULL;
        if (procQueueStart == NULL){
            procQueueStart = procPtr;
            procQueueEnd = procPtr;
        } else {
            procQueueEnd->nextProcess = procPtr;
            procQueueEnd = procPtr;
        }
    }
}

struct Process* kernQueue_pop(void){
    if (isInSVCInterrupt()){
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
    return NULL;
}
