#include <assert.h>
#include <stm32l4xx.h>
#include "adc.h"

void ADC1_Init() {
	// Enable ADC
	RCC->AHB2ENR |= RCC_AHB2ENR_ADCEN;

	// Sample time
	ADC1->SMPR1 &= ~(ADC_SMPR1_SMP5_Msk);
	ADC1->SMPR1 |= (0b110 << ADC_SMPR1_SMP5_Pos); // 247.5 ADC clock cycles
						      //
	// Single conversion should be set by default
	
	// Calibration
	ADC1->CR |= ADC_CR_ADCAL;
	while (ADC1->CR & ADC_CR_ADCAL_Msk) {}
	
	// Enable ADC
	ADC1->CR |= ADC_CR_ADEN;

	while (!(ADC1->ISR & ADC_ISR_ADRDY_Msk)) {}

	ADC1->SQR1 &= ~(ADC_SQR1_L_Msk);
	ADC1->SQR1 &= ~(ADC_SQR1_SQ1_Msk);
	ADC1->SQR1 |= (5 << ADC_SQR1_SQ1_Pos);
}

uint16_t ADC1_ReadIN5() {
	ADC1->CR |= ADC_CR_ADSTART;
	while (!(ADC1->ISR & ADC_ISR_EOC_Msk)) {}
	return (uint16_t)(ADC1->DR & ADC_DR_RDATA_Msk);
}
