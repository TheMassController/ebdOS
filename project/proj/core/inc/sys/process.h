#ifndef PROCESS_H
#define PROCESS_H

#include "sysSleep.h" 

//States are handled as different bit flags:
//pos 0 = sleep
//pos 1 = wait
//if state = 0, then it is ready
//This way, a process can both be sleeping and waiting for a mutex.

#define STATE_READY 0x0
#define STATE_SLEEP 0x1
//Three wait states, to imply which type of object blockAddress is and which queue needs to be tuched when waking up from sleep
#define STATE_WAIT 0xE //A flag to surround them all
#define STATE_LOCKED 0x2
#define STATE_INC_WAIT 0x4
#define STATE_DEC_WAIT 0x8

//The next var is only about user processes, the kernel-based processes (kernel itself and idle) are counted seperately
#define MAXTOTALPROCESSES 10


//The order of the first two is vital to make the assembly work correctly
struct Process {
    void* stackPointer; //The actual stackpointer
    unsigned pid;

    unsigned mPid;
    char containsProcess;
    char name[21];
    struct Process* nextProcess;
    void* stack; //refers to the address returned by Malloc
    char state; //Set of 1 bit flags
    char priority; //Higher is higher: 255 is highest  

    //Block vars
    void* blockAddress;
    struct SleepingProcessStruct sleepObj;
};

/*
    Codes:
        0: Everything ok
        1: out of PIDS
        2: Out of mem
        3: Wrong caller pid, only kernel (PID 0) can create processes
*/
int __createNewProcess(unsigned mPid, unsigned long stacklen, char* name, void (*procFunc)(void*), void* param, char priority );

#endif
