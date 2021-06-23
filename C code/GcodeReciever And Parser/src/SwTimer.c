/*
 * SwTimer.c
 *
 *  Created on: Mar 9, 2021
 *      Author: abdoo
 */

#include <stdint.h>
#include "../../lib/Bit_Mask.h"
#include "../../lib/Bit_Math.h"
#include "../../lib/Error_codes.h"
#include "SystickTimer.h"
#include "SwTimer.h"
#include "Rcc.h"
/*TODO: Add the function index in the struct so that when you unregister it you don't need search for the index*/
#define MAX_NO_OF_CBF				10
#define MIN_NO_OF_WANTED_TICKS		0xFF


/*Array of structure for each registered call back function */
static struct {
	SwTimerCbf func;
	SwTimerMode_e mode;
	uint32_t time_ms;
	uint32_t reload;
}CbfList[MAX_NO_OF_CBF];

static uint32_t NextFree;
/*from my point of view this function saves memory,but consumes time in some cases if you have a huge list */
/*Turkey suggested making a freelist which contains the index of free places in the CBF list ,
 * but i think it will consume more memory in the case of huge list, because  */
static void CbfList_compact(uint32_t funIdx);

static void Scheduler(void);

void SwTimer_init(uint32_t time_ms){
	uint32_t AHBBusClkMhz;
	RCC_GetCurrentSysClkFreq(&AHBBusClkMhz);
	RCC_GetAHBFreqMhz(&AHBBusClkMhz);
	Systick_Init();
	Systick_SetTimer_ms(time_ms, AHBBusClkMhz);
	Systick_SetCbf(Scheduler);
	Systick_Start();
}

static void Scheduler(void){
	uint32_t cbfidx;
	/* loop on the registered call back functions in the list
	 * here we shifted the list logically to avoid the bug when decrementing the cbfidx-- and it was zero --> overflow  */
	for(cbfidx = 1; cbfidx <= NextFree ; cbfidx++){
		if(CbfList[cbfidx-1].time_ms == 0)
		{
			/*if the time has come for this function to execute, execute it.*/
			CbfList[cbfidx-1].func();

			if(CbfList[cbfidx-1].mode == SWTimer_TimerMode_Once)
			{
				/* if the function is called once, remove it*/
				CbfList_compact(cbfidx-1);
				cbfidx--;
			}
			else
			{
				/* After you call the function, you need to reload the reload value in the
				 * time_ms variable, to check again (if periodic)*/
				CbfList[cbfidx-1].time_ms = CbfList[cbfidx-1].reload-1;
			}
		}
		else
		{
			/*if the CBF time hasn't come yet, */
			CbfList[cbfidx-1].time_ms--;
		}
	}
}

static void CbfList_compact(uint32_t funIdx){
	/*loop starting from this index to the element before last element */

	for(;funIdx < NextFree-1;funIdx++){
		CbfList[funIdx] = CbfList[funIdx + 1];
	}
	NextFree--;
}

/*
 * =================================================================================================================
 * Name: SwTimer_RegisterCBF
 * Description: this function is used to register a function in the schedule of the timer
 *
 * Input:
 *		   - uint32_t ticks: the number of ticks that should be reloaded in the timer reload register
 *		   						in range {0 : }
 *
 *		   - SwTimerMode_e mode: the mode of the timer that should call this function
 *		   						in range {periodic, once}
 *
 *		   - SwTimerCbf cbf: pointer to the call back function that you wish to execute every time the timer finishes its count.
 *
 * return: SwTimerStatus_e : in range{ok:If the function worked correctly, nok:If the function failed }
 *
 * *****************************************************************************************************************
 * */
SwTimerStatus_e SwTimer_RegisterCBF(uint32_t time_ms,SwTimerMode_e mode,SwTimerCbf func){
	/*Return Error if you have reached the maximum number of elements in the CbfList*/
	if(NextFree >  MAX_NO_OF_CBF){
		return SWTimer_Nok;
	}

	/*Set the structure values */
	CbfList[NextFree].func = func;
	CbfList[NextFree].mode = mode;
	CbfList[NextFree].time_ms = time_ms;
	CbfList[NextFree].reload = time_ms;
	NextFree ++ ;

	return SWTimer_Ok;
}

/*
 * =================================================================================================================
 * Name: SwTimer_UnRegisterCBF
 * Description: this function is used to remove this function from the timer list
 *
 * Input:
 *		   - SwTimerCbf cbf: pointer to the call back function that you wish to remove .
 *
 * return: SwTimerStatus_e : in range{ok:If the function worked correctly, nok:If the function failed }
 *
 * *****************************************************************************************************************
 * */
SwTimerStatus_e SwTimer_UnRegisterCBF(SwTimerCbf func){
	uint32_t funcidx;
	uint8_t found = 0;

	for (funcidx =0; funcidx<NextFree; funcidx++){
		if (CbfList[funcidx].func == func){
			CbfList_compact(funcidx);
			found =1;
			break;
		}
	}

	if(!found){
		return SWTimer_Nok;
	}
	return SWTimer_Ok;
}
