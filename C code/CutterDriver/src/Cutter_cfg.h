/*
 * Cutter_cfg.h
 *
 *  Created on: Jun 23, 2021
 *      Author: Mohsen
 */

#ifndef CUTTER_CFG_H_
#define CUTTER_CFG_H_



/* this number is a factor in determining the frequency of the PWM signal
 * the 'FREQUENCY_PERIOD_TICKS' is the value timer will count up to before reset */
#define FREQUENCY_PERIOD_TICKS 	13125

#define TIMER_PRESCALER 	128



/* providing cutting and withdraw angle for the cutter */
#define CUT_ANGLE              3
#define WITHDRAW_ANGLE         8




/* structure used by HAL functions */
extern const TIM_HandleTypeDef    CutterConfigs;
extern const TIM_Base_InitTypeDef CutterTimerInitConfigs;
extern       TIM_OC_InitTypeDef	  CutterOCInitConfigs;

/* timer DIO pin */
extern const gpio_pinConfig_t TimerConfigPin;

#endif /* CUTTER_CFG_H_ */
