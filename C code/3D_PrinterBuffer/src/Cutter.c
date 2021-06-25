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
#include "../../../lib/src/RT_Debug.h"
#include "../../lib/Bits.h"
#include "../../lib/Bit_Math.h"
#include "../../lib/Error_codes.h"
#include "Rcc_int.h"
#include "Gpio_int.h"
#include "Cutter.h"
#include "Cutter_cfg.h"

/*******************************************Cutter connected to PA1****************************************************/


Status_e Cutter_enuInit(void)
{
	uint8_t Return_status;

	/* add the pulse info before passing the structure */
//	CutterOCInitConfigs->Pulse = (InitAngle * FREQUENCY_PERIOD_TICKS )/100.0;

	/*********************************Clocks Enable********************************************************/
	trace_printf("RCC_1  Enable Return = %d\n ",Rcc_AHB1_PeriClockStatus(RCC_AHB1_PERI_CLOCK_GPIOA, RCC_PERI_CLOCK_ENABLE));
	trace_printf("RCC_2 Enable Return = %d\n ",Rcc_APB1_PeriClockStatus(RCC_APB1_PERI_CLOCK_TIM2, RCC_PERI_CLOCK_ENABLE));
	trace_printf("GPIO Enable Return = %d\n ",Gpio_Init(&TimerConfigPin));


	/* Bug Fix: assination of structure is made here instead of link time */
	CutterConfigs.Init     = CutterTimerInitConfigs;
	CutterOCInitConfigs.Pulse =	(WITHDRAW_ANGLE * FREQUENCY_PERIOD_TICKS )/100.0;

	Return_status = HAL_TIM_PWM_Init(&CutterConfigs);
	Return_status |= HAL_TIM_PWM_ConfigChannel(&CutterConfigs, &CutterOCInitConfigs, TIM_CHANNEL_1);

	return Return_status;
}

static Status_e Cutter_enuChangeAngle(uint8_t Cutter_Angle)
{
	uint8_t Return_status;
	CutterOCInitConfigs.Pulse =	(Cutter_Angle * FREQUENCY_PERIOD_TICKS )/100.0;

	Return_status = HAL_TIM_PWM_ConfigChannel(&CutterConfigs, &CutterOCInitConfigs, TIM_CHANNEL_1);
	Return_status |= HAL_TIM_PWM_Start(&CutterConfigs,TIM_CHANNEL_1);
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
