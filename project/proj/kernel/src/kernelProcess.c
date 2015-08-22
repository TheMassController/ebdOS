//The functions of the actual kernel: this is the kernel process
#include "process.h"
#include "uartstdio.h"
#include "sysCalls.h"
#include "supervisorCall.h"

struct Process* kernReturnList;

void kernelMain(volatile const struct Process** kernMaintenancePtr){
    while(1){
        struct Process* kernMaintenanceProc = (struct Process*)*kernMaintenancePtr;
        struct ProcessContext* context = kernMaintenanceProc->context;
        switch(context->comVal){
            case SYSCALL_getpid:
                context->retVal = kernMaintenanceProc->pid;
                kernReturnList = kernMaintenanceProc;
                break;
            default:
                UARTprintf("Unknown code for kernel service: %d", context->comVal);
                break;
        }
        CALLSUPERVISOR(SVC_serviced);
    }
}
