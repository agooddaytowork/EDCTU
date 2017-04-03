/*
 * wrappedi2c.h
 *
 *  Created on: Jun 30, 2015
 *      Author: Dinh
 */

#ifndef OLEDSAMPLEAPP_WRAPPEDI2C_WRAPPEDI2C_H_
#define OLEDSAMPLEAPP_WRAPPEDI2C_WRAPPEDI2C_H_

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_i2c.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "../OLEDlibrary/OLED.h"
#include "../Systick/Systick.h"

#define I2C_ADDR 0x3C
#define I2C_TIMEOUT 100

void i2cInit();
uint8_t sendI2CBuffer();
void addToI2CBuffer(uint8_t c);

extern unsigned int i2c_indicator;
extern uint8_t i2c_buffer[1035];


#endif /* OLEDSAMPLEAPP_WRAPPEDI2C_WRAPPEDI2C_H_ */
