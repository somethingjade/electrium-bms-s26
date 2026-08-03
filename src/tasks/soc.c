#include "FreeRTOS.h"
#include "portmacro.h"
#include "projdefs.h"
#include <coulomb_count.h>
#include "task.h"
#include "sensors/current/current.h"
#include "sensors/voltage/voltage.h"
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <tle9012dqu.h>
#include "soc.h"
#include "ocv_lookup.h"
#include "queues.h"

// TODO: actual capacity
// probably cant just be a define
#define CAPACITY 100

void vSOCTask(void* pvParameters) {
	const TickType_t period = pdMS_TO_TICKS(TIME_STEP);
	const float dt = TIME_STEP / 1000.0;
	TickType_t last_wake_time = xTaskGetTickCount();
	float threshold = get_threhsold(CAPACITY);
	TickType_t idle_start_time = xTaskGetTickCount();
	const TickType_t idle_ticks = pdMS_TO_TICKS(THRESHOLD_MS);
	// TODO: actual SOC init
	float soc[CELLS] = {};
	for (size_t i = 0; i < CELLS; ++i) {
		soc[i] = 1.0;
	}
	float current = 0.0;
	bool use_ocv = false;
	while (1) {
		TickType_t now = xTaskGetTickCount();
		current = ReadCurrent();
		use_ocv = false;
		if (fabsf(current) < threshold) {
			TickType_t elapsed_ticks = now - idle_start_time;
			if (elapsed_ticks > idle_ticks) {
				use_ocv = true;
			}
		}
		else {
			idle_start_time = now;
		}
		for (size_t i = 0; i < CELLS; ++i) {
			soc[i] = CoulombCount_SOC(soc[i], current, CAPACITY, dt);
			if (use_ocv) {
				float v = ReadVoltage(i);
				soc[i] = 0.98*soc[i] + 0.02*ocv_lookup(v);
			}
		xQueueSend(soc_queue, soc + i, portMAX_DELAY);
		}
		vTaskDelayUntil(&last_wake_time, period);
	}
}
