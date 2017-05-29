/**
 * @file kernEventNotifier.h
 * @author Jacko Dirks
 *
 * This is the header file for the functions responsible for the communication towards the kernel from the rest of the world.
 * The functions defined here make sure that everything happens threadsafely.
 *
 * The communication is based on messages, that usually indicate an interrupt happend and the kernel should do something about it.
 * The process service part is mainly handled in core/inc/sysCalls.h (core). The messages are defined as an enum here.
 * The second one is processes. The SVC is always in this chain, allthough the root cause can be an interrupt.
 * An example is the segfault: this happens because of an interrupt, which tells the SVC, which removes the current process from running and passes it on to the kernel.
 * A more common example is a resource request: the SVC is notified by the process and passes the process to the kernel, which handles the actual process.
 *
 * There are no guarantees at all on any ordering.
 *
 * @warning Do not attempt to call any of these functions from unsupervised, this causes a memory violation.
 */
#ifndef KERNEVENTNOTIFIER_H
#define KERNEVENTNOTIFIER_H

#include "process.h"
#include "kernelPredefined.h"

enum KernBufferMessageCodes{
    noMessageAvailable = 0, // This way, a buffer specified in the .bss section will be set to all 0 on reset and thus will be set to noMessageAvailable.
                            // Note that this is not necessary: the C standard specifies that the first value of an enum gets 0 per default.
    sysTimerOverflow,
    sleepTimerExpired,
    waitModuleTimerExpired
};

/**
 * @brief Used to pass a message to the kernel
 * @param code The code you want to pass to the kernel
 * @warning Do not call this function from unsupervised.
 * @warning Do not call this function from Supervisor.
 * @return 0 if everything was fine, ENOMEM if the buffer was full.
 */
int passMessageToKernel(const enum KernBufferMessageCodes code);

/**
 * @brief Pops a kernelcode from the buffer and returns it.
 * @return noMessageAvailable if there is no message, else it returns the message.
 */
enum KernBufferMessageCodes kernelBufferGetCode(void);

/**
 * @brief Checks if the kernel buffer is empty
 * @return 1 if there is no message in the buffer, 0 if there is at least one.
 */
int kernBufferIsEmpty(void);
#endif //KERNEVENTNOTIFIER_H
