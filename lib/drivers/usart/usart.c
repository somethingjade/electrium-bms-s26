#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stm32l4xx.h>
#include "usart.h"

void USART3_Init(void) {
	// Enable USART3
	RCC->APB1ENR1 |= RCC_APB1ENR1_USART3EN;

	// TODO: set the baudrate

	// Enable USART, TX, and RX
	USART3->CR1 |= ((0b1 << USART_CR1_TE_Pos) | (0b1 << USART_CR1_RE_Pos) | (0b1 << USART_CR1_UE_Pos));
}

// TODO: error handle read/write
void USART3_Read(uint8_t* buf, size_t len) {
	for (size_t i = 0; i < len; ++i) {
		while (!(USART3->ISR & USART_ISR_RXNE_Msk)) {}
		buf[i] = (uint8_t)USART3->RDR;
	}
}

void USART3_Write(const uint8_t* buf, size_t len, bool waitForEnd) {
	for (size_t i = 0; i < len; ++i) {
		while (!(USART3->ISR & USART_ISR_TXE_Msk)) {}
		USART3->TDR = buf[i];
	}
	if (waitForEnd) {
		while (!(USART3->ISR & USART_ISR_TC_Msk)) {}
	}
}
