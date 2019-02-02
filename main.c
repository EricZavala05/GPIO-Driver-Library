

#include <stdint.h>
#include "stm32f446xx.h"
#include "led.h"
#include "GPIO_Driver.h"

#define BUTTON_PIN 13

void EXTI15_10_IRQHandler(void);

int main()
{
	
	ledInit();
	
	// button PC13
	RCC_GPIOC_CLK_ENABLE();
	
	GPIOC->MODER &= ~0x3;
	GPIOC->PUPDR &= ~0x3;
	
	//enable clock for RCC
	RCC->APB2ENR |= 0x00004000;
	SYSCFG->EXTICR[3] &= ~(0x0FU << 4);
  SYSCFG->EXTICR[3] |= (0x02U << 4);
	
	gpio_configure_interrupt(BUTTON_PIN ,FALLING_EDGE);
	gpio_enable_interrupt(BUTTON_PIN, EXTI15_10_IRQn);

	while(1)
	{
		/*ledWrite(GPIO_PORT_A, GPIO_PORTA_PIN5, ON);
		
		for(int i = 0;i < 500000;i++);
		
		ledWrite(GPIO_PORT_A, GPIO_PORTA_PIN5, OFF);
		
		for(int i = 0;i < 500000;i++);
		
		ledToggle(GPIO_PORT_A, GPIO_PORTA_PIN5);
		
		for(int i = 0;i < 500000;i++);
		
		ledToggle(GPIO_PORT_A, GPIO_PORTA_PIN5);
		
		for(int i = 0;i < 500000;i++);
		*/
	}
}

void EXTI15_10_IRQHandler(void)
{
	gpio_clear_interrupt(BUTTON_PIN);
	ledToggle(GPIO_PORT_A, GPIO_PORTA_PIN5);	
}

