/*
 * Ethernet.c
 *
 *  Created on: Jul 15, 2015
 *      Author: Dinh
 */

/*
 * This is not really a library, but a "wrapper" of lwIP APIs and callback functions
 * to help shorten the code in the main program
 */

#include "Ethernet.h"

struct tcp_pcb* thingspeakpcb;
volatile uint8_t ethernetStatus;
uint32_t g_ui32IPAddress;

uint32_t ui32NewIPAddress;

uint8_t pui8MACArray[8];

/** @brief Initialize the Ethernet connectivity
 *
 *  @return Void.
 */
void EthernetInit(void)
{
	uint32_t ui32User0, ui32User1;

	PinoutSet(true, false);

	//
	// Configure Port N1 for as an output for the animation LED.
	//
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1);

	//
	// Initialize LED to OFF (0)
	//
	MAP_GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, ~GPIO_PIN_1);

	//
	// Configure the hardware MAC address for Ethernet Controller filtering of
	// incoming packets.  The MAC address will be stored in the non-volatile
	// USER0 and USER1 registers.
	//
	MAP_FlashUserGet(&ui32User0, &ui32User1);
	if ((ui32User0 == 0xffffffff) || (ui32User1 == 0xffffffff))
	{
		//
		// We should never get here.  This is an error if the MAC address has
		// not been programmed into the device.  Exit the program.
		// Let the user know there is no MAC address
		//
#ifdef DEBUG_PRINT_UART
		UARTprintf("No MAC programmed!\n");
#endif
		while (1)
		{
		}
	}

	//
	// Tell the user what we are doing just now.
	//
#ifdef DEBUG_PRINT_UART
	UARTprintf("Waiting for IP.\n");
#endif

	//
	// Convert the 24/24 split MAC address from NV ram into a 32/16 split MAC
	// address needed to program the hardware registers, then program the MAC
	// address into the Ethernet Controller registers.
	//
	pui8MACArray[0] = ((ui32User0 >> 0) & 0xff);
	pui8MACArray[1] = ((ui32User0 >> 8) & 0xff);
	pui8MACArray[2] = ((ui32User0 >> 16) & 0xff);
	pui8MACArray[3] = ((ui32User1 >> 0) & 0xff);
	pui8MACArray[4] = ((ui32User1 >> 8) & 0xff);
	pui8MACArray[5] = ((ui32User1 >> 16) & 0xff);

	//
	// Initialize the lwIP library, using DHCP.
	//
	lwIPInit(g_ui32SysClock, pui8MACArray, 0, 0, 0, IPADDR_USE_DHCP);

	//
	// Set the interrupt priorities.  We set the SysTick interrupt to a higher
	// priority than the Ethernet interrupt to ensure that the file system
	// tick is processed if SysTick occurs while the Ethernet handler is being
	// processed.  This is very likely since all the TCP/IP and HTTP work is
	// done in the context of the Ethernet interrupt.
	//
	MAP_IntPrioritySet(INT_EMAC0, ETHERNET_INT_PRIORITY);
}

void DisplayIPAddress(uint32_t ui32Addr)
{
	char pcBuf[16];

	usprintf(pcBuf, "%d.%d.%d.%d", ui32Addr & 0xff, (ui32Addr >> 8) & 0xff,
			(ui32Addr >> 16) & 0xff, (ui32Addr >> 24) & 0xff);
	OLEDsinglePrint(pcBuf);
}

/** @brief Call back function for the TCP connected event
 *
 *	This callback function simply set the THINGSPEAK_CONNECTED flag
 *	in order to notify the sequential function that a connection has
 *	been established.
 *
 *  @param *arg event arguments
 *  @param *tpcb The pcb struct instance pointer for the TCP connection
 *  @param err Error
 *
 *  @return Error
 */
err_t connectCallback(void *arg, struct tcp_pcb *tpcb, err_t err)
{
#ifdef DEBUG_PRINT_UART
	UARTprintf("C\n");
#endif
	ethernetStatus |= THINGSPEAK_CONNECTED;
	return 0;
}

/** @brief Call back function for the Error event
 *
 *	This callback function simply set the ETHERNET_ERROR flag
 *	in order to notify the sequential function that an error has occured
 *
 *  @param *arg event arguments
 *  @param err Error
 *
 *  @return Error
 */

void tcpErrorHandler(void *arg, err_t err)
{
#ifdef DEBUG_PRINT_UART
	UARTprintf("E:");
	UARTprintf("%d\n", err);
#endif
	ethernetStatus |= ETHERNET_ERROR;
}

