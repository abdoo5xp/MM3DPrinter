/*
 * Extruder_Hal.h
 *
 *  Created on: Jun 20, 2021
 *      Author: Islam
 */

#ifndef EXTRUDER_H_
#define EXTRUDER_H_


#include "Extruder_cfg.h"


typedef void (*PtrNotify)(void);

// Stepper_Status**********************************************************************************
#define EXTRUDER_ENABLE				1
#define EXTRUDER_DISABLE			0


// Stepper_Direction**********************************************************************************
#define EXTRUDER_DIR_CW				1
#define EXTRUDER_DIR_CCW			0


/* Public Function: Extruder_Init															      *
 * Description: This function is used to Configure Pins that connected to Stepper_Driver
 * Input parameters:
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
 **********************************************************************************************/
void Extruder_Init(void);

/* Public Function:  Extruder_SetDirection															   *
 * Description: This function is used to Set Direction of Extruder
 *  * Input parameters:
 * 		- Extruder_Direction		in range :{- EXTRUDER_DIR_CW		-EXTRUDER_DIR_CCW}
 *
 * Return:
 * 		- void
 *
 * Input/Output Parameter:
 * 		- Not Applicable
 **********************************************************************************************/
RT_Debug Extruder_SetDirection(uint32_t Copy_ExtruderId,uint32_t Extruder_Direction);


/* Public Function:  Extruder_SetALLDirection															   *
 * Description: This function is used to Set Direction of Extruder
 *  * Input parameters:
 * 		- Extruder_Direction		in range :{- EXTRUDER_DIR_CW		-EXTRUDER_DIR_CCW}
 *
 * Return:
 * 		- void
 *
 * Input/Output Parameter:
 * 		- Not Applicable
 **********************************************************************************************/
RT_Debug Extruder_SetALLDirection(uint32_t Extruder_Direction);



/* Public Function:  Extruder_SetStatus															   *
 * Description: This function is used to Enable/Disable of Extruder
 *  * Input parameters:
 * 		- Extruder_Status		in range :{- EXTRUDER_ENABLE	-EXTRUDER_DISABLE}
 *
 * Return:
 * 		- void
 *
 * Input/Output Parameter:
 * 		- Not Applicable
 **********************************************************************************************/
RT_Debug Extruder_SetStatus(uint32_t Copy_ExtruderId,uint32_t Extruder_Status);


/* Public Function:  Extruder_SetAllStatus															   *
 * Description: This function is used to Enable/Disable ALL Extruder
 *  * Input parameters:
 * 		- Extruder_Status		in range :{- EXTRUDER_ENABLE	-EXTRUDER_DISABLE}
 *
 * Return:
 * 		- void
 *
 * Input/Output Parameter:
 * 		- Not Applicable
 **********************************************************************************************/
RT_Debug Extruder_SetAllStatus(uint32_t Extruder_Status);



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
void Extruder_SetFeedRate(uint32_t ExtruderId, uint32_t Extruder_FeedRate);


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
void Extruder_SetMaterialLength(uint32_t ExtruderId, uint32_t Extruder_MaterialLength_um);

/* Public Function:  Extruder_Pause														      *
 * Description: This function is used to Pause Extruder
 *
 * Input parameters:
 *      - Copy_ExtruderId	in range : {EXTRUDER_M_1 -> EXTRUDER_E}
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
extern RT_Debug Extruder_Pause(uint32_t Copy_ExtruderId);


/* Public Function:  Extruder_Continue														      *
 * Description: This function is used to Continue Extruder
 *
 * Input parameters:
 *      - Copy_ExtruderId	in range : {EXTRUDER_M_1 -> EXTRUDER_E}
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
extern RT_Debug Extruder_Continue(uint32_t Copy_ExtruderId);

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
RT_Debug Extruder_SetCallBackFunction(PtrNotify MterialEndNotify);


#endif /* EXTRUDER_H_ */
