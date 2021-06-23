/*
 * SW_Timer_types.h
 *
 *  Created on: Mar 16, 2021
 *      Author: micro
 */

#ifndef SW_TIMER_TYPES_H_
#define SW_TIMER_TYPES_H_


typedef void (*SW_Timer_cbf_t)(void);

typedef enum {

SW_Timer_Mode_Periodic ,
SW_Timer_Mode_Once    ,
__SW_Timer_Mode_Length__

}SW_Timer_Mode_t;

typedef struct {

	SW_Timer_cbf_t Function ;
	SW_Timer_Mode_t Mode ;
	uint32_t Time_ms ;
	uint32_t Reload ;

}SW_TimerCbfList_t;

#endif /* SW_TIMER_TYPES_H_ */
