/*
 * wrappedCAN.c
 *
 *  Created on: Jul 22, 2015
 *      Author: Dinh
 */

/*
 * This helps simplify the CAN interfaces (making use of the TivaWare CAN peripheral driver).
 * - Interrupts are serviced here, to provide a sequential set of functions
 * - Timeouts
 */

#include "wrappedCAN.h"

volatile bool g_bRXFlag = 0;
volatile bool g_bErrFlag = 0;

volatile uint8_t CANstatus = 0;
volatile uint8_t receivedPacketFlags = 0;

tCANMsgObject sCANMessage;

// Typical 8-byte buffer
uint8_t pui8MsgData[8];
// 1 byte buffer for presence checking
uint8_t presenceBuffer;
// This is made extern so that functions outside of this scope can gain access to the error
volatile uint32_t ui32Status;

/** @brief The interrupt handler of the CAN peripheral
 *
 * Sets neccessary flags for the sequential functions below
 *
 *  @return Void.
 */
void CANIntHandler(void)
{
	/*
	 * Find the cause of the interrupt
	 */
	ui32Status = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);

	/*
	 * If this is a control interrupt, check for error or status
	 */
	if (ui32Status == CAN_INT_INTID_STATUS)
	{
		ui32Status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);

		if ((ui32Status & CAN_STATUS_TXOK) || (ui32Status & CAN_STATUS_RXOK))
		{
			return;
		}
		else
		{
			// If the CAN bus enterred BUS_OFF state, try to reconnect
			if (ui32Status & CAN_STATUS_BUS_OFF)
			{
			    CANSetup();
			    CANMessageObjectsSetup();
			}
			CANstatus |= CAN_ERROR;
		}
	}

	// If the interrupt is due to an array of data from the SDCS being received
	else if (ui32Status == 7)
	{
		// Clear the interrupt flag
		CANIntClear(CAN0_BASE, 7);

		receivedPacketFlags |= REV_PACKET_7;
		// Set data receive flag
		if (receivedPacketFlags == 0b01111111)
		{
			CANstatus |= DATA_RECEIVED;
			receivedPacketFlags = 0;
		}

		// Clear Error flag
		CANstatus &= ~CAN_ERROR;
	}

	else if (ui32Status == 8)
	{
		// Clear the interrupt flag and initialize the internal receive buffer
		CANIntClear(CAN0_BASE, 8);
		sCANMessage.pui8MsgData = &presenceBuffer;

		// Set presence receive flag
		CANstatus |= PRESENCE_RECEIVED;

		// Get the message
		CANMessageGet(CAN0_BASE, 8, &sCANMessage, 0);

		// Update the warehouse data structure
		thisWarehouse.SDCSDataList[thisWarehouse.SDCSnum].address =
				(sCANMessage.ui32MsgID >> 4) + 1;
		thisWarehouse.SDCSDataList[thisWarehouse.SDCSnum].status = presenceBuffer;
		thisWarehouse.SDCSnum++;

		// Clear Error flag
		CANstatus &= ~CAN_ERROR;
	}
	else if (ui32Status == 9)
	{
		// Clear the interrupt flag
		CANIntClear(CAN0_BASE, 9);

		// Set presence sent flag
		CANstatus |= PRESENCE_REQUEST_SENT;

		// Clear Error flag
		CANstatus &= ~CAN_ERROR;
	}
	else if (ui32Status == 10)
	{
		// Clear the interrupt flag
		CANIntClear(CAN0_BASE, 10);

		// Set presence sent flag
		CANstatus |= DATA_REQUEST_SENT;

		// Clear Error flag
		CANstatus &= ~CAN_ERROR;
	}
	/*
	 * This should never happen
	 */
	else
	{
		switch (ui32Status)
		{
			case 1:
				receivedPacketFlags |= REV_PACKET_1;
				CANIntClear(CAN0_BASE, 1);
				break;
			case 2:
				receivedPacketFlags |= REV_PACKET_2;
				CANIntClear(CAN0_BASE, 2);
				break;
			case 3:
				receivedPacketFlags |= REV_PACKET_3;
				CANIntClear(CAN0_BASE, 3);
				break;
			case 4:
				receivedPacketFlags |= REV_PACKET_4;
				CANIntClear(CAN0_BASE, 4);
				break;
			case 5:
				receivedPacketFlags |= REV_PACKET_5;
				CANIntClear(CAN0_BASE, 5);
				break;
			case 6:
				receivedPacketFlags |= REV_PACKET_6;
				CANIntClear(CAN0_BASE, 6);
				break;
			default: break;
		}

		if (receivedPacketFlags == 0b01111111)
		{
			CANstatus |= DATA_RECEIVED;
			receivedPacketFlags = 0;
		}
		// I do not know what to do here
	}
}

