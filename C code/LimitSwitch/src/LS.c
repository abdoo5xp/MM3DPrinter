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
#include "LS.h"
#include "LS_cfg.h"





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
Status_e LS_enuGetState(LS_State_e *LSState, uint8_t LS_InstanceNumber)
{
	uint32_t pinVal;
	if(LSState == NULL || LS_InstanceNumber >= LS_INTANCES_NUMBER )
	{
		return _PARAM;
	}

	/*Read the GPIO Pin value */
	GPIO_ReadPin(LS_instances[LS_InstanceNumber].port,LS_instances[LS_InstanceNumber].gpioPinNum, &pinVal);

	/*Return the IR Sensor status to the User in the input pointer */
	if(pinVal == LS_STATE_ON)
	{
		*LSState = LS_State_Pressed;
	}
	else
	{
		*LSState = LS_State_NotPressed;
	}

	return _SUCCESS;
}
