#include "sysCalls.h"
#include "supervisorCall.h"

unsigned getPid(void){
    currentContext->comVal = SYSCALL_getpid;
    CALLSUPERVISOR(SVC_serviceRequired);
    return currentContext->retVal;
}
