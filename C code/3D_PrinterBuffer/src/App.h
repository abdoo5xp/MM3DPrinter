/*
 * App.h
 *
 *  Created on: Jun 24, 2021
 *      Author: abdoo
 */

#ifndef APP_H_
#define APP_H_


typedef enum {
	APP_DataNotReceived,
	APP_DataReceived
}APP_DataReceiveStatus_e;



/**************************************************************************************************************
 * Public Function: App_vidInit
 * Description: This function is used to Initialize the whole system and wait for Gcode receiving
 * Input Parameters:
 * 					 -Not Applicable (void)
 *
 *
 * Return:           -Not Applicable (void)
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
void App_vidInit();

/**************************************************************************************************************
 * Public Function: App_vidSystemSleep
 * Description: This function is used to Set the system in Sleep mode and wait for the reception of the
 * Input Parameters:
 * 					 -Not Applicable (void)
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
void App_vidSystemSleep();

/**************************************************************************************************************
 * Public Function: App_vidParseGcode
 * Description: This function is used to parse the Gcode and get the Action to be taken
 * Input Parameters:
 * 					 -GcodeParser_Action_t* ExtruderAction: input structure for the function to fill its data
 *
 *
 * Return:           -GcodeParser_Action_t* ExtruderAction
 *
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
void App_vidParseGcode(GcodeParser_Action_t* ExtruderAction);

/**************************************************************************************************************
 * Public Function: App_vidTakeAction
 * Description: This function is used to Execute the Required action
 * Input Parameters:
 * 					 -GcodeParser_Action_t* ExtruderAction:
 *
 *
 * Return:           -Not Applicable (void)
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
void App_vidTakeAction(GcodeParser_Action_t* ExtruderAction);

/**************************************************************************************************************
 * Public Function: App_vidWaitForActionExecution
 * Description: This function is used to wait for Extruder action to be executed by hardware
 * Input Parameters:
 * 					 -Not Applicable (void)
 *
 *
 * Return:           -Not Applicable (void)
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
void App_vidWaitForActionExecution();

/**************************************************************************************************************
 * Public Function:App_vidWaitForDataReception
 * Description: This function is used to wait for the Gcode data to be received by UART
 * Input Parameters:
 * 					 -Not Applicable (void)
 *
 *
 * Return:           -Not Applicable (void)
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
void App_vidWaitForDataReception();

/**************************************************************************************************************
 * Public Function:App_HasGcodeEnded
 * Description: This function is used to get if the Gcode has reached in the
 * Input Parameters:
 * 					 -Not Applicable (void)
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
APP_GcodeEndStatus_e App_HasGcodeEnded();


#endif /* APP_H_ */
