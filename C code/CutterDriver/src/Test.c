/*
 * Test.c
 *
 *  Created on: Jun 25, 2021
 *      Author: Islam
 */



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
#include "Extruder.h"
#include "Buffer.h"


typedef enum
{
	stage_1 ,
	stage_2 ,
	stage_3 ,
	stage_4
}Stepper_Stage_enu;


Stepper_Stage_enu Stepper_Stage = stage_1 ;

volatile uint32_t ActionFlag = ExtruderAction_NotDone  ;

void dataReceivedCallback(void)
{
	uint8_t * GcodeBytes;
	uint16_t GcodeNumberOfBytes;
	GcodeBytes = GcodeReceiver_GetGcodeData(&GcodeNumberOfBytes);
	GcodeParser_enuInitParsing(GcodeBytes, GcodeNumberOfBytes);
	trace_printf("The End elhamdullah \n");
}

void Stepper_Test(void)
{
	Extruder_SetStatus(EXTRUDER_M_1,EXTRUDER_ENABLE);
	Extruder_SetDirection(EXTRUDER_M_1,EXTRUDER_DIR_CW);

	/*****************************************Least FeedRate = 500*********************************************************************/
	Extruder_SetFeedRate(EXTRUDER_M_1,6000);
	Extruder_SetMaterialLength(EXTRUDER_M_1,268000,Extruder_NotWorking);
}

void Stepper_PauseContinue_Test(void)
{
	do
	{
		trace_printf("Delay\n");
		trace_printf("Delay\n");
		trace_printf("Delay\n");
		trace_printf("Delay\n");

		uint32_t Return_Status = Extruder_Pause() ;
		trace_printf("Stepper_Stop= %d\n",Return_Status);

		trace_printf("Delay\n");
		trace_printf("Delay\n");
		trace_printf("Delay\n");
		trace_printf("Delay\n");

		Return_Status = Extruder_Continue() ;
		trace_printf("Stepper_Continue= %d\n",Return_Status);
	}while(0);
}

void Stepper_StateMachine(void)
{
	switch(Stepper_Stage)
	{
	case stage_1 :
		Stepper_Stage = stage_2 ;
		Extruder_SetDirection(EXTRUDER_M_1,EXTRUDER_DIR_CCW);
		Extruder_SetFeedRate(EXTRUDER_M_1,4000);
		Extruder_SetMaterialLength(EXTRUDER_M_1,260000,Extruder_NotWorking);
		break;
	case stage_2 :
		Stepper_Stage = stage_3 ;
		Extruder_SetDirection(EXTRUDER_M_2,EXTRUDER_DIR_CW);
		Extruder_SetFeedRate(EXTRUDER_M_2,2000);
		Extruder_SetMaterialLength(EXTRUDER_M_2,100000,Extruder_NotWorking);
		break;
	case stage_3 :
		Stepper_Stage = stage_4;
		Extruder_SetDirection(EXTRUDER_M_2,EXTRUDER_DIR_CCW);
		Extruder_SetFeedRate(EXTRUDER_M_2,2000);
		Extruder_SetMaterialLength(EXTRUDER_M_2,100000,Extruder_NotWorking);
		break;
	case stage_4 :
		Stepper_Stage = stage_1;
		Extruder_SetDirection(EXTRUDER_M_1,EXTRUDER_DIR_CW);
		Extruder_SetFeedRate(EXTRUDER_M_1,4000);
		Extruder_SetMaterialLength(EXTRUDER_M_1,260000,Extruder_NotWorking);
		break;
	}
}


void Buffer_Test(void)
{
	Buffer_Init();
}
int main(void){
	Extruder_Init();
	//GcodeReceiver_vidInit(dataReceivedCallback);
	Extruder_SetNotifyFlag(&ActionFlag);

	Extruder_SetAllStatus(EXTRUDER_ENABLE);
	Extruder_SetALLDirection(EXTRUDER_DIR_CW);

	Extruder_SetFeedRate(EXTRUDER_M_1,4000);
	Extruder_SetMaterialLength(EXTRUDER_M_1,260000,Extruder_NotWorking);
////
	while(1)
	{
		while(ActionFlag == ExtruderAction_NotDone);
		ActionFlag = ExtruderAction_NotDone ;

		Extruder_SetDirection(EXTRUDER_M_1,EXTRUDER_DIR_CCW);
		Extruder_SetFeedRate(EXTRUDER_M_1,4000);
		Extruder_SetMaterialLength(EXTRUDER_M_1,260000,Extruder_NotWorking);

		while(ActionFlag == ExtruderAction_NotDone);
		ActionFlag = ExtruderAction_NotDone ;

		Extruder_SetDirection(EXTRUDER_M_2,EXTRUDER_DIR_CW);
		Extruder_SetFeedRate(EXTRUDER_M_2,2000);
		Extruder_SetMaterialLength(EXTRUDER_M_2,100000,Extruder_Working);

		while(ActionFlag == ExtruderAction_NotDone);
		ActionFlag = ExtruderAction_NotDone ;

		Extruder_SetDirection(EXTRUDER_M_2,EXTRUDER_DIR_CCW);
		Extruder_SetFeedRate(EXTRUDER_M_2,2000);
		Extruder_SetMaterialLength(EXTRUDER_M_2,100000,Extruder_Working);

		while(ActionFlag == ExtruderAction_NotDone);
		ActionFlag = ExtruderAction_NotDone ;


		Extruder_SetDirection(EXTRUDER_M_1,EXTRUDER_DIR_CW);
		Extruder_SetFeedRate(EXTRUDER_M_1,4000);
		Extruder_SetMaterialLength(EXTRUDER_M_1,260000,Extruder_NotWorking);
	}
	while(1);
	return 0;
}

/* pulse-  => PD 15  => Blue   led
 * DIR-    => PD 14  => Red    Led
 * ENA-    => PD 13  => Orange led*/


