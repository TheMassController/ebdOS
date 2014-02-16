//Implements the _sbrk function
//#include <stdio.h> 
#include <sys/types.h> //Needed for caddr_t

static caddr_t heap_end = NULL;
extern char _heap_bottom; //The start of the heap (defined in linker script)
extern char _heap_top;	//The end of the heap (defined in linker script)
//Heap grows up, stack grows down

caddr_t _sbrk(int incr){
	char* returnVal = NULL;	
	if (heap_end == NULL){ //Init
		heap_end = &_heap_bottom;
	}
	
	if (heap_end + incr <= &_heap_top){ //Heap starts at bottom and works up until heap_top. Therefore heap_top is ALWAYS smaller then heap_end: _heap_bottom = end of SRAM
		heap_end += incr;
		returnVal = heap_end;	
	}
	return returnVal;
}
