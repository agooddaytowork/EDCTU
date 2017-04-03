/*
 * GPfunctions.c
 *
 *  Created on: Jul 28, 2015
 *      Author: Dinh
 */

#include "GPfunctions.h"

uint8_t TempSDCSList[6];

uint16_t success = 0;

uint8_t count = 0;
uint8_t sent = 0;

/** @brief Update the list of the discovered SDCS's address
 *
 * Added gauge display from Sep 20th 2015
 *
 *  @return Void.
 */

void updateOLEDSDCSList()
{
	uint8_t counter = 0;
	setCursor(0,0);
	char a[10];
	OLEDclear(0, 0, 128, 56);
	for (counter = 0; counter < thisWarehouse.SDCSnum; counter++)
	{
		setCursor((15 * counter) + 5, 0);
		sprintf(a, "%d", thisWarehouse.SDCSDataList[counter].address);
		OLEDprint(a);
		if (thisWarehouse.SDCSDataList[counter].status & HAS_GAUGE)
		{
			setCursor((15 * counter) + 5, 3);
			OLEDprint("G");
		}
	}
}

/** @brief Update the status of the SDCS list on the OLED
 *
 *  @return Void.
 */

void updateOLEDSDCSStatus()
{
	uint8_t counter = 0;
	for (counter = 0; counter < thisWarehouse.SDCSnum; counter++)
	{
		setCursor((15 * counter) + 3, 1);
		if (CANstatus & BROKEN)
		{
			drawSDCSunreachable();
		}
		else
		{

			if (thisWarehouse.SDCSDataList[counter].status & CANNOT_REACH)
			{
				drawSDCSunreachable();
			}
			else
			{
				drawSDCSOK();
			}
		}
	}
}

/** @brief Update OLED icons
 *
 *	These icons represent the working status of the EDCTU and
 *	the fault state of the system
 *	CAN - Internet - Thingspeak availability
 *
 *	added later: updating of the status of the SDCS in the system
 *
 *  @return Void.
 */

void updateOLEDicons()
{
	updateOLEDSDCSStatus();
	if (CANstatus & BROKEN)
	{
		deleteCAN();
	}
	else
	{
		drawCAN();
	}

	if (ethernetStatus & IP_ACQUIRED)
	{
		drawLAN();
		if (ethernetStatus & THINGSPEAK_UNREACHABLE)
		{
			deleteTS();
		}
		else
		{
			drawTS();
		}
	}
	else
	{
		deleteLAN();
		deleteTS();
	}

}

/** @brief Swap the 2 SDCSes
 *
 *  @return Void.
 */
void swapSDCS(uint8_t SDCSOnePosition, uint8_t SDCSTwoPosition)
{
	SDCSData dummy;
	memcpy(&dummy, &(thisWarehouse.SDCSDataList[SDCSOnePosition]),
			sizeof(SDCSData));
	memcpy(&(thisWarehouse.SDCSDataList[SDCSOnePosition]),
			&(thisWarehouse.SDCSDataList[SDCSTwoPosition]), sizeof(SDCSData));
	memcpy(&(thisWarehouse.SDCSDataList[SDCSTwoPosition]), &dummy,
			sizeof(SDCSData));
}

/** @brief Sort the SDCS list using the addresses
 *
 *	Bubble sort the SDCS list to ensure position unity
 *
 *  @return Void.
 */

void sortSDCSList()
{
	int countingVariable = thisWarehouse.SDCSnum - 2;
	int tempLimit = countingVariable + 1;
	if (countingVariable < 0)
	{
		return;
	}
	else
	{
		for (tempLimit = countingVariable + 1; tempLimit > 0; tempLimit--)
		{
			for (countingVariable = 0; countingVariable < tempLimit;
					countingVariable++)
			{
				if (thisWarehouse.SDCSDataList[countingVariable].address
						> thisWarehouse.SDCSDataList[countingVariable + 1].address)
				{
					swapSDCS(countingVariable, countingVariable + 1);
				}
			}
		}
	}
}

/** @brief Set up the peripherals needed for the operation of the EDCTU
 *
 *  @return Void.
 */

void peripheralSetup()
{
	SysCtlMOSCConfigSet(SYSCTL_MOSC_HIGHFREQ);

// Run from the PLL at 120 MHz.
	g_ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
	SYSCTL_OSC_MAIN |
	SYSCTL_USE_PLL |
	SYSCTL_CFG_VCO_480), 120000000);

	SysCtlDelay(1000000);
// Configure the device pins.
	PinoutSet(true, false);

