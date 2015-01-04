//This is where a fault lands

#include "uartstdio.h"
#include "asmUtils.h"

void faultISRHandler(void){
    UARTprintf("Hard fault\r\nReset the device to continue...\r\n");
    while(1);
}
