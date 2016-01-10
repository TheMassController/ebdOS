//The functions of the actual kernel: this is the kernel process
#include <stdlib.h>
#include <errno.h>

#include "processModule.h"
#include "uartstdio.h"
#include "sysCalls.h"
#include "context.h"
#include "supervisorCall.h"
#include "kernMaintenanceQueue.h"
#include "kernEventNotifier.h"

void kernelMain(void){
    while(1){
        struct Process* kernMaintenanceProc = kernelBufferGetProcess();
        while(kernMaintenanceProc != NULL){
            struct ProcessContext* context = kernMaintenanceProc->context;
            switch(context->comVal){
                case GETPID:
                    context->retVal = kernMaintenanceProc->pid;
                    kernRetQueuePush(kernMaintenanceProc);
                    break;
                case SPAWNCHILDPROCESS:
                    kernRetQueuePush(kernMaintenanceProc);
                    struct ProcessCreateParams* params = (struct ProcessCreateParams*)context->genericPtr;
                    params->priority = kernMaintenanceProc->priority;
                    params->isPrivileged = 0;
                    struct Process* proc = createNewProcess(params, kernMaintenanceProc);
                    if (proc == NULL){
                        context->retVal = -1;
                        context->context_errno = errno;
                    } else {
                        kernRetQueuePush(proc);
                        context->retVal = proc->pid;
                    }
                    break;
                case PROCESSSLEEP:
                    context->retVal = 0;
                    struct Process* it = addSleeper(kernMaintenanceProc, context->genericPtr);
                    kernRetQueueAddList(it);
                    break;
                default:
                    UARTprintf("Unknown code for kernel service: %d, process name: %s, pid: %d\n", context->comVal, kernMaintenanceProc->name, kernMaintenanceProc->pid);
                    break;
            }
            kernMaintenanceProc = kernelBufferGetProcess();
        }
        enum KernBufferMessageCodes code = kernelBufferGetCode();
        while(code != noMessageAvailable){
            switch(code) {
                struct Process* it;
                case sysTimerOverflow:
                    it = sleepHandleSysTimerOverflow();
                    kernRetQueueAddList(it);
                    break;
                case sleepTimerExpired:
                    it = refreshSleeplist();
                    kernRetQueueAddList(it);
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
