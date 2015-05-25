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

#define KERNREGIONADDR 0x50

void testMPUPriv(void){
    unsigned volatile tempData;
    unsigned* volatile testLocation = (unsigned*)KERNREGIONADDR;
    printIntro();
    UARTprintf("The address which we are going to test with: 0x%x\n", (unsigned)testLocation);
    UARTprintf("First test: I am privileged and therefore I should be able to read from the flash. Try to do so..\n");
    tempData = *testLocation;
    UARTprintf("Success! Here is the data I found: %u\n", tempData);
    UARTprintf("The second test is writing to the flash in the kernel region. This should fail with an MPU error.\n");
    *testLocation = 0;
    tempData = *testLocation;
    UARTprintf("Oops, this was successfull. Here is the data currently in 0x50: %u\n", tempData);
    while(1) sleepS(100);
}

void testMPUUpriv(void){
    printIntro();
    while(1) sleepS(100);
}
