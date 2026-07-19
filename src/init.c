#include <adc.h>
#include <gpio.h>
#include <tle9012dqu.h>
#include <usart.h>

void BMS_Init() {
	GPIOA_Init();
	GPIOB_Init();
	ADC1_Init();
	USART3_Init();
	TLE9012DQU_Init(NODE_ID);
}
