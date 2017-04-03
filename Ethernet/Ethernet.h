/*
 * Ethernet.h
 *
 *  Created on: Jul 14, 2015
 *      Author: Dinh
 */

/*
 * This is not really a library, but a "wrapper" of lwIP APIs and callback functions
 * to help shorten the code in the main program
 */

#ifndef COINHUTAODACHET_ETHERNET_ETHERNET_H_
#define COINHUTAODACHET_ETHERNET_ETHERNET_H_

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/flash.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "utils/lwiplib.h"
#include "utils/ustdlib.h"
#include "utils/uartstdio.h"
#include "drivers/pinout.h"
#include "lwip/tcp.h"
#include "string.h"

#include "../configs/configs.h"
#include "../Systick/Systick.h"
#include "../OLEDlibrary/OLED.h"

#define ETHERNET_INT_PRIORITY   3<<5

#define LINK_AVAILABLE 			0b00000001
#define IP_ACQUIRED 			0b00000010
#define THINGSPEAK_CONNECTED 	0b00000100
#define THINGSPEAK_UNREACHABLE 	0b00001000
#define ETHERNET_ERROR			0b00010000
#define UPLOAD_SUCCESS			0b00100000

#define CONNECTION_TIMEOUT 	600
#define SEND_TIMEOUT 		350

extern struct tcp_pcb* thingspeakpcb;
extern volatile uint8_t ethernetStatus;
extern uint32_t g_ui32IPAddress;

extern uint8_t pui8MACArray[8];

void DisplayIPAddress(uint32_t ui32Addr);
err_t connectCallback(void *arg, struct tcp_pcb *tpcb, err_t err);
void tcpErrorHandler(void *arg, err_t err);
err_t tcpRecvCallback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
uint8_t connectToThingspeak();
size_t Ethernetwrite(const uint8_t *buf, size_t size);
void EthernetPrint(const uint8_t *buf);
void closeConnectionManually();

void EthernetInit(void);
uint32_t numberOfEntry(char* inputPointer, uint16_t lengthOfData);
#endif /* COINHUTAODACHET_ETHERNET_ETHERNET_H_ */
