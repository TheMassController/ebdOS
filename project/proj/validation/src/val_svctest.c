//Generates a supervisor call interrupt. Thats it

#include "uartstdio.h"
#include "asmUtils.h"

int testSVCcall(void){
    UARTprintf("Generating supervisor call interrupt...\r\n");
    generateSupervisorCall();
    UARTprintf("Done, return\r\n");
    return 1;
}
