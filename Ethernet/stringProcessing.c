/*
 * stringProcessing.c
 *
 *  Created on: Aug 6, 2015
 *      Author: Dinh
 */

#include "stringProcessing.h"

unsigned char originalString[1867] =
		"{\"e\":0,\"f\":[{\"a\":1,\"u\":[1,2,3,4,5,6]},{\"a\":2,\"u\":[1,2,3,4,5,6]},{\"a\":3,\"u\":[1,2,3,4,5,6]},{\"a\":4,\"u\":[1,2,3,4,5,6]},{\"a\":5,\"u\":[1,2,3,4,5,6]},{\"a\":6,\"u\":[1,2,3,4,5,6]}],\"i\":{\"r\":10,\"d\":1000},\"g\":{\"a\":[1,2,3],\"p\":[16000,16000,16000]},\"p\":[{\"a\":1,\"d\":[{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]}]},{\"a\":2,\"d\":[{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]}]},{\"a\":3,\"d\":[{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]}]},{\"a\":4,\"d\":[{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]}]},{\"a\":5,\"d\":[{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]}]},{\"a\":6,\"d\":[{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]}]}],\"m\":[255,255,255,255,255,255]} ";
unsigned char httpRequestString[1867] =
		"{\"e\":0,\"f\":[{\"a\":1,\"u\":[1,2,3,4,5,6]},{\"a\":2,\"u\":[1,2,3,4,5,6]},{\"a\":3,\"u\":[1,2,3,4,5,6]},{\"a\":4,\"u\":[1,2,3,4,5,6]},{\"a\":5,\"u\":[1,2,3,4,5,6]},{\"a\":6,\"u\":[1,2,3,4,5,6]}],\"i\":{\"r\":10,\"d\":1000},\"g\":{\"a\":[1,2,3],\"p\":[16000,16000,16000]},\"p\":[{\"a\":1,\"d\":[{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]}]},{\"a\":2,\"d\":[{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]}]},{\"a\":3,\"d\":[{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]}]},{\"a\":4,\"d\":[{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]}]},{\"a\":5,\"d\":[{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]}]},{\"a\":6,\"d\":[{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]},{\"p\":[16000,16000],\"r\":[255,255,255,255]}]}],\"m\":[255,255,255,255,255,255]} ";

uint8_t numberBegin = 0;

uint32_t stringPointer = 0;
char bodyField[256];
char endingField[82];

/** @brief Send the built data to Thingspeak
 *
 *  @return Boolean on whether the TCP transmission was successful
 */
uint8_t sendDataToThingSpeak() {
	unsigned long timeDummy = 0;
	//static uint8_t fakeMAC[6] = {0, 0x1a, 0xb6, 2, 0xbe, 0xb7};
	populateString();
	//updateMAC(fakeMAC);
	stringPointer = 0;

	ethernetStatus &= ~ETHERNET_ERROR;
	ethernetStatus &= ~UPLOAD_SUCCESS;

	EthernetPrint("POST /KTproj/update.php HTTP/1.1 \n");
	EthernetPrint("Host: 119.17.254.105 \n");
	//EthernetPrint("Host: 10.104.97.209\n");
	EthernetPrint("Connection: close\n");
	//EthernetPrint("Connection: keep-alive\r\n");
	//DHDGNJOOOP0666CN : Ho
	//X2KHBHLV9RFY6947: Quang
	EthernetPrint("X-THINGSPEAKAPIKEY: P30OX79S1VO2887G\n");
	EthernetPrint("Content-Type: application/x-www-form-urlencoded\n");
	EthernetPrint("Content-Length: 1929\r\n");
	EthernetPrint("\r\n");

	EthernetPrint("field1=");
	loadBody();
	printBody();
	EthernetPrint("&field2=");
	loadBody();
	printBody();
	EthernetPrint("&field3=");
	loadBody();
	printBody();
	EthernetPrint("&field4=");
	loadBody();
	printBody();
	EthernetPrint("&field5=");
	loadBody();
	printBody();
	EthernetPrint("&field6=");
	loadBody();
	printBody();
	EthernetPrint("&field7=");
	loadBody();
	printBody();
	EthernetPrint("&field8=");
	loadEnding();
	printEnding();
	EthernetPrint("\r\n");
	//CHUA CHAY, VL LAM ANH EM OI
	//return 1;

	// YEU LAI TU DAU
	timeOutSet(&timeDummy);

	while (1) {
		if ((timeIsOut(timeDummy, SEND_TIMEOUT))
				|| (ethernetStatus & ETHERNET_ERROR)) {
			return 0;
		}
		if (!(ethernetStatus & THINGSPEAK_CONNECTED)) {
			if (ethernetStatus & UPLOAD_SUCCESS) {
				return 1;
			} else {
				return 0;
			}
		}
	}

}

