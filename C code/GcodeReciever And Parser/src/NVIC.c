/*
 * NVIC.c
 *
 *  Created on: Feb 22, 2021
 *      Author: abdoo
 *
 *      memory is word addressable so every register is four addresses
 *
 */

#include <stdint.h>
#include "../../lib/Bit_Mask.h"
#include "../../lib/Bit_Math.h"
#include "../../lib/Error_codes.h"
#include "NVIC.h"
#define NULL 		(void *) 0

typedef struct{
	uint32_t iser[8];
	uint32_t Res0[24];
	uint32_t icer[8];
	uint32_t Res1[24];
	uint32_t ispr[8];
	uint32_t Res2[24];
	uint32_t icpr[8];
	uint32_t Res3[24];
	uint32_t iabr[8];
	uint32_t Res4[56];
	uint8_t  ipr[240];
	//pinnumber/32
}nvic_t;

/*we could have made this Register is for CFSR */
/*
typedef union{
	struct{
	uint8_t MMSR;
	uint8_t BFSR;
	uint16_t UFSR ;
	}fields;

	uint32_t allReg;
};
*/
typedef struct {

	uint32_t CPUID  ;
	uint32_t ICSR   ;
	uint32_t VTOR   ;
	uint32_t AIRCR  ;
	uint32_t SCR    ;
	uint32_t CCR    ;
	uint32_t SHPR1  ;
	uint32_t SHPR2  ;
	uint32_t SHPR3  ;
	uint32_t SHCSR  ;

	/*this Register is for CFSR */
	uint8_t  MMSR   ;
	uint8_t  BFSR   ;
	uint16_t UFSR   ;

	uint32_t HFSR   ;
	uint32_t MMAR   ;
	uint32_t BFAR   ;
	uint32_t AFSR   ;

}scb_t;

#define NVIC_STIR				(*(volatile uint32_t*)  0xE000EF00)
#define NVIC		 			((volatile nvic_t *)  0xE000E100)
#define NVIC_SCB				((volatile scb_t  *)  0xE000ED00)

/*This function is used to Clear the PRIMASK which enables all the IRQs*/
void NVIC_EnableAll(){
	asm("CPSIE I");
}

/*This function is used to Set the PRIMASK which disables all the IRQs*/
void NVIC_DisableAll(){
	asm("CPSID I");
}

/* **************************************************************************************************************
 * Public Function: NVIC_EnableIntr
 * Description: This function is used to Select a System clock from the provided RCC clocks
 * Input Parameters:
 * 					-uint32_t RCC_Clk_Ctrl : in range { RCC_HSI,
 *                                                      RCC_HSE,
 *			                                            RCC_PLL }
 *
 *
 * Return:           -uint8_t : in range {  RT_PARAM,
 *											RT_ERROR,
 *											RT_SUCCESS }
 *
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
uint32_t NVIC_EnableIntr(irqn_t Nvic_Intr){
	if(Nvic_Intr <0 || Nvic_Intr > 81 ){
		return RT_PARAM;
	}
	/*this register of you put a zero value will have no effect */
	NVIC->iser[ Nvic_Intr/32] = (1 << Nvic_Intr%32);

	return RT_SUCCESS;
}

uint32_t NVIC_DisableIntr(irqn_t Nvic_Intr){
	if(Nvic_Intr <0 || Nvic_Intr > 81 ){
		return RT_PARAM;
	}

	NVIC->icer[ Nvic_Intr/32] = (1 << Nvic_Intr%32);

	return RT_SUCCESS;
}

uint8_t NVIC_SetPriority(irqn_t Nvic_Intr, uint8_t Priority){
	if(Nvic_Intr <0 || Nvic_Intr > 81
			||
			(Priority != NVIC_PRIO_0   &&
			Priority != NVIC_PRIO_1   &&
			Priority != NVIC_PRIO_2   &&
			Priority != NVIC_PRIO_3   &&
			Priority != NVIC_PRIO_4   &&
			Priority != NVIC_PRIO_5   &&
			Priority != NVIC_PRIO_6   &&
			Priority != NVIC_PRIO_7   &&
			Priority != NVIC_PRIO_8   &&
			Priority != NVIC_PRIO_9   &&
			Priority != NVIC_PRIO_10  &&
			Priority != NVIC_PRIO_11  &&
			Priority != NVIC_PRIO_12  &&
			Priority != NVIC_PRIO_13  &&
			Priority != NVIC_PRIO_14  )

	){
			return RT_PARAM;
	}

	NVIC ->ipr[Nvic_Intr] = Priority;

	return RT_SUCCESS;
}

