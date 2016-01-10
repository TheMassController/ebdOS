#include <string.h>

#include "process.h"
#include "sysCalls.h"
#include "context.h"
#include "supervisorCall.h"

unsigned getPid(void){
    setContextParams(GETPID, NULL, 0);
    CALLSUPERVISOR(SVC_serviceRequired);
    return currentContext->retVal;
}

int createChildProcess(size_t stacklen, char* name, void (*procFunc)(), void* param){
    struct ProcessCreateParams params;
    params.stacklen = stacklen;
    strcpy(params.name, name);
    params.procFunc = procFunc;
    params.param = param;
    setContextParams(SPAWNCHILDPROCESS, &params, 0);
    CALLSUPERVISOR(SVC_serviceRequired);
    return currentContext->retVal;
}

int sysCallSleep(struct SleepRequest* sleepReq){
    setContextParams(PROCESSSLEEP, sleepReq, 0);
    CALLSUPERVISOR(SVC_serviceRequired);
    return currentContext->retVal;
}
