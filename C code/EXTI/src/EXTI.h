/*
 * EXTI.h
 *
 *  Created on: Jun 23, 2021
 *      Author: abdoo
 */

#ifndef EXTI_H_
#define EXTI_H_

typedef void (*pfun)(void);
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

void EXTI_vidInit();

Status_e EXTI_enuEnableINT(EXTI_config_t * pinConfig);

Status_e EXTI_enuSetCbf(pfun cbf, uint8_t EXTINum);

#endif /* EXTI_H_ */
