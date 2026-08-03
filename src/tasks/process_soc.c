#include <tle9012dqu.h>
#include "portmacro.h"
#include "projdefs.h"
#include "queues.h"

void vProcessSOCTask(void* pvParameters) {
	float soc[CELLS] = {};
	if (xQueueReceive(soc_queue, soc, portMAX_DELAY) == pdPASS) {

	}
}
