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


#endif /* EXTRUDER_H_ */
