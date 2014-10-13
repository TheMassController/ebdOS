#ifndef PROCESS_H
#define PROCESS_H


//This is a function pionter which forces the function to have the signature "void proc(void*)". The last void* is for possible params
typedef void (*processFunc)(void*);

//All the states that exist
enum STATE {
    READY,
    SLEEP,
    WAIT
};
//The order of the first two is vital to make the assembly work correctly
struct Process {
    void* stackPointer; //The actual stackpointer
    char pid;

    char mPid;
    char* name;
    struct Process* nextProcess;
    void* stack; //refers to the address returned by Malloc
    enum STATE state;
    
};

/*
    Codes:
        0: Everything ok
        1: out of PIDS
        2: Out of mem
        3: Wrong caller pid, only kernel (PID 0) can create processes
*/
int __createNewProcess(unsigned char mPid, unsigned long stacklen, char* name, processFunc procFunc, void* param, char priority );

int __deleteProcess(unsigned char pid);

void processReturn(void);

#endif
