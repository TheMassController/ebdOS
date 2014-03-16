//This file makes sure all the default settings are set
//The following things will be set:
//PLL: to maximum speed

//#include "hw_memmap.h"      //Contains the memory addresses needed
#include "hw_types.h" //Contains the types
#include "sysctl.h" 	//Contains defines for PLL regs
#include "rom_map.h" //Call functions directly from the ROM if available
#include "rom.h" //Declare ROM addresses for rom funcs
#include "hw_memmap.h" //address of GPIO etc
#include "gpio.h" //Address of GPIO stuff
#include "uart.h" //UART addresses and stuff
#include "uartstdio.h" //UART printf n stuff

void setupHardware(void){
	//Consts
	const long baud = 115200;
	//Setup the PLL
	//Datasheet pp 217
	//Driver API pp 284
	//Sysclock = 80 Mhz (maxmimum)
	//PLL = 400, predivide = /2, 200/80 = 2.5, so we want to enable the default PLL setup and then divide by 2.5
	//                 Divide input by 2.5|Use the PLL |Use the main oscillator|Main oscillator is 16 Mhz
	ROM_SysCtlClockSet(SYSCTL_SYSDIV_2_5| SYSCTL_USE_PLL          |SYSCTL_OSC_MAIN        |SYSCTL_XTAL_16MHZ);

	//Setup the Debug UART out
	//Enable the correct interfaces: GPIOA for USB Debug, UART0 for USB Debug
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	//Setup GPIO A as UART
	ROM_GPIOPinTypeUART(GPIO_PORTA_BASE,GPIO_PIN_0|GPIO_PIN_1);	
	//Set the clock to the 16 MHz oscillator
	//ROM_UARTClockSourceSet(UART0_BASE,UART_CLOCK_PIOSC);
	////Setup the UART
	////	                UART0,clockspeed of internal oscillator, 115200 baud, 8-bit char len, 1 stop bit, no parity  
	//ROM_UARTConfigSetExpClk(UART0_BASE,16000000,baud,UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);	
	////enable the UART
	//ROM_UARTEnable(UART0_BASE);
	UARTStdioInitExpClk(0,baud);
}