err_t tcpSentCallback(void *arg, struct tcp_pcb *tpcb,
                              u16_t len)
{
//	ethernetStatus |= UPLOAD_SUCCESS;
	//closeConnectionManually();
//	tcp_close(thingspeakpcb);
//	ethernetStatus &= ~THINGSPEAK_CONNECTED;
	return 0;
}

/** @brief Call back function for the TCP Receive event
 *
 *  @param *arg event arguments
 *  @param *tpcb The pcb struct instance pointer for the TCP connection
 *  @param err Error
 *
 *  @return Error
 */
err_t tcpRecvCallback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p,
		err_t err)
{
	//uint64_t numberOfEntries = 0;
	//char abc[500];

	if (p == NULL)
	{
		if (ethernetStatus & THINGSPEAK_CONNECTED)
		{
			tcp_close(thingspeakpcb);
			ethernetStatus &= ~THINGSPEAK_CONNECTED;
		}
		pbuf_free(p);
#ifdef DEBUG_PRINT_UART
		UARTprintf("D\n");
#endif
		// Skip authentication
		ethernetStatus |= UPLOAD_SUCCESS;
		return ERR_ABRT;
	}
	else
	{
		//memcpy(p->payload, abc, 458);
		tcp_recved(thingspeakpcb, p->tot_len);
		//if (p->tot_len > 2 * 458)
		//{

		//}
		//else
		//{
			//numberOfEntries = numberOfEntry(p->next->payload,
			//		p->tot_len - p->len);
			//if (numberOfEntries > 0)
			//{
				ethernetStatus |= UPLOAD_SUCCESS;
			//}
		//}
	}
	pbuf_free(p);
	return 0;
}

/** @brief Close the connection manually
 *
 *  This function can be called when a connection has been established
 *  but no end of response is reached with the Thingspeak server.
 *
 *  @return Void
 */
void closeConnectionManually()
{
	//tcp_close(thingspeakpcb);
	tcp_abort(thingspeakpcb);
	ethernetStatus &= ~THINGSPEAK_CONNECTED;
}

/** @brief Create a connection with the Thingspeak cloud server
 *
 *  @return Boolean on whether the connection process is completed successfully or not
 */
uint8_t connectToThingspeak()
{
	unsigned long time = 0;

	ethernetStatus &= ~ETHERNET_ERROR;
#ifdef DEBUG_PRINT_UART
	UARTprintf("\nConnect\n");
#endif
	uint32_t data = 0xdeadbeef;

	struct ip_addr ip;

	if (ethernetStatus & THINGSPEAK_CONNECTED)
	{
		closeConnectionManually();
		timeOutSet(&time);
		while (!timeIsOut(time, 10))
			;
	}

	IP4_ADDR(&ip, 119, 17, 254, 105);
	//IP4_ADDR(&ip, 192, 168, 1, 67);
	// vay thoi phai hok ah hihi
	// Mo Hercules ok
	//10.104.97.224
	//IP4_ADDR(&ip, 10, 104, 97, 224);
	thingspeakpcb = tcp_new();

	tcp_arg(thingspeakpcb, &data);
	tcp_recv(thingspeakpcb, tcpRecvCallback);
	tcp_sent(thingspeakpcb, tcpSentCallback);
	tcp_err(thingspeakpcb, tcpErrorHandler);

	ethernetStatus &= ~ETHERNET_ERROR;
	tcp_connect(thingspeakpcb, &ip, 80, connectCallback);
	timeOutSet(&time);
	while (1)
	{
		if ((timeIsOut(time, CONNECTION_TIMEOUT))
				|| (ethernetStatus & ETHERNET_ERROR))
		{
			return 0;
		}
		if (ethernetStatus & THINGSPEAK_CONNECTED)
		{
			return 1;
		}
	}
}

/** @brief Parse the thingspeak response for the number of entries uploaded to the server
 *
 *  @param *inputPointer Pointer to the start of the char array of the HTTP response
 *  @param lengthOfData length of the HTTP response in chars
 *
 *  @return 0 if the upload was unsuccessful, number of entries of the upload was successful
 */
uint32_t numberOfEntry(char* inputPointer, uint16_t lengthOfData)
{
	uint32_t i = 0;
	uint32_t ii = 0;
	uint32_t number = 0;
	//char abc[500];
	//memcpy(inputPointer, abc, 400);
	for (i = 0; i < lengthOfData; i++)
	{
		if ((inputPointer[i] == 13) && (inputPointer[i + 1] == 10)
				&& (inputPointer[i + 2] >= '1') && (inputPointer[i + 2] <= '9')
				&& (inputPointer[i + 3] == 13) && (inputPointer[i + 4] == 10))
		{
			for (ii = 5; ii < lengthOfData; ii++)
			{
				if ((inputPointer[ii + i]) == 13)
					break;
				else if ((inputPointer[ii + i] >= '0')
						&& (inputPointer[ii + i] <= '9'))
				{
					number = number * 10 + (inputPointer[ii + i] - '0');
				}
			}
		}
	}
	return number;
}

