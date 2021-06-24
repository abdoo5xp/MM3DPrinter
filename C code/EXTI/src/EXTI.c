/*
 * EXTI.c
 *
 *  Created on: Jun 23, 2021
 *      Author: abdoo
 */


#include <stdint.h>
#include "../../lib/Bit_Mask.h"
#include "../../lib/Bit_Math.h"
#include "../../lib/Error_codes.h"
#include "RCC.h"
#include "EXTI.h"

#define	EXTI_SYSCFG			((void*) 0x40013808)
#define	EXTI				((void*) 0x40013C00)
#define	EXTI_BASE_ADD		(0x40013C00)

#define  EXTI_SYSCFG_MASK(val,IDX) 	(val << (IDX << 2))
#define  EXTI_SYSCFG_NUMBER_OF_BITS (0x0F)

#define NUM_OF_EXTI_CBFs		7

typedef struct
{
	uint32_t SYSCFG_EXTI_CR[4];
}SYSCFG_EXTI_t;

typedef struct
{
	uint32_t EXTI_IMR	;
	uint32_t EXTI_EMR	;
	uint32_t EXTI_RTSR	;
	uint32_t EXTI_FTSR	;
	uint32_t EXTI_SWIER	;
	uint32_t EXTI_PR	;
}EXTI_t;

static pfun EXTICallBacks[NUM_OF_EXTI_CBFs];

void EXTI_vidInit()
{
	RCC_ControlAPB2PeriClk(RCC_APB2_PREPH_SYSCFG, RCC_PREPH_ENABLE);
}


Status_e EXTI_enuEnableINT(EXTI_config_t * pinConfig)
{
	if (	pinConfig == NULL 		||
			pinConfig->EXTINum > 15 ||
			pinConfig->pinNum  > 15 ||
			pinConfig->port > _EXTI_PORTI_LENGTH_)
	{
		return _PARAM;
	}

	((volatile SYSCFG_EXTI_t *)EXTI_SYSCFG)->SYSCFG_EXTI_CR[pinConfig->pinNum >> 2] &=~ EXTI_SYSCFG_MASK(EXTI_SYSCFG_NUMBER_OF_BITS, pinConfig->EXTINum %4);
	((volatile SYSCFG_EXTI_t *)EXTI_SYSCFG)->SYSCFG_EXTI_CR[pinConfig->pinNum >> 2] |=  EXTI_SYSCFG_MASK(pinConfig->port, pinConfig->EXTINum %4) ;

	/*if it is interrupt then the base address will be the one of the interrupt
	 * if not the base address will be incremented by 4 which will give the bas address of the EMR */
	((volatile EXTI_t *)(EXTI + pinConfig->maskType))->EXTI_IMR = (1 << pinConfig->EXTINum);
//	((volatile EXTI_t *)(EXTI))->EXTI_EMR = (1 << pinConfig->EXTINum);

	if(pinConfig->EdgeDetectionType == EXTI_EDGE_RISING)
	{
		((volatile EXTI_t*)EXTI)->EXTI_RTSR |= (1 << pinConfig->EXTINum);
	}
	else if(pinConfig->EdgeDetectionType == EXTI_EDGE_FALLING)
	{
		((volatile EXTI_t*)EXTI)->EXTI_FTSR |= (1 << pinConfig->EXTINum);
	}
	else
	{
		((volatile EXTI_t*)EXTI)->EXTI_RTSR |= (1 << pinConfig->EXTINum);
		((volatile EXTI_t*)EXTI)->EXTI_FTSR |= (1 << pinConfig->EXTINum);
	}

	return _SUCCESS;
}

Status_e EXTI_enuSetCbf(pfun cbf, uint8_t EXTINum)
{
	if(EXTINum >= NUM_OF_EXTI_CBFs)
	{
		return _ERROR;
	}

	EXTICallBacks[EXTINum] = cbf;

	return _SUCCESS;
}

inline static void my_EXTI_IRQHandler(uint8_t EXTINum)
{
	/*Clear the pending of that interrupt */
	((volatile EXTI_t*)EXTI)->EXTI_PR |= (1 << EXTINum);

	if(EXTICallBacks[EXTINum])
	{
		EXTICallBacks[EXTINum]();
	}
}



EXTI0_IRQHandler(void)
{
	my_EXTI_IRQHandler(0);
}

EXTI1_IRQHandler(void)
{
	my_EXTI_IRQHandler(1);
}

EXTI2_IRQHandler(void)
{
	my_EXTI_IRQHandler(2);
}

EXTI3_IRQHandler(void)
{
	my_EXTI_IRQHandler(3);
}

EXTI4_IRQHandler(void)
{
	my_EXTI_IRQHandler(4);
}
