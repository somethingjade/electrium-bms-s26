#include "FreeRTOS.h"
#include "balancing.h"
#include <stdbool.h>
#include <stddef.h>
#include <tle9012dqu.h>
#include "portmacro.h"
#include "queue.h"
#include "queues.h"

void vBalancingTask(void* pvParameters) {
	float soc[CELLS] = {};
	bool bleeding[CELLS] = {};
	for (size_t i = 0; i < CELLS; ++i) {
		bleeding[i] = false;
	}
	const TickType_t period = pdMS_TO_TICKS(PERIOD_MS);
	TickType_t last_wake_time = xTaskGetTickCount();
	while (1) {
		xQueueReceive(latest_soc_queue, soc, portMAX_DELAY);
		float sum = 0.0;
		for (size_t i = 0; i < CELLS; ++i) {
			sum += soc[i];
		}
		float mean = sum/CELLS;
		for (size_t i = 0; i < CELLS; ++i) {
			if (!bleeding[i] && soc[i] > mean + BLEED_START_THRESHOLD) {
				// TODO: bleed this cell
				bleeding[i] = true;
			} else if (bleeding[i] && soc[i] < mean + BLEED_STOP_THRESHOLD) {
				// TODO: stop bleeding cell
				bleeding[i] = false;
			}
		}
		vTaskDelayUntil(&last_wake_time, period);
	}
}
