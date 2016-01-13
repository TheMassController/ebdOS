#include "validation.h"
#include "uartstdio.h"
#include "coreUtils.h"
#include "process.h"
#include "sysCalls.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "sleep.h"

void ledsDanceMain(void);

int main(void){
    int pid = createChildProcess(256, "I seek to flicker", val_ledsFlicker, NULL);
    if (pid == -1){
        UARTprintf("Errors: pid: %d, code: %d (%s)\n", pid, errno, strerror(errno));
    } else {
        UARTprintf("I seek to flicker has been created! Pid: %d\n", pid);
    }
    pid = createChildProcess(256, "prime_50000", findNthPrimeNumber, (void*)50000);
    if (pid == -1){
        UARTprintf("Errors: pid: %d, code: %d (%s)\n", pid, errno, strerror(errno));
    } else {
        UARTprintf("prime_50000 has been created! Pid: %d\n", pid);
    }
    pid = createChildProcess(256, "prime_25000", findNthPrimeNumber, (void*)25000);
    if (pid == -1){
        UARTprintf("Errors: pid: %d, code: %d (%s)\n", pid, errno, strerror(errno));
    } else {
        UARTprintf("prime_25000 has been created! Pid: %d\n", pid);
    }

    pid = getPid();
    UARTprintf("I am the main, and I did my thingy. Going to exit now. Pid: %d\n", pid);
}