/** @brief The host timer, handling timer event for the LwIP stack
 *
 *  @return Void
 */
void lwIPHostTimerHandler(void)
{

	//
	// Get the current IP address.
	//
	ui32NewIPAddress = lwIPLocalIPAddrGet();

	//
	// See if the IP address has changed.
	//
	if (ui32NewIPAddress != g_ui32IPAddress)
	{
		//
		// See if there is an IP address assigned.
		//
		if (ui32NewIPAddress == 0xffffffff)
		{
			//
			// Indicate that there is no link.
			//
			//UARTprintf("Waiting for link.\n");
			ethernetStatus &= ~LINK_AVAILABLE;
			ethernetStatus &= ~THINGSPEAK_CONNECTED;
			ethernetStatus &= ~IP_ACQUIRED;
		}
		else if (ui32NewIPAddress == 0)
		{
			//
			// There is no IP address, so indicate that the DHCP process is
			// running.
			//
			//UARTprintf("Waiting for IP address.\n");
			ethernetStatus |= LINK_AVAILABLE;
			ethernetStatus &= ~THINGSPEAK_CONNECTED;
			ethernetStatus &= ~IP_ACQUIRED;
		}
		else
		{
			//
			// Display the new IP address.
			//
			//UARTprintf("IP Address: ");
			//DisplayIPAddress(ui32NewIPAddress);
			ethernetStatus |= LINK_AVAILABLE;
			ethernetStatus |= IP_ACQUIRED;
		}

		//
		// Save the new IP address.
		//
		g_ui32IPAddress = ui32NewIPAddress;

		//
		// Turn GPIO off.
		//
		MAP_GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, ~GPIO_PIN_1);
	}

	//
	// If there is not an IP address.
	//
	/*
	 if((ui32NewIPAddress == 0) || (ui32NewIPAddress == 0xffffffff))
	 {
	 //
	 // Loop through the LED animation.
	 //

	 for(ui32Idx = 1; ui32Idx < 17; ui32Idx++)
	 {

	 //
	 // Toggle the GPIO
	 //
	 MAP_GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1,
	 (MAP_GPIOPinRead(GPIO_PORTN_BASE, GPIO_PIN_1) ^
	 GPIO_PIN_1));

	 SysCtlDelay(g_ui32SysClock/(ui32Idx << 1));
	 }
	 } */
}

/** @brief Simplified TCP transmission function, for Thingspeak
 *
 *	This function detects if the buffer is stuffed, so that it can
 *	flush the chars in the FIFO before starting to load it with even more bytes
 *
 *  @param *buf pointer to the start of the array
 *  @param size Size of the array to send
 *
 *  @return Size
 */
size_t Ethernetwrite(const uint8_t *buf, size_t size)
{
	uint32_t i = 0, inc = 0;
	uint32_t delaycount = 0;
	uint8_t stuffed_buffer = 0;

	struct tcp_pcb * cpcb = thingspeakpcb;

	if (!cpcb)
		return 0;

	while (i < size)
	{
		inc = (size - i) < 1024 ? size - i : 1024;
		err_t err = tcp_write(cpcb, buf + i, inc, TCP_WRITE_FLAG_COPY);
		if (err != ERR_MEM)
		{
			i += inc;
			stuffed_buffer = false;
		}
		else
		{
			if (!stuffed_buffer)
			{
				tcp_output(cpcb);
				stuffed_buffer = 1;
			}
			else
			{
				while (delaycount < 12000)
				{
					delaycount++;
				}
			}
		}
	}

	//Output the remaining bytes
	if (!stuffed_buffer)
	{
		tcp_output(cpcb);
	}

	return size;
}

/** @brief Send a string without knowing the length to Thingspeak
 *
 *	Dangerous for using strlen
 *
 *	Updated: strings are automatically null terminated, no sweat!!
 *
 *  @param *buf The pointer pointing to the starting address of the string
 *
 *  @return Void.
 */

void EthernetPrint(const uint8_t *buf)
{
	if (ethernetStatus & (THINGSPEAK_CONNECTED | LINK_AVAILABLE | IP_ACQUIRED))
		Ethernetwrite(buf, strlen((const char *) buf));
}
