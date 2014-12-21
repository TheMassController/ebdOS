/*
 * schedule.h
 *
 *  Created on: 12 nov. 2013
 *      Author: Daniel Versluis
 *       Email:	VersD @ hr.nl
 *
 * Description:
 * Contains the scheduler, switcher (pendsv ISR)
 * and the systick ISR. Simple and uncomplete implementation
 *
 */
#include "lm4f120h5qr.h"
#include "schedule.h"
#include "switch.h"
#include "task.h"
#include "std.h"

#define MAIN_RETURN 	0xFFFFFFF9 //Tells the handler to return using the MSP
#define THREAD_RETURN 	0xFFFFFFFD //Tells the handler to return using the PSP
#define NULL (void*)0

extern task taskList[MAX_TASKS];

//Global pointers
task * currentTask;
task * taskToExecute;

/*
 * This variable is used to make sure we can safely use R0
 * with the assembly routines and not overwrite any other context
*/
int iTempRegister=0;

/*
 * Interrupt routine for the Systick timer
 * simply calls the scheduler
 *
 * ToDo: critical sections
 * */
void SystickISR(void)
{
	NVIC_INT_CTRL_R |= (1<<28);
//	schedule();
}

/*
 * It is recommended by ARM to use this interrupt
 * for the context switch. And thus we have :)
 *
 * push->switch->pop
 */
void PendSVISR(void)
{
	int five = testFunc();
	void** testR7 = malloc(sizeof(void*));
	getR7(testR7);
	free(testR7);
	return;

	//Push {R4-R11} context to PSP
	currentTask->stack = pushRegistersToCurrentPSP(iTempRegister);
	

	//Save the new stack pointer after the push
	currentTask->stack = readPSP(iTempRegister);

	//we've pushed the registers at least once
	//thus the task becomes initialized
	currentTask->bInitialized = 1;

	//Update current task
	currentTask = taskToExecute;

	//Update the CPU PSP to the newly selected tasks' SP
	writePSP(taskToExecute->stack);

	//This modifies the Main stack to return
	//to thread mode after the ISR, and thus
	//run our functions.
	int * msp = readMSP(iTempRegister);
	msp +=5;
	*((uint32_t*)msp) = THREAD_RETURN;

	//Is the task initialized? If it hasn't (run), the software
	//context (r4-r11) hasn't been saved yet, and thus shouldn't
	//be popped back to the CPU
	if(taskToExecute->bInitialized)
	{
		//Otherwise we can safely pop things :)
		popRegistersFromCurrentPSP(iTempRegister);
	}
}


/*
 * This does the following:
 *
 * select the next task
 *
 * call the pendsv isr to switch
 * OR
 * return
 *
 * Tasks are allowed to call this function
 * and thus pre-empt themselves. e.g. for
 * suspending prematurely
 * */
void schedule(void)
{
	//This is our true scheduler function
	//select a new task to run
	taskToExecute = getNextTask();

	//Only if the new task isn't equal to the current one,
	//call the context switch
	if(taskToExecute != currentTask || taskToExecute->bInitialized==0)
	{
		//States to help the scheduler decide
		currentTask->state	 = READY;
		taskToExecute->state = RUNNING;

		//call pendsv interrupt to perform the context switch
		NVIC_INT_CTRL_R |= (1<<28);
	}else{
		//Clearly no need to switch anything so we
		//just restore things like they were before the Systick

		currentTask->state	 = RUNNING;
	}
}

/*
 * Our genuine scheduler. Currently very static and
 * not-advanced
 *
 * returns a pointer to the selected task
 */
task * getNextTask(void)
{
	static int i=0;

	while(taskList[++i].function == 0)
	{
		if(i==3)
		{
			i = -1;
		}
	}

	return &taskList[i];
}