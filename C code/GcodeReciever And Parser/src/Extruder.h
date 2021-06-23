/*
 * Stepper_Hal.h
 *
 *  Created on: Jun 20, 2021
 *      Author: Islam
 */

#ifndef EXTRUDER_H_
#define EXTRUDER_H_

#define EXTRUDER_M_1 	0
#define EXTRUDER_M_2 	1
#define EXTRUDER_M_3 	2
#define EXTRUDER_E 		3


typedef void (*PtrNotify)(void);

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



/* Public Function:  Extruder_SetCallBackFunction														      *
 * Description: This function is used to Configure Pin Status (HIGH ,LOW)
 *
 * Input parameters:
 *      - MterialEndNotify		in range : Pointer To Function
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
void Extruder_SetCallBackFunction(PtrNotify MterialEndNotify);

#endif /* EXTRUDER_H_ */
