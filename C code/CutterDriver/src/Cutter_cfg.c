/*
 * Cutter_cfg.c
 *
 *  Created on: Jun 23, 2021
 *      Author: Mohsen
 */

#include <stdint.h>

#include <stm32f4xx.h>
#include <stm32f4xx_hal_tim.h>

#include "../../lib/Bit_Mask.h"
#include "../../lib/Bit_Math.h"
#include "../../lib/Error_codes.h"

#include "Rcc.h"
#include "GPIO.h"

#include "Cutter.h"
#include "Cutter_cfg.h"


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
		.Channel  = HAL_TIM_ACTIVE_CHANNEL_4,

		.Lock     = HAL_UNLOCKED,
		.State    = HAL_TIM_STATE_RESET,
};



/* timer DIO pin */
const gpio_pinConfig_t TimerConfigPin = {

		.port     = GPIO_PORTA,
		.mode     = GPIO_MODE_AF,

		.pupd     = GPIO_NO_PULL,
		.otype    = GPIO_OTYPE_PUSH_PULL,

		.pinNum   = GPIO_PIN_3,
		.AF       = GPIO_AF1_TIM1_TIM2,

		.ospeed   = GPIO_SPEED_HIGH,
};
