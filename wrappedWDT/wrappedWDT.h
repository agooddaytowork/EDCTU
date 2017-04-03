/*
 * wrappedWDT.h
 *
 *  Created on: Sep 6, 2015
 *      Author: Dinh
 */

#ifndef COINHUTAODACHET_WRAPPEDWDT_WRAPPEDWDT_H_
#define COINHUTAODACHET_WRAPPEDWDT_WRAPPEDWDT_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/watchdog.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "drivers/buttons.h"

#include "../configs/configs.h"

void InitWatchDogTimer();
void kickTheDog(uint8_t seconds);
void feedTheDog();

#endif /* COINHUTAODACHET_WRAPPEDWDT_WRAPPEDWDT_H_ */
