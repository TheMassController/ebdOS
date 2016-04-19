#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>             // Types like uint32_t are defined here
#include <stddef.h>             // size_t

#include "abstrSysSleepStructs.h"      // SleepingProcessStruct

/* States are handled as different bit flags:
 * pos 0 = sleep
 * pos 1,2 = wait
 * if state = 0, then it is ready
 * This way, a process can both be sleeping and waiting for a mutex.
 */

enum ProcessStates {
    STATE_READY,
    STATE_SLEEP,
    STATE_WAIT,
    STATE_WAIT_TIMEOUT,
    STATE_INC_WAIT, //TODO depricate
    STATE_DEC_WAIT, //TODO depricate
    STATE_TERM
};

//CS means context switcher
#define CS_SAVEDREGSPACE 8
#define CS_FPSAVEDREGSPACE 16
#define CS_USING_FP 0x4

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
    uintptr_t  mPid;                                                // Mother pid
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

    int32_t retval;                                                 // The returnvalue of the process, set on termination
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
