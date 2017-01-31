#ifndef SUPERVISORCALL_H
#define SUPERVISORCALL_H

// Helper macros
#define STR_HELPER(x) #x

// The codes
#define SVC_yield                               0
#define SVC_sleep                               1
#define SVC_wakeup                              2
#define SVC_wakeupCurrent                       3
#define SVC_wakeupKernel                        4
#define SVC_serviceRequired                     5
#define SVC_serviced                            6
#define SVC_mainClockInterrupt                  7
#define SVC_abort                               8
#ifdef DEBUG
#define SVC_test                                255
#endif // DEBUG

// Contains the macro to create the supervisor call
#define CALLSUPERVISOR(code) __asm__("svc "STR_HELPER(code));

#endif // SUPERVISORCALL_H
