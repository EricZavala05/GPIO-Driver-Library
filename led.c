/*
* led.c
*
*
*	Creatrd on: 12/29/2018
*			Author: Eric Zavala
*/

#include "led.h"


/**
	* @brief	Initializes the MCU's on board LED
	* @param	None
	*	@retval	None	
**/
void ledInit(void)
{
	RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef led;

	led.pin_no = GPIO_PORTA_PIN5;
	led.mode = GPIO_OUTPUT_MODE;
	led.output_type = GPIO_PUSH_PULL_OUTPUT;
	led.pull = GPIO_NO_PULL_PUSH;
	led.output_speed = GPIO_LOW_SPEED_OUTPUT;
	
	gpio_init(GPIO_PORT_A, &led);
	
}

/**
	* @brief	Turns ON/OFF the led 
	* @param	*GPIOx	:	GPIO PORT Base Address
	*	@param	pin_no	:	Pin number that the LED is connected to
	*	@param	value		:	1 to turn ON LED. 0 to turn OFF LED
	*	@retval	None	
**/
void ledWrite(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint8_t value)
{
	if(value == ON || value == OFF)
	gpio_write(GPIOx, pin_no, value);
	
}

/**
	* @brief	Toggles the LED connected to the pin
	* @param	*GPIOx	:	GPIO PORT Base Address
	*	@param	pin_no	:	Pin number that the LED is connected to
	*	@retval	None	
**/
void ledToggle(GPIO_TypeDef *GPIOx, uint16_t pin_no)
{
	if(gpio_read(GPIOx,pin_no) == ON)
	{
		gpio_write(GPIOx,pin_no,OFF);
	}
	else
	{
		gpio_write(GPIOx,pin_no,ON);
	}
	
}






