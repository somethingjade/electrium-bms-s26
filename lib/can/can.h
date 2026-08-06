#include <stdbool.h>
#include <stdint.h>

typedef struct {
	uint16_t id;
	uint8_t dlc;
	uint64_t data;
} CANDataFrame;

void CAN1_Init();
void CAN1_Transmit(uint16_t id, uint8_t dlc, uint64_t data, bool wait_for_completion);
bool CAN1_Receive(CANDataFrame* p_data);
