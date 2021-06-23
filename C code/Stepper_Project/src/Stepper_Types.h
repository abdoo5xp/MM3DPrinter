/*
 * Stepper_Types.h
 *
 *  Created on: Jun 20, 2021
 *      Author: Islam
 */

#ifndef STEPPER_TYPES_H_
#define STEPPER_TYPES_H_

typedef struct {
	Pincfg_t Stepper_Pin[STEPPER_PINS_NUM] 		;
}Steppercfg_t;

typedef struct
{
TIM_HandleTypeDef StepperConfigs;
TIM_Base_InitTypeDef StepperTimerInitConfigs;
TIM_OC_InitTypeDef	StepperOCInitConfigs;
uint32_t StepperChannel ;
}StepperChannelcfg_t;

extern Steppercfg_t Steppercfg[STEPPER_NUM];

extern StepperChannelcfg_t StepperChannelcfg[STEPPER_NUM];

#endif /* STEPPER_TYPES_H_ */
