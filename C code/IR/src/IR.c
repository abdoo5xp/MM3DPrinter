/*
 * IR.c
 *
 *  Created on: Jun 20, 2021
 *      Author: abdoo
 */


#include <stdint.h>
#include "../../lib/Bit_Mask.h"
#include "../../lib/Bit_Math.h"
#include "../../lib/Error_codes.h"
#include "GPIO.h"
#include "IR.h"
#include "IR_cfg.h"





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
Status_e IR_enuGetState(IR_State_e *IRState)
{
	uint32_t pinVal;
	if(IRState == NULL)
	{
		return _PARAM;
	}

	/*Read the GPIO Pin value */
	GPIO_ReadPin(IR_GPIO_PORT,IR_GPIO_PINNUM, &pinVal);

	/*Return the IR Sensor status to the User in the input pointer */
	if(pinVal == IR_STATE_ON)
	{
		*IRState = IR_State_On;
	}
	else
	{
		*IRState = IR_State_Off;
	}

	return _SUCCESS;
}
