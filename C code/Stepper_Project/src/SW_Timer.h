/*
 * SW_Timer.h
 *
 *  Created on: Mar 10, 2021
 *      Author: micro
 */

#ifndef SW_TIMER_H_
#define SW_TIMER_H_

#include "SW_Timer_types.h"


/* Public Function: SW_Timer_Init														      *
 * Description: This function is used to Initialize SW_Timer
 *
 * Input parameters:
 *
 * Return:
 * 		- Status (uint8_t)
 *         RT_SUCCESS
 *         RT_PARAM
 *         RT_ERROR
 *         RT_TIME_OUT
 *
 * Input/Output Parameter:
 * 		- Not Applicable

 ***************************************************************************************************/
void SW_Timer_Init(void);


/* Public Function: SW_TimerRegisterCbf														      *
 * Description: This function is used to Register Functions
 *
 * Input parameters:
 * - SW_TimerCallBack (SW_Timer_cbf_t)
 * - SW_Timer_Time_ms (uint32_t) in range { Time in milliseconds }
 * - SW_TimerMode (SW_Timer_Mode_t) in range : { SW_Timer_Mode_Periodic , SW_Timer_Mode_Once }
 *
 * Return:
 * 		- Status (uint8_t)
 *         RT_SUCCESS
 *         RT_PARAM
 *         RT_ERROR
 *         RT_TIME_OUT
 *
 * Input/Output Parameter:
 * 		- Not Applicable

 ***************************************************************************************************/
uint8_t SW_TimerRegisterCbf(SW_Timer_cbf_t SW_TimerCallBack,uint32_t SW_Timer_Time_ms, SW_Timer_Mode_t SW_TimerMode);


/* Public Function: SW_TimerUnRegisterCbf														      *
 * Description: This function is used to Unregister Functions
 *
 * Input parameters:
 *
 * Return:
 * 		- Status (uint8_t)
 *         RT_SUCCESS
 *         RT_PARAM
 *         RT_ERROR
 *         RT_TIME_OUT
 *
 * Input/Output Parameter:
 * 		- Not Applicable

 ***************************************************************************************************/
uint8_t SW_TimerUnRegisterCbf(SW_Timer_cbf_t SW_TimerCallBack);


extern uint32_t counter ;

#endif /* SW_TIMER_H_ */