/** @brief Set up CAN
 *
 *	Set up CAN peripheral and interrupts
 *
 *  @return Void.
 */

void CANSetup()
{
	/*
	 * Setting up CAN communications for the EDCTU
	 * 500kbps, interrupt-driven
	 */
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

	GPIOPinConfigure(GPIO_PA0_CAN0RX);
	GPIOPinConfigure(GPIO_PA1_CAN0TX);

	GPIOPinTypeCAN(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);

	CANInit(CAN0_BASE);

	CANBitRateSet(CAN0_BASE, g_ui32SysClock, 500000);

	CANIntRegister(CAN0_BASE, CANIntHandler);

	CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);

	IntEnable(INT_CAN0);

	IntPrioritySet(INT_CAN0, CAN_PRIORITY);

	CANEnable(CAN0_BASE);

	// Messages retries are done manually in the program
	// This is to prevent a message from being stuck inside the CAN bus
	CANRetrySet(CAN0_BASE, false);
}

/** @brief Get the current presence status of the warehouse
 *
 *  @return boolean on whether the operation completed successfully
 */
uint8_t CANGetPresence()
{
	unsigned char failureCounter = 0;
	while (failureCounter < 4)
	{
		if (CANPresenceCheckSend())
		{
			CANstatus &= ~BROKEN;
			return 1;
		}
		else
		{
			failureCounter++;
		}
	}
	CANstatus |= BROKEN;
	return 0;
}

/** @brief Read a single SDCS's data
 *
 *  a failure counter is kept by the loop in order to mark the CAN status as BROKEN
 *  once a counter of more than 4 is met
 *
 *  @param index the numerical index of the SDCS in the warehouse structure
 *
 *  @return boolean on whether the operation completed successfully
 */

