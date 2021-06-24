/*
 * Servo.c
 *
 *  Created on: Jun 22, 2021
 *      Author: Mohsen
 */



#include "../../lib/Bit_Mask.h"
#include "../../lib/Bit_Math.h"
#include "../../lib/Error_codes.h"

#include <stdint.h>
#include <stm32f4xx.h>
#include <stm32f4xx_hal_tim.h>
#include "diag/Trace.h"

#include "Rcc.h"
#include "GPIO.h"
#include "Heater.h"
#include "Heater_cfg.h"


static TIM_HandleTypeDef    HeaterConfigs;
static TIM_Base_InitTypeDef HeaterTimerInitConfigs;
static TIM_OC_InitTypeDef	HeaterOCInitConfigs;


extern Status_e HEATER_enuInit(uint8_t InitDutyCycle)
{
	uint8_t Return_status;

	HeaterTimerInitConfigs.Prescaler = 	TIMER_PRESCALER;
	HeaterTimerInitConfigs.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	HeaterTimerInitConfigs.CounterMode = TIM_COUNTERMODE_UP;

	/* 84,000,000 / 128 --> Ans /1000 , where 1000 is the desired frequency */
	HeaterTimerInitConfigs.Period = FREQUENCY_PERIOD_TICKS;

	HeaterTimerInitConfigs.RepetitionCounter = 0;


	HeaterConfigs.Channel  =             HAL_TIM_ACTIVE_CHANNEL_2;
	HeaterConfigs.Instance =             TIM3_BASE;
	HeaterConfigs.Lock     =             HAL_UNLOCKED;
	HeaterConfigs.State    =             HAL_TIM_STATE_RESET;
	HeaterConfigs.Init     =             HeaterTimerInitConfigs;


	/* choosing PWM mode 2, clear on compare match */
	HeaterOCInitConfigs.OCMode        =    TIM_OCMODE_PWM2;


	HeaterOCInitConfigs.Pulse         =	   (InitDutyCycle * FREQUENCY_PERIOD_TICKS )/100.0;

	HeaterOCInitConfigs.OCPolarity    =    TIM_OCPOLARITY_LOW;
	HeaterOCInitConfigs.OCIdleState   =    TIM_OCIDLESTATE_RESET;
	HeaterOCInitConfigs.OCFastMode    =    TIM_OCFAST_ENABLE;

	Return_status   =    HAL_TIM_PWM_Init(&HeaterConfigs);
	Return_status   |=   HAL_TIM_PWM_ConfigChannel(&HeaterConfigs, &HeaterOCInitConfigs, TIM_CHANNEL_2);

	return Return_status;
}


/* Duty Cycle in range of 0-100 % */
Status_e HEATER_enuChangeDutyCycle(uint8_t DutyCycle)
{
	uint8_t Return_status;

	HeaterOCInitConfigs.Pulse =	(DutyCycle * FREQUENCY_PERIOD_TICKS )/100.0;

	Return_status = HAL_TIM_PWM_ConfigChannel(&HeaterConfigs, &HeaterOCInitConfigs, TIM_CHANNEL_2);
	Return_status |= HAL_TIM_PWM_Start(&HeaterConfigs,TIM_CHANNEL_2);
	return Return_status;
}

/*-----------*/
Status_e HEATER_enuStart()
{
	uint8_t Return_status;

	Return_status = HAL_TIM_PWM_Start(&HeaterConfigs,TIM_CHANNEL_2);
	return Return_status;
}

Status_e HEATER_enuStop()
{
	uint8_t Return_status;
	Return_status = HAL_TIM_PWM_Stop(&HeaterConfigs,TIM_CHANNEL_2);
	return Return_status;
}


void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	/* our PWM pin (of timer 4 channel 1) is in Port B, pin 6 */
	gpio_pinConfig_t TimerConfigPin;
	TimerConfigPin.port  = GPIO_PORTB;
	TimerConfigPin.mode  = GPIO_MODE_AF;

	TimerConfigPin.pupd  = GPIO_NO_PULL;
	TimerConfigPin.otype = GPIO_OTYPE_PUSH_PULL;

	TimerConfigPin.pinNum= GPIO_PIN_6;
	TimerConfigPin.AF    = GPIO_AF2_TIM3_5; /* this macro covers timers from 3 -> 5 */

	TimerConfigPin.ospeed=GPIO_SPEED_HIGH;

	/* GPIO peripheral enable */
	trace_printf("RCC-1  Enable Return = %d\n ",Rcc_AHB1_PeriClockStatus(RCC_AHB1_PREPH_GPIOB, RCC_PREPH_ENABLE));

	/* timer peripheral enable */
	trace_printf("RCC-2 Enable Return = %d\n ",Rcc_APB1_PeriClockStatus(RCC_APB1_PERI_CLOCK_TIM3, RCC_PREPH_ENABLE));

	/* Init. the pin in GPIO */
	trace_printf("GPIO Enable Return = %d\n ",GPIO_InitPin(&TimerConfigPin));

}




