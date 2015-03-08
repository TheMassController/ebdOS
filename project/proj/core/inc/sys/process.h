#ifndef PROCESS_H
#define PROCESS_H

#include "sysSleep.h" 

//States are handled as different bit flags:
//pos 0 = sleep
//pos 1,2 = wait
//if state = 0, then it is ready
//This way, a process can both be sleeping and waiting for a mutex.

#define STATE_READY 0x0
#define STATE_SLEEP 0x1
//Three wait states, to imply which type of object blockAddress is and which queue needs to be tuched when waking up from sleep
#define STATE_WAIT 0x6 //A flag to surround them all
#define STATE_INC_WAIT 0x2
#define STATE_DEC_WAIT 0x4

//The next var is only about user processes, the kernel-based processes (kernel itself and idle) are counted seperately
#define MAXTOTALPROCESSES 10

//The order of the first three is vital to make the assembly work correctly
struct Process {
    void* stackPointer;                     //The actual stackpointer
    unsigned pid;                           //Pid of the process
    void* savedRegsPointer;                 //Points towards the point were the saved data needs to be retrieved from or stored to

    unsigned savedRegSpace[8];                  //Space to save the saved temporaries. (8*4 byte, 1 reg is 4 byte (32 bit))
    unsigned mPid;                          //Mother pid
    char containsProcess;                   //Flag used for mempooling
    char name[21];                          //The name can be 20 chars max, the last char is a /0
    void* stack;                            //refers to the address returned by Malloc
    char state;                             //Set of 1 bit flags indicating if the process is sleeping, waiting.. etc
    char priority;                          //Higher is higher: 255 is highest  

    void* blockAddress;                     //The multilockobject this process is waiting for
    struct SleepingProcessStruct sleepObj;  //The sleepobject, contains all data necessary for sleeping

    struct Process* nextProcess;            //Makes the thing a linkedlist
};

/*
    Codes:
        0: Everything ok
        1: out of PIDS
        2: Out of mem
        3: Wrong caller pid, only kernel (PID 0) can create processes
*/
int __createNewProcess(unsigned mPid, unsigned long stacklen, char* name, void (*procFunc)(), void* param, char priority );

#endif
