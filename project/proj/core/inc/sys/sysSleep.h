#ifndef SYSSLEEP_H
#define SYSSLEEP_H

#include "process.h" 

struct SleepingProcessStruct{
    struct Process* process;
    struct SleepingProcessStruct* nextPtr;
    unsigned overflows;
    unsigned sleepUntil;
};

void setSleepTimerWB(void);
void addSleeperToList(struct SleepingProcessStruct* ptr);

#endif //SYSSLEEP_H
