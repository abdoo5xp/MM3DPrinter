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


static uint32_t Delay_ns ;

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
void Extruder_SetFeedRate(uint32_t StepperId,uint32_t Extruder_FeedRate)
{

	Delay_ns = (uint32_t)((uint64_t)(EXTRUDER_LENGTH_um_PER_REVOLUTION * 30 * 1000000) / (uint64_t)(Extruder_FeedRate * STEPPER_STEP_PER_REVOLUTION ));


	/* 84,000,000 / 128 --> Ans /50 , where 50 is the desired frequency */
	trace_printf("Delay_ns = %d\n",Delay_ns);
	trace_printf("Freq = %d\n",1000000000 / (Delay_ns * 2) );

	StepperFrequencyPeriodTicks = (STEPPER_TIMER_2_FREQ_Mhz * Delay_ns * 2 ) / 1000 ;
	trace_printf("FREQUENCY_PERIOD_TICKS = %d\n",StepperFrequencyPeriodTicks);
	Stepper_SetSpeed(StepperId,StepperFrequencyPeriodTicks);

	//trace_printf("%d\n",Delay_ns);
/*desired time = Num_timer_ticks * Time_of_one_tick */

}
/*
 * 134 mm  -->
 *
 *
 * */

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
	TimerBasePeriodTicks = (Delay_ns * 2 * Steps * 84) / (1000 * STEPPER_TIMER_BASE_PRESCALER) ;
	trace_printf("TimerBasePeriodTicks = %d\n",TimerBasePeriodTicks);

	Stepper_StepsTime(StepperId,TimerBasePeriodTicks);

}
