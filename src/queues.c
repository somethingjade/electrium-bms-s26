#include "queues.h"
#include <can.h>
#include <stdint.h>

QueueHandle_t soc_queue;
QueueHandle_t soh_queue;
QueueHandle_t can_recv_queue;

void QueueManager_Init() {
	soc_queue = xQueueCreate(16, sizeof(float));
	soh_queue = xQueueCreate(16, sizeof(float));
	can_recv_queue = xQueueCreate(16, sizeof(CANDataFrame));
}
