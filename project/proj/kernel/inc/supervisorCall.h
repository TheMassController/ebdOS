#ifndef SUPERVISORCALL_H
#define SUPERVISORCALL_H

// Helper macros
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

// The codes
#define SVC_reschedule 0
#define SVC_multiObjectIncrease 4
#define SVC_multiObjectDecrease 5
#define SVC_multiObjectWaitForIncrease 6
#define SVC_multiObjectWaitForDecrease 7
#define SVC_multiObjectWaitForIncreaseAndSleep 8
#define SVC_multiObjectWaitForDecreaseAndSleep 9
#define SVC_setKernelPrioMax 10
#define SVC_sleep 11
#define SVC_wakeup 12
#define SVC_wakeupCurrent 13
#define SVC_processAdd 14
#ifdef DEBUG
#define SVC_test 255
#endif // DEBUG

// Contains the macro to create the supervisor call
#define CALLSUPERVISOR(code) __asm__("svc "STR(code));

#endif // SUPERVISORCALL_H
