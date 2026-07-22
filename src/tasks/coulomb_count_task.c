#include "FreeRTOS.h"
#include "portmacro.h"
#include "projdefs.h"
#include <coulomb_count.h>
#include "task.h"

// TODO: actual capacity
#define CAPACITY 100

void vCoulombCountTask(void* pvParameters) {
	const TickType_t period = pdMS_TO_TICKS(TIME_STEP);
	TickType_t last_wake_time = xTaskGetTickCount();
	// TODO: actual SOC init
	float soc = 1;
	while (1) {
		soc = CoulombCount_SOC(soc, CAPACITY);
		vTaskDelayUntil(&last_wake_time, period);
	}
}
