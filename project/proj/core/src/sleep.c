//Contains all sleep related code
#include "sleep.h"                  // Header of the same name
#include "sysSleep.h"               // Kernel facing sleep funcs
#include "sysCalls.h"               // Syscall defs
#include "systemClockManagement.h"  // Contains getSystemClockValue

int sleep(struct SleepRequest* sleepReq){
    sleepReq->refTime = getSystemClockValue();
    return sysCallSleep(sleepReq);
}

int sleepMS(unsigned mSec){
    struct SleepRequest req;
    req.uSec = 0;
    req.mSec = mSec;
    req.sec = 0;
    return sleep(&req);
}

int sleepUS(unsigned uSec){
    struct SleepRequest req;
    req.uSec = uSec;
    req.mSec = 0;
    req.sec = 0;
    return sleep(&req);
}

int sleepS(unsigned sec){
    struct SleepRequest req;
    req.uSec = 0;
    req.mSec = 0;
    req.sec = sec;
    return sleep(&req);
}
