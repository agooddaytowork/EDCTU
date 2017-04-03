/*
 * faultProcessing.c
 *
 *  Created on: Aug 11, 2015
 *      Author: Dinh
 */

#include "faultProcessing.h"

/** @brief Reset the currentFault structure
 *
 *  @return Void.
 */
void resetFault()
{
	memset(&currentFault,0,sizeof(currentFault));
}

/** @brief add an SDCS to the fault list
 *
 *  This function is called when a SDCS cannot be reached in a CAN query
 *
 *  @param address The address of the inputteed SDCS
 *  @return Void.
 */
void addToFaultSDCS(uint8_t inputAddress)
{
	currentFault.faultSDCSList[currentFault.faultSDCSNum].address = inputAddress;
	currentFault.faultSDCSList[currentFault.faultSDCSNum].faultStationNum = 0;
	currentFault.faultSDCSNum++;
}

/** @brief Add an SDCS and its faulty stations to the fault list
 *
 *	This function is called when a SDCS can be reached,
 *	Faulty stations are added to the list for fault reporting
 *	and reference.
 *
 *	If no station is faulty, this function returns immediately.
 *
 *  @param address the address of the inputted SDCS
 *  @param inputState the 8-bit indicator of which stations are faulty
 *  @return Void.
 */
void addToFaultStation(uint8_t inputAddress, uint8_t inputState)
{
	uint8_t currentFaultStation = 0;
	if (inputState == 0)
	{
		return;
	}
	else
	{
		// Add the SDCS to the fault list
		currentFault.faultSDCSList[currentFault.faultSDCSNum].address = inputAddress;
		currentFault.faultSDCSList[currentFault.faultSDCSNum].faultStationNum = 0;
		while (currentFaultStation < 6)
		{
			//Check whether the fault is present
			if (inputState & 0x01)
			{
				currentFault.faultSDCSList[currentFault.faultSDCSNum].faultStationList[currentFault.faultSDCSList[currentFault.faultSDCSNum].faultStationNum] =
						currentFaultStation + 1;
				currentFault.faultSDCSList[currentFault.faultSDCSNum].faultStationNum++;
			}
			//Shift the stats byte to the right to observe the next bit of the SDCS status
			inputState = inputState >> 1;
			currentFaultStation++;
		}
	}
}
