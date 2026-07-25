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
}
