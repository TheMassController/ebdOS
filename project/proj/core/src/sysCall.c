#include <string.h>

#include "process.h"
#include "sysCalls.h"
#include "context.h"
#include "supervisorCall.h"

unsigned getPid(void){
    setContextParams(GETPID, NULL);
    CALLSUPERVISOR(SVC_serviceRequired);
    return currentContext->retVal;
}

int createChildProcess(unsigned long stacklen, char* name, void (*procFunc)(), void* param){
    struct ProcessCreateParams params;
    params.stacklen = stacklen;
    strcpy(params.name, name);
    params.procFunc = procFunc;
    params.param = param;
    setContextParams(SPAWNCHILDPROCESS, &params);
    CALLSUPERVISOR(SVC_serviceRequired);
    return currentContext->retVal;
}

int sysCallSleep(struct SleepRequest* sleepReq){
    setContextParams(PROCESSSLEEP, sleepReq);
    CALLSUPERVISOR(SVC_serviceRequired);
    return currentContext->retVal;
}
