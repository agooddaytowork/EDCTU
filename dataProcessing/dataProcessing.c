/*
 * dataProcessing.c
 *
 *  Created on: Jul 27, 2015
 *      Author: Dinh
 */

/*
 * This helps process data stored in the thisWarehouse struct
 * - Detection of duplicated addresses
 * - Detection of misconfigured SDCS
 * - Detection of gauge and gauge number
 */

#include "dataProcessing.h"

uint8_t numberOfErrorSDCS = 0;
uint8_t listOfErrorSDCS[10] = {0,0,0,0,0,0,0,0,0,0};

/** @brief Zero initialize the thisWarehouse data structure
 *
 *  @return Void.
 */

void resetData()
{
	memset(&thisWarehouse, 0, sizeof(thisWarehouse));
}

/** @brief Populate the gauge list in the thisWarehouse struct
 *         based on the data already present in the SDCS list
 *
 *  @return boolean on whether the number of gauges is below 3 (valid)
 */

uint8_t populateGaugeList()
{
	uint8_t gaugeCount = 0;
	uint8_t i = 0;
	while (i < thisWarehouse.SDCSnum)
	{
		if (thisWarehouse.SDCSDataList[i].status & HAS_GAUGE)
		{
			thisWarehouse.gaugeDataList[gaugeCount].address = thisWarehouse.SDCSDataList[i].address;
			addToErrorSDCS(thisWarehouse.SDCSDataList[i].address);
			gaugeCount++;
		}
		i++;
	}
	if (gaugeCount > 3)
		return 0;
	else
	{
		thisWarehouse.gaugeNum = gaugeCount;
		return 1;
	}
}

/** @brief Check if all the SDCS's configurations are compatible
 *
 *	The data used is also stored in the thisWarehouse struct
 *
 *  @return boolean on whether the configs match
 */

uint8_t allConfigMatched()
{
	populateUnmatchedConfig();
	if (numberOfErrorSDCS == 0)
		return 1;
	else
		return 0;
}


/** @brief Check if there is any duplicated address in the CAN bus
 *
 *  @return boolean on whether no duplicated address is found (which is valid)
 */
uint8_t noDuplicatedAddress()
{
	populateDuplicatedAddress();
	if (numberOfErrorSDCS == 0)
		return 1;
	else
		return 0;
}

/** @brief Find the numerical index of a gauge when its SDCS address is known
 *
 *  @return the numerical index of the addressed gauge
 */
uint8_t getIndexByAddressGauge(uint8_t address)
{
	int i = 0;
	for (i = 0; i < 3; i++)
	{
		if (thisWarehouse.gaugeDataList[i].address == address)
		{
			return i;
		}
	}
	return 4;
}


/** @brief Populate the unmatched configs into the Error SDCS array
 *
 * For showing on the OLED display only, this will generate a blocking menu waiting for
 * the authorized person to check.
 *  @return Void.
 */
void populateUnmatchedConfig()
{
	uint8_t i = 0;
	resetErrorSDCS();
	while (i < thisWarehouse.SDCSnum)
	{
		if (!(thisWarehouse.SDCSDataList[i].status & CONFIG_VALID))
		{
			addToErrorSDCS(thisWarehouse.SDCSDataList[i].address);
		}
		i++;
	}
}

/** @brief Populate the duplicated addresses into the ErrorSDCS array
 *
 * For showing on the OLED display only, this will generate a blocking menu waiting for
 * the authorized person to check.
 *  @return Void.
 */
void populateDuplicatedAddress()
{
	uint8_t i = 0;
	resetErrorSDCS();
	while (i < thisWarehouse.SDCSnum)
	{
		if (addressDuplicated(thisWarehouse.SDCSDataList[i].address))
		{
			if (!presentInErrorList(thisWarehouse.SDCSDataList[i].address))
			{
				addToErrorSDCS(thisWarehouse.SDCSDataList[i].address);
			}
		}
		i++;
	}
}

/** @brief Check if an address is already in the error list
 *
 *  @param data the inputted SDCS address
 *  @return boolean on whether the address is already in the error list
 */
uint8_t presentInErrorList(uint8_t data)
{
	uint8_t i = 0;
	while (i < numberOfErrorSDCS)
	{
		if (listOfErrorSDCS[i] == data)
		{
			return 1;
		}
		i++;
	}
	return 0;
}

/** @brief Check if an address is duplicated in the SDCS list of the thisWarehouse struct
 *
 *  @param address the address of the queried SDCS
 *  @return boolean on whether another SDCS with a similar address is present in the list.
 */
uint8_t addressDuplicated(uint8_t address)
{
	uint8_t match = 0;
	uint8_t i = 0;
	while (i < thisWarehouse.SDCSnum)
	{
		if (thisWarehouse.SDCSDataList[i].address == address)
		{
			match++;
		}
		i++;
	}
	if (match > 1)
		return 1;
	else
		return 0;
}

/** @brief Reset the error SDCS list
 *
 *  @return Void.
 */
void resetErrorSDCS()
{
	memset(listOfErrorSDCS, 0, sizeof(listOfErrorSDCS));
	numberOfErrorSDCS = 0;
}

/** @brief Add an SDCS to the error list
 *
 *  @param address the address of the inputteed SDCS
 *  @return Void.
 */
void addToErrorSDCS(uint8_t address)
{
	listOfErrorSDCS[numberOfErrorSDCS] = address;
	numberOfErrorSDCS++;
}

