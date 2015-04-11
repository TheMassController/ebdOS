//Used to test the mpu
#include "uartstdio.h"
#include "sysCalls.h"
#include "sleep.h"
#include "process.h"
#include <hw_types.h>

extern struct Process* currentProcess;

void printIntro(void){
    UARTprintf("Hello there! My name is %s, my pid is %d and my mothers' pid is: %d\n", currentProcess->name, currentProcess->pid, currentProcess->mPid);
}

void testMPUPriv(void){
    unsigned tempData;
    printIntro();
    UARTprintf("First test: I am privileged and therefore I should be able to read from the flash. Try to do so..\n");
    tempData = HWREG(0x50);
    UARTprintf("Success! Here is the data I found: %u\n", tempData);
    UARTprintf("The second test is writing to the flash. This should fail with an MPU error.\n");
    HWREG(0x50) = 22;
    tempData = HWREG(0x50);
    UARTprintf("Oops, this was successfull. Here is the data currently in 0x50: %u\n", tempData);
    while(1) sleepS(100);
}

void testMPUUpriv(void){
    printIntro();
    while(1) sleepS(100);
}
