/*
 * wrappedi2c.c
 *
 *  Created on: Jun 30, 2015
 *      Author: Dinh
 */

#include "wrappedi2c.h"

unsigned int i2c_indicator = 0;
uint8_t i2c_buffer[1035];


/** @brief Set up the I2C peripherals
 *
 * I2C0, High-speed (400kbps)
 *
 *  @return Void.
 */
void i2cInit()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);

    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    GPIOPinConfigure(GPIO_PB2_I2C0SCL);
    GPIOPinConfigure(GPIO_PB3_I2C0SDA);

    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
    GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);

    I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), true);

    //clear I2C FIFOs
    HWREG(I2C0_BASE + I2C_O_FIFOCTL) = 80008000;
}

/** @brief Add a 8-bit value to the I2C buffer array
 *
 *  @param c The character to be added to the array
 *  @return Void.
 */

void addToI2CBuffer(uint8_t c)
{
	i2c_buffer[i2c_indicator] = c;
	i2c_indicator++;
}

/** @brief Sends the array to the I2C bus, clearing the
 * 		   array in the process
 *.
 *  @return boolean on whether the operation completed successfully.
 */

uint8_t sendI2CBuffer()
{
	unsigned long timeKeeper = 0;
	unsigned int counter = 0;
	if (i2c_indicator > 0)
	{
		I2CMasterSlaveAddrSet(I2C0_BASE, I2C_ADDR, false);
		if (i2c_indicator > 1)
		{
			 I2CMasterDataPut( I2C0_BASE, i2c_buffer[0]);
			 I2CMasterControl( I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START );

			 timeOutSet(&timeKeeper);
			 while (1)
			 {
				 if (timeIsOut(timeKeeper, I2C_TIMEOUT))
				 {
					 OLEDbroken = 1;
					 return 0;
				 }
				 else if (!I2CMasterBusy(I2C0_BASE))
				 {
					 break;
				 }
			 }
			 if ((I2CMasterErr(I2C0_BASE) == I2C_MASTER_ERR_ADDR_ACK) && (!OLEDbroken))
			 {
				 OLEDbroken = 1;
				 return 0;
			 }
			 //while(I2CMasterBusy(I2C0_BASE));
			 counter = 2;
			 while (counter < i2c_indicator)
			 {
				 I2CMasterDataPut( I2C0_BASE, i2c_buffer[counter - 1] );
				 I2CMasterControl( I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT );
				 while (1)
				 {
					 if (timeIsOut(timeKeeper, I2C_TIMEOUT))
					 {
						 OLEDbroken = 1;
						 return 0;
					 }
					 else if (!I2CMasterBusy(I2C0_BASE))
					 {
						 break;
					 }
				 }
				 if ((I2CMasterErr(I2C0_BASE) == I2C_MASTER_ERR_ADDR_ACK) && (!OLEDbroken))
				 {
					 OLEDbroken = 1;
					 return 0;
				 }
				 //while(I2CMasterBusy(I2C0_BASE));
				 counter++;
			 }
			 I2CMasterDataPut( I2C0_BASE, i2c_buffer[counter - 1] );
			 I2CMasterControl( I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH );
			 while (1)
			 {
				 if (timeIsOut(timeKeeper, I2C_TIMEOUT))
				 {
					 OLEDbroken = 1;
					 return 0;
				 }
				 else if (!I2CMasterBusy(I2C0_BASE))
				 {
					 break;
				 }
			 }
			 if ((I2CMasterErr(I2C0_BASE) == I2C_MASTER_ERR_ADDR_ACK) && (!OLEDbroken))
			 {
				 OLEDbroken = 1;
				 return 0;
			 }
			 i2c_indicator = 0;
			 return 1;
		}
		else
		{
			 I2CMasterDataPut( I2C0_BASE, i2c_buffer[0] );
			 I2CMasterControl( I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);
			 while(I2CMasterBusy(I2C0_BASE));
			 i2c_indicator = 0;
			 return 2;
		}
	}
	else return 0;
}
