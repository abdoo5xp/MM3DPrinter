/*
 * Limit_SW_types.h
 *
 *  Created on: Jun 24, 2021
 *      Author: Islam
 */

#ifndef LIMIT_SW_TYPES_H_
#define LIMIT_SW_TYPES_H_

typedef enum
{
	EXTI_PORTA,
	EXTI_PORTB,
	EXTI_PORTC,
	EXTI_PORTD,
	EXTI_PORTE,
	EXTI_PORTF,
	EXTI_PORTG,
	EXTI_PORTH,
	EXTI_PORTI,
	_EXTI_PORTI_LENGTH_
}EXTI_ports_e;

typedef enum{
	EXTI_MASKTYPE_INTERRUPT = 0,
	EXTI_MASKTYPE_EVENT	= 4
}EXTI_maskType_e;

typedef enum{
	EXTI_EDGE_RISING  ,
	EXTI_EDGE_FALLING ,
	EXTI_EDGE_BOTH
}EXTI_EdgeType_e;


typedef struct{
	EXTI_ports_e port;	/*gpio port*/
	uint8_t pinNum;   	/*0-15*/
	uint8_t EXTINum;  	/*0-15*/
	EXTI_maskType_e maskType;
	EXTI_EdgeType_e EdgeDetectionType;
}EXTI_config_t;



#endif /* LIMIT_SW_TYPES_H_ */
