/*
 * configs.h
 *
 *  Created on: Jul 15, 2015
 *      Author: Dinh
 */

#ifndef COINHUTAODACHET_CONFIGS_CONFIGS_H_
#define COINHUTAODACHET_CONFIGS_CONFIGS_H_

//#define DEBUG_PRINT_UART

#include <stdbool.h>
#include <stdint.h>
#include "datatypes.h"

#define TWO_PUMPS 	0b00000001
#define NO_RFID 	0b00000010

#define MAX_RETRIES 99
#define MAX_DROPS	9999

extern uint32_t g_ui32SysClock;
extern warehouseData thisWarehouse;
extern faultData currentFault;
extern uint8_t systemConfig;

extern volatile uint8_t retries;
extern volatile uint16_t drops;

void increaseRetries();
void increaseDrops();
uint16_t getDrops();
void loadToDrop(uint16_t input);

#endif /* COINHUTAODACHET_CONFIGS_CONFIGS_H_ */
