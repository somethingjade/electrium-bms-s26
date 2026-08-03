#include <init.h>
#include "tasks/soc.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queues.h"

// placeholders for now
#define STACK_SIZE 512

int main(void) {
	BMS_Init();
	QueueManager_Init();
	xTaskCreate(
		vSOCTask,
		"SOC",
		STACK_SIZE,
		NULL,
		tskIDLE_PRIORITY + 1,
		NULL
	);
	vTaskStartScheduler();
	while (1) {}
}