uint8_t CANGetSDCSData(uint8_t index)
{
	uint8_t address;
	unsigned long timeKeeper = 0;
	unsigned char failureCounter = 0;

	address = thisWarehouse.SDCSDataList[index].address;
	CANstatus &= ~ DATA_RECEIVED;

	receivedPacketFlags = 0;

	dataReceiveMessageObjectSetup(address);

	while (failureCounter < 4)
	{
		if (CANDataRequestSend(address))
		{
			CANstatus &= ~BROKEN;
			sCANMessage.pui8MsgData = pui8MsgData;
			timeOutSet(&timeKeeper);
			while (1)
			{
				if (CANstatus & DATA_RECEIVED)
				{
					CANMessageGet(CAN0_BASE, 1, &sCANMessage, false);
					thisWarehouse.SDCSDataList[index].stationDataList[0].RFID[0] = pui8MsgData[0];
					thisWarehouse.SDCSDataList[index].stationDataList[0].RFID[1] = pui8MsgData[1];
					thisWarehouse.SDCSDataList[index].stationDataList[0].RFID[2] = pui8MsgData[2];
					thisWarehouse.SDCSDataList[index].stationDataList[0].RFID[3] = pui8MsgData[3];
					thisWarehouse.SDCSDataList[index].stationDataList[0].pressureOne = (pui8MsgData[4]<<8) | (pui8MsgData[5]);
					thisWarehouse.SDCSDataList[index].stationDataList[0].pressureTwo = (pui8MsgData[6]<<8) | (pui8MsgData[7]);
					CANMessageGet(CAN0_BASE, 2, &sCANMessage, false);
					thisWarehouse.SDCSDataList[index].stationDataList[1].RFID[0] = pui8MsgData[0];
					thisWarehouse.SDCSDataList[index].stationDataList[1].RFID[1] = pui8MsgData[1];
					thisWarehouse.SDCSDataList[index].stationDataList[1].RFID[2] = pui8MsgData[2];
					thisWarehouse.SDCSDataList[index].stationDataList[1].RFID[3] = pui8MsgData[3];
					thisWarehouse.SDCSDataList[index].stationDataList[1].pressureOne = (pui8MsgData[4]<<8) | (pui8MsgData[5]);
					thisWarehouse.SDCSDataList[index].stationDataList[1].pressureTwo = (pui8MsgData[6]<<8) | (pui8MsgData[7]);
					CANMessageGet(CAN0_BASE, 3, &sCANMessage, false);
					thisWarehouse.SDCSDataList[index].stationDataList[2].RFID[0] = pui8MsgData[0];
					thisWarehouse.SDCSDataList[index].stationDataList[2].RFID[1] = pui8MsgData[1];
					thisWarehouse.SDCSDataList[index].stationDataList[2].RFID[2] = pui8MsgData[2];
					thisWarehouse.SDCSDataList[index].stationDataList[2].RFID[3] = pui8MsgData[3];
					thisWarehouse.SDCSDataList[index].stationDataList[2].pressureOne = (pui8MsgData[4]<<8) | (pui8MsgData[5]);
					thisWarehouse.SDCSDataList[index].stationDataList[2].pressureTwo = (pui8MsgData[6]<<8) | (pui8MsgData[7]);
					CANMessageGet(CAN0_BASE, 4, &sCANMessage, false);
					thisWarehouse.SDCSDataList[index].stationDataList[3].RFID[0] = pui8MsgData[0];
					thisWarehouse.SDCSDataList[index].stationDataList[3].RFID[1] = pui8MsgData[1];
					thisWarehouse.SDCSDataList[index].stationDataList[3].RFID[2] = pui8MsgData[2];
					thisWarehouse.SDCSDataList[index].stationDataList[3].RFID[3] = pui8MsgData[3];
					thisWarehouse.SDCSDataList[index].stationDataList[3].pressureOne = (pui8MsgData[4]<<8) | (pui8MsgData[5]);
					thisWarehouse.SDCSDataList[index].stationDataList[3].pressureTwo = (pui8MsgData[6]<<8) | (pui8MsgData[7]);
					CANMessageGet(CAN0_BASE, 5, &sCANMessage, false);
					thisWarehouse.SDCSDataList[index].stationDataList[4].RFID[0] = pui8MsgData[0];
					thisWarehouse.SDCSDataList[index].stationDataList[4].RFID[1] = pui8MsgData[1];
					thisWarehouse.SDCSDataList[index].stationDataList[4].RFID[2] = pui8MsgData[2];
					thisWarehouse.SDCSDataList[index].stationDataList[4].RFID[3] = pui8MsgData[3];
					thisWarehouse.SDCSDataList[index].stationDataList[4].pressureOne = (pui8MsgData[4]<<8) | (pui8MsgData[5]);
					thisWarehouse.SDCSDataList[index].stationDataList[4].pressureTwo = (pui8MsgData[6]<<8) | (pui8MsgData[7]);
					CANMessageGet(CAN0_BASE, 6, &sCANMessage, false);
					thisWarehouse.SDCSDataList[index].stationDataList[5].RFID[0] = pui8MsgData[0];
					thisWarehouse.SDCSDataList[index].stationDataList[5].RFID[1] = pui8MsgData[1];
					thisWarehouse.SDCSDataList[index].stationDataList[5].RFID[2] = pui8MsgData[2];
					thisWarehouse.SDCSDataList[index].stationDataList[5].RFID[3] = pui8MsgData[3];
					thisWarehouse.SDCSDataList[index].stationDataList[5].pressureOne = (pui8MsgData[4]<<8) | (pui8MsgData[5]);
					thisWarehouse.SDCSDataList[index].stationDataList[5].pressureTwo = (pui8MsgData[6]<<8) | (pui8MsgData[7]);
					CANMessageGet(CAN0_BASE, 7, &sCANMessage, false);
					addToFaultStation(address,pui8MsgData[2]);

					if (thisWarehouse.SDCSDataList[index].status & HAS_GAUGE)
					{
						thisWarehouse.gaugeDataList[getIndexByAddressGauge(
								thisWarehouse.SDCSDataList[index].address)].pressure =
								(pui8MsgData[0] << 8) | (pui8MsgData[1]);
					}

					CANstatus &= ~BROKEN;
					return 1;
				}
				else if (timeIsOut(timeKeeper, CAN_DATA_GET_TIMOUT))
				{
					return 0;
				}
			}
		}
		else
		{
			failureCounter++;
		}
	}
	CANstatus |= BROKEN;
	return 0;
}

