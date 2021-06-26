/*
 * Servo_cfg.h
 *
 *  Created on: Jun 22, 2021
 *      Author: Mohsen
 */

#ifndef HEATER_CFG_H_
#define HEATER_CFG_H_

/* read the ReadMe file for more info. */

#define HEATER_PORT				GPIOC
#define HEATER_PIN				GPIO_PIN6

#define FREQUENCY_PERIOD_TICKS 	1312

#define TIMER_PRESCALER 	    127  /* because prescaler internal = x + 1 from st*/


#endif /* HEATER_CFG_H_ */