/** @brief Populate the string with meaningful data from the thisWarehouse struct
 *
 *  @return Void
 */
void populateString() {
	uint8_t i = 0;
	uint8_t ii = 0;

	//
	memmove(httpRequestString, originalString, 1867);

	// Remove SDCS that are not present
	removeSDCS(6 - thisWarehouse.SDCSnum);

	// Populate the data (pump & RFID)
	for (i = 0; i < thisWarehouse.SDCSnum; i++) {
		updateSDCSDataAddress(i + 1, thisWarehouse.SDCSDataList[i].address);
		removeStationFromSDCS(i + 1,
				6 - (thisWarehouse.SDCSDataList[i].status & 0x0F));
		for (ii = 0; ii < (thisWarehouse.SDCSDataList[i].status & 0x0F); ii++) {
			updateStationDataSingle(i + 1, ii + 1,
					thisWarehouse.SDCSDataList[i].stationDataList[ii].pressureOne);
			if (systemConfig & NO_RFID) {
				removeRFID(i + 1, ii + 1);
			} else {
				updateRFIDInStation(i + 1, ii + 1,
						thisWarehouse.SDCSDataList[i].stationDataList[ii].RFID);
			}
		}
	}

	// Populate data (Gauges)
	updateGaugeAddress(thisWarehouse.gaugeDataList[0].address,
			thisWarehouse.gaugeDataList[1].address,
			thisWarehouse.gaugeDataList[2].address);
	updateGaugeData(thisWarehouse.gaugeDataList[0].pressure,
			thisWarehouse.gaugeDataList[1].pressure,
			thisWarehouse.gaugeDataList[2].pressure);
	deleteGauge(3 - thisWarehouse.gaugeNum);

	// Populate fault
	if (currentFault.faultSDCSNum == 0) {
		clearFault();
	} else {
		clearSingleFault(6 - currentFault.faultSDCSNum);
		for (i = 0; i < currentFault.faultSDCSNum; i++) {
			updateFaultSDCSAddress(i + 1,
					currentFault.faultSDCSList[i].address);
			updateFaultStationAddress(i + 1,
					currentFault.faultSDCSList[i].faultStationList,
					currentFault.faultSDCSList[i].faultStationNum);
		}
	}

	updateDrops(drops);
	updateRetry(retries);

	if (CANstatus & BROKEN) {
		changeError(1);
	} else {
		changeError(0);
	}

	updateMAC(pui8MACArray);

	httpRequestString[1866] = 0;
}

/** @brief Load the 255-byte long body segments
 *
 *  @return Void.
 */
void loadBody() {
	int ii = 0;
	for (ii = 0; ii < 255; ii++) {
		bodyField[ii] = httpRequestString[stringPointer];
		stringPointer++;
	}
	bodyField[255] = 0;
}

/** @brief Load the remaining bytes at the end of the string
 *
 *  @return Void.
 */
void loadEnding() {
	int ii = 0;
	for (ii = 0; ii < 81; ii++) {
		endingField[ii] = httpRequestString[stringPointer];
		stringPointer++;
	}
	endingField[81] = 0;
}

/** @brief Send the 255-byte body
 *
 *  @return Void.
 */
void printBody() {
	Ethernetwrite((const uint8_t *) bodyField, 255);
}

/** @brief Print the remaining bytes
 *
 *  @return Void.
 */
void printEnding() {
	Ethernetwrite((const uint8_t *) endingField, 81);
}

/** @brief Reset the itoa decoder
 *
 *  @return Void.
 */
void resetDecode() {
	numberBegin = 0;
}

/** @brief Simple itoa decoder
 *
 *  @return decoded char.
 */
uint8_t decDecode(uint8_t input) {
	if (input == 0) {
		if (numberBegin) {
			return '0';
		}
		return ' ';
	} else {
		numberBegin = 1;
		return (input + '0');
	}
}

/*
 * FOR MAC
 * MAC ADDRESS
 */

/** @brief Update the MAC address in the HTTP request string
 *
 *	@param *MAC_address Pointer to the first byte in the 6-byte long MAC array
 *
 *  @return Void.
 */

