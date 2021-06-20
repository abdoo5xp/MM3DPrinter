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
#include "Heater.h"
#include "Heater_cfg.h"




/**************************************************************************************************************
 * Public Function:HEATER_enuSetState
 * Description: This function is used to Set the status of the HEATER
 * Input Parameters:
 * 					 -HEATER_Control_e HeaterState:in range {
 * 					 										HEATER_Off,
															HEATER_On}
 *
 * Return:           -Status_e : in range {  _PARAM,
 *											 _ERROR,
 *											 _SUCCESS }
 *
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
Status_e HEATER_enuSetState(HEATER_Control_e HeaterState)
{
	if(HeaterState != HEATER_On || HeaterState != HEATER_Off)
	{
		return _PARAM;
	}

	/*Set the GPIO Pin value */
	if(!(HEATER_ACTIVE_STATE ^ HeaterState))
	{
		GPIO_WritePin(HEATER_GPIO_PORT, HEATER_GPIO_PINNUM, GPIO_STATUS_HIGH);
	}
	else
	{
		GPIO_WritePin(HEATER_GPIO_PORT, HEATER_GPIO_PINNUM, GPIO_STATUS_LOW);
	}

	return _SUCCESS;
}


/**************************************************************************************************************
 * Public Function:HEATER_enuSetState
 * Description: This function is used to Get the status of the HEATER
 * Input Parameters:
 * 					 -HEATER_Control_e * HeaterState:the status of the heater will be returned in this parameter
* 					 								in range {
* 					 											HEATER_Off,
																HEATER_On}
 *
 * Return:           -Status_e : in range {  _PARAM,
 *											 _ERROR,
 *											 _SUCCESS }
 *
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
extern Status_e HEATER_enuGetState(HEATER_Control_e *HeaterState)
{
	uint32_t pinVal;
	if(HeaterState == NULL)
	{
		return _PARAM;
	}

	GPIO_ReadPin(HEATER_GPIO_PORT, HEATER_GPIO_PINNUM, &pinVal);
	/*Set the GPIO Pin value */
	if(!(HEATER_ACTIVE_STATE ^ pinVal))
	{
		*HeaterState = HEATER_On;
	}
	else
	{
		*HeaterState = HEATER_Off;
	}

	return _SUCCESS;
}
