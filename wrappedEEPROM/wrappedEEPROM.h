/*
 * wrappedEEPROM.h
 *
 *  Created on: Aug 25, 2015
 *      Author: Dinh
 */

#ifndef COINHUTAODACHET_WRAPPEDEEPROM_WRAPPEDEEPROM_H_
#define COINHUTAODACHET_WRAPPEDEEPROM_WRAPPEDEEPROM_H_

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "driverlib/eeprom.h"
#include "driverlib/sysctl.h"
#include "../configs/configs.h"

void setupEEPROM();
void loadDropToEEPROM(uint16_t dropToLoad);
uint16_t getEEPROMDrop();
void loadDataToEEPROM();
void getEEPROMdata();

#endif /* COINHUTAODACHET_WRAPPEDEEPROM_WRAPPEDEEPROM_H_ */
