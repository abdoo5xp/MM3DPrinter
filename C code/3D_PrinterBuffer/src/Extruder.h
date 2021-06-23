/*
 * Stepper_Hal.h
 *
 *  Created on: Jun 20, 2021
 *      Author: Islam
 */

#ifndef EXTRUDER_H_
#define EXTRUDER_H_

/* Public Function:  Extruder_SetFeedRate														      *
 * Description: This function is used to Set FeedRate of Extruder
 *
 * Input parameters:
 *      - Extruder_FeedRate
 *
 * Return:
 * 		- void
 *
 * Input/Output Parameter:
 * 		- Not Applicable
 ***************************************************************************************************/
void Extruder_SetFeedRate(uint32_t StepperId, uint32_t Extruder_FeedRate);


/* Public Function:  Extruder_SetFeedRate														      *
 * Description: This function is used to Set Material output from Extruder
 *
 * Input parameters:
 *      - Extruder_MaterialLength
 *
 * Return:
 * 		- void
 *
 * Input/Output Parameter:
 * 		- Not Applicable
 ***************************************************************************************************/
void Extruder_SetMaterialLength(uint32_t StepperId, uint32_t Extruder_MaterialLength);


/* Public Function:  Extruder_Pause														      *
 * Description: This function is used to Pause Extruder
 *
 * Input parameters:
 *      - Copy_StepperId	in range : {EXTRUDER_M_1 -> EXTRUDER_E}
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
extern RT_Debug Extruder_Pause(uint32_t Copy_StepperId);


/* Public Function:  Extruder_Continue														      *
 * Description: This function is used to Continue Stepper
 *
 * Input parameters:
 *      - Copy_StepperId	in range : {EXTRUDER_M_1 -> EXTRUDER_E}
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
extern RT_Debug Extruder_Continue(uint32_t Copy_StepperId);



#endif /* EXTRUDER_H_ */