void updateMAC(uint8_t * MAC_address) {
	uint32_t startingPoint = MAC_START;

	resetDecode();
	httpRequestString[startingPoint] = MAC_address[0] / 100;
	httpRequestString[startingPoint + 1] = MAC_address[0] / 10
			- (httpRequestString[startingPoint] * 10);
	httpRequestString[startingPoint + 2] = MAC_address[0]
			- (httpRequestString[startingPoint + 1] * 10)
			- (httpRequestString[startingPoint] * 100);

	httpRequestString[startingPoint] = decDecode(
			httpRequestString[startingPoint]);
	httpRequestString[startingPoint + 1] = decDecode(
			httpRequestString[startingPoint + 1]);
	if (httpRequestString[startingPoint + 2] == 0)
		httpRequestString[startingPoint + 2] = '0';
	else
		httpRequestString[startingPoint + 2] = decDecode(
				httpRequestString[startingPoint + 2]);

	resetDecode();
	httpRequestString[startingPoint + 4] = MAC_address[1] / 100;
	httpRequestString[startingPoint + 5] = MAC_address[1] / 10
			- (httpRequestString[startingPoint + 4] * 10);
	httpRequestString[startingPoint + 6] = MAC_address[1]
			- (httpRequestString[startingPoint + 5] * 10)
			- (httpRequestString[startingPoint + 4] * 100);

	httpRequestString[startingPoint + 4] = decDecode(
			httpRequestString[startingPoint + 4]);
	httpRequestString[startingPoint + 5] = decDecode(
			httpRequestString[startingPoint + 5]);
	if (httpRequestString[startingPoint + 6] == 0)
		httpRequestString[startingPoint + 6] = '0';
	else
		httpRequestString[startingPoint + 6] = decDecode(
				httpRequestString[startingPoint + 6]);

	resetDecode();
	httpRequestString[startingPoint + 8] = MAC_address[2] / 100;
	httpRequestString[startingPoint + 9] = MAC_address[2] / 10
			- (httpRequestString[startingPoint + 8] * 10);
	httpRequestString[startingPoint + 10] = MAC_address[2]
			- (httpRequestString[startingPoint + 9] * 10)
			- (httpRequestString[startingPoint + 8] * 100);

	httpRequestString[startingPoint + 8] = decDecode(
			httpRequestString[startingPoint + 8]);
	httpRequestString[startingPoint + 9] = decDecode(
			httpRequestString[startingPoint + 9]);
	if (httpRequestString[startingPoint + 10] == 0)
		httpRequestString[startingPoint + 10] = '0';
	else
		httpRequestString[startingPoint + 10] = decDecode(
				httpRequestString[startingPoint + 10]);

	resetDecode();
	httpRequestString[startingPoint + 12] = MAC_address[3] / 100;
	httpRequestString[startingPoint + 13] = MAC_address[3] / 10
			- (httpRequestString[startingPoint + 12] * 10);
	httpRequestString[startingPoint + 14] = MAC_address[3]
			- (httpRequestString[startingPoint + 13] * 10)
			- (httpRequestString[startingPoint + 12] * 100);

	httpRequestString[startingPoint + 12] = decDecode(
			httpRequestString[startingPoint + 12]);
	httpRequestString[startingPoint + 13] = decDecode(
			httpRequestString[startingPoint + 13]);
	if (httpRequestString[startingPoint + 14] == 0)
		httpRequestString[startingPoint + 14] = '0';
	else
		httpRequestString[startingPoint + 14] = decDecode(
				httpRequestString[startingPoint + 14]);

	resetDecode();
	httpRequestString[startingPoint + 16] = MAC_address[4] / 100;
	httpRequestString[startingPoint + 17] = MAC_address[4] / 10
			- (httpRequestString[startingPoint + 16] * 10);
	httpRequestString[startingPoint + 18] = MAC_address[4]
			- (httpRequestString[startingPoint + 17] * 10)
			- (httpRequestString[startingPoint + 16] * 100);

	httpRequestString[startingPoint + 16] = decDecode(
			httpRequestString[startingPoint + 16]);
	httpRequestString[startingPoint + 17] = decDecode(
			httpRequestString[startingPoint + 17]);
	if (httpRequestString[startingPoint + 18] == 0)
		httpRequestString[startingPoint + 18] = '0';
	else
		httpRequestString[startingPoint + 18] = decDecode(
				httpRequestString[startingPoint + 18]);

	resetDecode();
	httpRequestString[startingPoint + 20] = MAC_address[5] / 100;
	httpRequestString[startingPoint + 21] = MAC_address[5] / 10
			- (httpRequestString[startingPoint + 20] * 10);
	httpRequestString[startingPoint + 22] = MAC_address[5]
			- (httpRequestString[startingPoint + 21] * 10)
			- (httpRequestString[startingPoint + 20] * 100);

	httpRequestString[startingPoint + 20] = decDecode(
			httpRequestString[startingPoint + 20]);
	httpRequestString[startingPoint + 21] = decDecode(
			httpRequestString[startingPoint + 21]);
	if (httpRequestString[startingPoint + 22] == 0)
		httpRequestString[startingPoint + 22] = '0';
	else
		httpRequestString[startingPoint + 22] = decDecode(
				httpRequestString[startingPoint + 22]);
}

/*
 * FOR INFO
 * RETRIES + DROPS
 */
/** @brief Update the number of retries in the HTTP request string
 *
 *	@param numOfRetries The number of Retries
 *
 *  @return Void.
 */
