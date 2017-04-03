/*
 * wrappedEEPROM.c
 *
 *  Created on: Aug 25, 2015
 *      Author: Dinh
 */

#include "wrappedEEPROM.h"

void setupEEPROM()
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);
	EEPROMInit();
}

void loadDropToEEPROM(uint16_t dropToLoad)
{
	uint32_t foobar = dropToLoad;
	EEPROMProgram(&foobar,0,4);
}

uint16_t getEEPROMDrop()
{
	uint32_t foobar = 0;
	EEPROMRead(&foobar,0,4);
	return (uint16_t) foobar;
}

void loadDataToEEPROM()
{
	EEPROMProgram((uint32_t *) &thisWarehouse,0x04,sizeof(thisWarehouse));
}

void getEEPROMdata()
{
	warehouseData dummyData;
	EEPROMRead((uint32_t *)&dummyData,0x04,sizeof(dummyData));
	memcpy(&thisWarehouse, &dummyData, sizeof(dummyData));
}
