/*
 * GcodeParser.c
 *
 *  Created on: Jun 22, 2021
 *      Author: abdoo
 */


#include <stdint.h>
#include "../../lib/Bit_Mask.h"
#include "../../lib/Bit_Math.h"
#include "../../lib/Error_codes.h"
#include "Service.h"
#include "Extruder.h"
#include "GcodeParser.h"
#include "GcodeParser_cfg.h"
#include "Timer.h"
#include "IR.h"

uint8_t *GcodeDataArray;
uint32_t Size;


static void GcodeParser_vidMaterialSwap(uint8_t OldMaterial, uint8_t CurrentMaterial,uint32_t MaterialLength ,uint32_t FeedRate)
{
	IR_State_e IRHasNewMaterialReached = IR_State_Off;
	timer_start();
	/*Perform the Cut Action
	 * TODO: configure the wait time */
	Cutter_enuTurnOn();
   	timer_sleep(GCODEPARSER_CUTTING_TIME_ms);
   	Cutter_enuTurnOff();

	/*Reverse the old material with the reverse speed */
	Extruder_SetFeedRate(OldMaterial, GCODEPARSER_REVERSE_FEEDRATE);
	Extruder_SetMaterialLength(OldMaterial, GCODEPARSER_MATERIAL_OFFSET_um);
	Extruder_SetFeedRate(OldMaterial, FeedRate);

	/*Run the new material */
	Extruder_SetMaterialLength(CurrentMaterial, GCODEPARSER_MATERIAL_OFFSET_um + MaterialLength);

	/*Wait till it reaches to the heater */
	do
	{
		IR_enuGetState(&IRHasNewMaterialReached);
	}while(IRHasNewMaterialReached == IR_State_Off);

	/*Pause the Feed of the new material */
	Extruder_Pause(CurrentMaterial);

	/*join the two material to together */
	HEATER_enuStart();
	timer_sleep(GCODEPARSER_HEATING_TIME_ms);
	HEATER_enuStop();

	/*Continue the Feed of the new material */
	Extruder_Continue();
}

/**************************************************************************************************************
 * Public Function:GcodeParser_enuStartParsing()
 * Description: This function is used to start the parsing process
 * Input Parameters:
 * 					 -uint8_t *GcodeArray : a pointer to The data to be parsed
 * 					  uint32_t NumberOfBytes: Size of this array
 *
 *
 * Return:           -Status_e : in range {  _PARAM,
 *											 _ERROR,
 *											 _SUCCESS }
 *
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
void GcodeParser_enuStartParsing(uint8_t *GcodeArray,uint32_t NumberOfBytes)
{
	GcodeDataArray = GcodeArray;
	Size = NumberOfBytes;

	 Extruder_SetCallBackFunction(GcodeParser_enuParseGcode);
	 GcodeParser_enuParseGcode();
}


/**************************************************************************************************************
 * Public Function:GcodeParser_enuParseGcode
 * Description: This function is used to parse the Gcode and take actions by calling the extruder functions
 * 				**This function is made to be called after the motors perform their actions**
 *
 * Input Parameters:
 * 					 -uint8_t *GcodeDataArray: a pointer to the Gcode Data array
 * 					  uint16_t Size : the number of elements of this array
 *
 *
 * Return:           -Status_e : in range {  _PARAM,
 *											 _ERROR,
 *											 _SUCCESS }
 *
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
void GcodeParser_enuParseGcode()
{	/* 'X' '5''5''6' */
	static uint32_t ByteIdx;
	static uint8_t OldMaterial = GcodeDataArray[ByteIdx+4];/*At first set the old material with the first material to be printed */
	static uint32_t FeedRate;
	uint8_t LengthTemp[4];
	uint32_t MaterialLength;

	if(ByteIdx >= Size )
	{
		/*TODO: stop the timer or return error then stop the timer in the caller function the BASE TIMER ISR */
		return ;
	}

	/*Get the Material Extrusion Length Bytes */
	LengthTemp[0] = GcodeDataArray[ByteIdx+1];
	LengthTemp[1] = GcodeDataArray[ByteIdx+2];
	LengthTemp[2] = GcodeDataArray[ByteIdx+3];

	if(GcodeDataArray[ByteIdx] == 'F')
	{
		/*Call the Set Feed Rate Here */
		FeedRate = (uint32_t)Service_u32Concat(LengthTemp, 3);

		Extruder_SetFeedRate(EXTRUDER_M_1, FeedRate);
		Extruder_SetFeedRate(EXTRUDER_M_2, FeedRate);
		Extruder_SetFeedRate(EXTRUDER_M_3, FeedRate);
		Extruder_SetFeedRate(EXTRUDER_E, FeedRate);

//		trace_printf("setting the feed rate with %d \n",(uint32_t)Service_u32Concat(LengthTemp, 3));
	}
	else
	{
		MaterialLength = (uint32_t)Service_u32Concat(LengthTemp, 3);
		/*if the current material is not the same as the previous material--> call material swap */
		if (GcodeDataArray[ByteIdx] != OldMaterial )
		{
			GcodeParser_vidMaterialSwap(OldMaterial, GcodeDataArray[ByteIdx], MaterialLength,FeedRate);
			OldMaterial = GcodeDataArray[ByteIdx];
		}
		else
		{
			/* Call the Set Material to run the Material Extruder and the main extruder   */
			Extruder_SetMaterialLength(GcodeDataArray[ByteIdx] - 'X', GCODEPARSER_MATERIAL_OFFSET_um+ MaterialLength);
		}
		Extruder_SetMaterialLength(EXTRUDER_E, GCODEPARSER_MATERIAL_OFFSET_um + MaterialLength);

//		trace_printf("setting the motor %c rate with %d \n",GcodeDataArray[ByteIdx], MaterialLength);
	}

	/*Go to the next Gcode line */
	ByteIdx +=4;
}

