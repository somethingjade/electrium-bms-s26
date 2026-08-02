#include "FreeRTOS.h";
#include "queue.h"

extern QueueHandle_t soc_queue;
extern QueueHandle_t request_queue;
extern QueueHandle_t response_queue;

void QueueManager_Init();
