/*
 * Stepper.h
 *
 *  Created on: Jun 20, 2021
 *      Author: Islam
 */

#ifndef STEPPER_H_
#define STEPPER_H_

#include "Stepper_cfg.h"

typedef enum
{
	Stepper_NotWorking ,
	Stepper_Working
}StepperWorking_enu;

typedef void (*PtrNotify)(void);

extern uint32_t StepperFrequencyPeriodTicks ;

extern uint32_t StepperTimerBasePeriodTicks ;//12000//6563

extern uint32_t StepperWorking_Id[STEPPER_NUM];


// Stepper_Status**********************************************************************************
#define STEPPER_ENABLE				1
#define STEPPER_DISABLE				0


// Stepper_Direction**********************************************************************************
#define STEPPER_DIR_CW				1
#define STEPPER_DIR_CCW				0

/* Public Function:  Stepper_Init															      *
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
uint8_t Stepper_Init(void);

/* Public Function:  Stpper_SetStep															   *
 * Description: This function is used to Set No. of steps to Stepper
 *  * Input parameters:
 * 		- Stepper_Steps		#Number of steps
 *
 * Return:
 * 		- void
 *
 * Input/Output Parameter:
 * 		- Not Applicable
 **********************************************************************************************/
RT_Debug Stepper_StepsTime(uint32_t StepperId ,uint32_t Copy_TimerBasePeriodTicks,StepperWorking_enu Stepper_Status);



/* Public Function:  Stepper_SetSpeed															   *
 * Description: This function is used to Set Speed of Stepper
 *  * Input parameters:
 * 		- Stepper_Speed
 *
 * Return:
 * 		- void
 *
 * Input/Output Parameter:
 * 		- Not Applicable
 **********************************************************************************************/
RT_Debug Stepper_SetSpeed(uint32_t StepperId, uint32_t Stepper_Speed);


/* Public Function:  Stepper_SetDirection															   *
 * Description: This function is used to Set Direction of Stepper
 *  * Input parameters:
 * 		- Stepper_Direction		in range :{- STEPPER_DIR_CW		-STEPPER_DIR_CCW}
 *
 * Return:
 * 		- void
 *
 * Input/Output Parameter:
 * 		- Not Applicable
 **********************************************************************************************/
RT_Debug Stepper_SetDirection(uint32_t Copy_StepperId,uint32_t Stepper_Direction);


/* Public Function:  Stepper_SetALLDirection															   *
 * Description: This function is used to Set Direction of Stepper
 *  * Input parameters:
 * 		- Stepper_Direction		in range :{- STEPPER_DIR_CW		-STEPPER_DIR_CCW}
 *
 * Return:
 * 		- void
 *
 * Input/Output Parameter:
 * 		- Not Applicable
 **********************************************************************************************/
RT_Debug Stepper_SetALLDirection(uint32_t Stepper_Direction);



/* Public Function:  Stepper_SetStatus															   *
 * Description: This function is used to Enable/Disable of Stepper
 *  * Input parameters:
 * 		- Stepper_Status		in range :{- STEPPER_ENABLE	-STEPPER_DISABLE}
 *
 * Return:
 * 		- void
 *
 * Input/Output Parameter:
 * 		- Not Applicable
 **********************************************************************************************/
RT_Debug Stepper_SetStatus(uint32_t Copy_StepperId,uint32_t Stepper_Status);


/* Public Function:  Stepper_SetAllStatus															   *
 * Description: This function is used to Enable/Disable ALL Stepper
 *  * Input parameters:
 * 		- Stepper_Status		in range :{- STEPPER_ENABLE	-STEPPER_DISABLE}
 *
 * Return:
 * 		- void
 *
 * Input/Output Parameter:
 * 		- Not Applicable
 **********************************************************************************************/
RT_Debug Stepper_SetAllStatus(uint32_t Stepper_Status);



/* Public Function:  Stepper_SetCallBack														      *
 * Description: This function is used to Call User Function atEnd of feeding Material
 *
 * Input parameters:
 *      - Stepper_StopNotify	in range : pointer to function
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
RT_Debug Stepper_SetCallBack(PtrNotify Stepper_StopNotify);


/* Public Function:  Stepper_SetNotifyFlag														      *
 * Description: This function is used to Set Flag Function at End of feeding Material
 *
 * Input parameters:
 *      - Stepper_StopNotifyFlag	in range : pointer to uint32_t
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
RT_Debug Stepper_SetNotifyFlag(volatile uint32_t* Stepper_StopNotifyFlag);

/* Public Function:  Stepper_Pause														      *
 * Description: This function is used to Pause Stepper
 *
 * Input parameters:
 *      - Copy_StepperId	in range : {STEEPER_1 -> STEPPER_4}
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
extern RT_Debug Stepper_Pause(uint32_t Copy_StepperId);


/* Public Function:  Stepper_Continue														      *
 * Description: This function is used to Continue Stepper
 *
 * Input parameters:
 *      - Copy_StepperId	in range : {STEEPER_1 -> STEPPER_4}
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
extern RT_Debug Stepper_Continue(uint32_t Copy_StepperId);



#endif /* STEPPER_H_ */