void updateRetry(uint8_t numOfRetries) {
	httpRequestString[INFO_RETRY_START] = numOfRetries / 10;
	httpRequestString[INFO_RETRY_START + 1] = numOfRetries
			- (httpRequestString[INFO_RETRY_START] * 10);

	resetDecode();
	httpRequestString[INFO_RETRY_START] = decDecode(
			httpRequestString[INFO_RETRY_START]);
	if (httpRequestString[INFO_RETRY_START + 1] == 0)
		httpRequestString[INFO_RETRY_START + 1] = '0';
	else
		httpRequestString[INFO_RETRY_START + 1] = decDecode(
				httpRequestString[INFO_RETRY_START + 1]);
}

/** @brief Update the number of drops in the HTTP request string
 *
 *	@param numOfDrops The number of drops
 *
 *  @return Void.
 */
void updateDrops(uint16_t numOfDrops) {
	httpRequestString[INFO_DROP_START] = numOfDrops / 1000;
	httpRequestString[INFO_DROP_START + 1] = numOfDrops / 100
			- (httpRequestString[INFO_DROP_START] * 10);
	httpRequestString[INFO_DROP_START + 2] = numOfDrops / 10
			- (httpRequestString[INFO_DROP_START + 1] * 10)
			- (httpRequestString[INFO_DROP_START] * 100);
	httpRequestString[INFO_DROP_START + 3] = numOfDrops
			- (httpRequestString[INFO_DROP_START + 2] * 10)
			- (httpRequestString[INFO_DROP_START + 1] * 100)
			- (httpRequestString[INFO_DROP_START] * 1000);

	resetDecode();
	httpRequestString[INFO_DROP_START] = decDecode(
			httpRequestString[INFO_DROP_START]);
	httpRequestString[INFO_DROP_START + 1] = decDecode(
			httpRequestString[INFO_DROP_START + 1]);
	httpRequestString[INFO_DROP_START + 2] = decDecode(
			httpRequestString[INFO_DROP_START + 2]);
	if (httpRequestString[INFO_DROP_START + 3] == 0)
		httpRequestString[INFO_DROP_START + 3] = '0';
	else
		httpRequestString[INFO_DROP_START + 3] = decDecode(
				httpRequestString[INFO_DROP_START + 3]);

}
/*
 * FOR THE ERROR AND FAULT
 * ERROR + FAULT
 */

/** @brief Update the generic error in the HTTP request string
 *
 *	@param input The numerical value of the error
 *
 *  @return Void.
 */
void changeError(uint8_t input) {
	httpRequestString[ERROR_POSITION] = input + '0';
}

/** @brief Clear the fault in the HTTP request string
 *
 *  @return Void.
 */
void clearFault() {
	uint32_t i = 0;
	for (i = FAULT_BEGIN; i <= FAULT_END; i++) {
		httpRequestString[i] = ' ';
	}
}

/** @brief Clear a single fault from the HTTP request string
 *
 *	@param input The number of faults to delete
 *
 *  @return Void.
 */
void clearSingleFault(uint8_t input) {
	uint32_t i = 0;
	for (i = (FAULT_END - 1); i >= (FAULT_END - (input * SINGLE_FAULT_LENGTH));
			i--) {
		httpRequestString[i] = ' ';
	}
}

/** @brief Update an SDCS address in the fault list for the HTTP request string
 *
 *	@param position The position of the SDCS
 *	@param address The address of the SDCS
 *
 *  @return Void.
 */
void updateFaultSDCSAddress(uint8_t position, uint8_t address) {
	position--;
	httpRequestString[FAULT_BEGIN + FAULT_SDCS_ADDRESS_OFFSET
			+ position * SINGLE_FAULT_LENGTH] = address + '0';
}

/** @brief Update the addresses of the stations in a faulty SDCS
 *
 *	@param SDCSposition The position of the SDCS
 *	@param *dataSource Pointer to the array containing faulty stations
 *	@param numberOfStation Number of faulty station
 *
 *  @return Void.
 */
void updateFaultStationAddress(uint8_t SDCSposition, uint8_t *dataSource,
		uint8_t numberOfStation) {
	SDCSposition--;
	uint32_t i = 1;
	uint32_t ii = FAULT_BEGIN + FAULT_STATION_ADDRESS_OFFSET
			+ SDCSposition * SINGLE_FAULT_LENGTH;
	uint32_t startingPosition = ii;
	for (i = 1; i <= 6; i++) {
		if (i <= numberOfStation) {
			httpRequestString[ii] = *(dataSource + (ii - startingPosition) / 2)
					+ '0';
			ii += 2;
			if (i == numberOfStation) {
				httpRequestString[ii - 1] = ' ';
			}
		} else {
			httpRequestString[ii] = ' ';
			httpRequestString[ii + 1] = ' ';
			ii += 2;
		}
	}
	httpRequestString[startingPosition + 11] = ']';
}

