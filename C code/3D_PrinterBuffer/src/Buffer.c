/*
 * Buffer.c
 *
 *  Created on: Jun 23, 2021
 *      Author: Islam
 */

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "../../../lib/src/Bits.h"
#include "../../lib/Bit_Mask.h"
#include "../../../lib/src/Bit_Math.h"
#include "../../../lib/src/RT_Debug.h"
#include "../../lib/Error_codes.h"
#include "Gpio_int.h"
#include "NVIC.h"
#include "Stepper.h"
#include "Limit_SW_types.h"
#include "Limit_SW.h"


static void Buffer_IsFull(void)
{
	trace_printf("Allah <3 \n");

	Stepper_Pause();

}


static void Buffer_IsEmpty(void)
{
	trace_printf("Allah Akbar <3 ");
	Stepper_Continue(Stepper_Working);

}

void Buffer_Init(void)
{
	LimitSW_vidInit();
	LimitSW_SetCallBack(Buffer_IsFull,LimitSWcfg[LIMIT_SW_1].exti_config.EXTINum);
	LimitSW_SetCallBack(Buffer_IsEmpty,LimitSWcfg[LIMIT_SW_2].exti_config.EXTINum);
	for (uint32_t EXINT_LineIdx = 0 ; EXINT_LineIdx < LIMIT_SW_NUM ; EXINT_LineIdx++ )
	{
		NVIC_EnableIntr(LimitSWcfg[EXINT_LineIdx].EXINT_Line);
	}
	for (uint32_t LimitSW_Idx = 0 ; LimitSW_Idx < LIMIT_SW_NUM ; LimitSW_Idx++)
	{
		LimitSW_enuEnableINT(&LimitSWcfg[LimitSW_Idx].exti_config);
	}
}


