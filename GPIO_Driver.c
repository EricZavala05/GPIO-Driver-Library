/*
* GPIO_DRIVER.c
*
*
*	Creatrd on: 12/29/2018
*			Author: Eric Zavala
*/

#include "GPIO_Driver.h"

/************************************************************************************************************/
/*																																																					*/
/*															Static Helper Functions																											*/
/*																																																					*/
/************************************************************************************************************/

/**
	* @brief	Configures the mode of a pin: input, output, alt, or analog
	* @param	*GPIOx	:	GPIO PORT Base Address
	*	@param	pin_no	:	GPIO pin number
	*	@param	mode		:	mode to be configured
	*	@retval	None 
**/
static void gpio_configure_pin_mode(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint32_t mode)
{
	
	GPIOx->MODER |= (mode << (2 *pin_no));
	
}

/**
	* @brief	Configures the ouput type of a pin
	* @param	*GPIOx	:	GPIO PORT Base Address
	*	@param	pin_no	:	GPIO pin number
	*	@param	op_type	:	output type to be configured with
	*	@retval	None 
**/
static void gpio_configure_pin_output_type(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint32_t op_type)
{
	
	GPIOx->OTYPER |= (op_type << pin_no);

}

/**
	* @brief	Configures the ouput speed of a pin
	* @param	*GPIOx	:	GPIO PORT Base Address
	*	@param	pin_no	:	GPIO pin number
	*	@param	speed		:	value of the speed 
	*	@retval	None 
**/
static void gpio_configure_pin_output_speed(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint32_t speed)
{
	
	GPIOx->OSPEEDR |= (speed << (2 *pin_no));
	
}

/**
	* @brief	Configures the input pin to be pulled up, pulled down, or floating 
	* @param	*GPIOx	:	GPIO PORT Base Address
	*	@param	pin_no	:	GPIO pin number
	*	@param	pull		:	specifies which resistors to activate
	*	@retval	None 
**/
static void gpio_configure_pin_pupd(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint32_t pull)
{
	
	GPIOx->PUPDR |= (pull << (2 *pin_no));
	
}

/************************************************************************************************************/
/*																																																					*/
/*															Driver exposed APIs																													*/
/*																																																					*/
/************************************************************************************************************/

/**
	* @brief	Initializes the gpio pin
	* @param	*GPIOx	:	GPIO PORT Base Address
	*	@param	gpio_pin_conf_t	:	Pointer to the pin conf structure sent by application
	*	@retval	None 
**/
void gpio_init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *gpio_conf)
{
	if(gpio_conf->mode)
		gpio_configure_pin_mode(GPIOx, gpio_conf->pin_no, gpio_conf->mode);
	
	if(gpio_conf->output_type)
		gpio_configure_pin_output_type(GPIOx, gpio_conf->pin_no, gpio_conf->output_type);
	
	if(gpio_conf->pull)
		gpio_configure_pin_pupd(GPIOx, gpio_conf->pin_no, gpio_conf->pull);
	
	if(gpio_conf->output_speed)
		gpio_configure_pin_output_speed(GPIOx, gpio_conf->pin_no, gpio_conf->output_speed);

}

/**
	* @brief	Set the alternate functionality for the given pin 
	* @param	*GPIOx	:	GPIO PORT Base Address
	*	@param	pin_no	:	GPIO pin number
	*	@param	aternate:	specifies the alternate function to be configured with
	*	@retval	None 
**/
void gpio_set_alt_funct(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint32_t alternate)
{
	if(pin_no <= 7)
	{
		GPIOx->AFR[0] |= (alternate << (4 *pin_no));
	}
	else 
	{
		GPIOx->AFR[1] |= (alternate << (4 *(pin_no % 8)));
	}
}

/**
	* @brief	Read a value from a given pin number
	* @param	*GPIOx	:	GPIO PORT Base Address
	*	@param	pin_no	:	GPIO pin number
	*	@retval	uint8_t	:	Value read
**/
uint8_t gpio_read(GPIO_TypeDef *GPIOx, uint16_t pin_no)
{
	uint8_t value;
	value = ((GPIOx->IDR >> pin_no) & 0x00000001);
	
	return value;
}

/**
	* @brief	Write a value to given pin number 
	* @param	*GPIOx	:	GPIO PORT Base Address
	*	@param	pin_no	:	GPIO pin number
	*	@param	value		:	value to be written
	*	@retval	none	
**/
void gpio_write(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint8_t value)
{
	if(value)
		GPIOx->ODR |= (1 << pin_no);
	else
		GPIOx->ODR &= ~(1 << pin_no);
}

/**
	* @brief	Configure the interrupt for the a given pin number 
	*	@param	pin_no	:	GPIO pin number
	*	@param	edge_sel:	Triggering edge selection value of type "int_edge_sel_t"
	*	@retval	None	
**/
void gpio_configure_interrupt(uint16_t pin_no, Edge_Select_Typedef edge)
{
	if(edge == RISING_EDGE)
	{
		EXTI->RTSR |= (1 << pin_no);
	}
	else
		if(edge == FALLING_EDGE)
			{
				EXTI->FTSR |= (1 << pin_no);
			}
			else
			{
				EXTI->RTSR |= (1 << pin_no);
				EXTI->FTSR |= (1 << pin_no);
			}		
}

/**
	* @brief	Enable interrupt for a given pin number and irq number 
	*	@param	pin_no	:	GPIO pin number
	*	@param	irq_no	:	irq_number to be enabled in NVIC
	*	@retval	None	
**/
void gpio_enable_interrupt(uint16_t pin_no, IRQn_Type irq_no)
{
	EXTI->IMR |= (1 << pin_no);
	NVIC_EnableIRQ(irq_no);
}

/**
	* @brief	Clear the sticky interrupt pending bit if set
	*	@param	pin_no	:	GPIO pin number
	*	@retval	None	
**/
void gpio_clear_interrupt(uint16_t pin_no)
{
	if(EXTI->PR & (1 << pin_no))
	{
		EXTI->PR |= 1 << pin_no;
	}	
}




