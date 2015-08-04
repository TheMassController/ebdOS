//The functions of the actual kernel: this is the kernel process
#include "process.h"
#include "uartstdio.h"
#include "sysCalls.h"
#include "supervisorCall.h"

struct Process* kernMaintenacePtr;

void kernelMain(void){
    while(1){
        struct ProcessContext* context = kernMaintenacePtr->context;
        switch(context->comVal){
            case SYSCALL_getpid:
                context->retVal = kernMaintenacePtr->pid;
                break;
            default:
                UARTprintf("Unknown code for kernel service: %d", context->comVal);
        }
        CALLSUPERVISOR(SVC_serviced);
    }
}
