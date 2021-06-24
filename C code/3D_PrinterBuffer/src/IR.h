/*
 * IR.h
 *
 *  Created on: Jun 20, 2021
 *      Author: abdoo
 */

#ifndef IR_H_
#define IR_H_

#include "IR_cfg.h"


typedef enum{
	IR_State_Off,
	IR_State_On
}IR_State_e;


/* Public Function:  IR_Init															      *
 * Description: This function is used to Configure Pins that connected to IRs
 * Input parameters:
 *
 * Return:
 * 		-void
 *
 * Input/Output Parameter:
 * 		- Not Applicable
 **********************************************************************************************/
void IR_Init(void);

/**************************************************************************************************************
 * Public Function:IR_enuGetState
 * Description: This function is used to get the status of the IR sensor if it has detected something or not
 * Input Parameters:
 * 					 -IR_State_e *IRState: the value of the IR sensor is returned in this variable
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
extern RT_Debug IR_enuGetState(IR_State_e *IRState);

#endif /* IR_H_ */
