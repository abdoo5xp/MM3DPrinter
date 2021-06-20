/*
 * IR_cfg.h
 *
 *  Created on: Jun 20, 2021
 *      Author: abdoo
 */

#ifndef IR_CFG_H_
#define IR_CFG_H_

#define IR_STATE_ON 	1
#define IR_STATE_OFF 	0

/*		in range {  GPIO_PORTA ,
 	 	 	 	 	GPIO_PORTB ,
 					GPIO_PORTC ,
 					GPIO_PORTD ,
 *					GPIO_PORTE ,
 *					GPIO_PORTF ,
 *					GPIO_PORTG ,
 *					GPIO_PORTH  }
*/


#define IR_GPIO_PORT	GPIO_PORTA


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
#define IR_GPIO_PINNUM	GPIO_PIN_0





#endif /* IR_CFG_H_ */
