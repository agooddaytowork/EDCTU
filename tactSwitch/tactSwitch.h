/*
 * tactSwitch.h
 *
 *  Created on: Jul 23, 2015
 *      Author: Dinh
 */

/*
 * The tact switches that are used on the EDCTU are as follows:
 * SELECT 1
 * ENTER 2
 * Wrap the GPIO-interrupt of the Tiva in buffer-style functions
 * (this is just for easier handling of buttons)
 */

#ifndef COINHUTAODACHET_TACTSWITCH_TACTSWITCH_H_
#define COINHUTAODACHET_TACTSWITCH_TACTSWITCH_H_

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/rom_map.h"
#include "utils/ustdlib.h"
#include "utils/uartstdio.h"
#include "drivers/pinout.h"
#include "driverlib/uart.h"

#include "../Systick/Systick.h"

/*
#define SW1_PORT GPIO_PORTJ_BASE
#define SW1_PIN GPIO_PIN_0

#define SW2_PORT GPIO_PORTJ_BASE
#define SW2_PIN GPIO_PIN_1
*/

#define SW1_PORT GPIO_PORTC_BASE
#define SW1_PIN GPIO_PIN_5

#define SW2_PORT GPIO_PORTC_BASE
#define SW2_PIN GPIO_PIN_6

#define DEBOUNCE_TIME 	20
#define SWITCH_PRIORITY (4<<5) //0x05

void SWInit();
uint8_t buttonPressed();
uint8_t getButton();
void clearButtonBuffer();

#endif /* COINHUTAODACHET_TACTSWITCH_TACTSWITCH_H_ */
