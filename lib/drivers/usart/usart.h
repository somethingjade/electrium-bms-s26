#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void USART3_Init(void);
void USART3_Read(uint8_t* buf, size_t len);
void USART3_Write(const uint8_t* buf, size_t len, bool waitForEnd);
