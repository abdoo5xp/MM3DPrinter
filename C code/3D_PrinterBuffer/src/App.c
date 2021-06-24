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
#include "Extruder.h"
#include "Buffer.h"
#include "Cutter.h"
#include "GcodeParser.h"
#include "App.h"
#include "App_cfg.h"


APP_DataReceiveStatus_e DataReceiveState = APP_DataNotReceived;

void dataReceivedCallback()
{
	uint8_t * GcodeBytes;
	uint16_t GcodeNumberOfBytes;
	GcodeBytes = GcodeReceiver_GetGcodeData(&GcodeNumberOfBytes);
	GcodeParser_enuInitParsing(GcodeBytes, GcodeNumberOfBytes);
	DataReceiveState= APP_DataReceived;
	trace_printf("Data Received successfully \n");
}


void App_vidInit()
{
	Extruder_Init();
	Extruder_SetAllStatus(EXTRUDER_ENABLE);
	Extruder_SetALLDirection(EXTRUDER_DIR_CW);

//	Buffer_Init();
	Cutter_enuInit();
	GcodeReceiver_vidInit(dataReceivedCallback);
	GcodeParser_TimerBaseInit();
}







