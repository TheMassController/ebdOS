#include "stdlib.h" //Malloc
#include "rom.h" //rom_ funcs
#include "uartstdio.h" //For printf, scanf

#include "getRegisters.h" //ASM funcs for getting CPU regs
#include "asmUtils.h"
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
	void* mainStackPointer = getMSP();
    void* programStackPointer = getPSP();
	UARTprintf("i=%x   MSP = %p\r\n",i,mainStackPointer);
	UARTprintf("i=%x   PSP = %p\r\n",i,programStackPointer);
    int testRet = testUARTstdio();
    testRet = testRegDumpLoad();
	while(1){ //On success the program hangs here
        waitForInterrupt();
    }
}
