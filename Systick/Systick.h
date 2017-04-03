/*
 * Systick.h
 *
 *  Created on: Jul 14, 2015
 *      Author: Dinh
 */

/*
 * This provides a millis()-like systick counter for easier time-keeping
 * Small timeout functions are added for better code clarity
 *
 * Systick is possibly not as precise as timer, but lwIP stacks  sample code
 * relies on systick interrupt to run, so I will keep this as to simplify the code
 */

#ifndef COINHUTAODACHET_SYSTICK_SYSTICK_H_
#define COINHUTAODACHET_SYSTICK_SYSTICK_H_

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
#include "utils/locator.h"
#include "utils/lwiplib.h"
#include "utils/ustdlib.h"
#include "utils/uartstdio.h"
#include "drivers/pinout.h"
#include "string.h"

#include "../OLEDlibrary/OLED.h"
#include "../configs/configs.h"

#define SYSTICKHZ               100
#define SYSTICKMS               (1000 / SYSTICKHZ)

#define SYSTICK_INT_PRIORITY    (2<<5)

void sysTickInit(void);
void timeOutSet(unsigned long *input);
uint8_t timeIsOut(unsigned long input, unsigned int timeInterval);

#endif /* COINHUTAODACHET_SYSTICK_SYSTICK_H_ */