/*
 * FOR THE DATA
 * DATA
 */

/** @brief Update the Address of an SDCS in the HTTP request string
 *
 *	@param position The position of the SDCS
 *	@param address The address of the SDCS
 *  @return Void.
 */
void updateSDCSDataAddress(uint8_t position, uint8_t address) {
	position--;
	httpRequestString[DATA_ADDRESS_BEGIN_WITH_OFFSET
			+ position * DATA_SDCS_LENGTH] = address + '0';
}

/** @brief Update the data of an SDCS in the HTTP request string
 *
 *	@param SDCSposition The position of the SDCS
 *	@param stationPosition The position/address of the Station
 *	@param data The pressure data in 32bits (14bit ADC from the SDCS)
 *
 *  @return Void.
 */
void updateStationDataSingle(uint8_t SDCSposition, uint8_t stationPosition,
		uint32_t data) {
	SDCSposition--;
	stationPosition--;
	uint32_t startingPoint = DATA_BEGIN_WITH_OFFSET
			+ SDCSposition * DATA_SDCS_LENGTH
			+ stationPosition * DATA_STATION_LENGTH;

	resetDecode();

	httpRequestString[startingPoint] = data / 10000;
	httpRequestString[startingPoint + 1] = data / 1000
			- (httpRequestString[startingPoint] * 10);
	httpRequestString[startingPoint + 2] = data / 100
			- httpRequestString[startingPoint + 1] * 10
			- httpRequestString[startingPoint] * 100;
	httpRequestString[startingPoint + 3] = data / 10
			- httpRequestString[startingPoint + 2] * 10
			- httpRequestString[startingPoint + 1] * 100
			- httpRequestString[startingPoint] * 1000;
	httpRequestString[startingPoint + 4] = data
			- httpRequestString[startingPoint + 3] * 10
			- httpRequestString[startingPoint + 2] * 100
			- httpRequestString[startingPoint + 1] * 1000
			- httpRequestString[startingPoint] * 10000;

	httpRequestString[startingPoint] = decDecode(
			httpRequestString[startingPoint]);
	httpRequestString[startingPoint + 1] = decDecode(
			httpRequestString[startingPoint + 1]);
	httpRequestString[startingPoint + 2] = decDecode(
			httpRequestString[startingPoint + 2]);
	httpRequestString[startingPoint + 3] = decDecode(
			httpRequestString[startingPoint + 3]);
	if (httpRequestString[startingPoint + 4] == 0)
		httpRequestString[startingPoint + 4] = '0';
	else
		httpRequestString[startingPoint + 4] = decDecode(
				httpRequestString[startingPoint + 4]);

	httpRequestString[startingPoint + 5] = ' ';
	httpRequestString[startingPoint + 6] = ' ';
	httpRequestString[startingPoint + 7] = ' ';
	httpRequestString[startingPoint + 8] = ' ';
	httpRequestString[startingPoint + 9] = ' ';
	httpRequestString[startingPoint + 10] = ' ';
}

void updateStationDataDual(uint8_t SDCSposition, uint8_t stationPosition,
		uint32_t data, uint32_t second_data) {
	SDCSposition--;
	stationPosition--;
	uint32_t startingPoint = DATA_BEGIN_WITH_OFFSET
			+ SDCSposition * DATA_SDCS_LENGTH
			+ stationPosition * DATA_STATION_LENGTH;

	resetDecode();

	httpRequestString[startingPoint] = data / 10000;
	httpRequestString[startingPoint + 1] = data / 1000
			- (httpRequestString[startingPoint] * 10);
	httpRequestString[startingPoint + 2] = data / 100
			- httpRequestString[startingPoint + 1] * 10
			- httpRequestString[startingPoint] * 100;
	httpRequestString[startingPoint + 3] = data / 10
			- httpRequestString[startingPoint + 2] * 10
			- httpRequestString[startingPoint + 1] * 100
			- httpRequestString[startingPoint] * 1000;
	httpRequestString[startingPoint + 4] = data
			- httpRequestString[startingPoint + 3] * 10
			- httpRequestString[startingPoint + 2] * 100
			- httpRequestString[startingPoint + 1] * 1000
			- httpRequestString[startingPoint] * 10000;

	httpRequestString[startingPoint] = decDecode(
			httpRequestString[startingPoint]);
	httpRequestString[startingPoint + 1] = decDecode(
			httpRequestString[startingPoint + 1]);
	httpRequestString[startingPoint + 2] = decDecode(
			httpRequestString[startingPoint + 2]);
	httpRequestString[startingPoint + 3] = decDecode(
			httpRequestString[startingPoint + 3]);
	httpRequestString[startingPoint + 4] = decDecode(
			httpRequestString[startingPoint + 4]);

	httpRequestString[startingPoint + 5] = ',';

	resetDecode();

	httpRequestString[startingPoint + 6] = second_data / 10000;
	httpRequestString[startingPoint + 7] = second_data / 1000
			- (httpRequestString[startingPoint + 6] * 10);
	httpRequestString[startingPoint + 8] = second_data / 100
			- httpRequestString[startingPoint + 7] * 10
			- httpRequestString[startingPoint + 6] * 100;
	httpRequestString[startingPoint + 9] = second_data / 10
			- httpRequestString[startingPoint + 8] * 10
			- httpRequestString[startingPoint + 7] * 100
			- httpRequestString[startingPoint + 6] * 1000;
	httpRequestString[startingPoint + 10] = second_data
			- httpRequestString[startingPoint + 9] * 10
			- httpRequestString[startingPoint + 8] * 100
			- httpRequestString[startingPoint + 7] * 1000
			- httpRequestString[startingPoint + 6] * 10000;

	httpRequestString[startingPoint + 6] = decDecode(
			httpRequestString[startingPoint + 6]);
	httpRequestString[startingPoint + 7] = decDecode(
			httpRequestString[startingPoint + 7]);
	httpRequestString[startingPoint + 8] = decDecode(
			httpRequestString[startingPoint + 8]);
	httpRequestString[startingPoint + 9] = decDecode(
			httpRequestString[startingPoint + 9]);
	httpRequestString[startingPoint + 10] = decDecode(
			httpRequestString[startingPoint + 10]);
}