/** @brief Send the presence check packet into the CAN bus
 *
 *  @return boolean on whether the operation completed successfully
 */
uint8_t CANPresenceCheckSend()
{
	unsigned long timeKeeper = 0;

	sCANMessage.ui32MsgID = 0xF0;
	sCANMessage.ui32Flags = MSG_OBJ_USE_ID_FILTER | MSG_OBJ_TX_INT_ENABLE;
	sCANMessage.ui32MsgLen = 1;
	sCANMessage.pui8MsgData = &presenceBuffer;

	// Send the configuration variable to the SDCS
	presenceBuffer = systemConfig;

	// Clear the presence request sent flag
	CANstatus &= ~PRESENCE_REQUEST_SENT;
	CANMessageSet(CAN0_BASE, 9, &sCANMessage, MSG_OBJ_TYPE_TX);

	timeOutSet(&timeKeeper);
	// Clear the error flag beforehand so that the loop does not return immediately due to previous errors
	CANstatus &= ~CAN_ERROR;
	while (1)
	{
		if (CANstatus & PRESENCE_REQUEST_SENT)
		{
			break;
		}
		else if ((timeIsOut(timeKeeper, CAN_SEND_TIMEOUT)) || (CANstatus & CAN_ERROR))
		{
			return 0;
		}
	}

	timeOutSet(&timeKeeper);
	while (!timeIsOut(timeKeeper, CAN_PRESENCE_TIMEOUT));
	return 1;
}


/** @brief Send the data requet packet into the CAN bus
 * 		   to one specific SDCS
 *
 *  @param address The address of the SDCS
 *  @return boolean on whether the operation completed successfully
 */

uint8_t CANDataRequestSend(uint8_t address)
{
	unsigned long timeKeeper = 0;

	address -= 1;

	sCANMessage.ui32MsgID = ((address<<4)|0b00000111);
	sCANMessage.ui32Flags = MSG_OBJ_USE_ID_FILTER | MSG_OBJ_TX_INT_ENABLE;
	sCANMessage.ui32MsgLen = 1;
	sCANMessage.pui8MsgData = &presenceBuffer;

	presenceBuffer = 'b';

	CANstatus &= ~DATA_REQUEST_SENT;
	CANMessageSet(CAN0_BASE, 10, &sCANMessage, MSG_OBJ_TYPE_TX);
	timeOutSet(&timeKeeper);
	CANstatus &= ~CAN_ERROR;
	while (1)
	{
		if (CANstatus & DATA_REQUEST_SENT)
		{
			break;
		}
		else if ((timeIsOut(timeKeeper, CAN_SEND_TIMEOUT))
				|| (CANstatus & CAN_ERROR))
		{
			return 0;
		}
	}
	return 1;
}

/** @brief Set up the receive CAN message objects
 *
 * This function should be called every time a data requet packet is due
 * to be sent in the CAN bus to prevent the EDCTU from receiving packets
 * from the unintended SDCS
 *
 *  @param address the address of the SDCS
 *  @return Void, since this operation cannot fail
 */

