#include <stdint.h>
#include <stddef.h>

#define POLYNOMIAL 0x1D
#define INITIAL_CRC 0xFF
#define XOROUT 0xFF

#define WRITE_FRAMES_LEN 5
#define READ_FRAMES_LEN 3
#define READ_BYTES 4

#define SYNC_FRAME 0x1E
#define WRITE_COMMAND 0x80
#define READ_COMMAND 0x7F
#define CONFIG_ADDR 0x36

uint8_t crc8_j1850(const uint8_t* data, size_t len);
void TLE9012DQU_Init(uint8_t node_id);
