/*
 * Stepper_Hal.c
 *
 *  Created on: Jun 20, 2021
 *      Author: Islam
 */

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "../../../lib/src/Bits.h"
#include "../../../lib/src/Bit_Math.h"
#include "../../../lib/src/RT_Debug.h"
#include "Stepper.h"
#include "Extruder.h"
#include "Extruder_cfg.h"



typedef void (*PtrNotify)(void);
static uint32_t Delay_ns ;


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
void Extruder_Init(void)
{
	Stepper_Init();
}

/* Public Function:  Extruder_SetDirection															   *
 * Description: This function is used to Set Direction of Extruder
 *  * Input parameters:
 * 		- Extruder_Direction		in range :{- STEPPER_DIR_CW		-STEPPER_DIR_CCW}
 *
 * Return:
 * 		- void
 *
 * Input/Output Parameter:
 * 		- Not Applicable
 **********************************************************************************************/
RT_Debug Extruder_SetDirection(uint32_t Copy_ExtruderId,uint32_t Extruder_Direction)
{
	RT_Debug Return_Status ;

	Return_Status = Stepper_SetDirection(Copy_ExtruderId,Extruder_Direction);

	return Return_Status ;
}


/* Public Function:  Extruder_SetALLDirection															   *
 * Description: This function is used to Set Direction of Extruder
 *  * Input parameters:
 * 		- Extruder_Direction		in range :{- STEPPER_DIR_CW		-STEPPER_DIR_CCW}
 *
 * Return:
 * 		- void
 *
 * Input/Output Parameter:
 * 		- Not Applicable
 **********************************************************************************************/
RT_Debug Extruder_SetALLDirection(uint32_t Extruder_Direction)
{
	RT_Debug Return_Status ;

	Return_Status = Stepper_SetALLDirection(Extruder_Direction);

	return Return_Status ;
}



/* Public Function:  Extruder_SetStatus															   *
 * Description: This function is used to Enable/Disable of Extruder
 *  * Input parameters:
 * 		- Extruder_Status		in range :{- STEPPER_ENABLE	-STEPPER_DISABLE}
 *
 * Return:
 * 		- void
 *
 * Input/Output Parameter:
 * 		- Not Applicable
 **********************************************************************************************/
RT_Debug Extruder_SetStatus(uint32_t Copy_ExtruderId,uint32_t Extruder_Status)
{
	RT_Debug Return_Status ;

	Return_Status = Stepper_SetDirection(Copy_ExtruderId,Extruder_Status);

	return Return_Status ;
}

/* Public Function:  Extruder_SetAllStatus															   *
 * Description: This function is used to Enable/Disable ALL Extruder
 *  * Input parameters:
 * 		- Extruder_Status		in range :{- STEPPER_ENABLE	-STEPPER_DISABLE}
 *
 * Return:
 * 		- void
 *
 * Input/Output Parameter:
 * 		- Not Applicable
 **********************************************************************************************/
RT_Debug Extruder_SetAllStatus(uint32_t Extruder_Status)
{
	RT_Debug Return_Status ;

	Return_Status = Stepper_SetAllStatus(Extruder_Status);

	return Return_Status ;
}

/* Public Function:  Extruder_SetFeedRate														      *
 * Description: This function is used to Set FeedRate of Extruder
 *
 * Input parameters:
 *      - Extruder_FeedRate		Minimum FeedRate = 403
 *
 * Return:
 * 		- void
 *
 * Input/Output Parameter:
 * 		- Not Applicable
 ***************************************************************************************************/
void Extruder_SetFeedRate(uint32_t StepperId,uint32_t Extruder_FeedRate)
{

	Delay_ns = (uint32_t)((uint64_t)(EXTRUDER_LENGTH_um_PER_REVOLUTION * 30 * 1000000) / (uint64_t)(Extruder_FeedRate * STEPPER_STEP_PER_REVOLUTION ));


	/* 84,000,000 / 128 --> Ans /50 , where 50 is the desired frequency */
	trace_printf("Delay_ns = %d\n",Delay_ns);
	trace_printf("Freq = %d\n",1000000000 / (Delay_ns * 2) );

	StepperFrequencyPeriodTicks = (STEPPER_TIMER_PWM_FREQ_Mhz * Delay_ns * 2 ) / 1000 ;
	trace_printf("FREQUENCY_PERIOD_TICKS = %x\n",StepperFrequencyPeriodTicks);
	Stepper_SetSpeed(StepperId,StepperFrequencyPeriodTicks);

/*desired time = Num_timer_ticks * Time_of_one_tick */

}


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
void Extruder_SetMaterialLength(uint32_t StepperId, uint32_t Extruder_MaterialLength_um)
{
	trace_printf("Extruder_MaterialLength_um = %d\n",Extruder_MaterialLength_um);
	uint64_t Steps = (uint64_t)(Extruder_MaterialLength_um * STEPPER_STEP_PER_REVOLUTION / EXTRUDER_LENGTH_um_PER_REVOLUTION) ;
	trace_printf("Steps = %d\n",(uint32_t)Steps);
	StepperTimerBasePeriodTicks = (Delay_ns * 2 * Steps * 84) / (1000 * STEPPER_TIMER_BASE_PRESCALER) ;
	trace_printf("TimerBasePeriodTicks = %x\n",StepperTimerBasePeriodTicks);

	Stepper_StepsTime(StepperId,StepperTimerBasePeriodTicks-20);

}



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
RT_Debug Extruder_SetCallBackFunction(PtrNotify MterialEndNotify)
{
	RT_Debug Return_Status = RT_SUCCESS ;

	Return_Status = Stepper_SetCallBack(MterialEndNotify);

	return Return_Status ;
}

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
extern RT_Debug Extruder_Pause(uint32_t Copy_StepperId)
{
	RT_Debug Return_Status = RT_SUCCESS ;

	Return_Status = Stepper_Pause(Copy_StepperId);

	return Return_Status ;
}


/* Public Function:  Extruder_Continue														      *
 * Description: This function is used to Continue Extruder
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
extern RT_Debug Extruder_Continue(uint32_t Copy_StepperId)
{

	RT_Debug Return_Status = RT_SUCCESS ;

	Return_Status = Stepper_Continue(Copy_StepperId);

	return Return_Status ;

}
