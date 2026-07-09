#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include "tle9012dqu.h"
#include "../usart/usart.h"


uint8_t crc8_j1850(const uint8_t* data, size_t len) {
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

void TLE9012DQU_Init(uint8_t node_id) {
	// Write ID
	uint8_t write_frames[WRITE_FRAMES_LEN] = {SYNC_FRAME, WRITE_COMMAND, CONFIG_ADDR, 0x00, node_id}; // i really hope it's msb first
	uint8_t write_crc = crc8_j1850(write_frames, WRITE_FRAMES_LEN);
	USART3_Write(write_frames, WRITE_FRAMES_LEN, false);
	USART3_Write(&write_crc, 1, false);
	uint8_t reply_frame_buf[1] = {};
	USART3_Read(reply_frame_buf, 1);
	// Read back ID
	uint8_t read_frames[READ_FRAMES_LEN] = {SYNC_FRAME, READ_COMMAND & node_id, CONFIG_ADDR};
	uint8_t read_crc = crc8_j1850(read_frames, READ_FRAMES_LEN);
	USART3_Write(read_frames, READ_FRAMES_LEN, false);
	USART3_Write(&read_crc, 1, false);
	uint8_t read_buf[READ_BYTES] = {};
	USART3_Read(read_buf, READ_BYTES);
	assert(((uint16_t)read_buf[1] << 8 | read_buf[2]) == node_id);
}
