#include "stdlib.h" //Malloc
#include "rom.h" //rom_ funcs
#include "uartstdio.h" //For printf, scanf

#include "getSetRegisters.h" //ASM funcs for getting CPU regs
#include "asmUtils.h"
#include "validation.h" 

int main(void){
    int testRet = testUARTstdio();
    int failure = 0;
    if (testRet != 1){
        UARTprintf("TestUARTstdio failure %d\n",testRet);
        failure = 1;
    }
    testRet = testProcessStructure();
    if (testRet != 1){
        UARTprintf("testProcessStructure failure %d\n",testRet);
        failure = 1;
    }
    //testRet = testGPIO();
    //if (testRet != 1){
    //    UARTprintf("testGPIO failure %d\n");
    //    failure = 1;
    //}
    if (failure){
        UARTprintf("Run failed!");
    } else {
        UARTprintf("Great Succes!");
    }
    UARTprintf(" (Run finished)\r\n");
	while(1){ //On success the program hangs here
        waitForInterrupt();
    }
}
