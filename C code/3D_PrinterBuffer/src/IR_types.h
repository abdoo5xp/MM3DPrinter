/*
 * Led_Types.h
 *
 *  Created on: Feb 22, 2021
 *      Author: micro
 */

#ifndef IR_TYPES_H_
#define IR_TYPES_H_


typedef struct {
	Pincfg_t Led_Pin 		;
}IRcfg_t;

extern const IRcfg_t IRcfg[IR_NUM];

#endif /* IR_TYPES_H_ */
