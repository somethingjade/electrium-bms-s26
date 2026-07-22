#include <init.h>
#include "tasks/coulomb_count_task.h"
#include "FreeRTOS.h"
#include "task.h"

// placeholders for now
#define STACK_SIZE 512

int main(void) {
	BMS_Init();
	xTaskCreate(
		vCoulombCountTask,
		"Coulomb Count",
		STACK_SIZE,
		NULL,
		tskIDLE_PRIORITY + 1,
		NULL
	);
	vTaskStartScheduler();
	while (1) {}
}
