/*
 * datatypes.h
 *
 *  Created on: Jul 22, 2015
 *      Author: Dinh
 */

#ifndef COINHUTAODACHET_DATATYPES_H_
#define COINHUTAODACHET_DATATYPES_H_

/*
 * Definition macros for SDCS status
 * + config MASK
 */
#define CONFIG_VALID 0b10000000
#define HAS_GAUGE	 0b01000000
#define CANNOT_REACH 0b00100000

#define CONFIG_MASK 		0xF0
#define STATION_NUMBER_MASK 0x0F;

// Data structure for stations
typedef struct
{
	// 4-bit long RFID data
	unsigned char RFID[4];
	// Pump controller data
	unsigned short pressureOne;
	unsigned short pressureTwo;
} stationData;

// Data structure for SDCSs
typedef struct
{
	unsigned char address;
	unsigned char status;
	stationData stationDataList[6];
} SDCSData;

// Data structure for gauges
typedef struct
{
	unsigned char address;
	unsigned short pressure;
} gaugeData;

// Data structure for warehouse
typedef struct
{
	unsigned char SDCSnum;
	unsigned char gaugeNum;
	SDCSData SDCSDataList[6];
	gaugeData gaugeDataList[3];
} warehouseData;

typedef struct
{
	unsigned char address;
	unsigned char faultStationNum;
	unsigned char faultStationList[6];
} faultSDCStype;

typedef struct
{
	unsigned char faultSDCSNum;
	faultSDCStype faultSDCSList[6];
} faultData;


#endif /* COINHUTAODACHET_DATATYPES_H_ */
