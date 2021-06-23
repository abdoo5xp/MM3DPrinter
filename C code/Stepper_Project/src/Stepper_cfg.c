/*
 * Stepper_cfg.c
 *
 *  Created on: Jun 20, 2021
 *      Author: Islam
 */


#include <stdio.h>
#include <stdlib.h>
#include <stm32f4xx_hal.h>
#include <stm32f4xx_hal_conf.h>
#include <stm32f4xx_hal_tim.h>
#include "../../../lib/src/RT_Debug.h"
#include "../../../lib/src/Bits.h"
#include "Gpio_int.h"
#include "Stepper.h"
#include "Stepper_cfg.h"
#include "Stepper_types.h"



/* Configuration Parameters for each Led ************************************************************																		*
 *
 * 		- Gpio_Mode 	in range : { GPIO_MODE_xx  ( xx : - OUTPUT  - INPUT - ANALOG - AF )}
 * 		- Gpio_OType   	in range : { - GPIO_OTYPE_PUSH_PULL	 - GPIO_OTYPE_OPEN_DRAIN }
 * 		- Gpio_OSpeed  	in range : { GPIO_OSPEED_xx  ( xx : - LOW_SPEED     - MEDIUM_SPEED
 * 														    - HIGH_SPEE	   - VERY_HIGH_SPEED)}
 * 		- Gpio_PUPD 	in range : { GPIO_PUPD_xx ( xx : - FLOATING	- PULL_UP  - PULL_DOWN )}
 * 		- Gpio_AF 	  	in range : { GPIO_AFxx  (xx :  0 .. 15)}
 *      - Gpio_Port		in range : { GPIOxx (xx : A , B , C , D , E , H)}
 *      - Gpio_PinNum	in range : { GPIO_PINXX (xx :  0 .. 15)}
 *
 *		- Led_Mode 		in range : { LED_ACTIVE_HIGH - LED_ACTIVE_LOW }
 *
 ***************************************************************************************************/
Steppercfg_t Steppercfg[STEPPER_NUM] = {

		[STEPPER_1]	=
						{
						.Stepper_Pin[STEPPER_ENABLE_PIN] =
							{
							   .Gpio_Mode  	 = GPIO_MODE_OUTPUT 		    	,
							   .Gpio_OType 	 = GPIO_OTYPE_PUSH_PULL    			,
							   .Gpio_OSpeed  = GPIO_OSPEED_VERY_HIGH_SPEED		,
							   .Gpio_PUPD 	 = GPIO_PUPD_PULL_UP 				,
							   .Gpio_Port  	 = GPIOD							,
							   .Gpio_PinNum  = GPIO_PIN13
							},
						.Stepper_Pin[STEPPER_DIR_PIN] =
							{
							   .Gpio_Mode  	 = GPIO_MODE_OUTPUT  				,
							   .Gpio_OType 	 = GPIO_OTYPE_PUSH_PULL    			,
							   .Gpio_OSpeed  = GPIO_OSPEED_VERY_HIGH_SPEED		,
							   .Gpio_PUPD 	 = GPIO_PUPD_PULL_UP 				,
							   .Gpio_Port  	 = GPIOD							,
							   .Gpio_PinNum  = GPIO_PIN14
							},
						.Stepper_Pin[STEPPER_PUL_PIN] =
							{
							   .Gpio_Mode  	 = GPIO_MODE_AF 		    		,
							   .Gpio_OType 	 = GPIO_OTYPE_PUSH_PULL    			,
							   .Gpio_OSpeed  = GPIO_OSPEED_VERY_HIGH_SPEED		,
							   .Gpio_PUPD 	 = GPIO_PUPD_FLOATING				,
							   .Gpio_Port  	 = GPIOB							,
							   .Gpio_PinNum  = GPIO_PIN9						,
							   .Gpio_AF = GPIO_AF2
							}
						},
		[STEPPER_2]	=
								{
								.Stepper_Pin[STEPPER_ENABLE_PIN] =
									{
									   .Gpio_Mode  	 = GPIO_MODE_OUTPUT 		    	,
									   .Gpio_OType 	 = GPIO_OTYPE_PUSH_PULL    			,
									   .Gpio_OSpeed  = GPIO_OSPEED_VERY_HIGH_SPEED		,
									   .Gpio_PUPD 	 = GPIO_PUPD_PULL_UP 				,
									   .Gpio_Port  	 = GPIOD							,
									   .Gpio_PinNum  = GPIO_PIN11
									},
								.Stepper_Pin[STEPPER_DIR_PIN] =
									{
									   .Gpio_Mode  	 = GPIO_MODE_OUTPUT  				,
									   .Gpio_OType 	 = GPIO_OTYPE_PUSH_PULL    			,
									   .Gpio_OSpeed  = GPIO_OSPEED_VERY_HIGH_SPEED		,
									   .Gpio_PUPD 	 = GPIO_PUPD_PULL_UP 				,
									   .Gpio_Port  	 = GPIOD							,
									   .Gpio_PinNum  = GPIO_PIN12
									},
								.Stepper_Pin[STEPPER_PUL_PIN] =
									{
									   .Gpio_Mode  	 = GPIO_MODE_AF 		    		,
									   .Gpio_OType 	 = GPIO_OTYPE_PUSH_PULL    			,
									   .Gpio_OSpeed  = GPIO_OSPEED_VERY_HIGH_SPEED		,
									   .Gpio_PUPD 	 = GPIO_PUPD_FLOATING				,
									   .Gpio_Port  	 = GPIOB							,
									   .Gpio_PinNum  = GPIO_PIN8						,
									   .Gpio_AF = GPIO_AF2
									}
								}
};

