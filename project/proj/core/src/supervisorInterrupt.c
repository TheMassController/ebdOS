//Handles the supervisor interrupt call
#include "uartstdio.h"
#include "lm4f120h5qr.h" //Hardware regs

void rescheduleImmediately(void){
    NVIC_INT_CTRL_R |= (1<<26); //Set the SysTick to pending (Datasheet pp 156)
    NVIC_ST_CURRENT_R = 0; //Clear the register by writing to it with any value (datasheet pp 118, 136)
}

void sayHi(void){
    UARTprintf("Hi from your favorite supervisor!\r\n");
}

//This function responds to an interrupt that can be generated at any runlevel.
void svcHandler_main(char reqCode){
    //UARTprintf("supervisor interrupt, id:%d\r\n",reqCode);
    switch(reqCode){
        case 0:
            rescheduleImmediately();
            break;
        case 255:
            sayHi();
            break;
        default:
            UARTprintf("Supervisor call handler: unknown code %d\r\n",reqCode);
            break;
    }
}
