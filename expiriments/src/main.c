/*
 * main.c
 *
 *  Created on: 12 nov. 2013
 *      Author: Daniel Versluis
 *       Email:	VersD @ hr.nl
 *
 *  Description:
 *  Framework for ROS01 scheduling assignment
 *
 *  Currently an incomplete basis for a RTOS
 *  To make the kernel complete the following things
 *  have to be added:
 *  -	Support for FPU
 *  -	Advanced scheduler
 *  -	Critical sections etc.
 *
 */
#include "lm4f120h5qr.h"
#include "task.h"
#include "schedule.h"
#include "switch.h"

/*------------------------------------Definitions--------------------------------*/

//CPU frequency
#define F_CPU	  40000000
//Systick freq
#define F_TICK	  (F_CPU/1000)

//Led definitions
#define RED_LED   (1<<1)
#define BLUE_LED  (1<<2)
#define GREEN_LED (1<<3)

/*------------------------------------DEMO---------------------------------------*/
//unworthy delay function
void delay(unsigned int count)
{
	while(count--);
}


void toggleRed(void)
{
	while(1)
	{
		GPIO_PORTF_AHB_DATA_R	^= RED_LED;		//Toggle red led.. surprise!
		delay(3000000);
	}
}

void toggleGreen(void)
{
	while(1)
	{
		GPIO_PORTF_AHB_DATA_R	^= GREEN_LED;	//Toggle green led..
		delay(6000000);
	}
}

void toggleBlue(void)
{
	while(1)
	{
		GPIO_PORTF_AHB_DATA_R	^= BLUE_LED;	//Toggle blue led..
		delay(1500000);
	}
}

void initLeds(void)
{
    // Enable and configure the GPIO port for the LED operation.
	SYSCTL_RCGCGPIO_R  		= SYSCTL_RCGC2_GPIOF;			//Enable clock for GPIOF
	SYSCTL_GPIOHBCTL_R		= (1<<5);						//Enable the AHB for portf

	//actually configure the pins
	GPIO_PORTF_AHB_DEN_R	= RED_LED|BLUE_LED|GREEN_LED;	//Digital enable pins
	GPIO_PORTF_AHB_DIR_R 	= RED_LED|BLUE_LED|GREEN_LED;	//Set pins to output
	GPIO_PORTF_AHB_DATA_R	= 0;							//Make PORTF low
}

void interrupt(void){
	SystickISR();
}

/*------------------------------------DEMO---------------------------------------*/

int main(void)
{
    // Setup the system clock to run at 40 Mhz from PLL with crystal reference
	SYSCTL_RCC_R = 0x02C00540;

	initLeds();
	//fpointer, stacksize, priority
	//addTaskToList(toggleRed		, 128, 2);
	//addTaskToList(toggleGreen	, 128, 2);
	//addTaskToList(toggleBlue	, 128, 2);
	

	//Configure Systick
	NVIC_ST_RELOAD_R 	= F_TICK-1;		//a systick every ms
	NVIC_ST_CURRENT_R	= F_TICK-1;     //a systick every ms
	NVIC_ST_CTRL_R 		= 0x7;			//enable systick timer, interrupt, main clock source

	//Interupt enable
	NVIC_EN0_R 			|= (1<<15);		//systick is vector 15 in the interrupt table, enable it

    while(1)
    {
    	//this could be used as an idle function
    	//sleep();
    }
}

