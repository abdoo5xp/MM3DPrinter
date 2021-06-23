/*
 * Systick.c
 *
 *  Created on: Feb 25, 2021
 *      Author: micro
 */


#include <stdint.h>
#include <stddef.h>
#include "diag/Trace.h"
#include "../../../lib/src/Bits.h"
#include "../../../lib/src/RT_Debug.h"
#include "Systick.h"
#include "Systick_types.h"
#include "Systick_cfg.h"

typedef struct {

	uint32_t CTRL;
	uint32_t LOAD;
	uint32_t VAL ;
	uint32_t CALIB;

}Systick_t;


// Systick registers Base Address***********************************************************
#define   SYSTICK					((volatile Systick_t*)(uint32_t)0xE000E010)

// Systick_ CTRL Clear Mask*****************************************************************
#define SYSTICK_CTRL_CLR_MASK		(uint32_t)(~(BIT_0 | BIT_1 | BIT_2))

// Systick start MASK***********************************************************************
#define SYSTICK_START				BIT_0

// Systick start MASK***********************************************************************
#define SYSTICK_DISABLE				~BIT_0

static uint8_t Flag = 0 ;



/* Public Function:  SysTick_Handler														      *
 * Description: This function is Systick Exception Handler
 *
 * Input parameters:
 *
 * Return:
 *
 * Input/Output Parameter:
 * 		- Not Applicable

 ***************************************************************************************************/
void SysTick_Handler(void) // SYSTICK exception handler
{

	// in case it has been pended again
	if ( Flag == 1 )
		Ptr_SystickHandler();

	return;
}


/* Public Function: Systick_Callback														      *
 * Description: This function is used to Pass Function created in Application to Systick Handler (HIGH ,LOW)
 *
 * Input parameters:
 *
 * Return:
 *
 * Input/Output Parameter:
 * 		- void(*Ptr_Function)(void)

 ***************************************************************************************************/
void Systick_Callback(void(*Ptr_Function)(void)){

	Ptr_SystickHandler = Ptr_Function ;
	Flag = 1 ;
}


/* Public Function: Systick_Init															      *
 * Description: This function is used to Initialize Systick Timer
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

 ***************************************************************************************************/
extern uint8_t Systick_Init(void){

	RT_Debug status = RT_SUCCESS ;

	if ((Systick_cfg.SysTick_Int == SYSTICK_INT_ENABLE || Systick_cfg.SysTick_Int == SYSTICK_INT_DISABLE) &&
			(Systick_cfg.SysTickCLK_Source == SYSTICK_CLK_SOURCE_PROCESSOR_CLOCK || Systick_cfg.SysTickCLK_Source == SYSTICK_CLK_SOURCE_EXTERNAL_REFERENCE_CLOCK )){

		SYSTICK->CTRL &= SYSTICK_CTRL_CLR_MASK;
		SYSTICK->CTRL |= Systick_cfg.SysTick_Int;
		SYSTICK->CTRL |= Systick_cfg.SysTickCLK_Source ;

	}
	else
		status = RT_PARAM ;

	return
			status ;
}
/* Public Function: Systick_SetTicks														      *
 * Description: This function is used to Set ticks that counter will start decrement from .
 *
 * Input parameters:
 *      - Systick_Time_ms	(uint32_t)
 *      - Systick_AHB_Freq 	(uint32_t)
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
extern uint8_t Systick_SetTicks(uint32_t Systick_Time_ms,uint32_t Systick_AHB_Freq){

	uint32_t Systick_Ticks = 0 ;

	if ( Systick_cfg.SysTickCLK_Source == SYSTICK_CLK_SOURCE_EXTERNAL_REFERENCE_CLOCK )
	{
		Systick_Ticks = (Systick_Time_ms * (Systick_AHB_Freq / 8) )  / 1000  ;
	}
	else{
		Systick_Ticks = (Systick_Time_ms * (Systick_AHB_Freq) )  / 1000  ;
	}

	if (Systick_Ticks <= SYSTICK_TICKS_LIMIT){

		SYSTICK->LOAD = Systick_Ticks - 1;
		SYSTICK->VAL  = 0;
	}
	else
		return
				RT_PARAM;
	return
			RT_SUCCESS;
}

/* Public Function: Systick_Start														      *
 * Description: This function is used make Systick timer start counting
 *
 * Input parameters:
 *
 * Return:
 *
 * Input/Output Parameter:
 * 		- Not Applicable

 ***************************************************************************************************/
extern void Systick_Start(void){

	SYSTICK->CTRL |= SYSTICK_START;
}



/* Public Function: Systick_Disable														      *
 * Description: This function is used to Disable Systick Timer
 * Input parameters:
 *
 * Return
 * 		- Status (uint8_t)
 *         RT_SUCCESS
 *         RT_PARAM
 *         RT_ERROR
 *         RT_TIME_OUT
 *
 * Input/Output Parameter:
 * 		- Not Applicable

 ***************************************************************************************************/
extern void Systick_Disable(void){

	SYSTICK->CTRL &= SYSTICK_DISABLE;

}

