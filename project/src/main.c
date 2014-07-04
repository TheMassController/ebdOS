#include "stdlib.h" //Malloc
#include "rom.h" //rom_ funcs
#include "uartstdio.h" //For printf, scanf

#include "assembly.h"
#include "validation.h" 

int main(void){
	UARTprintf("Hello, World!\n");
	int i = 2;
	int *j = NULL;
	j = (int*)malloc(sizeof(int));	
	//Check the cpu speed
	unsigned long cpuSpeed = ROM_SysCtlClockGet();	
	if ((j ==  NULL)| (cpuSpeed != 80000000)){
		for(;;); //On failure, the program hangs here
	}
	void* stackPointer = getSP();
	UARTprintf("i=%x   SP = %p\r\n",i,stackPointer);
    testUARTstdio();
	while(1); //On success the program hangs here
}
