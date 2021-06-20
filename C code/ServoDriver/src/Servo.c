/*
 * Servo.c
 *
 *  Created on: Jun 20, 2021
 *      Author: abdoo
 */


#include <stdint.h>
#include <stm32f4xx.h>
#include <stm32f4xx_hal_tim.h>

#include "../../lib/Bit_Mask.h"
#include "../../lib/Bit_Math.h"
#include "../../lib/Error_codes.h"
#include "Rcc.h"
#include "GPIO.h"
#include "Servo.h"
#include "Servo_cfg.h"
#include "Servo_priv.h"


static TIM_HandleTypeDef ServoConfigs;
static TIM_Base_InitTypeDef ServoTimerInitConfigs;
static TIM_OC_InitTypeDef	ServoOCInitConfigs;


#define FREQUENCY_PERIOD_TICKS 	13125
/*THE APB1 BUS CLOCK IS 84 MHZ */
#define TIMER_PRESCALER 	128

Status_e SERVO_enuInit(Servo_Angles_e InitAngle)
{
	uint8_t Return_status;

	ServoTimerInitConfigs.Prescaler = TIMER_PRESCALER;
	ServoTimerInitConfigs.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	ServoTimerInitConfigs.CounterMode = TIM_COUNTERMODE_UP;
	ServoTimerInitConfigs.Period = FREQUENCY_PERIOD_TICKS; 		/* 84,000,000 / 128 --> Ans /50 , where 50 is the desired frequency */
	ServoTimerInitConfigs.RepetitionCounter = 0;


	ServoConfigs.Channel = HAL_TIM_ACTIVE_CHANNEL_4;
	ServoConfigs.Instance= TIM2_BASE;
	ServoConfigs.Lock = HAL_UNLOCKED;
	ServoConfigs.State = HAL_TIM_STATE_RESET;
	ServoConfigs.Init = ServoTimerInitConfigs;


	ServoOCInitConfigs.OCMode = TIM_OCMODE_PWM2;
	ServoOCInitConfigs.Pulse =	(InitAngle * FREQUENCY_PERIOD_TICKS )/100.0;
	ServoOCInitConfigs.OCPolarity = TIM_OCPOLARITY_LOW;
	ServoOCInitConfigs.OCIdleState = TIM_OCIDLESTATE_RESET;
	ServoOCInitConfigs.OCFastMode = TIM_OCFAST_ENABLE;

	Return_status = HAL_TIM_PWM_Init(&ServoConfigs);
	Return_status |= HAL_TIM_PWM_ConfigChannel(&ServoConfigs, &ServoOCInitConfigs, TIM_CHANNEL_4);

	return Return_status;
}


Status_e SERVO_enuChangeAngle(Servo_Angles_e Servo_Angle)
{

	uint8_t Return_status;

	ServoOCInitConfigs.Pulse =	(Servo_Angle * FREQUENCY_PERIOD_TICKS )/100.0;


	Return_status = HAL_TIM_PWM_ConfigChannel(&ServoConfigs, &ServoOCInitConfigs, TIM_CHANNEL_4);
	Return_status |= HAL_TIM_PWM_Start(&ServoConfigs,TIM_CHANNEL_4);
	return Return_status;
}


Status_e SERVO_enuStart()
{	uint8_t Return_status;

Return_status = HAL_TIM_PWM_Start(&ServoConfigs,TIM_CHANNEL_4);
return Return_status;
}


/*
 *
 * No of Ticks = Timer_Tick_freq / Desired Frequency
 *
 * */
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	gpio_pinConfig_t TimerConfigPin;
	TimerConfigPin.port  = GPIO_PORTA;
	TimerConfigPin.mode  = GPIO_MODE_AF;

	TimerConfigPin.pupd  = GPIO_NO_PULL;
	TimerConfigPin.otype = GPIO_OTYPE_PUSH_PULL;

	TimerConfigPin.pinNum= GPIO_PIN_3;
	TimerConfigPin.AF    = GPIO_AF1_TIM1_TIM2;

	TimerConfigPin.ospeed=GPIO_SPEED_HIGH;

	trace_printf("RCC-1  Enable Return = %d\n ",RCC_ControlAHB1PeriClk(RCC_AHB1_PREPH_GPIOA, RCC_PREPH_ENABLE));
	trace_printf("RCC-2 Enable Return = %d\n ",RCC_ControlAPB1PeriClk(RCC_APB1_PREPH_TIM2, RCC_PREPH_ENABLE));
	trace_printf("GPIO Enable Return = %d\n ",GPIO_InitPin(&TimerConfigPin));

}




