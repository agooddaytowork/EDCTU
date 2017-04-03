/*
 * OLEDmenu.c
 *
 *  Created on: Jul 25, 2015
 *      Author: Dinh
 */

/*
 * This helps with creating configuration menus, each function
 * represents a menu and returns the value of the selected option.
 */

#include "OLEDmenu.h"

volatile uint8_t autoSetup = 0;

/*
 * The wrapped function, call THIS
 */
uint8_t configMenu()
{
	uint8_t configParameter = 0;
	while (1)
	{
		if (pumpNumberConfig())
		{
			configParameter |= TWO_PUMPS;
		}
		else
		{
			if (autoSetup)
			{
				//configParameter = getEEPROMConfig();
				configParameter = 0;
				return configParameter;
			}
			else
				configParameter &= ~TWO_PUMPS;
		}

		if (RFIDConfig())
		{
			configParameter |= NO_RFID;
		}
		else
		{
			configParameter &= ~NO_RFID;
		}

		if (confirmConfig(configParameter))
		{
			continue;
		}
		else
		{
			OLEDsinglePrint("Scanning...");
			return configParameter;
		}
	}
}

uint8_t retryOrResetMenu()
{
	uint8_t selectedOption = 0;
	OLEDclear(0, 0, 128, 64);
	setCursor(0, 0);
	OLEDprint("What to do?");
	setCursor(10, 1);
	OLEDprint("Retry");
	setCursor(10, 2);
	OLEDprint("Reset");
	setCursor(0, 1);
	drawArrow();
	clearButtonBuffer();
	while (1)
	{
		while (!buttonPressed())
			;
		if (getButton() == 1)
		{
			selectedOption ^= 1;
			if (selectedOption == 0)
			{
				OLEDclear(0, 16, 8, 8);
				setCursor(0, 1);
				drawArrow();
			}
			else
			{
				OLEDclear(0, 8, 8, 8);
				setCursor(0, 2);
				drawArrow();
			}
		}
		else
		{
			return selectedOption;
		}
	}
}

uint8_t pumpNumberConfig()
{
	uint8_t selectedOption = 0;
	unsigned long time = 0;
	OLEDclear(0, 0, 128, 64);
	setCursor(0, 0);
	OLEDprint("Number of pumps");
	setCursor(10, 1);
	OLEDprint("1 pump");
	setCursor(10, 2);
	OLEDprint("2 pumps");
	setCursor(0, 1);
	drawArrow();
	clearButtonBuffer();
	timeOutSet(&time);
	while (1)
	{
		if (buttonPressed())
		{
			timeOutSet(&time);
			if (getButton() == 1)
			{
				selectedOption ^= 1;
				if (selectedOption == 0)
				{
					OLEDclear(0, 16, 8, 8);
					setCursor(0, 1);
					drawArrow();
				}
				else
				{
					OLEDclear(0, 8, 8, 8);
					setCursor(0, 2);
					drawArrow();
				}
			}
			else
			{
				return selectedOption;
			}
		}
		else if (timeIsOut(time,MENU_TIMEOUT))
		{
			autoSetup = 1;
			return 0;
		}
	}
}

uint8_t RFIDConfig()
{
	uint8_t selectedOption = 0;
	OLEDclear(0, 0, 128, 64);
	setCursor(0, 0);
	OLEDprint("RFID");
	setCursor(10, 1);
	OLEDprint("With RFID");
	setCursor(10, 2);
	OLEDprint("Without RFID");
	setCursor(0, 1);
	drawArrow();
	clearButtonBuffer();
	while (1)
	{
		while (!buttonPressed())
			;
		if (getButton() == 1)
		{
			selectedOption ^= 1;
			if (selectedOption == 0)
			{
				OLEDclear(0, 16, 8, 8);
				setCursor(0, 1);
				drawArrow();
			}
			else
			{
				OLEDclear(0, 8, 8, 8);
				setCursor(0, 2);
				drawArrow();
			}
		}
		else
		{
			return selectedOption;
		}
	}
}

uint8_t confirmConfig(uint8_t configVariable)
{
	uint8_t selectedOption = 0;
	OLEDclear(0, 0, 128, 64);
	setCursor(0, 0);
	clearButtonBuffer();

	switch (configVariable)
	{
	case TWO_PUMPS + NO_RFID:
		OLEDprint("2 pumps, no RFID");
		break;
	case NO_RFID:
		OLEDprint("1 pump, no RFID");
		break;
	case TWO_PUMPS:
		OLEDprint("2 pumps, with RFID");
		break;
	case 0:
		OLEDprint("1 pump, with RFID");
		break;
	default:
		OLEDprint("Error, this line should never be reached");
		break;
	}

	setCursor(10, 1);
	OLEDprint("Confirm");
	setCursor(10, 2);
	OLEDprint("Reset");
	setCursor(0, 1);
	drawArrow();
	while (1)
	{
		while (!buttonPressed())
			;
		if (getButton() == 1)
		{
			selectedOption ^= 1;
			if (selectedOption == 0)
			{
				OLEDclear(0, 16, 8, 8);
				setCursor(0, 1);
				drawArrow();
			}
			else
			{
				OLEDclear(0, 8, 8, 8);
				setCursor(0, 2);
				drawArrow();
			}
		}
		else
		{
			return selectedOption;
		}
	}
}
