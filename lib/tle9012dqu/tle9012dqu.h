#include <stdint.h>
#include <stddef.h>

#define POLYNOMIAL 0x1D
#define INITIAL_CRC 0xFF
#define XOROUT 0xFF

#define WRITE_FRAMES_LEN 5
#define READ_FRAMES_LEN 3
#define READ_BYTES 2

#define CELLS 12

#define SYNC_FRAME 0x1E

#define WRITE_COMMAND 0x80
#define READ_COMMAND 0x00
#define NODE_ID_MASK 0x3F

#define MEAS_CTRL_ADDR 0x18
#define PCVM_BASE_ADDR 0x19
#define CONFIG_ADDR 0x36

#define CVM_DEL_POS 0
#define PBOFF_POS 5
#define SCVM_START_POS 6
#define AVM_START_POS 7
#define BVM_MODE_POS 8
#define BVM_START_POS 11
#define CVM_MODE_POS 12
#define PCVM_START_POS 15

#define PBOFF (0b1 << PBOFF_POS)
#define SCVM_START (0b1 << SCVM_START_POS)
#define AVM_START (0b1 << AVM_START_POS)
#define BVM_START (0b1 << BVM_START_POS)
#define PCVM_START (0b1 << PCVM_START_POS)

#define NODE_ID 1 // maybe make this a param in the voltage sense functions instead


uint8_t CRC8_J1850(const uint8_t* data, size_t len); 
void TLE9012DQU_Send(const uint8_t* buf, size_t len); 
void TLE9012DQU_HandleReplyFrame(); 
uint16_t TLE9012DQU_ReadDataFrames(); 
void TLE9012DQU_Write(uint8_t id, uint8_t addr, uint16_t data); 
uint16_t TLE9012DQU_Read(uint8_t id, uint8_t addr); 
void TLE9012DQU_Init(uint8_t nodeId); 
void TLE9012DQU_ReadPCVM(uint8_t nodeId, uint16_t* buf); 
uint16_t TLE9012DQU_ReadPCVMi(uint8_t nodeId, uint8_t i); 
