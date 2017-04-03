/*
 * tactSwitch.c
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

#include "tactSwitch.h"

unsigned long debouncerSw1 = 0;
unsigned long debouncerSw2 = 0;

uint8_t buttonIsPressed = 0;
uint8_t buttonThatWasPressed = 0;

/** @brief Hardware interrupt service routine when a button is pushed
 *
 *  @return Void.
 */
void OnSWdown()
{
	if (GPIOIntStatus(SW1_PORT, false) & SW1_PIN)
	{
		GPIOIntClear(SW1_PORT, SW1_PIN);
		if (timeIsOut(debouncerSw1, DEBOUNCE_TIME))
		{
			timeOutSet(&debouncerSw1);
			buttonIsPressed = 1;
			buttonThatWasPressed = 1;
		}
	}
	else if (GPIOIntStatus(SW2_PORT, false) & SW2_PIN)
	{
		GPIOIntClear(SW2_PORT, SW2_PIN);
		if (timeIsOut(debouncerSw2, DEBOUNCE_TIME))
		{
			timeOutSet(&debouncerSw2);
			buttonIsPressed = 1;
			buttonThatWasPressed = 2;
		}
	};
}

/** @brief Initilize the GPIO peripherals
 *
 *	Pull-up, Falling edge interrupt
 *
 *  @return Void.
 */
void SWInit()
{
    GPIOPinTypeGPIOInput(SW1_PORT, SW1_PIN);
    GPIOPadConfigSet(SW1_PORT, SW1_PIN, GPIO_STRENGTH_10MA, GPIO_PIN_TYPE_STD_WPU);
    // This is for stability
    GPIOIntDisable(SW1_PORT, SW1_PIN);
    GPIOIntClear(SW1_PORT, SW1_PIN);
    GPIOIntRegister(SW1_PORT, OnSWdown);
    // Falling edge, as the button is pulled up
    GPIOIntTypeSet(SW1_PORT, SW1_PIN, GPIO_FALLING_EDGE);
    GPIOIntEnable(SW1_PORT, SW1_PIN);

    GPIOPinTypeGPIOInput(SW2_PORT, SW2_PIN);
    GPIOPadConfigSet(SW2_PORT, SW2_PIN, GPIO_STRENGTH_10MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOIntDisable(SW2_PORT, SW2_PIN);
    GPIOIntClear(SW2_PORT, SW2_PIN);

    GPIOIntTypeSet(SW2_PORT, SW2_PIN, GPIO_FALLING_EDGE);
    GPIOIntEnable(SW2_PORT, SW2_PIN);

    MAP_IntPrioritySet(INT_GPIOJ_TM4C129,SWITCH_PRIORITY);
}

/** @brief Clear the button pending
 *
 *  @return Void
 */
void clearButtonBuffer()
{
	buttonIsPressed = 0;
	buttonThatWasPressed = 0;
}

/** @brief Check if a button waas pressed
 *
 *  @return Boolean on whether a button was pressed or not
 */
uint8_t buttonPressed()
{
	return buttonIsPressed;
}

/** @brief Find the pressed button
 *
 *  @return Indicator on which button was pressed
 */
uint8_t getButton()
{
	// Clear the button flag
	buttonIsPressed = 0;

	return buttonThatWasPressed;
}
