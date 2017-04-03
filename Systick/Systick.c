/*
 * Systick.c
 *
 *  Created on: Jul 15, 2015
 *      Author: Dinh
 */

/*
 * This provides a millis()-like systick counter for easier time-keeping
 * Small timeout functions are added for better code clarity
 *
 * Systick is possibly not as precise as timer, but lwIP stacks  sample code
 * relies on systick interrupt to run, so I will keep this as to simplify the code
 */

#include "Systick.h"

volatile unsigned long sysTickCount;

/** @brief Initialize the systick timer peripherals
 *
 *  @return Void.
 */
void sysTickInit(void)
{
    MAP_SysTickPeriodSet(g_ui32SysClock / SYSTICKHZ);
    MAP_SysTickEnable();
    MAP_SysTickIntEnable();

    MAP_IntPrioritySet(FAULT_SYSTICK, SYSTICK_INT_PRIORITY);
    sysTickCount = 0;
}

/** @brief Systick interrupt service routine
 *
 *	This ISR increases the systick counting variable and load the increment
 *	value to the lwIP timer handler
 *  @return Void.
 */
void SysTickIntHandler(void)
{
	sysTickCount++;
    //
    // Call the lwIP timer handler.
    //
    lwIPTimer(SYSTICKMS);
}

/** @brief Start a timeout process
 *
 *	Pointer is used to provide the function access to the argument's address, thus
 *	making it able to change the variable's value.
 *
 *  @param *input The pointer to the unsigned long variable holding the starting time value
 *  @return Void.
 */
void timeOutSet(unsigned long * input)
{
	*input = sysTickCount;
}

/** @brief Check if timeout happened
 *
 *  @return boolean on whether the timeout has happened on a designated variable
 */
uint8_t timeIsOut(unsigned long input, unsigned int timeInterval)
{
	if ((unsigned long) (sysTickCount - input) >= timeInterval)
		return 1;
	else
		return 0;
}

