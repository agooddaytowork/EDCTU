/*
 * faultProcessing.h
 *
 *  Created on: Aug 11, 2015
 *      Author: Dinh
 */

#ifndef COINHUTAODACHET_DATAPROCESSING_FAULTPROCESSING_H_
#define COINHUTAODACHET_DATAPROCESSING_FAULTPROCESSING_H_

#include "datatypes.h"
#include "../configs/configs.h"
#include "string.h"

void resetFault();
void addToFaultSDCS(uint8_t inputAddress);
void addToFaultStation(uint8_t inputAddress, uint8_t inputState);

#endif /* COINHUTAODACHET_DATAPROCESSING_FAULTPROCESSING_H_ */
