#include <stdint.h>
#include "can_recv_dispatch.h"
#include "portmacro.h"
#include "queues.h"
#include <can.h>

void vCANRecvDispatch(void* pvParameters) {
	CANDataFrame data = {};
	if (xQueueReceive(can_recv_queue, &data, portMAX_DELAY)) {

	}
}
