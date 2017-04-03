/*
 * dataProcessing.h
 *
 *  Created on: Jul 27, 2015
 *      Author: Dinh
 */

 /* This helps process data stored in the thisWarehouse struct
 * - Detection of duplicated addresses
 * - Detection of misconfigured SDCS
 * - Detection of gauge and gauge number
 */

#ifndef COINHUTAODACHET_DATAPROCESSING_DATAPROCESSING_H_
#define COINHUTAODACHET_DATAPROCESSING_DATAPROCESSING_H_

#include "../configs/configs.h"
#include "string.h"

extern uint8_t numberOfErrorSDCS;
extern uint8_t listOfErrorSDCS[10];

void resetData();
uint8_t noDuplicatedAddress();
uint8_t allConfigMatched();

uint8_t getIndexByAddressGauge(uint8_t address);
void resetErrorSDCS();
void addToErrorSDCS(uint8_t address);
uint8_t populateGaugeList();
uint8_t addressDuplicated(uint8_t address);
void populateUnmatchedConfig();
uint8_t presentInErrorList(uint8_t data);
void populateDuplicatedAddress();

/*
 * For faults
 */

#endif /* COINHUTAODACHET_DATAPROCESSING_DATAPROCESSING_H_ */
