#include <stdint.h>
#include <adc.h>

float ReadCurrent() {
	uint16_t adc_read = ADC1_ReadIN5();
	float voltage = 3.3*((float)adc_read/0xfff);
	return 5*voltage;
}