#ifdef DEBUG_PRINT_UART

	// Configure UART.

	UARTStdioConfig(2, 115200, g_ui32SysClock);
	UARTprintf(
			"KLA Tencor Warehouse Monitoring System\nEmbedded Data Collection and Transfer Unit\n\n");
#endif

// Delay for stability
	SysCtlDelay(5000000);

// Initialize the SysTick and SysTick interrupt
	sysTickInit();

// Initialize OLED
	OLEDbegin();

// Initialize Ethernet
	EthernetInit();

	if (OLEDbroken)
	{
#ifdef DEBUG_PRINT_UART
		UARTprintf(
				"\nCannot connect to the OLED, please check if the OLED is connected.\n");
#endif
	}
	else
	{
#ifdef DEBUG_PRINT_UART
		UARTprintf("\nOLED found, no problem is detected\n");
#endif
	}

	/*
	 * Setting up CAN
	 */
	CANSetup();
	CANMessageObjectsSetup();

	SWInit();
	setupEEPROM();

}

/** @brief Set up the warehouse
 *
 *	Includes OLED menus that return on timeout or option selection
 *  @return Void.
 */

void warehouseSetup()
{
	char abc[100];
	char xyz[100];
	int i = 0;

	while (1)
	{
		if ((SysCtlResetCauseGet() & (SYSCTL_CAUSE_POR | SYSCTL_CAUSE_EXT)))
		{
			systemConfig = configMenu();
		}
		else
		{
			OLEDclear(0, 0, 128, 64);
			autoSetup = 2;
		}
		SysCtlResetCauseClear(SysCtlResetCauseGet());

		if (autoSetup == 0)
		{
			//loadConfigToEEPROM(systemConfig);

			while (1)
			{
				CANGetPresence();
				if (CANstatus & BROKEN)
				{
					OLEDsinglePrint("CAN error, press any key to retry");
					clearButtonBuffer();
					while (!buttonPressed())
						;
					resetData();
					OLEDsinglePrint("RETRY");
					continue;
				}
				else
				{
					if (thisWarehouse.SDCSnum == 0)
					{
						OLEDsinglePrint("Did not find any SDCS");
						while (!buttonPressed())
							;
						resetData();
						if (retryOrResetMenu())
						{
							// Reset
							break;
						}
						else
						{
							// Retry
							continue;
						}
					}
					else if (thisWarehouse.SDCSnum > 6)
					{
						OLEDsinglePrint("Number of SDCS larger than 6");
						while (!buttonPressed())
							;
						resetData();
						if (retryOrResetMenu())
						{
							// Reset
							break;
						}
						else
						{
							// Retry
							continue;
						}
					}
					else
					{
						// Check for duplicated address, this part is mandatory
						// if a faul-free data acquisition session is to be run
						if (!noDuplicatedAddress())
						{
							OLEDclear(0, 0, 128, 64);
							sprintf(abc, "There are %d duplicated addresses: ",
									numberOfErrorSDCS);
							i = 0;
							while (i < numberOfErrorSDCS)
							{
								sprintf(xyz, "%d ", listOfErrorSDCS[i]);
								strcat(abc, xyz);
								i++;
							}
							OLEDprintwrap(abc);

							clearButtonBuffer();
							while (!buttonPressed())
								;
							resetData();
							if (retryOrResetMenu())
							{
								// Reset
								break;
							}
							else
							{
								// Retry
								continue;
							}
						}
						// Check for misconfigured SDCS's
						// this part can only run correctly if the SDCS was able to detect
						// a misconfigured option inside its array of connection jacks
						else if (!allConfigMatched())
						{
							OLEDclear(0, 0, 128, 64);
							sprintf(abc, "There are %d misconfigured SDCS: ",
									numberOfErrorSDCS);
							i = 0;
							while (i < numberOfErrorSDCS)
							{
								sprintf(xyz, "%d ", listOfErrorSDCS[i]);
								strcat(abc, xyz);
								i++;
							}
							OLEDprintwrap(abc);
							clearButtonBuffer();
							while (!buttonPressed())
								;
							resetData();
							if (retryOrResetMenu())
							{
								// Reset
								break;
							}
							else
							{
								// Retry
								continue;
							}
						}
						else
						{
							// Bubble sort the SDCS list inside the data structure
							// This part is needed for mutual agreement between the EDCTU and the online database
							sortSDCSList();
							if (!populateGaugeList())
							{
								OLEDsinglePrint(
										"The number of gauges is larger than 3");
								clearButtonBuffer();
								while (!buttonPressed())
									;
								resetData();
								if (retryOrResetMenu())
								{
									// Reset
									break;
								}
								else
								{
									// Retry
									continue;
								}
							}
							OLEDclear(0, 0, 128, 64);
							memset(abc, 0, sizeof(abc));
							sprintf(abc, "Found %d SDCS: ",
									thisWarehouse.SDCSnum);

							i = 0;
							while (i < thisWarehouse.SDCSnum)
							{
								sprintf(xyz, "%d ",
										thisWarehouse.SDCSDataList[i].address);
								strcat(abc, xyz);
								i++;
							}
							OLEDprintwrap(abc);
							clearButtonBuffer();

							while (!buttonPressed())
								;
							OLEDsinglePrint("Saving data");
							loadDataToEEPROM();
							return;
						}
					}
				}

			}
		}
		else
		{
			getEEPROMdata();
			return;
		}
	}
}

