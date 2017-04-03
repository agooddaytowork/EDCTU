/*
 * wrappedCAN.h
 *
 *  Created on: Jul 22, 2015
 *      Author: Dinh
 */

/*
 * This helps simplify the CAN interfaces (making use of the TivaWare CAN peripheral driver).
 * - Interrupts are serviced here, to provide a sequential set of functions
 * - Timeouts
 * - Higher-level functions are added on Jul 24th, 2015 - to shorten the code in the main file
 */

#ifndef COINHUTAODACHET_WRAPPEDCAN_WRAPPEDCAN_H_
#define COINHUTAODACHET_WRAPPEDCAN_WRAPPEDCAN_H_

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/flash.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "utils/ustdlib.h"
#include "utils/uartstdio.h"
#include "drivers/pinout.h"
#include "driverlib/uart.h"
#include "driverlib/can.h"
#include "inc/hw_can.h"
#include "driverlib/pin_map.h"
#include "string.h"

#include "../configs/configs.h"
#include "../Systick/Systick.h"
#include "../dataProcessing/dataProcessing.h"
#include "../dataProcessing/faultProcessing.h"

#define PRESENCE_REQUEST_SENT 	0b00000001
#define DATA_REQUEST_SENT 		0b00000010
#define PRESENCE_RECEIVED 		0b00000100
#define DATA_RECEIVED 			0b00001000
#define CAN_ERROR 				0b00010000
#define BROKEN 					0b00100000

#define REV_PACKET_1	0b00000001
#define REV_PACKET_2	0b00000010
#define REV_PACKET_3	0b00000100
#define REV_PACKET_4	0b00001000
#define REV_PACKET_5	0b00010000
#define REV_PACKET_6	0b00100000
#define REV_PACKET_7	0b01000000

#define CAN_SEND_TIMEOUT 		50
#define CAN_PRESENCE_TIMEOUT 	200
#define CAN_DATA_GET_TIMOUT 	200

#define CAN_PRIORITY			(1<<5)

extern volatile uint8_t CANstatus;
extern volatile uint32_t ui32Status;

void CANSetup();
void CANMessageObjectsSetup();
uint8_t CANGetSDCSData(uint8_t index);
uint8_t CANGetPresence();

uint8_t CANPresenceCheckSend();
uint8_t CANDataRequestSend(uint8_t address);
void dataReceiveMessageObjectSetup(uint8_t address);

#endif /* COINHUTAODACHET_WRAPPEDCAN_WRAPPEDCAN_H_ */
