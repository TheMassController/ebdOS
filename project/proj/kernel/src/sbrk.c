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
	char* returnVal = (char*)-1;
	if (heap_end == NULL){ //Init
		heap_end = &_ebss;
	}

	if (heap_end + incr <= (caddr_t)(((unsigned long)getMSP()) - ((unsigned long)(&_stack_buffer)))){
		heap_end += incr;
		returnVal = heap_end;
	}

	return returnVal;
}
