/*
 * wrappedWDT.c
 *
 *  Created on: Sep 6, 2015
 *      Author: Dinh
 */


#include "wrappedWDT.h"

volatile uint8_t dogIsFed = 0;

void watchDogHandler(void)
{
	if (dogIsFed == 1)
	{
		dogIsFed = 0;
		MAP_WatchdogIntClear(WATCHDOG0_BASE);
	}
	else
	{
		//SysCtlReset();
	}
	return;
}

void InitWatchDogTimer()
{
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_WDOG0);

	MAP_WatchdogIntClear(WATCHDOG0_BASE);

	MAP_IntMasterEnable();
	MAP_IntEnable(INT_WATCHDOG);
	MAP_WatchdogReloadSet(WATCHDOG0_BASE, g_ui32SysClock*30);
	MAP_IntPrioritySet(INT_WATCHDOG, 0);
	MAP_WatchdogResetEnable(WATCHDOG0_BASE);
	MAP_WatchdogEnable(WATCHDOG0_BASE);
}

void kickTheDog(uint8_t seconds)
{
	MAP_WatchdogReloadSet(WATCHDOG0_BASE, g_ui32SysClock*seconds);
}

void feedTheDog()
{
	dogIsFed = 1;
}
