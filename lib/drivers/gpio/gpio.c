#include <stm32l4xx.h>
#include "gpio.h"

void GPIOA_Init(void) {
	// Enable GPIOA
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

	// Set PA0 to analog
	GPIOA->MODER &= ~(GPIO_MODER_MODE0_Msk);
	GPIOA->MODER |= (0b11 << GPIO_MODER_MODE0_Pos);

	// TODO: init GPIOA for CAN
}

void GPIOB_Init(void) {
	// Enable GPIOB
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

	// Set to AF
	GPIOB->MODER &= ~(GPIO_MODER_MODE10_Msk | GPIO_MODER_MODE11_Msk);
	GPIOB->MODER |= ((0b10 << GPIO_MODER_MODE10_Pos) | (0b10 << GPIO_MODER_MODE11_Pos));

	// Select AF7
	GPIOB->AFR[1] &= ~(GPIO_AFRH_AFSEL10_Msk | GPIO_AFRH_AFSEL11_Msk);
	GPIOB->AFR[1] |= ((0b0111 << GPIO_AFRH_AFSEL10_Pos) | (0b0111 << GPIO_AFRH_AFSEL11_Pos));
}
