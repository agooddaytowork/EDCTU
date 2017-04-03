/*
 * wrappedRTC.c
 *
 *  Created on: Aug 1, 2015
 *      Author: Dinh
 */

#include "wrappedRTC.h"

void setUpRTC()
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_HIBERNATE);
	HibernateEnableExpClk(SysCtlClockGet());

	HibernateClockConfig(HIBERNATE_OSC_LOWDRIVE);
	HibernateRTCEnable();

	HibernateRTCSet(0);

	HibernateCounterMode(HIBERNATE_COUNTER_24HR);
}
