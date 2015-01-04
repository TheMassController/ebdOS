//Implements the _sbrk function
//#include <stdio.h> 
#include <sys/types.h> //Needed for caddr_t
#include "getSetRegisters.h" //Needed for getMSP

#ifdef DEBUG
#include "uartstdio.h"
#endif

static caddr_t heap_end = NULL;
extern char _ebss; //The end of the hard defined sections and the start of the heap (defined in linker script)
extern char _stack_buffer; //The minimal difference between stack and heap
//Heap grows up, stack grows down

caddr_t _sbrk(int incr){
	char* returnVal = -1;	
	if (heap_end == NULL){ //Init
		heap_end = &_ebss;
	}

#ifdef DEBUG
    UARTprintf("(S) MSP: 0x%x, heap_end 0x%x, diff %u\r\n", getMSP(), heap_end, (unsigned)getMSP() - (unsigned)heap_end);
#endif
	
	if (heap_end + incr <= (caddr_t)(((unsigned long)getMSP()) - ((unsigned long)(&_stack_buffer)))){ 
		heap_end += incr;
		returnVal = heap_end;	
	} 
#ifdef DEBUG
    UARTprintf("(F) MSP: 0x%X, heap_end 0x%X, diff %u\r\n", getMSP(), heap_end, (unsigned)getMSP() - (unsigned)heap_end);
    if (returnVal == -1){
        UARTprintf("Heap full\r\n");
    }
#endif
    
	return returnVal;
}
