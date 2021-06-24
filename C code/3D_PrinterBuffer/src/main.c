// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include <stm32f4xx_hal.h>
#include <stm32f4xx_hal_conf.h>
#include <stm32f4xx_hal_tim.h>
#include "../../../lib/src/Bits.h"
#include "../../lib/Error_codes.h"
#include "../../../lib/src/RT_Debug.h"
#include "Stepper.h"
#include "Extruder.h"
#include "GcodeParser.h"
#include "GcodeReceiver.h"

void dataReceivedCallback(void)
{
	uint8_t * GcodeBytes;
	uint16_t GcodeNumberOfBytes;
	GcodeBytes = GcodeReceiver_GetGcodeData(&GcodeNumberOfBytes);
	GcodeParser_enuStartParsing(GcodeBytes, GcodeNumberOfBytes);
	trace_printf("The End elhamdullah \n");
}

int main(void)
{
	Stepper_Init();
	GcodeReceiver_vidInit(dataReceivedCallback);

//	Stepper_SetStatus(STEPPER_1,STEPPER_ENABLE);
//	Stepper_SetDirection(STEPPER_1,STEPPER_DIR_CW);
//
//	/*****************************************Least FeedRate = 500*********************************************************************/
//	Extruder_SetFeedRate(EXTRUDER_M_1,6000);
//	Extruder_SetMaterialLength(EXTRUDER_M_1,268000);

	/*Extruder_SetFeedRate(STEPPER_2,4000);
	Extruder_SetMaterialLength(STEPPER_2,67000);*/

	/*do
	{
	trace_printf("Delay\n");
	trace_printf("Delay\n");
	trace_printf("Delay\n");
	trace_printf("Delay\n");

	uint32_t Return_Status = Stepper_Pause(STEPPER_1) ;
	trace_printf("Stepper_Stop= %d\n",Return_Status);

	trace_printf("Delay\n");
	trace_printf("Delay\n");
	trace_printf("Delay\n");
	trace_printf("Delay\n");

	Return_Status = Stepper_Continue(STEPPER_1) ;
	trace_printf("Stepper_Continue= %d\n",Return_Status);
	}while(0);*/

	while(1){

	}
	return 0;
}

/* pulse-  => PD 15  => Blue   led
 * DIR-    => PD 14  => Red    Led
 * ENA-    => PD 13  => Orange led*/


