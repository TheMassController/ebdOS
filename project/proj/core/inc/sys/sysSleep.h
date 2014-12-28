#ifndef SYSSLEEP_H
#define SYSSLEEP_H

#include "process.h" 

struct SleepingProcessStruct{
    struct Process* process;
    struct SleepingProcessStruct* nextPtr;
    unsigned overflows;
    unsigned sleepUntil;
};

void __setSleepTimerWB(void);
void __addSleeperToList(struct SleepingProcessStruct* ptr);
void __sleepActive(unsigned seconds);
void __sleepMSActive(unsigned seconds);

#endif //SYSSLEEP_H
