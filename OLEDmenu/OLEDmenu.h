/*
 * OLEDmenu.h
 *
 *  Created on: Jul 25, 2015
 *      Author: Dinh
 */

/*
 * This helps with creating configuration menus, each function
 * represents a menu and returns the value of the selected option.
 */

#ifndef COINHUTAODACHET_OLEDMENU_OLEDMENU_H_
#define COINHUTAODACHET_OLEDMENU_OLEDMENU_H_

#include <stdint.h>
#include "../OLEDlibrary/OLED.h"
#include "../Systick/Systick.h"
#include "../tactSwitch/tactSwitch.h"
#include "../configs/configs.h"
#include "../wrappedEEPROM/wrappedEEPROM.h"

#define MENU_TIMEOUT 2500
extern volatile uint8_t autoSetup;

uint8_t pumpNumberConfig();
uint8_t RFIDConfig();
uint8_t confirmConfig(uint8_t configVariable);
uint8_t configMenu();
uint8_t retryOrResetMenu();


#endif /* COINHUTAODACHET_OLEDMENU_OLEDMENU_H_ */
