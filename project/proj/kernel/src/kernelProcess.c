//The functions of the actual kernel: this is the kernel process
#include <stdlib.h>
#include <errno.h>

#include "processModule.h"
#include "uartstdio.h"
#include "core/inc/sysCalls.h"
#include "core/inc/context.h"
#include "supervisorCall.h"
#include "kernMaintenanceQueue.h"
#include "kernEventNotifier.h"
#include "sysSleep.h"
#include "sysFutex.h"
#include "sysManagedLock.h"
#include "waitModule.h"

static void createProcessHelper(struct ProcessContext* context, struct Process* kernMaintenanceProc){
    struct ProcessCreateParams* params = (struct ProcessCreateParams*)context->genericPtr;
    params->priority = kernMaintenanceProc->priority;
    params->isPrivileged = 0;
    struct Process* tProc = createNewProcess(params, kernMaintenanceProc);
    if (tProc == NULL){
        context->retVal = -1;
        context->context_errno = errno;
    } else {
        kernRetQueuePush(tProc);
        context->retVal = tProc->pid;
    }
}

struct DoublePtr{
    struct Futex* fut;
    struct SleepRequest* sleepReq;
};

static int futexWaitTimeoutHelper(struct DoublePtr* ptr, struct Process* kernMaintenanceProc){
    return sysFutexWaitTimeout(ptr->fut, kernMaintenanceProc, ptr->sleepReq);
}

void kernelMain(void){
    while(1){
        struct Process* kernMaintenanceProc = kernelBufferGetProcess();
        while(kernMaintenanceProc != NULL){
            struct ProcessContext* context = kernMaintenanceProc->context;
            struct Process* tProc = NULL;
            int retval;
            switch(context->comVal){
                case GETPID:
                    context->retVal = kernMaintenanceProc->pid;
                    kernRetQueuePush(kernMaintenanceProc);
                    break;
                case SPAWNCHILDPROCESS:
                    createProcessHelper(context, kernMaintenanceProc);
                    kernRetQueuePush(kernMaintenanceProc);
                    break;
                case PROCESSSLEEP:
                    addSleeper(kernMaintenanceProc, context->genericPtr);
                    break;
                case PROCESSEXIT:
                    terminateProcess(kernMaintenanceProc, context->passVal);
                    break;
                case FUTEXINIT:
                    context->retVal = sysInitFutex(context->genericPtr, kernMaintenanceProc);
                    kernRetQueuePush(kernMaintenanceProc);
                    break;
                case FUTEXPOST:
                    context->retVal = sysFutexPost(context->genericPtr, &tProc);
                    if (tProc != NULL) kernRetQueuePush(tProc);
                    kernRetQueuePush(kernMaintenanceProc);
                    break;
                case FUTEXWAIT:
                    retval = sysFutexWait(context->genericPtr, kernMaintenanceProc);
                    if (retval != 0){
                        if (retval != EAGAIN) {
                            context->retVal = retval;
                        } else {
                            context->retVal = 0;
                        }
                        kernRetQueuePush(kernMaintenanceProc);
                    }
                    break;
                case FUTEXWAITTIMEOUT:
                    retval = futexWaitTimeoutHelper(context->genericPtr, kernMaintenanceProc);
                    if (retval != 0){
                        if (retval != EAGAIN) {
                            context->retVal = retval;
                        } else {
                            context->retVal = 0;
                        }
                        kernRetQueuePush(kernMaintenanceProc);
                    }
                    break;
                case FUTEXDESTROY:
                    context->retVal = sysDestroyFutex(context->genericPtr);
                    kernRetQueuePush(kernMaintenanceProc);
                    break;
                default:
                    UARTprintf("Unknown code for kernel service: %d, process name: %s, pid: %d\n", context->comVal, kernMaintenanceProc->name, kernMaintenanceProc->pid);
                    break;
            }
            kernMaintenanceProc = kernelBufferGetProcess();
        }
        enum KernBufferMessageCodes code = kernelBufferGetCode();
        while(code != noMessageAvailable){
            struct Process* it;
            switch(code) {
                case sysTimerOverflow:
                    it = sleepHandleSysTimerOverflow();
                    kernRetQueueAddList(it);
                    waitTimerSysTimerOverflow();
                    break;
                case sleepTimerExpired:
                    it = refreshSleeplist();
                    kernRetQueueAddList(it);
                    break;
                case waitModuleTimerExpired:
                    waitTimerTimeout();
                    break;
                default:
                    UARTprintf("Unknown event code: %d\n", code);
                    break;
            }
            code = kernelBufferGetCode();
        }
        CALLSUPERVISOR(SVC_serviced);
    }
}
