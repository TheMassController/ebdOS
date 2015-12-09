//The functions of the actual kernel: this is the kernel process
#include <stdlib.h>

#include "process.h"
#include "uartstdio.h"
#include "sysCalls.h"
#include "supervisorCall.h"
#include "kernMaintenanceQueue.h"

void kernelMain(void){
    while(1){
        struct Process* kernMaintenanceProc = kernelBufferGetProcess();
        while(kernMaintenanceProc != NULL){
            struct ProcessContext* context = kernMaintenanceProc->context;
            switch(context->comVal){
                case SYSCALL_getpid:
                    context->retVal = kernMaintenanceProc->pid;
                    kernRetQueuePush(kernMaintenanceProc);
                    break;
                default:
                    UARTprintf("Unknown code for kernel service: %d, process name: %s, pid: %d\n", context->comVal, kernMaintenanceProc->name, kernMaintenanceProc->pid);
                    break;
            }
            kernMaintenanceProc = kernelBufferGetProcess();
        }
        CALLSUPERVISOR(SVC_serviced);
    }
}