uint32_t NVIC_SetPending(irqn_t Nvic_Intr){
	if(Nvic_Intr <0 || Nvic_Intr > 81 ){
		return RT_PARAM;
	}

	NVIC->ispr[ Nvic_Intr/32] = (1 << Nvic_Intr%32);

	return RT_SUCCESS;
}

uint32_t NVIC_ClearPending(irqn_t Nvic_Intr){
	if(Nvic_Intr <0 || Nvic_Intr > 81 ){
		return RT_PARAM;
	}

	NVIC->icpr[ Nvic_Intr/32] = (1 << Nvic_Intr%32);

	return RT_SUCCESS;
}

#define NVIC_GROUP_CLEAR_MASK 			(uint32_t)0x0000F8FF

uint32_t NVIC_SetPriorityGrouping(uint32_t PriorityGroup){
	if( 	PriorityGroup != NVIC_GROUP_0 &&
			PriorityGroup != NVIC_GROUP_1 &&
			PriorityGroup != NVIC_GROUP_2 &&
			PriorityGroup != NVIC_GROUP_3 &&
			PriorityGroup != NVIC_GROUP_4 &&
			PriorityGroup != NVIC_GROUP_5 &&
			PriorityGroup != NVIC_GROUP_6 &&
			PriorityGroup != NVIC_GROUP_7){
		return RT_PARAM;
	}

	uint32_t loc_RegVal =  	NVIC_SCB->AIRCR & NVIC_GROUP_CLEAR_MASK;
	loc_RegVal |= PriorityGroup;

	NVIC_SCB->AIRCR = loc_RegVal;

	return RT_SUCCESS;
}

#define NVIC_GROUP_MASK 			(uint32_t)0x00000700

uint32_t NVIC_GetPriorityGrouping(uint32_t *PriorityGroup){
	if(PriorityGroup == NULL ){
		return RT_PARAM;
	}

	/*The read value of the most 16 bits are different from our macros so we convert them*/
	*PriorityGroup = ((NVIC_SCB->AIRCR & NVIC_GROUP_MASK) | 0x5FA00000);

	return RT_SUCCESS ;
}

/*TODO:add Get Active*/


/* Here we can use this function to go to from user mode to privilage mode
 *  when we said that we need to throw an exception to switch from user mode to privilage mode  */
uint32_t NVIC_GenerateSWIntr(irqn_t Nvic_Intr){
	if(Nvic_Intr <0 || Nvic_Intr > 81 ){
		return RT_PARAM;
	}

	NVIC_STIR  = Nvic_Intr;

	return RT_SUCCESS;
}
								/*range  = {0->7} */			/*0->127*/		/*0->255*/
uint32_t NVIC_EncodePriority(uint32_t PriorityGroup, uint32_t PreemptPriority,uint32_t SubPriority ){
	uint32_t Priority;
	/*Mask the result of shifting the preempt value with the number of priority group +1 */
	Priority =  ( (PreemptPriority) << (PriorityGroup+1) ) & ~CONV_TO_ONES(PriorityGroup+1);

	/*Mask the subPriority to make sure that the user entered it in the correct range */
	Priority |= (SubPriority & CONV_TO_ONES(PriorityGroup+1));


	return Priority;
}


#define CONV_TO_ONES(Num)				~( (0xFF) << (Num) )
void NVIC_DecodePriority( uint8_t Priority, uint8_t PriorityGroup, uint8_t* PreemptPriority,uint8_t *SubPriority ){

	/*an idea we should shift the preempt priority >> priorityGroup+1 */
	*PreemptPriority = Priority &~CONV_TO_ONES(PriorityGroup+1);
	*SubPriority = Priority & CONV_TO_ONES(PriorityGroup+1);
}











