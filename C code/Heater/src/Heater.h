/*
 * HEATER.h
 *
 *  Created on: Jun 20, 2021
 *      Author: abdoo
 */

#ifndef HEATER_H_
#define HEATER_H_

typedef enum{
	HEATER_Off,
	HEATER_On
}HEATER_Control_e;

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
extern Status_e HEATER_enuSetState(HEATER_Control_e HeaterState);

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
extern Status_e HEATER_enuGetState(HEATER_Control_e *HeaterState);

#endif /* HEATER_H_ */
