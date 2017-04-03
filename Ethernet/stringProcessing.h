/*
 * stringProcessing.h
 *
 *  Created on: Aug 6, 2015
 *      Author: Dinh
 */

#ifndef COINHUTAODACHET_ETHERNET_STRINGPROCESSING_H_
#define COINHUTAODACHET_ETHERNET_STRINGPROCESSING_H_

#include "Ethernet.h"
#include "../Systick/Systick.h"
#include "stdint.h"
#include "../configs/configs.h"
#include "../wrappedCAN/wrappedCAN.h"

#define INFO_RETRY_START 178
#define INFO_DROP_START 185

#define ERROR_POSITION 5
#define FAULT_BEGIN 6
#define FAULT_END 167
#define SINGLE_FAULT_LENGTH 26
#define FAULT_SDCS_ADDRESS_OFFSET 11
#define FAULT_STATION_ADDRESS_OFFSET 18

#define DATA_ADDRESS_BEGIN_WITH_OFFSET 243
#define DATA_BEGIN_WITH_OFFSET 256
#define DATA_SDCS_LENGTH 266
#define DATA_STATION_LENGTH 42
#define DATA_END 1830
#define DATA_RFID_OFFSET_FROM_PUMP 18

#define GAUGE_ADDRESS_START 201
#define GAUGE_VALUE_START 213

#define MAC_START 1840

extern unsigned char httpRequestString[1867];

void populateString();
uint8_t sendDataToThingSpeak();

void updateMAC(uint8_t * MAC_address);

void updateRetry(uint8_t numOfRetries);
void updateDrops(uint16_t numOfDrops);

void changeError(uint8_t input);
void clearFault();
void clearSingleFault(uint8_t input);
void updateFaultSDCSAddress(uint8_t position, uint8_t address);
void updateFaultStationAddress(uint8_t SDCSposition, uint8_t *dataSource, uint8_t numberOfStation);

void updateSDCSDataAddress(uint8_t position, uint8_t address);
void updateStationDataSingle(uint8_t SDCSposition, uint8_t stationPosition, uint32_t data);
void updateStationDataDual(uint8_t SDCSposition, uint8_t stationPosition, uint32_t data, uint32_t second_data);
void removeRFID(uint8_t SDCSposition, uint8_t stationPosition);
void updateRFIDInStation(uint8_t SDCSposition, uint8_t stationPosition, uint8_t* RFIDinput);
void removeSDCS(uint8_t numberOfSDCS);
void removeStationFromSDCS(uint8_t SDCSposition, uint8_t numberOfStations);

void deleteGauge(uint8_t numOfGauges);
void updateGaugeAddress(uint8_t addressOne, uint8_t addressTwo, uint8_t addressThree);
void updateGaugeData(uint16_t dataOne, uint16_t dataTwo, uint16_t dataThree);

void resetDecode();
uint8_t decDecode(uint8_t input);

void loadBody();
void loadEnding();
void printBody();
void printEnding();

#endif /* COINHUTAODACHET_ETHERNET_STRINGPROCESSING_H_ */