void dataReceiveMessageObjectSetup(uint8_t address)
{
	CANMessageClear(CAN0_BASE,1);
	CANMessageClear(CAN0_BASE,2);
	CANMessageClear(CAN0_BASE,3);
	CANMessageClear(CAN0_BASE,4);
	CANMessageClear(CAN0_BASE,5);
	CANMessageClear(CAN0_BASE,6);
	CANMessageClear(CAN0_BASE,7);
	/*
	 * Setting up the message objects for data transmission
	 */
	sCANMessage.ui32MsgID = ((address-1)<<4)|0;
	sCANMessage.ui32MsgIDMask = 0xFF;
	sCANMessage.ui32Flags = MSG_OBJ_USE_ID_FILTER | MSG_OBJ_RX_INT_ENABLE;
	sCANMessage.ui32MsgLen = 8;
	sCANMessage.pui8MsgData = pui8MsgData;

	CANMessageSet(CAN0_BASE, 1, &sCANMessage, MSG_OBJ_TYPE_RX);

	sCANMessage.ui32MsgID = ((address-1)<<4)|1;
	CANMessageSet(CAN0_BASE, 2, &sCANMessage, MSG_OBJ_TYPE_RX);

	sCANMessage.ui32MsgID = ((address-1)<<4)|2;
	CANMessageSet(CAN0_BASE, 3, &sCANMessage, MSG_OBJ_TYPE_RX);

	sCANMessage.ui32MsgID = ((address-1)<<4)|3;
	CANMessageSet(CAN0_BASE, 4, &sCANMessage, MSG_OBJ_TYPE_RX);

	sCANMessage.ui32MsgID = ((address-1)<<4)|4;
	CANMessageSet(CAN0_BASE, 5, &sCANMessage, MSG_OBJ_TYPE_RX);

	sCANMessage.ui32MsgID = ((address-1)<<4)|5;
	CANMessageSet(CAN0_BASE, 6, &sCANMessage, MSG_OBJ_TYPE_RX);

	sCANMessage.ui32MsgID = ((address-1)<<4)|6;

	CANMessageSet(CAN0_BASE, 7, &sCANMessage, MSG_OBJ_TYPE_RX);
}

/** @brief Set up initial CAN message objects
 *
 *  @return Void, since this operation cannot fail
 */

void CANMessageObjectsSetup()
{
	memset(&thisWarehouse, 0, sizeof(thisWarehouse));
	thisWarehouse.SDCSnum = 0;

	/*
	 * Setting up the message objects for data transmission
	 */
	sCANMessage.ui32MsgID = 0x00;
	sCANMessage.ui32MsgIDMask = 0x0F;
	sCANMessage.ui32Flags = MSG_OBJ_USE_ID_FILTER | MSG_OBJ_RX_INT_ENABLE;
	sCANMessage.ui32MsgLen = 8;
	sCANMessage.pui8MsgData = pui8MsgData;

	CANMessageSet(CAN0_BASE, 1, &sCANMessage, MSG_OBJ_TYPE_RX);

	sCANMessage.ui32MsgID = 0x01;
	CANMessageSet(CAN0_BASE, 2, &sCANMessage, MSG_OBJ_TYPE_RX);

	sCANMessage.ui32MsgID = 0x02;
	CANMessageSet(CAN0_BASE, 3, &sCANMessage, MSG_OBJ_TYPE_RX);

	sCANMessage.ui32MsgID = 0x03;
	CANMessageSet(CAN0_BASE, 4, &sCANMessage, MSG_OBJ_TYPE_RX);

	sCANMessage.ui32MsgID = 0x04;
	CANMessageSet(CAN0_BASE, 5, &sCANMessage, MSG_OBJ_TYPE_RX);

	sCANMessage.ui32MsgID = 0x05;
	CANMessageSet(CAN0_BASE, 6, &sCANMessage, MSG_OBJ_TYPE_RX);

	sCANMessage.ui32MsgID = 0x06;
	sCANMessage.ui32Flags = MSG_OBJ_USE_ID_FILTER | MSG_OBJ_RX_INT_ENABLE;

	CANMessageSet(CAN0_BASE, 7, &sCANMessage, MSG_OBJ_TYPE_RX);

	/*
	 * Setting up the message objects for presence checking
	 */
	sCANMessage.ui32MsgID = 0x0F;
	sCANMessage.ui32MsgIDMask = 0x0F;
	sCANMessage.ui32Flags = MSG_OBJ_USE_ID_FILTER | MSG_OBJ_RX_INT_ENABLE
			| MSG_OBJ_USE_ID_FILTER;
	sCANMessage.ui32MsgLen = 1;
	sCANMessage.pui8MsgData = &presenceBuffer;

	CANMessageSet(CAN0_BASE, 8, &sCANMessage, MSG_OBJ_TYPE_RX);
}
