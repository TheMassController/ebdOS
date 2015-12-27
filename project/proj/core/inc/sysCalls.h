#ifndef SYSCALLS_H
#define SYSCALLS_H

#include "sleep.h"

// The following are the defenitions of the different syscall values
enum SyscallCodes {
    GETPID,
    SPAWNCHILDPROCESS,
    PROCESSSLEEP
};

/**
 * @brief Returns the PID of the caller. This function cannot fail, unless the entire OS goes down.
 */
unsigned getPid(void);

/**
 * @brief create a childprocess with given parameters
 * @param stacklen The size of the stack of the child process
 * @param name The name of the childprocess, can contain at most 31 chars, excluding the /0
 * @param procFunc The pointer to the function you want to start on a different thread
 * @param param Optional parameter to pass to the process. Usually NULL.
 * @return -1 if there was an error, errno will be set. PID of the child if everything went ok, errno will be untuched.
 */
int createChildProcess(unsigned long stacklen, char* name, void (*procFunc)(), void* param);
/**
 * @brief Puts a process into sleep.
 *
 * A Process can be signaled to stop sleeping, in that case the function returns -1.
 * Errno will also be set. If everything happens as it should, the function returns 0.
 *
 * @param sleepReq This param is passed to the kernel.
 * @return -1 if error (errno will be set) 0 else.
 */
int sysCallSleep(struct SleepRequest* sleepReq);
#endif //SYSCALLS_H
