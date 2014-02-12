//Implements the _sbrk function
//#include <stdio.h> 

#define NULL (void*)0

static unsigned char *heap_end = NULL;
extern unsigned char* _heap_bottom;
extern unsigned char* _heap_top;

unsigned char* _sbrk(int incr){
	unsigned char* returnVal = NULL;	
	if (heap_end == NULL){
		heap_end = _heap_bottom;
	}
	if (heap_end + incr <= _heap_top){
		returnVal = heap_end;	
		heap_end += incr;
	}
	return returnVal;
}
