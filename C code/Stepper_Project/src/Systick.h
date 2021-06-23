/*
 * Systick.h
 *
 *  Created on: Feb 25, 2021
 *      Author: micro
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_


#define 	SYSTICK_TICKS_LIMIT					0xFFFFFF


/* Public Function: Systick_Init															      *
 * Description: This function is used to Initialize Systick Timer
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
extern uint8_t Systick_Init(void);


/* Public Function: Systick_Start														      *
 * Description: This function is used make Systick timer start counting
 *
 * Input parameters:
 *
 * Return:
 *
 * Input/Output Parameter:
 * 		- Not Applicable

 ***************************************************************************************************/
extern void Systick_Start(void);


/* Public Function: Systick_SetTicks														      *
 * Description: This function is used to Set ticks that counter will start decrement from .
 *
 * Input parameters:
 *      - Systick_Time_ms	(uint32_t)
 *      - Systick_AHB_Freq 	(uint32_t)
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
extern uint8_t Systick_SetTicks(uint32_t Systick_Time_ms,uint32_t Systick_AHB_Freq);

/* Public Function: Systick_Disable														      *
 * Description: This function is used to Disable Systick Timer
 * Input parameters:
 *
 * Return
 * 		- Status (uint8_t)
 *         RT_SUCCESS
 *         RT_PARAM
 *         RT_ERROR
 *         RT_TIME_OUT
 *
 * Input/Output Parameter:
 * 		- Not Applicable

 ***************************************************************************************************/
void Systick_Disable(void);


/* Public Function: Systick_Callback														      *
 * Description: This function is used to Pass Function created in Application to Systick Handler (HIGH ,LOW)
 *
 * Input parameters:
 *
 * Return:
 *
 * Input/Output Parameter:
 * 		- void(*Ptr_Function)(void)

 ***************************************************************************************************/
void Systick_Callback(void(*Ptr_Function)(void));


void (*Ptr_SystickHandler)(void);


#endif /* SYSTICK_H_ */
