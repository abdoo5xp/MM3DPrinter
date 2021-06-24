/*
 * Cutter_cfg.c
 *
 *  Created on: Jun 23, 2021
 *      Author: Mohsen
 */

#include <stdint.h>
#include <stm32f4xx.h>
#include <stm32f4xx_hal_tim.h>
#include "../../../lib/src/RT_Debug.h"
#include "../../lib/Bits.h"
#include "../../lib/Bit_Math.h"
#include "../../lib/Error_codes.h"
#include "Gpio_int.h"
#include "Cutter.h"
#include "Cutter_cfg.h"


/*******************************************Cutter connected to PA1****************************************************/


TIM_OC_InitTypeDef	CutterOCInitConfigs = {
		.OCMode = TIM_OCMODE_PWM2,
		//		.Pulse not gonna be initialized here
		.OCPolarity = TIM_OCPOLARITY_LOW,
		.OCIdleState = TIM_OCIDLESTATE_RESET,
		.OCFastMode = TIM_OCFAST_ENABLE,
};


TIM_Base_InitTypeDef CutterTimerInitConfigs = {
		.Prescaler         = TIMER_PRESCALER,
		.ClockDivision     = TIM_CLOCKDIVISION_DIV1,
		.CounterMode       = TIM_COUNTERMODE_UP,
		.Period            = FREQUENCY_PERIOD_TICKS,		/* 84,000,000 / 128 --> Ans /50 , where 50 is the desired frequency */
		.RepetitionCounter = 0,
};


TIM_HandleTypeDef    CutterConfigs = {

		.Instance = (TIM_TypeDef *) TIM2_BASE, /* casting to make 'TIM2_BASE' of the same type as 'Instance' */
		.Channel  = HAL_TIM_ACTIVE_CHANNEL_1,

		.Lock     = HAL_UNLOCKED,
		.State    = HAL_TIM_STATE_RESET,
};



/* timer DIO pin */
const Pincfg_t TimerConfigPin = {
		.Gpio_Mode  	 = GPIO_MODE_AF 		    		,
		.Gpio_OType 	 = GPIO_OTYPE_PUSH_PULL    			,
		.Gpio_OSpeed  = GPIO_OSPEED_VERY_HIGH_SPEED		,
		.Gpio_PUPD 	 = GPIO_PUPD_FLOATING				,
		.Gpio_Port  	 = GPIOA							,
		.Gpio_PinNum  = GPIO_PIN3						,
		.Gpio_AF = GPIO_AF1_TIM2
};
