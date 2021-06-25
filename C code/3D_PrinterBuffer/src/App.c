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
	Extruder_SetMaterialLength(OldMaterial, APP_MATERIAL_OFFSET_um, EXTRUDER_ENABLE);
	/*Wait for it */
	App_vidWaitForActionExecution();

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

	/*Run the new material */
	Extruder_SetDirection(CurrentMaterial ,EXTRUDER_DIR_CW);
	Extruder_SetFeedRate(CurrentMaterial, FeedRate);
	Extruder_SetMaterialLength(CurrentMaterial, MaterialLength, EXTRUDER_ENABLE);

	/*Wait till it reaches to the heater */
	do
	{
		IR_enuGetState(&IRHasNewMaterialReached);
	}while(IRHasNewMaterialReached == IR_State_Off);

	/*Pause the Feed of the new material */
	Extruder_Pause(CurrentMaterial);

	/*join the two material to together */
	HEATER_enuStart();
	Service_enuDelay(APP_HEATING_TIME);
	HEATER_enuStop();

	/*Continue the Feed of the new material */
	Extruder_Continue(CurrentMaterial);
}

/*TODO: Modify this function to set the system in sleep mode, till the reception of Gcode*/
void App_vidInit()
{
	Extruder_Init();
	Extruder_SetAllStatus(EXTRUDER_ENABLE);
	Extruder_SetALLDirection(EXTRUDER_DIR_CW);

	Buffer_Init();
	Cutter_enuInit();
	HEATER_enuInit(HEATER_DUTYCYCLE);
	Service_TimerBaseInit();
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
		Extruder_SetDirection(ExtruderAction->Material, ExtruderAction->Direction);
		Extruder_SetFeedRate(ExtruderAction->Material, ExtruderAction->FeedRate);
		Extruder_SetMaterialLength(ExtruderAction->Material, ExtruderAction->MaterialLength_um, EXTRUDER_ENABLE);
		break;
	case GcodeParser_SwapMaterial:
		App_vidMaterialSwap(ExtruderAction->OldMaterial, ExtruderAction->Material,ExtruderAction->MaterialLength_um,ExtruderAction->FeedRate);
		break;
	}
}
