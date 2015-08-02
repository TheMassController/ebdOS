#ifndef SUPERVISORCALL_H
#define SUPERVISORCALL_H

// Helper macros
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

// The codes
#define SVC_yield                               0
#define SVC_multiObjectIncrease                 1
#define SVC_multiObjectDecrease                 2
#define SVC_multiObjectWaitForIncrease          3
#define SVC_multiObjectWaitForDecrease          4
#define SVC_multiObjectWaitForIncreaseAndSleep  5
#define SVC_multiObjectWaitForDecreaseAndSleep  6
#define SVC_sleep                               7
#define SVC_wakeup                              8
#define SVC_wakeupCurrent                       9
#define SVC_processAdd                          10
#ifdef DEBUG
#define SVC_test                                255
#endif // DEBUG

// Contains the macro to create the supervisor call
#define CALLSUPERVISOR(code) __asm__("svc "STR(code));

#endif // SUPERVISORCALL_H
