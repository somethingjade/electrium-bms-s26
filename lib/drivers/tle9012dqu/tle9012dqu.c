#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include "tle9012dqu.h"
#include "../usart/usart.h"

uint8_t CRC8_J1850(const uint8_t* data, size_t len) {
	uint8_t crc = INITIAL_CRC;
	for (size_t i = 0; i < len; ++i) {
		crc ^= data[i];
		for (uint8_t j = 0; j < 8; ++j) {
			if (crc & 0x80) {
				crc = (crc << 1) ^ POLYNOMIAL;
			} else {
				crc <<= 1;
			}
		}
	}
	return crc ^ XOROUT;
}

void TLE9012DQU_Send(const uint8_t* buf, size_t len) {
	uint8_t crc = CRC8_J1850(buf, len);
	USART3_Write(buf, len, false);
	USART3_Write(&crc, 1, false);
}

void TLE9012DQU_HandleReplyFrame() {
	uint8_t buf[1] = {};
	USART3_Read(buf, 1); // TODO: handle the reply frame
}

uint16_t TLE9012DQU_ReadDataFrames() {
	uint8_t buf[READ_BYTES] = {}; // idk if this even works
				      // not sure how many bytes are read back
				      // (crc, status, etc.)
				      // for now im assuming its only the 2 data frames
	USART3_Read(buf, READ_BYTES);
	return ((uint16_t)(buf[0]) << 8) | buf[1];
}

void TLE9012DQU_Write(uint8_t id, uint8_t addr, uint16_t data) {
	uint8_t frames[WRITE_FRAMES_LEN] = {SYNC_FRAME, WRITE_COMMAND | (NODE_ID_MASK & id), addr, (uint8_t)(data >> 8), (uint8_t)data};
	TLE9012DQU_Send(frames, WRITE_FRAMES_LEN);
	TLE9012DQU_HandleReplyFrame();
}

uint16_t TLE9012DQU_Read(uint8_t id, uint8_t addr) {
	uint8_t frames[READ_FRAMES_LEN] = {SYNC_FRAME, READ_COMMAND | (NODE_ID_MASK & id), addr};
	TLE9012DQU_Send(frames, READ_FRAMES_LEN);
	return TLE9012DQU_ReadDataFrames();
}

void TLE9012DQU_Init(uint8_t nodeId) {
	// Write ID
	TLE9012DQU_Write(0x00, CONFIG_ADDR, nodeId);
	// Read back ID
	uint16_t readId = TLE9012DQU_Read(nodeId, CONFIG_ADDR);
	assert(readId == nodeId);
}

void TLE9012DQU_ReadPCVM(uint8_t nodeId, uint16_t* buf) {
	TLE9012DQU_Write(nodeId, MEAS_CTRL_ADDR, (0b110 << CVM_MODE_POS) | PCVM_START);
	while (TLE9012DQU_Read(nodeId, MEAS_CTRL_ADDR) & PCVM_START) {} // i feel like this isnt how i should be waiting for the measurement to complete
	for (uint8_t i = 0; i < CELLS; ++i) {
		buf[i] = TLE9012DQU_Read(nodeId, PCVM_BASE_ADDR + i);
	}
}

uint16_t TLE9012DQU_ReadPCVMi(uint8_t nodeId, uint8_t i) {
	TLE9012DQU_Write(nodeId, MEAS_CTRL_ADDR, (0b110 << CVM_MODE_POS) | PCVM_START);
	while (TLE9012DQU_Read(nodeId, MEAS_CTRL_ADDR) & PCVM_START) {} // i feel like this isnt how i should be waiting for the measurement to complete
	return TLE9012DQU_Read(nodeId, PCVM_BASE_ADDR + i);
}
