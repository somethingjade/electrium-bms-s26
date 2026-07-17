#include <stddef.h>
#include <stdint.h>
#include <tle9012dqu.h>

inline float PCVMFormula(uint16_t read_val) {
	return (5.0/65536.0)*((float)read_val);
}

void ReadAllVoltages(float* buf) {
	uint16_t read_buf[CELLS] = {};
	TLE9012DQU_ReadPCVM(NODE_ID, read_buf);
	for (size_t i = 0; i < CELLS; ++i) {
		buf[i] = PCVMFormula(read_buf[i]);
	}
}

float ReadVoltage(uint8_t i) {
	uint16_t read_val = TLE9012DQU_ReadPCVMi(NODE_ID, i);
	return PCVMFormula(read_val);
}
