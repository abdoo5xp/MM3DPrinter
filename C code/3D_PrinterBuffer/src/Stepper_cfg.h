/*
 * Stepper_cfg.h
 *
 *  Created on: Jun 20, 2021
 *      Author: Islam
 */

#ifndef STEPPER_CFG_H_
#define STEPPER_CFG_H_

/*************************************Stepper Instances*****************************************************/
#define 	STEPPER_1						0
#define 	STEPPER_2		     			1
#define     STEPPER_3						2
#define     STEPPER_4						3

/*************************************Stepper Pins********************************************************/
#define 	STEPPER_ENABLE_PIN				0
#define 	STEPPER_DIR_PIN     			1
#define     STEPPER_PUL_PIN					2

/************************************Stepper_Pins_Num*****************************************************/
#define 	STEPPER_PINS_NUM				3

/************************************Steppers_Num*********************************************************/
#define 	STEPPER_NUM						2

/************************************Steps Per Revolution*************************************************/
#define 	STEPPER_STEP_PER_REVOLUTION		6400

/*THE APB1 BUS CLOCK IS 42 MHZ */
#define 	STEPPER_TIMER_PWM_PRESCALER 	0

#define 	STEPPER_TIMER_PWM_FREQ_Mhz		84

#define 	STEPPER_FREQUENCY_PERIOD_TICKS	4200

#define 	STEPPER_TIMER_BASE_PRESCALER 	49999  /* because prescaler internal = x + 1 from st*/


#endif /* STEPPER_CFG_H_ */
