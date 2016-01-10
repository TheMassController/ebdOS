#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>         // Types like uint32_t are defined here
#include <stddef.h>         // size_t

#include "sysSleep.h"       // SleepingProcessStruct

/* States are handled as different bit flags:
 * pos 0 = sleep
 * pos 1,2 = wait
 * if state = 0, then it is ready
 * This way, a process can both be sleeping and waiting for a mutex.
 */

#define STATE_READY 0x0
#define STATE_SLEEP 0x1
//Three wait states, to imply which type of object blockAddress is and which queue needs to be tuched when waking up from sleep
#define STATE_WAIT 0x6 //A flag to surround them all
#define STATE_INC_WAIT 0x2
#define STATE_DEC_WAIT 0x4
#define STATE_TERM 0x8
//CS means context switcher
#define CS_SAVEDREGSPACE 8
#define CS_FPSAVEDREGSPACE 16
#define CS_USING_FP 0x4

//The next var is only about user processes, the kernel-based processes (kernel itself and idle) are counted seperately
#define MAXTOTALPROCESSES 10

//The HWFlags
#define PROCESS_DEFAULT 0x0
#define PROCESS_IS_PRIVILEGED 0x1
#define PROCESS_ENABLE_FP 0x10
#define PROCESS_USES_MSP 0x4

//The order of the first block is vital to make the assembly work correctly
struct Process {
    void* stackPointer;                                             // The actual stackpointer
    uintptr_t pid;                                                  // Pid of the process
    void* savedRegsPointer;                                         // Points towards the point were the saved data needs to be retrieved from or stored to
    uintptr_t hwFlags;                                              // HWflags used for context switching
    struct ProcessContext* context;                                 // The userspace context of the process

    uint32_t savedRegSpace[CS_SAVEDREGSPACE + CS_FPSAVEDREGSPACE];  // Space to save the saved temporaries. (8*4 byte, 1 reg is 4 byte (32 bit))
    uint32_t mPid;                                                  // Mother pid
    uint32_t stacklen;                                              // The length of the stack. Used to detect stack underflows
    void* stack;                                                    // refers to the address returned by Malloc
    char name[32];                                                  // The name can be 31 chars max, the last char always needs to be a zero.
    uint8_t state;                                                  // Set of 1 bit flags indicating if the process is sleeping, waiting.. etc
    uint8_t priority;                                               // Higher is higher: 255 is highest
    uint8_t containsProcess;                                        // Flag used for mempooling

    void* blockAddress;                                             // The multilockobject this process is waiting for
    struct SleepingProcessStruct sleepObj;                          // The sleepobject, contains all data necessary for sleeping

    struct Process* nextProcess;                                    // Makes the thing a linkedlist
    struct Process* childPtr;                                       // Refers to its first child
    struct Process* nextChildPtr;                                   // Refers to its little brother
};

struct ProcessCreateParams {
    size_t stacklen;
    char name[32];
    void (*procFunc)();
    void* param;
    uint8_t priority;
    uint8_t isPrivileged;
};

extern struct Process kernelStruct;
extern struct Process idleProcessStruct;
#endif
