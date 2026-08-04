#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stm32l4xx.h>
#include "can.h"

void CAN1_Init() {
	// Enable CAN1
	RCC->APB1ENR1 |= RCC_APB1ENR1_CAN1EN;

	// Enter initialization mode
	CAN1->MCR |= CAN_MCR_INRQ;
	while (!(CAN1->MSR & CAN_MSR_INAK_Msk)) {}
	// TODO: configure timing
	// Filters
	CAN1->FMR |= CAN_FMR_FINIT;
	CAN1->FA1R &= ~(CAN_FA1R_FACT0);
	CAN1->FM1R &= ~(CAN_FM1R_FBM0_Msk);
	CAN1->FS1R |= CAN_FS1R_FSC0;
	CAN1->sFilterRegister[0].FR1 = 0;
	CAN1->sFilterRegister[0].FR2 = 0;
	CAN1->FFA1R &= ~(CAN_FFA1R_FFA0);
	CAN1->FA1R |= CAN_FA1R_FACT0;
	CAN1->FMR &= ~(CAN_FMR_FINIT);
	CAN1->MCR &= ~(CAN_MCR_INRQ);
	while (CAN1->MSR & CAN_MSR_INAK_Msk) {}
	CAN1->IER |= CAN_IER_FMPIE0;
	NVIC_EnableIRQ(CAN1_RX0_IRQn);
}

void CAN1_Transmit(uint16_t id, uint8_t dlc, uint64_t data, bool wait_for_completion) {
	assert(dlc <= 8);
	uint8_t mailbox;
	uint64_t tme;
	while (1) {
		if (CAN1->TSR & CAN_TSR_TME0) {
			mailbox = 0;
			tme = CAN_TSR_TME0;
			break;
		}
		if (CAN1->TSR & CAN_TSR_TME1) {
			mailbox = 1;
			tme = CAN_TSR_TME1;
			break;
		}
		if (CAN1->TSR & CAN_TSR_TME2) {
			mailbox = 2;
			tme = CAN_TSR_TME2;
			break;
		}
	}
	id &= 0x7ff; // id length is 11 bits
	dlc &= 0xf; // data length is 4 bits
	CAN1->sTxMailBox[mailbox].TIR = id << CAN_TI0R_STID_Pos;
	CAN1->sTxMailBox[mailbox].TDTR = dlc;
	CAN1->sTxMailBox[mailbox].TDLR = data;
	CAN1->sTxMailBox[mailbox].TDHR = data >> 32;
	CAN1->sTxMailBox[mailbox].TIR |= CAN_TI0R_TXRQ;
	if (wait_for_completion) {
		while (!(CAN1->TSR & tme)) {}
	}
}

// everything on fifo 0 for now
bool CAN1_Receive(uint16_t* p_id, uint8_t* p_dlc, uint64_t* p_data) {
	if (CAN1->RF0R & CAN_RF0R_FMP0_Msk) {
		uint16_t id = CAN1->sFIFOMailBox[0].RIR >> CAN_RI0R_STID_Pos;
		uint8_t dlc = CAN1->sFIFOMailBox[0].RDTR & CAN_RDT0R_DLC_Msk;
		uint32_t low = CAN1->sFIFOMailBox[0].RDLR;
		uint32_t high = CAN1->sFIFOMailBox[0].RDHR;
		*p_id = id;
		*p_dlc = dlc;
		*p_data = ((uint64_t)high << 32) | low;
		CAN1->RF0R |= CAN_RF0R_RFOM0;
		return true;
	}
	return false;
}

void CAN1_RX0_IRQHandler() {
	uint16_t id = 0;
	uint8_t dlc = 0;
	uint64_t data = 0;
	if (CAN1_Receive(&id, &dlc, &data)) {
	}
}
