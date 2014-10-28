//Generates a supervisor call interrupt. Thats it

#include "uartstdio.h"
#include "asmUtils.h"
#include "supervisorCall.h"

int testSVCcall(void){
    UARTprintf("Generating supervisor call interrupt...\r\n");
    CALLSUPERVISOR(SVC_test);
    UARTprintf("Done, return\r\n");
    return 1;
}
