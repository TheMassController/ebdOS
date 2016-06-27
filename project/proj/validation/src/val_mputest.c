//Used to test the mpu
#include <hw_types.h>
#include <uartstdio.h>

#include "core/inc/sysCalls.h"
#include "core/inc/sleep.h"
#include "kernel/inc/process.h" //TODO

extern struct Process* currentProcess;

extern unsigned long _flash_text_data_end_aligned;

void initializeProcesses(void);

void printIntro(void){
    UARTprintf("Hello there! My name is %s, my pid is %d and my mothers' pid is: %d\n", currentProcess->name, currentProcess->pid, currentProcess->mPid);
}

#define KERNREGIONADDR 0x50
unsigned* const NOMANSLANDADDR = (unsigned*)((unsigned)&_flash_text_data_end_aligned + 5);

void testMPUPriv(void){
    unsigned volatile tempData;
    unsigned* volatile testLocation = (unsigned*)KERNREGIONADDR;
    printIntro();
    UARTprintf("The address which we are going to test with: 0x%x\n", (unsigned)testLocation);
    UARTprintf("First test: I am privileged and therefore I should be able to read from the flash. Try to do so..\n");
    tempData = *testLocation;
    UARTprintf("Success! Here is the data I found: %x\n", tempData);
    //UARTprintf("The second test is writing to the flash in the kernel region. This should fail with an MPU error.\n");
    //*testLocation = 0;
    //tempData = *testLocation;
    //UARTprintf("Oops, this was successfull. Here is the data currently in 0x50: %u\n", tempData);
    UARTprintf("Third test: writing to a flash area which we are alowed to write to\n");
    tempData = *NOMANSLANDADDR;
    UARTprintf("Read success! Here is the data I found: %x\n", tempData);
    *NOMANSLANDADDR = 0xB00B5;
    tempData = *NOMANSLANDADDR;
    UARTprintf("Write and read success! Here is the data I found: %x\n", tempData);
    while(1) sleepS(100);
}

void testMPUUpriv(void){
    printIntro();
    initializeProcesses();
    *NOMANSLANDADDR = 0xB00B5;
    while(1) sleepS(100);
}
