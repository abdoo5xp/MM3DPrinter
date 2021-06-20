/*
 * IR.h
 *
 *  Created on: Jun 20, 2021
 *      Author: abdoo
 */

#ifndef LS_H_
#define LS_H_

typedef enum{
	LS_State_NotPressed,
	LS_State_Pressed
}LS_State_e;

/**************************************************************************************************************
 * Public Function:LS_enuGetState
 * Description: This function is used to get the status of the Limit switch if it is pressed or not
 * Input Parameters:
 * 					 -LS_State_e *LSState: the value of the Limit switch is returned in this pointer
 *
 *
 * Return:           -Status_e : in range {  _PARAM,
 *											 _ERROR,
 *											 _SUCCESS }
 *
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
extern Status_e LS_enuGetState(LS_State_e *LSState, uint8_t LS_InstanceNumber);

#endif /* LS_H_ */
