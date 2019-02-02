/*
* led.h
*
*
*	Creatrd on: 12/29/2018
*			Author: Eric Zavala
*/

#ifndef LED_H
#define LED_H

#include "GPIO_Driver.h"

#define GPIO_PORTA_PIN5 5

#define OFF 0
#define ON 	1


/**
	* @brief	Initializes the MCU's on board LED
	* @param	None
	*	@retval	None	
**/
void ledInit(void);

/**
	* @brief	Turns ON/OFF the led 
	* @param	*GPIOx	:	GPIO PORT Base Address
	*	@param	pin_no	:	Pin number that the LED is connected to
	*	@param	value		:	1 to turn ON LED. 0 to turn OFF LED
	*	@retval	None	
**/
void ledWrite(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint8_t value);

/**
	* @brief	Toggles the LED connected to the pin
	* @param	*GPIOx	:	GPIO PORT Base Address
	*	@param	pin_no	:	Pin number that the LED is connected to
	*	@retval	None	
**/
void ledToggle(GPIO_TypeDef *GPIOx, uint16_t pin_no);


#endif 

