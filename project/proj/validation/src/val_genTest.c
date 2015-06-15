//This file can be used to test the quirks of ARM, C and the CC

#include "stdlib.h" //Malloc
#include "uartstdio.h" //For printf, scanf


int heapTest(){
    char* testCharPtr = malloc(5);
    char* testCharPtr2 = malloc(5);
    UARTprintf("%d\n",testCharPtr2 - testCharPtr);
    return 0;
}
