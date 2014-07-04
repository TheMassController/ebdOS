/**
* This file tests the UARTstdio functionality
**/

#include "uartstdio.h" //For printf, scanf, etc.

int testUARTstdio(void){
    UARTprintf("String test: %s\n","This is a string");
    UARTprintf("Int test: %i\n",5);
    int i = 6;
    UARTprintf("Pointer test: %p\n",&i);
    return 0;
}
