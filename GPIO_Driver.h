/*
* GPIO_DRIVER.h
*
*
*	Creatrd on: 12/29/2018
*			Author: Eric Zavala
*/

#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

/*MCU specific header file for stm32f446 based NUCLEO board */
#include "stm32f446xx.h"

/************************************************************************************************************/
/*																																																					*/
/*															1. Macros for GPIO Pin Initialization 																			*/
/*																																																					*/
/************************************************************************************************************/

/* GPIO MODE setting values */
#define GPIO_INPUT_MODE									((uint32_t)0x00)
#define GPIO_OUTPUT_MODE								((uint32_t)0x01)
#define GPIO_ALT_MODE										((uint32_t)0x02)
#define GPIO_ANALOG_MODE								((uint32_t)0x03)

/* GPIO OUTPUT TYPE setting values */
#define GPIO_PUSH_PULL_OUTPUT						((uint32_t)0x00)
#define GPIO_OPEN_DRAIN_OUTPUT					((uint32_t)0x01)

/* GPIO OUTPUT SPEED setting values */
#define GPIO_LOW_SPEED_OUTPUT						((uint32_t)0x00)
#define GPIO_MED_SPEED_OUTPUT						((uint32_t)0x01)
#define GPIO_FAST_SPEED_OUTPUT					((uint32_t)0x02)
#define GPIO_HIGH_SPEED_OUTPUT					((uint32_t)0x03)

/* GPIO PULL-UP/PULL-DOWN setting values */
#define GPIO_NO_PULL_PUSH								((uint32_t)0x00)
#define GPIO_PULL_UP										((uint32_t)0x01)
#define GPIO_PULL_DOWN									((uint32_t)0x02)


/* GPIO PORT ADDRESSES */
#define GPIO_PORT_A GPIOA
#define GPIO_PORT_B GPIOB
#define GPIO_PORT_C GPIOC
#define GPIO_PORT_D GPIOD
#define GPIO_PORT_E GPIOE
#define GPIO_PORT_F GPIOF
#define GPIO_PORT_G GPIOG
#define GPIO_PORT_H GPIOH


/* Macros for Enabling Clock of different GPIO ports in RCC register */
#define RCC_GPIOA_CLK_ENABLE() 					(RCC->AHB1ENR |= (1 << 0))
#define RCC_GPIOB_CLK_ENABLE() 					(RCC->AHB1ENR |= (1 << 1))
#define RCC_GPIOC_CLK_ENABLE() 					(RCC->AHB1ENR |= (1 << 2))
#define RCC_GPIOD_CLK_ENABLE() 					(RCC->AHB1ENR |= (1 << 3))
#define RCC_GPIOE_CLK_ENABLE() 					(RCC->AHB1ENR |= (1 << 4))
#define RCC_GPIOF_CLK_ENABLE() 					(RCC->AHB1ENR |= (1 << 5))
#define RCC_GPIOG_CLK_ENABLE() 					(RCC->AHB1ENR |= (1 << 6))
#define RCC_GPIOH_CLK_ENABLE() 					(RCC->AHB1ENR |= (1 << 7))


/************************************************************************************************************/
/*																																																					*/
/*															2. Data Dtructure for GPIO pin Initialization 															*/
/*																																																					*/
/************************************************************************************************************/

/** 
  * @brief GPIO pin configuration structure 
	*					This structure will be filled and passed to driver by the application
	*					to initialize the gpio pin
  */
typedef struct
{
	uint16_t pin_no;				// Specifies the GPIO pin to be configured
	uint32_t mode;					// Specifies the operating mode for the selected pin
	uint32_t output_type;		// Speifies the output type for the selected pins
	uint32_t pull;					// specifies the pull-up or pull-down activation for the pin
	uint32_t output_speed;	// specifies the speed for the selected pins
	uint32_t alt_funct;			// specifies the alternate function value 
} GPIO_InitTypeDef;



/**
	* @brief	Interrupt Edge selection enum
**/
typedef enum
{
	RISING_EDGE,
	FALLING_EDGE,
	RISING_FALLING_EDGE
}Edge_Select_Typedef;


/************************************************************************************************************/
/*																																																					*/
/*															3. Driver Exposed APIs																											*/
/*																																																					*/
/************************************************************************************************************/

/**
	* @brief	Initializes the GPIO pin
	* @param	*GPIOx	:	GPIO PORT Base Address
	*	@param	GPIO_InitTypeDef:	Pointer to the pin conf structure sent by application
	*	@retval	None 
**/
void gpio_init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *gpio_conf);

/**
	* @brief	Set the alternate functionality for the given pin 
	* @param	*GPIOx	:	GPIO PORT Base Address
	*	@param	pin_no	:	GPIO pin number
	*	@param	aternate:	specifies the alternate function to be configured with
	*	@retval	None 
**/
void gpio_set_alt_funct(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint32_t alternate);

/**
	* @brief	Read a value from a given pin number
	* @param	*GPIOx	:	GPIO PORT Base Address
	*	@param	pin_no	:	GPIO pin number
	*	@retval	uint8_t	:	Value read
**/
uint8_t gpio_read(GPIO_TypeDef *GPIOx, uint16_t pin_no);

/**
	* @brief	Write a value to given pin number 
	* @param	*GPIOx	:	GPIO PORT Base Address
	*	@param	pin_no	:	GPIO pin number
	*	@param	value		:	value to be written
	*	@retval	None	
**/
void gpio_write(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint8_t value);

/**
	* @brief	Configure the interrupt for the a given pin number 
	*	@param	pin_no	:	GPIO pin number
	*	@param	edge_sel:	Triggering edge selection value of type "int_edge_sel_t"
	*	@retval	None	
**/
void gpio_configure_interrupt(uint16_t pin_no, Edge_Select_Typedef edge);

/**
	* @brief	Enable interrupt for a given pin number and irq number 
	*	@param	pin_no	:	GPIO pin number
	*	@param	irq_no	:	irq_number to be enabled in NVIC
	*	@retval	None	
**/
void gpio_enable_interrupt(uint16_t pin_no, IRQn_Type irq_no);

/**
	* @brief	Clear the sticky interrupt pending bit if set
	*	@param	pin_no	:	GPIO pin number
	*	@retval	None	
**/
void gpio_clear_interrupt(uint16_t pin_no);

#endif

