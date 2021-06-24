/*
 * Cutter.c
 *
 *  Created on: Jun 23, 2021
 *      Author: Mohsen
 */

#include <stdint.h>
#include <stm32f4xx.h>
#include <stm32f4xx_hal_tim.h>
#include "diag/Trace.h"

#include "../../lib/Bit_Mask.h"
#include "../../lib/Bit_Math.h"
#include "../../lib/Error_codes.h"

#include "Rcc.h"
#include "GPIO.h"

#include "Cutter.h"
#include "Cutter_cfg.h"



Status_e Cutter_enuInit(void)
{
	uint8_t Return_status;

	/* add the pulse info before passing the structure */
//	CutterOCInitConfigs->Pulse = (InitAngle * FREQUENCY_PERIOD_TICKS )/100.0;

	/* Bug Fix: assination of structure is made here instead of link time */
	CutterConfigs.Init     = CutterTimerInitConfigs;
	CutterOCInitConfigs.Pulse =	(WITHDRAW_ANGLE * FREQUENCY_PERIOD_TICKS )/100.0;

	Return_status = HAL_TIM_PWM_Init(&CutterConfigs);
	Return_status |= HAL_TIM_PWM_ConfigChannel(&CutterConfigs, &CutterOCInitConfigs, TIM_CHANNEL_4);

	return Return_status;
}


static Status_e Cutter_enuChangeAngle(uint8_t Cutter_Angle)
{
	uint8_t Return_status;
	CutterOCInitConfigs.Pulse =	(Cutter_Angle * FREQUENCY_PERIOD_TICKS )/100.0;

	Return_status = HAL_TIM_PWM_ConfigChannel(&CutterConfigs, &CutterOCInitConfigs, TIM_CHANNEL_4);
	Return_status |= HAL_TIM_PWM_Start(&CutterConfigs,TIM_CHANNEL_4);
	return Return_status;
}


Status_e Cutter_enuTurnOn(void)
{
	uint8_t Return_status;

	Return_status = Cutter_enuChangeAngle(CUT_ANGLE);
	return Return_status;
}

Status_e Cutter_enuTurnOff(void)
{
	uint8_t Return_status;

	Return_status = Cutter_enuChangeAngle(WITHDRAW_ANGLE);
	return Return_status;
}




/* No of Ticks = Timer_Tick_freq / Desired Frequency */
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	trace_printf("RCC_1  Enable Return = %d\n ",RCC_ControlAHB1PeriClk(RCC_AHB1_PREPH_GPIOA, RCC_PREPH_ENABLE));
	trace_printf("RCC_2 Enable Return = %d\n ",RCC_ControlAPB1PeriClk(RCC_APB1_PREPH_TIM2, RCC_PREPH_ENABLE));
	trace_printf("GPIO Enable Return = %d\n ",GPIO_InitPin(&TimerConfigPin));
}