/** @brief The main loop
 *
 *  @return Void.
 */
void mainLoop()
{
	volatile int status = 0;
	unsigned long timeKeeper = 0;
	unsigned long resetTimeKeeper = 0;
	unsigned long delayTime = 0;
	unsigned long OLEDResetTime = 0;
	uint8_t OledDoReset = 0;
	if (autoSetup == 2)
	{
		loadToDrop(getEEPROMDrop());
	}
	else
	{
		loadToDrop(0);
	}
	sent = 1;
	while (1)
	{
		if (timeIsOut(OLEDResetTime, 6000))
		{
			timeOutSet(&OLEDResetTime);
			OLEDreset();
			OledDoReset = 1;
			//updateOLEDSDCSList();
		}

		if(OledDoReset == 0)
		updateOLEDicons();

		if(buttonPressed())
		{

			updateOLEDSDCSList();
			updateOLEDicons();
			clearButtonBuffer();
		}
		feedTheDog();

		if (timeIsOut(resetTimeKeeper, RESET_INTERVAL))
		{
			loadDropToEEPROM(getDrops());
			SysCtlReset();
		}

		if (timeIsOut(timeKeeper, SAMPLING_INTERVAL))
		{
#ifdef DEBUG_PRINT_UART
			UARTprintf("Fetching data\n");
#endif
			if (!sent)
			{
				increaseDrops();
			}
			sent = 0;
			retries = 0;

			timeOutSet(&timeKeeper);
			resetFault();
			for (count = 0; count < thisWarehouse.SDCSnum; count++)
			{
				status = CANGetSDCSData(count);
				if (status)
				{
					thisWarehouse.SDCSDataList[count].status &= ~CANNOT_REACH;
#ifdef DEBUG_PRINT_UART
					UARTprintf("Ngon\n");
#endif
				}
				else
				{
					if (CANstatus & BROKEN)
					{
						//OLEDsinglePrint("Broken CAN");
					}
					else
					{
						thisWarehouse.SDCSDataList[count].status |=
						CANNOT_REACH;
						addToFaultSDCS(
								thisWarehouse.SDCSDataList[count].address);
					}
				}
				timeOutSet(&delayTime);
				while (!timeIsOut(delayTime, 10))
					;
			}
		}

		/*
		 * Internet thingy
		 */
		if ((!(ethernetStatus & THINGSPEAK_CONNECTED))
				&& (ethernetStatus & IP_ACQUIRED) && (!sent))
		{
			if (connectToThingspeak())
			{
				ethernetStatus &= ~THINGSPEAK_UNREACHABLE;
				if (sendDataToThingSpeak())
				{
#ifdef DEBUG_PRINT_UART
					UARTprintf("Data uploaded successfully\n");
#endif
					timeOutSet(&resetTimeKeeper);
					sent = 1;
					retries = 0;
					drops = 0;
				}
				else
				{
#ifdef DEBUG_PRINT_UART
					UARTprintf("Data uploading failed\n");
#endif
					if (ethernetStatus & THINGSPEAK_CONNECTED)
					{
						increaseRetries();
						closeConnectionManually();
					}
				}
			}
			else
			{
#ifdef DEBUG_PRINT_UART
				UARTprintf("Connect failed\n");
#endif
				ethernetStatus |= THINGSPEAK_UNREACHABLE;
				closeConnectionManually();
				increaseRetries();
			}
		}
		else if ((thingspeakpcb != NULL)
				&& (thingspeakpcb->state == ESTABLISHED))
		{
			closeConnectionManually();
		}
	}
}