/** @brief Remove unnecessary RFID chars in the HTTP request string
 *
 *	@param SDCSposition The position of the SDCS
 *	@param stationPosition The position/address of the Station
 *
 *  @return Void.
 */
void removeRFID(uint8_t SDCSposition, uint8_t stationPosition) {
	SDCSposition--;
	stationPosition--;
	uint32_t startingPoint = DATA_BEGIN_WITH_OFFSET
			+ SDCSposition * DATA_SDCS_LENGTH
			+ stationPosition * DATA_STATION_LENGTH + DATA_RFID_OFFSET_FROM_PUMP;
	uint32_t i = 0;

	for (i = startingPoint - 6; i <= startingPoint + 15; i++) {
		httpRequestString[i] = ' ';
	}
}

/** @brief Update RFID chars in the HTTP request string
 *
 *	@param SDCSposition The position of the SDCS
 *	@param stationPosition The position/address of the Station
 *	@param *RFIDinput pointer to an RFID array
 *
 *  @return Void.
 */
void updateRFIDInStation(uint8_t SDCSposition, uint8_t stationPosition,
		uint8_t* RFIDinput) {
	SDCSposition--;
	stationPosition--;
	uint32_t startingPoint = DATA_BEGIN_WITH_OFFSET
			+ SDCSposition * DATA_SDCS_LENGTH
			+ stationPosition * DATA_STATION_LENGTH + DATA_RFID_OFFSET_FROM_PUMP;

	resetDecode();
	httpRequestString[startingPoint] = RFIDinput[0] / 100;
	httpRequestString[startingPoint + 1] = RFIDinput[0] / 10
			- (httpRequestString[startingPoint] * 10);
	httpRequestString[startingPoint + 2] = RFIDinput[0]
			- (httpRequestString[startingPoint + 1] * 10)
			- (httpRequestString[startingPoint] * 100);

	httpRequestString[startingPoint] = decDecode(
			httpRequestString[startingPoint]);
	httpRequestString[startingPoint + 1] = decDecode(
			httpRequestString[startingPoint + 1]);
	if (httpRequestString[startingPoint + 2] == 0)
		httpRequestString[startingPoint + 2] = '0';
	else
		httpRequestString[startingPoint + 2] = decDecode(
				httpRequestString[startingPoint + 2]);

	resetDecode();
	httpRequestString[startingPoint + 4] = RFIDinput[1] / 100;
	httpRequestString[startingPoint + 5] = RFIDinput[1] / 10
			- (httpRequestString[startingPoint + 4] * 10);
	httpRequestString[startingPoint + 6] = RFIDinput[1]
			- (httpRequestString[startingPoint + 5] * 10)
			- (httpRequestString[startingPoint + 4] * 100);

	httpRequestString[startingPoint + 4] = decDecode(
			httpRequestString[startingPoint + 4]);
	httpRequestString[startingPoint + 5] = decDecode(
			httpRequestString[startingPoint + 5]);
	if (httpRequestString[startingPoint + 6] == 0)
		httpRequestString[startingPoint + 6] = '0';
	else
		httpRequestString[startingPoint + 6] = decDecode(
				httpRequestString[startingPoint + 6]);

	resetDecode();
	httpRequestString[startingPoint + 8] = RFIDinput[2] / 100;
	httpRequestString[startingPoint + 9] = RFIDinput[2] / 10
			- (httpRequestString[startingPoint + 8] * 10);
	httpRequestString[startingPoint + 10] = RFIDinput[2]
			- (httpRequestString[startingPoint + 9] * 10)
			- (httpRequestString[startingPoint + 8] * 100);

	httpRequestString[startingPoint + 8] = decDecode(
			httpRequestString[startingPoint + 8]);
	httpRequestString[startingPoint + 9] = decDecode(
			httpRequestString[startingPoint + 9]);
	if (httpRequestString[startingPoint + 10] == 0)
		httpRequestString[startingPoint + 10] = '0';
	else
		httpRequestString[startingPoint + 10] = decDecode(
				httpRequestString[startingPoint + 10]);

	resetDecode();
	httpRequestString[startingPoint + 12] = RFIDinput[3] / 100;
	httpRequestString[startingPoint + 13] = RFIDinput[3] / 10
			- (httpRequestString[startingPoint + 12] * 10);
	httpRequestString[startingPoint + 14] = RFIDinput[3]
			- (httpRequestString[startingPoint + 13] * 10)
			- (httpRequestString[startingPoint + 12] * 100);

	httpRequestString[startingPoint + 12] = decDecode(
			httpRequestString[startingPoint + 12]);
	httpRequestString[startingPoint + 13] = decDecode(
			httpRequestString[startingPoint + 13]);
	if (httpRequestString[startingPoint + 14] == 0)
		httpRequestString[startingPoint + 14] = '0';
	else
		httpRequestString[startingPoint + 14] = decDecode(
				httpRequestString[startingPoint + 14]);
}

