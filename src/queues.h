#include "FreeRTOS.h"
#include "queue.h"

// extern QueueHandle_t soc_queue;
// extern QueueHandle_t soh_queue;
// extern QueueHandle_t can_recv_queue;
extern QueueHandle_t latest_soc_queue;

void QueueManager_Init();
