#ifndef SYSCALLS_H
#define SYSCALLS_H

#include "context.h"

// The following are the defenitions of the different syscall values
#define SYSCALL_getpid 0



/**
    RETCODES:
    0: sucess
    2: unknown error

    @warning DEPRECATED
**/
int createProcess(unsigned long stacklen, char* name, void (*procFunc)(), void* param, char priority);

/**
 * @brief Returns the PID of the caller. This function cannot fail, unless the entire OS goes down.
 */
unsigned getPid(void);
#endif //SYSCALLS_H
