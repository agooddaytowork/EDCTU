/*
 * GPfunction.h
 *
 *  Created on: Jul 28, 2015
 *      Author: Dinh
 */

/*
 * These functions are used for the sole purpose of shortening the code
 * in the main program.
 */
#ifndef COINHUTAODACHET_GPFUNCTIONS_GPFUNCTIONS_H_
#define COINHUTAODACHET_GPFUNCTIONS_GPFUNCTIONS_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "string.h"
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

#include "OLEDlibrary/OLED.h"
#include "Ethernet/Ethernet.h"
#include "Systick/Systick.h"
#include "configs/configs.h"
#include "wrappedCAN/wrappedCAN.h"
#include "tactSwitch/tactSwitch.h"
#include "OLEDmenu/OLEDmenu.h"
#include "dataProcessing/dataProcessing.h"
#include "Ethernet/stringProcessing.h"
#include "wrappedEEPROM/wrappedEEPROM.h"
#include "wrappedWDT/wrappedWDT.h"

#define SAMPLING_INTERVAL 	6000
#define RESET_INTERVAL		300000
void updateOLEDSDCSList();
void peripheralSetup();
void warehouseSetup();
void swapSDCS(uint8_t SDCSOnePosition, uint8_t SDCSTwoPosition);
void sortSDCSList();
void mainLoop();

#endif /* COINHUTAODACHET_GPFUNCTIONS_GPFUNCTIONS_H_ */
