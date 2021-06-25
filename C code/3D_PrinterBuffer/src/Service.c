/*
 * Service.c
 *
 *  Created on: Jun 23, 2021
 *      Author: abdoo
 */


#include <stdint.h>
#include "../../lib/Bits.h"
#include "../../lib/Error_codes.h"
#include "../../../lib/src/RT_Debug.h"
#include <stm32f4xx_hal.h>
#include <stm32f4xx_hal_tim.h>
#include "Rcc_int.h"
#include "App_cfg.h"
#include "Service.h"

/*************************************************Timer Base***************************************************************/
static uint32_t Heater_CutterTimerBasePeriodTicks =  0 ;//12000//6563

static TIM_HandleTypeDef    TimerBaseConfigs;
static TIM_Base_InitTypeDef TimerBaseTimerInitConfigs;


RT_Debug Service_TimerBaseInit(void)
{
	RT_Debug Return_status;

	Rcc_APB2_PeriClockStatus(RCC_APB2_PERI_CLOCK_TIM9, RCC_PERI_CLOCK_ENABLE);

	TimerBaseTimerInitConfigs.Prescaler     = APP_TIMER_BASE_PRESCALER;
	TimerBaseTimerInitConfigs.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	TimerBaseTimerInitConfigs.CounterMode   = TIM_COUNTERMODE_UP;

	/* 84,000,000 / desired frequency */
	TimerBaseTimerInitConfigs.Period        = Heater_CutterTimerBasePeriodTicks;

	/*TimerBaseTimerInitConfigs.RepetitionCounter parameter is valid only for TIM1 and TIM8.*/


	TimerBaseConfigs.Channel  =             HAL_TIM_ACTIVE_CHANNEL_1;
	TimerBaseConfigs.Instance =             TIM9_BASE;
	TimerBaseConfigs.Lock     =             HAL_UNLOCKED;
	TimerBaseConfigs.State    =             HAL_TIM_STATE_RESET;
	TimerBaseConfigs.Init     =             TimerBaseTimerInitConfigs;


	Return_status   =    HAL_TIM_Base_Init(&TimerBaseConfigs);
	trace_printf("HAL_TIM_Base_Init = %d\n",Return_status);

	//TIM_Base_SetConfig already exist inside 'HAL_TIM_Base_Init' function implementation
	return Return_status;
}


uint32_t Service_u32Concat(uint8_t *NumbersArray, uint8_t ArraySize)
{
	uint8_t LoopIdx;
	uint32_t result = 0;
	for(LoopIdx = 0; LoopIdx < ArraySize; LoopIdx++)
	{
		result |= NumbersArray[LoopIdx] << (LoopIdx << 3 );
	}
	return result;
}


RT_Debug Service_enuDelay(uint32_t delay)
{
	RT_Debug Return_Status = RT_SUCCESS ;
	/*************************************Heater_Timer_Delay_Reconfigure********************************/
	TimerBaseTimerInitConfigs.Period = delay;
	TimerBaseConfigs.Init    		 = TimerBaseTimerInitConfigs;
	Return_Status = HAL_TIM_Base_Init(&TimerBaseConfigs);
	/********************************************************Timer Base Start********************************************************************/
	(TimerBaseConfigs.Instance->SR) &= ~(TIM_IT_UPDATE);
	Return_Status = HAL_TIM_Base_Start_IT(&TimerBaseConfigs);//passing htim pointer to struct
	while((TimerBaseConfigs.Instance->SR & TIM_FLAG_UPDATE) != TIM_FLAG_UPDATE);
	Return_Status = HAL_TIM_Base_Stop_IT(&TimerBaseConfigs); //passing htim pointer to struct

	return Return_Status ;
}

