#ifndef PROCESS_H
#define PROCESS_H


//This is a function pionter which forces the function to have the signature "void proc(void*)". The last void* is for possible params
typedef void (*processFunc)(void*);

struct Process {
    unsigned char pid;
    unsigned char mPid;
    char* name;
    struct Process* nextProcess;
    void* stack; //refers to the address returned by Malloc
    void* stackPointer; //The actual stackpointer
};

/*
    Codes:
        0: Everything ok
        1: out of PIDS
        2: Out of mem
        3: Wrong caller pid, only kernel (PID 0) can create processes
*/
int __createNewProcess(unsigned char mPid, unsigned long stacklen, char* name, processFunc procFunc, void* param );

int __deleteProcess(unsigned char pid);

void processReturn(void);

#endif
