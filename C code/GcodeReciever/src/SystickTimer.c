/*
 * SystickTimer.c
 *
 *  Created on: Mar 7, 2021
 *      Author: abdoo
 */

#include <stdint.h>
#include <stddef.h>
#include "diag/Trace.h"
#include "../../lib/Bit_Mask.h"
#include "../../lib/Bit_Math.h"
#include "../../lib/Error_codes.h"
#include "SystickTimer_cfg.h"

#include "SystickTimer.h"

typedef struct {
	uint32_t CTRL;
	uint32_t LOAD;
	uint32_t VAL;
	uint32_t CALIBRATION;
}Systick_t;

#define 	SYSTICK 	 			(*(volatile Systick_t*) 0xE000E010 )
#define 	CLKINT_PIN				BIT_MASK_1
#define 	MAX_TIMER_VALUE 		0xFFFFFF

pfun systick_handler;


systickclk_t SystickTimer_CurrentClkSrc;

void Systick_Init(void){
	/*Reset the systick control register */
	SYSTICK.CTRL = 0;

	/*Select the clock source */
	SYSTICK.CTRL |= SYSTICK_DEF_CLK_SRC ;
	SystickTimer_CurrentClkSrc = SYSTICK_DEF_CLK_SRC;

	/*Enable the systick interrupt  */
	SYSTICK.CTRL |=  CLKINT_PIN ;
}

uint32_t  Systick_SelectClkSrc(systickclk_t clksrc ){
	/* clear the systick clk source and disable it */
	SYSTICK.CTRL &= BIT_MASK_CLEAR_0 & BIT_MASK_CLEAR_2 ;

	/*Select the clock source */
	SYSTICK.CTRL |= clksrc ;
	SystickTimer_CurrentClkSrc = clksrc;

	return RT_SUCCESS;
}

uint32_t Systick_Start(void){
	SYSTICK.CTRL |= 1;
	return RT_SUCCESS;
}

uint32_t Systick_Stop(void){
	SYSTICK.CTRL &=~ 1;
	return RT_SUCCESS;
}

uint32_t Systick_SetTimer_ms(uint32_t time_ms,uint32_t AHBBusClkMhz){
	uint32_t timerTicks;
	uint32_t return_status = RT_SUCCESS;

	if(time_ms == 0 || AHBBusClkMhz == 0){
		return RT_PARAM;
	}
	/* we divide time_ms by 1000 to convert it to seconds.
	 *
	 * ticks = time_ms / (1000 * time_of_each_system_clk)	--> 1/time_of_each_system_clk -->  system frequency
	 * ticks = time_ms * systemFrequencyMhz * 10^6 / 1000
	 * ticks = time_ms * systemFrequencyMhz * 10^6 / 1000
	 * ticks = time_ms * systemFrequencyMhz * 10^3
	 */

	if( systick_ahb_clk_src == SystickTimer_CurrentClkSrc ){
		timerTicks = AHBBusClkMhz * time_ms * 1000;
	}
	else if ( systick_ahb_8_clk_src == SystickTimer_CurrentClkSrc ){
		timerTicks = AHBBusClkMhz * time_ms * 1000/8;
	}
	else {
		return RT_ERROR;
	}

	/*return ERROR if the timer ticks is bigger than the maximum value */
	if (timerTicks > MAX_TIMER_VALUE ){
		return RT_ERROR;
	}

	/*Disable the systick timer */
	SYSTICK.CTRL  &=~ 1;
	/*Load the number of timer ticks in the reload register  */
	SYSTICK.LOAD  = timerTicks-1;
	/*Reset the timer value register */
	SYSTICK.VAL   = 0;

	return return_status;
}

uint32_t Systick_SetCbf(pfun callBackFn){
	systick_handler = callBackFn;
	return RT_SUCCESS;
}

// SYSTICK exception handler
void SysTick_Handler(void){
	// Execute required processing task
	if (systick_handler){
		systick_handler();
	}
}

