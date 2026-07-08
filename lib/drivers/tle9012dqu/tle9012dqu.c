#include <stdint.h>
#include <stddef.h>
#include "tle9012dqu.h"

#define POLYNOMIAL 0x1D
#define INITIAL_CRC 0xFF
#define XOROUT 0xFF

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