/** @brief Remove unncecessary SDCS chars from the HTTP request string
 *
 *	@param numberOfSDCS The number of SDCS to remove
 *
 *  @return Void.
 */
void removeSDCS(uint8_t numberOfSDCS) {
	uint32_t i = 0;
	for (i = DATA_END; i > DATA_END - (numberOfSDCS * DATA_SDCS_LENGTH); i--) {
		httpRequestString[i] = ' ';
	}
}

/** @brief Remove unncecessary station chars from the HTTP request string
 *
 *	@param SDCSposition The position of the SDCS
 *	@param numberOfStations The number of stations to remove
 *  @return Void.
 */
void removeStationFromSDCS(uint8_t SDCSposition, uint8_t numberOfStations) {
	uint32_t startingPoint = DATA_BEGIN_WITH_OFFSET
			+ SDCSposition * DATA_SDCS_LENGTH - 22;
	uint32_t endingPoint = startingPoint
			- (numberOfStations * DATA_STATION_LENGTH);
	uint32_t i = 0;
	for (i = startingPoint; i > endingPoint; i--) {
		httpRequestString[i] = ' ';
	}
}

/*
 * GAUGE update
 */

/** @brief Delete the unused gauge bytes in the HTTP request string
 *
 *	@param numOfGauges The number of gauges to be deleted
 *
 *  @return Void.
 */
void deleteGauge(uint8_t numOfGauges) {
	uint32_t startingPoint = GAUGE_ADDRESS_START + 4;
	uint32_t ii;
	for (ii = startingPoint; ii > (startingPoint - (numOfGauges * 2)); ii--) {
		httpRequestString[ii] = ' ';
	}
	startingPoint = GAUGE_VALUE_START + 16;
	for (ii = startingPoint; ii > (startingPoint - (numOfGauges) * 6); ii--) {
		httpRequestString[ii] = ' ';
	}
	httpRequestString[GAUGE_ADDRESS_START - 1] = '[';
	httpRequestString[GAUGE_VALUE_START - 1] = '[';
}

/** @brief Update the gauges addresses in the HTTP request string
 *
 *	@param addressOne The address representing the 1st gauge
 *	@param addressTwo The address representing the 2nd gauge
 *	@param addressThree The address representing the 3rd gauge
 *
 *  @return Void.
 */
void updateGaugeAddress(uint8_t addressOne, uint8_t addressTwo,
		uint8_t addressThree) {
	uint32_t startingPoint = GAUGE_ADDRESS_START;
	resetDecode();
	httpRequestString[startingPoint] = decDecode(addressOne);
	httpRequestString[startingPoint + 2] = decDecode(addressTwo);
	httpRequestString[startingPoint + 4] = decDecode(addressThree);
}

/** @brief Update the gauges data in the HTTP request string
 *
 *	@param dataOne The data representing the 1st gauge
 *	@param dataTwo The data representing the 2nd gauge
 *	@param dataThree The data representing the 3rd gauge
 *
 *  @return Void.
 */
