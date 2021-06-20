/*
 * LS_cfg.h
 *
 *  Created on: Jun 20, 2021
 *      Author: abdoo
 */

#ifndef LS_CFG_H_
#define LS_CFG_H_



typedef struct{
	void * port;
	uint32_t gpioPinNum;
}LS_Config_s;

/* Number of limit switches */
#define LS_INTANCES_NUMBER	2

/*Configure if the LS Sensor returns zero if is pressed or one */
#define LS_STATE_ON 	1
#define LS_STATE_OFF 	0


/*		in range {  GPIO_PORTA ,
 	 	 	 	 	GPIO_PORTB ,
 					GPIO_PORTC ,
 					GPIO_PORTD ,
 *					GPIO_PORTE ,
 *					GPIO_PORTF ,
 *					GPIO_PORTG ,
 *					GPIO_PORTH  }
*/



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


const LS_Config_s LS_instances[LS_INTANCES_NUMBER]=
{
	[0]={
		.port = GPIO_PORTB,
		.gpioPinNum = GPIO_PIN_2,
	},

	[1]={
		.port = GPIO_PORTB,
		.gpioPinNum = GPIO_PIN_5,
	},

};



#endif /* LS_CFG_H_ */
