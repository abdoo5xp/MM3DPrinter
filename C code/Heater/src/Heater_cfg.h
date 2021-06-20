/*
 * HEATER_cfg.h
 *
 *  Created on: Jun 20, 2021
 *      Author: abdoo
 */

#ifndef HEATER_CFG_H_
#define HEATER_CFG_H_

#define ACTIVE_LOW 		0
#define ACTIVE_HIGH 	1

/*Configure if the HEATER is turned on by setting one or zero */
#define HEATER_ACTIVE_STATE	ACTIVE_HIGH


/*		in range {  GPIO_PORTA ,
 	 	 	 	 	GPIO_PORTB ,
 					GPIO_PORTC ,
 					GPIO_PORTD ,
 *					GPIO_PORTE ,
 *					GPIO_PORTF ,
 *					GPIO_PORTG ,
 *					GPIO_PORTH  }
*/


#define HEATER_GPIO_PORT	GPIO_PORTA


/*
in range { GPIO_PIN_0	,
 *		   GPIO_PIN_1  ,
 *		   GPIO_PIN_2  ,
 *		   GPIO_PIN_3  ,
 *		   GPIO_PIN_4  ,
 *		   GPIO_PIN_5  ,
 *			GPIO_PIN_6  ,
 *			GPIO_PIN_7  ,
 *			GPIO_PIN_8  ,
 *			GPIO_PIN_9  ,
 *			GPIO_PIN_10 ,
 *			GPIO_PIN_11 ,
 *			GPIO_PIN_12 ,
 *			GPIO_PIN_13 ,
 *			GPIO_PIN_14 ,
 *			GPIO_PIN_15 }
 */
#define HEATER_GPIO_PINNUM	GPIO_PIN_6





#endif /* HEATER_CFG_H_ */