StepperChannelcfg_t StepperChannelcfg[STEPPER_NUM] ={

		[STEPPER_1] = {

				.StepperTimerInitConfigs =
				{
						.Prescaler 			= STEPPER_TIMER_PWM_PRESCALER	,
						.ClockDivision 		= TIM_CLOCKDIVISION_DIV1	,
						.CounterMode 		= TIM_COUNTERMODE_UP		,
						.Period 			= STEPPER_FREQUENCY_PERIOD_TICKS, 		/* 84,000,000 / desired frequency */
						.RepetitionCounter 	= 0
				},
					.StepperConfigs =
				{
						.Channel 			= HAL_TIM_ACTIVE_CHANNEL_4	,
						.Instance			= TIM4_BASE 				,
						.Lock 				= HAL_UNLOCKED 				,
						.State 				= HAL_TIM_STATE_RESET		,
						//.Init 				= StepperChannelcfg[STEPPER_1].StepperTimerInitConfigs
				},
				.StepperOCInitConfigs =
				{
						.OCMode 			= TIM_OCMODE_PWM2						,
						.Pulse 				= STEPPER_FREQUENCY_PERIOD_TICKS / 2	,
						.OCPolarity 		= TIM_OCPOLARITY_LOW					,
						.OCIdleState 		= TIM_OCIDLESTATE_RESET					,
						.OCFastMode 		= TIM_OCFAST_ENABLE
				},
				.StepperChannel = TIM_CHANNEL_4
		},

		[STEPPER_2] = {

				.StepperTimerInitConfigs =
				{
						.Prescaler 			= STEPPER_TIMER_PWM_PRESCALER	,
						.ClockDivision 		= TIM_CLOCKDIVISION_DIV1	,
						.CounterMode 		= TIM_COUNTERMODE_UP		,
						.Period 			= STEPPER_FREQUENCY_PERIOD_TICKS, 		/* 84,000,000 / desired frequency */
						.RepetitionCounter 	= 0
				},
					.StepperConfigs =
				{
						.Channel 			= HAL_TIM_ACTIVE_CHANNEL_3	,
						.Instance			= TIM4_BASE 				,
						.Lock 				= HAL_UNLOCKED 				,
						.State 				= HAL_TIM_STATE_RESET		,
						//.Init 				= StepperChannelcfg[STEPPER_1].StepperTimerInitConfigs
				},
				.StepperOCInitConfigs =
				{
						.OCMode 			= TIM_OCMODE_PWM2						,
						.Pulse 				= STEPPER_FREQUENCY_PERIOD_TICKS / 2	,
						.OCPolarity 		= TIM_OCPOLARITY_LOW					,
						.OCIdleState 		= TIM_OCIDLESTATE_RESET					,
						.OCFastMode 		= TIM_OCFAST_ENABLE
				},
				.StepperChannel = TIM_CHANNEL_3
		}
};
