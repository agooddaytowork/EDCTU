/*
 * configs.c
 *
 *  Created on: Jul 15, 2015
 *      Author: Dinh
 */

#include "configs.h"

uint32_t g_ui32SysClock;
warehouseData thisWarehouse;
faultData currentFault;
uint8_t systemConfig = 0;

volatile uint8_t retries = 0;
volatile uint16_t drops = 0;

void increaseRetries()
{
	if (retries >= MAX_RETRIES)
	{
		retries = MAX_RETRIES;
	}
	else
	{
		retries++;
	}
}

void increaseDrops()
{
	if (drops >= MAX_DROPS)
	{
		drops = MAX_DROPS;
	}
	else
	{
		drops++;
	}
}

uint16_t getDrops()
{
	return drops;
}

void loadToDrop(uint16_t input)
{
	drops = input;
}
