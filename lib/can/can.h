#include <stdbool.h>
#include <stdint.h>

void CAN1_Init();
void CAN1_Transmit(uint16_t id, uint8_t dlc, uint64_t data, bool wait_for_completion);
bool CAN1_Receive(uint16_t* p_id, uint8_t* p_dlc, uint64_t* p_data);
