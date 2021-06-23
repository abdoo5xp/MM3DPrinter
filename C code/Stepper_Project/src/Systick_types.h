/*
 * Systick_types.h
 *
 *  Created on: Mar 18, 2021
 *      Author: micro
 */

#ifndef SYSTICK_TYPES_H_
#define SYSTICK_TYPES_H_

typedef struct{

	uint8_t SysTick_Int;
	uint8_t SysTickCLK_Source;

}Systick_cfg_t;

extern const Systick_cfg_t Systick_cfg ;


#endif /* SYSTICK_TYPES_H_ */
