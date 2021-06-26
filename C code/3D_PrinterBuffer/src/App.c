/*
 * App.c
 *
 *  Created on: Jun 24, 2021
 *      Author: abdoo
 */

#include <stdint.h>
#include "../../lib/Bit_Mask.h"
#include "../../lib/Bit_Math.h"
#include "../../lib/Error_codes.h"
#include "../../../lib/src/RT_Debug.h"
#include "App_Types.h"
#include "GcodeReceiver.h"
#include "GcodeParser.h"
#include "Extruder.h"
#include "Service.h"
#include "Buffer.h"
#include "Cutter.h"
#include "Heater.h"
#include "IR.h"
#include "App.h"
#include "App_cfg.h"


/* Call the Set Material to run the Material Extruder and the main extruder   */



static APP_DataReceiveStatus_e DataReceiveState = APP_DataNotReceived;
static APP_GcodeEndStatus_e GcodeEndState = APP_GcodeNotEnd;
volatile uint32_t Extruder_ActionDoneFlag;

static void dataReceivedCallback()
{
	uint8_t * GcodeBytes;
	uint16_t GcodeNumberOfBytes;
	GcodeBytes = GcodeReceiver_GetGcodeData(&GcodeNumberOfBytes);
	GcodeParser_enuInitParsing(GcodeBytes, GcodeNumberOfBytes);
	DataReceiveState= APP_DataReceived;
	trace_printf("Data Received successfully \n");
}

static void App_vidMaterialSwap(uint8_t OldMaterial, uint8_t CurrentMaterial,uint32_t MaterialLength ,uint32_t FeedRate)
{
	IR_State_e IRHasNewMaterialReached = IR_State_Off;
	/*Extrude the old material to provide matrial for the Offset Length */
	Extruder_SetDirection(OldMaterial,EXTRUDER_DIR_CW);
	Extruder_SetFeedRate(OldMaterial, APP_REVERSE_FEEDRATE);
	Extruder_SetMaterialLength(OldMaterial, APP_MATERIAL_OFFSET_um, EXTRUDER_ENABLE);
	/*Wait for it */
	App_vidWaitForActionExecution();

	trace_printf("Cut \n");
	/*Perform the Cut Action
	 * TODO: configure the wait time */
	Cutter_enuTurnOn();
	Service_enuDelay(APP_CUTTING_TIME);
	Cutter_enuTurnOff();

	/*Reverse the old material with the reverse speed */
	Extruder_SetDirection(OldMaterial,EXTRUDER_DIR_CCW);
	Extruder_SetFeedRate(OldMaterial, APP_REVERSE_FEEDRATE);
	Extruder_SetMaterialLength(OldMaterial, APP_MATERIAL_OFFSET_um, EXTRUDER_DISABLE);

	/*Wait till Retraction */
	App_vidWaitForActionExecution();

	/***************************Move the old material from Cutter to The Heater**************************************/
	Extruder_SetDirection(EXTRUDER_E ,EXTRUDER_DIR_CCW);
	Extruder_SetFeedRate(EXTRUDER_E, FeedRate);
	Extruder_SetMaterialLength(EXTRUDER_E, APP_CUTTER_HEATER_OFFSET_um, EXTRUDER_DISABLE);

	/****************************************************************************************************************/

	App_vidWaitForActionExecution();

	/*if New Material Length Less than Distance Between Feeder and Heater
	 * Feed with compensated Length (Offset Between Feeder and Heater - Material Length)
	 * 	Extruder_SetMaterialLength(CurrentMaterial, MaterialLength + CompensatedLength, EXTRUDER_DISABLE);
	 *
	 * Retraction The compensated Length
	 */
	/*TODO: What if this (APP_FEEDER_HEATER_OFFSET - MaterialLength) is larger than buffer size ??!! */
	if(APP_FEEDER_HEATER_OFFSET_um > MaterialLength)
	{
		/*Run the new material */

		trace_printf("MaterialLength <  APP_FEEDER_HEATER_OFFSET_um \n");
		Extruder_SetDirection(CurrentMaterial ,EXTRUDER_DIR_CW);
		Extruder_SetFeedRate(CurrentMaterial, FeedRate);
		Extruder_SetMaterialLength(CurrentMaterial, MaterialLength + (APP_FEEDER_HEATER_OFFSET_um - MaterialLength) , EXTRUDER_DISABLE);

		/*Wait till action complete*/
		App_vidWaitForActionExecution();

		/*join the two material to together */
		for(uint8_t LoopIdx =0;LoopIdx < APP_NUMBER_OF_HEATING_TIMES; LoopIdx++)
		{
			HEATER_enuStart();
			Service_enuDelay(APP_HEATING_TIME);
			HEATER_enuStop();
			Service_enuDelay(APP_HEATING_TIME);
		}


		/*Retract the offset material */
		Extruder_SetDirection(CurrentMaterial ,EXTRUDER_DIR_CCW);
		Extruder_SetFeedRate(CurrentMaterial, FeedRate);
		Extruder_SetMaterialLength(CurrentMaterial, (APP_FEEDER_HEATER_OFFSET_um - MaterialLength) , EXTRUDER_ENABLE);

	}
	else
	{

		/*Run the new material */
		Extruder_SetDirection(CurrentMaterial ,EXTRUDER_DIR_CW);
		Extruder_SetFeedRate(CurrentMaterial, FeedRate);
		Extruder_SetMaterialLength(CurrentMaterial, APP_FEEDER_HEATER_OFFSET_um , EXTRUDER_DISABLE);

		App_vidWaitForActionExecution();

		/*Wait till it reaches to the heater */
	/*	do
		{
			IR_enuGetState(&IRHasNewMaterialReached);
		}while(IRHasNewMaterialReached == IR_State_Off);

		//trace_printf("read IR Wrong!!!! \n");
		/*Pause the Feed of the new material if Material Length > Offset Between Feeder and Heater
		Extruder_Pause();

		//trace_printf("Pause!!!! \n");
	 	 */
		/*join the two material to together */
		/*join the two material to together */

		/*Talsa2a Time */
		Service_enuDelay(42000);

		for(uint8_t LoopIdx =0;LoopIdx < APP_NUMBER_OF_HEATING_TIMES; LoopIdx++)
		{
			HEATER_enuStart();
			Service_enuDelay(APP_HEATING_TIME);
			HEATER_enuStop();
			Service_enuDelay(APP_HEATING_TIME);
		}
		//trace_printf("Continue!!!! \n");

		/*Continue the Feed of the new material if Material Length > Offset Between Feeder and Heater */
	/*	Extruder_SetDirection(EXTRUDER_E ,EXTRUDER_DIR_CW);
		Extruder_Continue(EXTRUDER_ENABLE);
		*/
		Extruder_SetDirection(CurrentMaterial ,EXTRUDER_DIR_CW);
		Extruder_SetFeedRate(CurrentMaterial, FeedRate);
		Extruder_SetMaterialLength(CurrentMaterial, MaterialLength - APP_FEEDER_HEATER_OFFSET_um , EXTRUDER_ENABLE);
	}
}

