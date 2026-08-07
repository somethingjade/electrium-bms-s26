#include "queues.h"
#include <can.h>
#include <stdint.h>
#include <tle9012dqu.h>

// QueueHandle_t soc_queue;
// QueueHandle_t soh_queue;
// QueueHandle_t can_recv_queue;
QueueHandle_t latest_soc_queue;

void QueueManager_Init() {
	// soc_queue = xQueueCreate(16, CELLS*sizeof(float));
	// soh_queue = xQueueCreate(16, CELLS*sizeof(float));
	// can_recv_queue = xQueueCreate(16, sizeof(CANDataFrame));
	latest_soc_queue = xQueueCreate(1, CELLS*sizeof(float));
}
