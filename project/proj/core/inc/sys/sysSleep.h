#ifndef SYSSLEEP_H
#define SYSSLEEP_H

#include "process.h" 

struct SleepingProcessStruct{
    struct Process* process;
    struct SleepingProcessStruct* nextPtr;
    unsigned overflows;
    unsigned sleepUntil;
};

void __sleepMSDelayBlock(unsigned ms);
void __sleepDelayBlockWakeup(void);

#endif //SYSSLEEP_H
