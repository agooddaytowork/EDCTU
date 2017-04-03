#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "driverlib/can.h"
#include "inc/hw_can.h"

#include "configs/configs.h"
#include "Ethernet/Ethernet.h"
#include "wrappedCAN/wrappedCAN.h"
#include "GPfunctions/GPfunctions.h"
#include "wrappedWDT/wrappedWDT.h"

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif


int main(void)
	{
	peripheralSetup();

	warehouseSetup();

	CANMessageClear(CAN0_BASE, 8);
	CANMessageClear(CAN0_BASE, 9);

	OLEDsinglePrint("Waiting for IP");
	// Wait for the IP to be available
	while (!(ethernetStatus & IP_ACQUIRED))
		;
	setCursor(0,0);
	updateOLEDSDCSList();
	InitWatchDogTimer();
	mainLoop();
}
