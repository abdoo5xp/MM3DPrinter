/*
 * EXTI.c
 *
 *  Created on: Jun 23, 2021
 *      Author: abdoo
 */

#include <stdint.h>
#include "../../lib/Bits.h"
#include "../../lib/Bit_Math.h"
#include "../../lib/Error_codes.h"
#include "../../../lib/src/RT_Debug.h"
#include "GPIO_int.h"
#include "Rcc_int.h"
#include "NVIC.h"
#include "Limit_SW_types.h"
#include "Limit_SW.h"

#define	EXTI_SYSCFG			((void*) 0x40013808)
#define	EXTI				((void*) 0x40013C00)
#define	EXTI_BASE_ADD		(0x40013C00)

#define  EXTI_SYSCFG_MASK(val,IDX) 	(val << (IDX << 2))
#define  EXTI_SYSCFG_NUMBER_OF_BITS (0x0F)

#define NUM_OF_EXTI_CBFs		5

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


uint64_t LimitSW_Gpio[5] =
{
		RCC_AHB1_PERI_CLOCK_GPIOA ,
		RCC_AHB1_PERI_CLOCK_GPIOB,
		RCC_AHB1_PERI_CLOCK_GPIOC,
		RCC_AHB1_PERI_CLOCK_GPIOD,
		RCC_AHB1_PERI_CLOCK_GPIOE
};

void LimitSW_vidInit(void)
{
	uint32_t LimitSW_Gpio_Idx ;

	/*****************************************External Interrupt********************************************/
	Rcc_APB2_PeriClockStatus(RCC_APB2_PERI_CLOCK_SYSCFG, RCC_PERI_CLOCK_ENABLE);

	for (uint8_t Limit_Pin_Idx = 0 ; Limit_Pin_Idx < LIMIT_SW_NUM ; Limit_Pin_Idx++)
	{
		LimitSW_Gpio_Idx = (uint32_t)(((uint32_t)(LimitSWcfg[Limit_Pin_Idx].btn_config.Gpio_Port) - (uint32_t)0x40020000) / (uint32_t)0x400);
		Rcc_AHB1_PeriClockStatus(LimitSW_Gpio[LimitSW_Gpio_Idx],RCC_PERI_CLOCK_ENABLE);
		Gpio_Init(&LimitSWcfg[Limit_Pin_Idx].btn_config);
	}
}


RT_Debug LimitSW_enuEnableINT(EXTI_config_t * pinConfig)
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
	((volatile EXTI_t *)(EXTI + pinConfig->maskType))->EXTI_IMR |= (1 << pinConfig->EXTINum);
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

RT_Debug LimitSW_SetCallBack(pfun cbf, uint8_t EXTINum)
{
	if(EXTINum >= NUM_OF_EXTI_CBFs && cbf != NULL )
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



void EXTI0_IRQHandler(void)
{
	my_EXTI_IRQHandler(0);
}

void EXTI1_IRQHandler(void)
{
	my_EXTI_IRQHandler(1);
}

void EXTI2_IRQHandler(void)
{
	my_EXTI_IRQHandler(2);
}

void EXTI3_IRQHandler(void)
{
	my_EXTI_IRQHandler(3);
}

void EXTI4_IRQHandler(void)
{
	my_EXTI_IRQHandler(4);
}
