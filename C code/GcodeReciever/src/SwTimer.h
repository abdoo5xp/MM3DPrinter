/*
 * SwTimer.h
 *
 *  Created on: Mar 9, 2021
 *      Author: abdoo
 */

#ifndef SWTIMER_H_
#define SWTIMER_H_

typedef enum{
	SWTimer_Ok,
	SWTimer_Nok
}SwTimerStatus_e;

typedef enum{
	SWTimer_TimerMode_Periodic,
	SWTimer_TimerMode_Once
}SwTimerMode_e;

typedef void(*SwTimerCbf)(void);


extern void SwTimer_init(uint32_t time_ms);

/*
 * =================================================================================================================
 * Name: SwTimer_RegisterCBF
 * Description: this function is used to convert the user wanted time to
 * 				the number of ticks that should be put in the reload of the timer
 *
 * Input:
 *		   - uint32_t time_ms: the number of ticks that should be reloaded in the timer reload register
 *		   						in range {0 : }
 *
 *		   - SwTimerMode_e mode: the mode of the timer that should call this function
 *		   						in range {periodic, once}
 *
 *		   - SwTimerCbf func: pointer to the call back function that you wish to execute every time the timer finishes its count.
 *
 * return: SwTimerStatus_e : in range{ok:If the function worked correctly, nok:If the function failed }
 *
 * *****************************************************************************************************************
 * */
extern SwTimerStatus_e SwTimer_RegisterCBF(uint32_t time_ms,SwTimerMode_e mode,SwTimerCbf func);

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
extern SwTimerStatus_e SwTimer_UnRegisterCBF(SwTimerCbf func);

#endif /* SWTIMER_H_ */