/*TODO: Modify this function to set the system in sleep mode, till the reception of Gcode*/
void App_vidInit()
{
	Extruder_Init();
	Extruder_SetAllStatus(EXTRUDER_ENABLE);
	Extruder_SetALLDirection(EXTRUDER_DIR_CW);
	Extruder_SetDirection(EXTRUDER_E,EXTRUDER_DIR_CCW);

	/* Limit Switch */
	//Buffer_Init();
	/*******************/
	Cutter_enuInit();
	HEATER_enuInit(HEATER_DUTYCYCLE);
	/*************Timer Delay of Heater and Cutter *********************************/
	Service_TimerBaseInit();
	/******************************************************************************/
	GcodeReceiver_vidInit(dataReceivedCallback);
	Extruder_SetNotifyFlag(&Extruder_ActionDoneFlag);
}

void App_vidWaitForActionExecution()
{
	/*Wait for the Extruder to finish its operation */
	while(Extruder_ActionDoneFlag == ExtruderAction_NotDone);
}

void App_vidWaitForDataReception()
{
	/*Wait for the data Reception CBF to Set this flag*/
	while(DataReceiveState == APP_DataNotReceived);
}

APP_GcodeEndStatus_e App_HasGcodeEnded()
{	/*TODO: Update the GcodeEndState Flag when the GcodeParser returns Done */
	return GcodeEndState;
}

void App_vidSystemSleep()
{
	Extruder_SetAllStatus(EXTRUDER_DISABLE);
	/*TODO: Disable anything else like LimitSwitch Interrupts,
	 *  by making Deinit functions */

	/*Reset the Receiving Flag */
	DataReceiveState = APP_DataNotReceived;

	/*Enable the Uart for the next file execution
	 * TODO: Change this to enable uart only not all the peripherals */
	GcodeReceiver_vidInit(dataReceivedCallback);
}

void App_vidParseGcode(GcodeParser_Action_t* ExtruderAction)
{
	GcodeEndState = GcodeParser_enuParseGcode(ExtruderAction);
}

void App_vidTakeAction(GcodeParser_Action_t* ExtruderAction)
{
	switch(ExtruderAction->action)
	{
	case GcodeParser_ExtrudeMaterial:
	case GcodeParser_ChangeFeedRate :
		trace_printf("GcodeParser_ExtrudeMaterial Stepper= %d \n" , ExtruderAction->Material);
		Extruder_SetDirection(ExtruderAction->Material, ExtruderAction->Direction);
		Extruder_SetFeedRate(ExtruderAction->Material, ExtruderAction->FeedRate);
		Extruder_SetFeedRate(EXTRUDER_E, ExtruderAction->FeedRate);
		Extruder_SetMaterialLength(ExtruderAction->Material, ExtruderAction->MaterialLength_um, EXTRUDER_ENABLE);
		break;
	case GcodeParser_SwapMaterial:
		trace_printf("GcodeParser_Swap \n");
		App_vidMaterialSwap(ExtruderAction->OldMaterial, ExtruderAction->Material,ExtruderAction->MaterialLength_um,ExtruderAction->FeedRate);
		break;
	}
}