void updateGaugeData(uint16_t dataOne, uint16_t dataTwo, uint16_t dataThree) {
	uint32_t startingPoint = GAUGE_VALUE_START;
	resetDecode();

	httpRequestString[startingPoint] = dataOne / 10000;
	httpRequestString[startingPoint + 1] = dataOne / 1000
			- (httpRequestString[startingPoint] * 10);
	httpRequestString[startingPoint + 2] = dataOne / 100
			- httpRequestString[startingPoint + 1] * 10
			- httpRequestString[startingPoint] * 100;
	httpRequestString[startingPoint + 3] = dataOne / 10
			- httpRequestString[startingPoint + 2] * 10
			- httpRequestString[startingPoint + 1] * 100
			- httpRequestString[startingPoint] * 1000;
	httpRequestString[startingPoint + 4] = dataOne
			- httpRequestString[startingPoint + 3] * 10
			- httpRequestString[startingPoint + 2] * 100
			- httpRequestString[startingPoint + 1] * 1000
			- httpRequestString[startingPoint] * 10000;

	httpRequestString[startingPoint] = decDecode(
			httpRequestString[startingPoint]);
	httpRequestString[startingPoint + 1] = decDecode(
			httpRequestString[startingPoint + 1]);
	httpRequestString[startingPoint + 2] = decDecode(
			httpRequestString[startingPoint + 2]);
	httpRequestString[startingPoint + 3] = decDecode(
			httpRequestString[startingPoint + 3]);
	if (httpRequestString[startingPoint + 4] == 0)
		httpRequestString[startingPoint + 4] = '0';
	else
		httpRequestString[startingPoint + 4] = decDecode(
				httpRequestString[startingPoint + 4]);

	httpRequestString[startingPoint + 5] = ',';

	resetDecode();

	httpRequestString[startingPoint + 6] = dataTwo / 10000;
	httpRequestString[startingPoint + 7] = dataTwo / 1000
			- (httpRequestString[startingPoint + 6] * 10);
	httpRequestString[startingPoint + 8] = dataTwo / 100
			- httpRequestString[startingPoint + 7] * 10
			- httpRequestString[startingPoint + 6] * 100;
	httpRequestString[startingPoint + 9] = dataTwo / 10
			- httpRequestString[startingPoint + 8] * 10
			- httpRequestString[startingPoint + 7] * 100
			- httpRequestString[startingPoint + 6] * 1000;
	httpRequestString[startingPoint + 10] = dataTwo
			- httpRequestString[startingPoint + 9] * 10
			- httpRequestString[startingPoint + 8] * 100
			- httpRequestString[startingPoint + 7] * 1000
			- httpRequestString[startingPoint + 6] * 10000;

	httpRequestString[startingPoint + 6] = decDecode(
			httpRequestString[startingPoint + 6]);
	httpRequestString[startingPoint + 7] = decDecode(
			httpRequestString[startingPoint + 7]);
	httpRequestString[startingPoint + 8] = decDecode(
			httpRequestString[startingPoint + 8]);
	httpRequestString[startingPoint + 9] = decDecode(
			httpRequestString[startingPoint + 9]);
	if (httpRequestString[startingPoint + 10] == 0)
		httpRequestString[startingPoint + 10] = '0';
	else
		httpRequestString[startingPoint + 10] = decDecode(
				httpRequestString[startingPoint + 10]);

	resetDecode();

	httpRequestString[startingPoint + 12] = dataThree / 10000;
	httpRequestString[startingPoint + 13] = dataThree / 1000
			- (httpRequestString[startingPoint + 12] * 10);
	httpRequestString[startingPoint + 14] = dataThree / 100
			- httpRequestString[startingPoint + 13] * 10
			- httpRequestString[startingPoint + 12] * 100;
	httpRequestString[startingPoint + 15] = dataThree / 10
			- httpRequestString[startingPoint + 14] * 10
			- httpRequestString[startingPoint + 13] * 100
			- httpRequestString[startingPoint + 12] * 1000;
	httpRequestString[startingPoint + 16] = dataThree
			- httpRequestString[startingPoint + 9] * 15
			- httpRequestString[startingPoint + 14] * 100
			- httpRequestString[startingPoint + 13] * 1000
			- httpRequestString[startingPoint + 12] * 10000;

	httpRequestString[startingPoint + 12] = decDecode(
			httpRequestString[startingPoint + 12]);
	httpRequestString[startingPoint + 13] = decDecode(
			httpRequestString[startingPoint + 13]);
	httpRequestString[startingPoint + 14] = decDecode(
			httpRequestString[startingPoint + 14]);
	httpRequestString[startingPoint + 15] = decDecode(
			httpRequestString[startingPoint + 15]);

	if (httpRequestString[startingPoint + 16] == 0)
		httpRequestString[startingPoint + 16] = '0';
	else
		httpRequestString[startingPoint + 16] = decDecode(
				httpRequestString[startingPoint + 16]);
}

