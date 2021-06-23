/*
 * SW_Timer.c
 *
 *  Created on: Mar 10, 2021
 *      Author: micro
 */

#include <stdint.h>
#include <stddef.h>
#include "diag/Trace.h"
#include "../../../lib/src/Bits.h"
#include "../../../lib/src/RT_Debug.h"
#include "SW_Timer.h"
#include "SW_Timer_cfg.h"
#include "Rcc_int.h"
#include "Systick.h"



uint32_t counter = 0 ;

static SW_TimerCbfList_t SW_TimerCallBack_List [SW_TIMER_MAX_CALL_BACK_FUNCTION];

static uint32_t SW_Timer_NextFree  = 0 ;

void SW_TimerScheduler(void);

/* Public Function: SW_Timer_Init														      *
 * Description: This function is used to Initialize SW_Timer
 *
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
void SW_Timer_Init(void){

	uint32_t SystemFreq = 0 ;
	uint32_t AHBPre = 0 ;
	uint32_t AHB_Freq = 0;

	Systick_Init();
	Rcc_GetCurrrentSysClk_Frequency(&SystemFreq);
	Rcc_GetAHB_Prescaler((uint16_t * )&AHBPre);
	AHB_Freq  = SystemFreq / AHBPre ;
	trace_printf("AHB Prescaler = %d\n",AHB_Freq);
	Systick_SetTicks(1,AHB_Freq);
	Systick_Callback(SW_TimerScheduler);
	Systick_Start();


}


/* Public Function: SW_TimerRegisterCbf														      *
 * Description: This function is used to Register Functions
 *
 * Input parameters:
 * - SW_TimerCallBack (SW_Timer_cbf_t)
 * - SW_Timer_Time_ms (uint32_t) in range { Time in milliseconds }
 * - SW_TimerMode (SW_Timer_Mode_t) in range : { SW_Timer_Mode_Periodic , SW_Timer_Mode_Once }
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
uint8_t SW_TimerRegisterCbf(SW_Timer_cbf_t SW_TimerCallBack,uint32_t SW_Timer_Time_ms, SW_Timer_Mode_t SW_TimerMode){

	RT_Debug status = RT_SUCCESS ;
	if (SW_TimerCallBack != NULL && SW_Timer_Time_ms != 0 && SW_TimerMode < __SW_Timer_Mode_Length__ ){

		if (SW_Timer_NextFree < SW_TIMER_MAX_CALL_BACK_FUNCTION){

			SW_TimerCallBack_List[SW_Timer_NextFree].Function = SW_TimerCallBack ;
			SW_TimerCallBack_List[SW_Timer_NextFree].Mode = SW_TimerMode ;
			SW_TimerCallBack_List[SW_Timer_NextFree].Time_ms = SW_Timer_Time_ms ;
			SW_TimerCallBack_List[SW_Timer_NextFree].Reload = SW_Timer_Time_ms ;

			SW_Timer_NextFree++ ;
		}
		else
			status = RT_BUFFER_FULL ;

	}
	else{

		status = RT_PARAM ;
	}


	return
			status ;
}


/* Public Function: SW_TimerUnRegisterCbf														      *
 * Description: This function is used to Unregister Functions
 *
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
uint8_t SW_TimerUnRegisterCbf(SW_Timer_cbf_t SW_TimerCallBack){

	RT_Debug status = RT_SUCCESS ;

	uint32_t UnregisterdFunctionIdx = 0 ;
	uint32_t RegisterdFunctionIdx = 0 ;

	if (SW_TimerCallBack != NULL){

		for (UnregisterdFunctionIdx = 0 ; UnregisterdFunctionIdx < SW_Timer_NextFree ; UnregisterdFunctionIdx++ ){

			if (SW_TimerCallBack_List[UnregisterdFunctionIdx].Function == SW_TimerCallBack){

				for (RegisterdFunctionIdx = UnregisterdFunctionIdx ; RegisterdFunctionIdx < SW_Timer_NextFree - 1  ; RegisterdFunctionIdx++){

					SW_TimerCallBack_List[UnregisterdFunctionIdx] = SW_TimerCallBack_List[UnregisterdFunctionIdx+1];

				}
				SW_Timer_NextFree-- ;
				break;
			}
		}

	}
	else
		status = RT_PARAM ;



	return
			status ;
}

/* Public Function: SW_TimerUnRegisterCbf														      *
 * Description: This function is used to Unregister Functions
 *
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
void SW_TimerScheduler(void){
	uint32_t SW_TimerIdx = 1 ;

	for (SW_TimerIdx = 1 ; SW_TimerIdx <= SW_Timer_NextFree ; SW_TimerIdx++){

		counter++;

		if (SW_TimerCallBack_List[SW_TimerIdx-1].Time_ms == 0){

			//trace_printf("counter = %d\n",counter);

			SW_TimerCallBack_List[SW_TimerIdx-1].Function();

			if ( SW_TimerCallBack_List[SW_TimerIdx-1].Mode == SW_Timer_Mode_Periodic){

				SW_TimerCallBack_List[SW_TimerIdx-1].Time_ms = SW_TimerCallBack_List[SW_TimerIdx-1].Reload ;
			}

			else{

				SW_TimerUnRegisterCbf(SW_TimerCallBack_List[SW_TimerIdx-1].Function);
				//unregister
				SW_TimerIdx--;
				continue;
			}

		}

		SW_TimerCallBack_List[SW_TimerIdx-1].Time_ms-- ;
	}

}

