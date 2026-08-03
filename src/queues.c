#include "queues.h"

QueueHandle_t soc_queue;

void QueueManager_Init() {
	soc_queue = xQueueCreate(16, sizeof(float));
}
