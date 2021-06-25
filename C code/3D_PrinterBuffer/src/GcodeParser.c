/*
 * GcodeParser.c
 *
 *  Created on: Jun 22, 2021
 *      Author: abdoo
 */


#include <stdint.h>
#include "../../lib/Bits.h"
#include "../../lib/Bit_Math.h"
#include "../../lib/Error_codes.h"
#include "../../../lib/src/RT_Debug.h"
#include <stm32f4xx_hal.h>
#include <stm32f4xx_hal_tim.h>
#include "App_Types.h"
#include "Service.h"
#include "Extruder.h"
#include "GcodeParser.h"



uint8_t *GcodeDataArray;
uint32_t Size;

/*************************************************************************************************************************/

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
void GcodeParser_enuInitParsing(uint8_t *GcodeArray,uint32_t NumberOfBytes)
{
	GcodeDataArray = GcodeArray;
	Size = NumberOfBytes;

//	GcodeParser_TimerBaseInit();

//	Extruder_SetCallBackFunction(GcodeParser_enuParseGcode);
//	Stepper_SetStatus(EXTRUDER_M_1,STEPPER_ENABLE);
//	Stepper_SetStatus(EXTRUDER_M_2,STEPPER_ENABLE);
//	Stepper_SetDirection(EXTRUDER_M_1,STEPPER_DIR_CW);
//	Stepper_SetDirection(EXTRUDER_M_2,STEPPER_DIR_CW);
//	GcodeParser_enuParseGcode();
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
APP_GcodeEndStatus_e GcodeParser_enuParseGcode(GcodeParser_Action_t *action)
{	/* 'X' '5''5''6' */
	static uint32_t ByteIdx;
	static uint8_t OldMaterial ;/*At first set the old material with the first material to be printed */
	static uint32_t FeedRate;
	uint8_t LengthTemp[4];
	uint32_t MaterialLength;

	if(OldMaterial == 0)
	{
		OldMaterial = GcodeDataArray[ByteIdx+4];
	}

	if(ByteIdx >= Size )
	{
		trace_printf("End of GCode\n");
		return APP_GcodeEnd;
	}

	/*Get the Material Extrusion Length Bytes */
	LengthTemp[0] = GcodeDataArray[ByteIdx+1];
	LengthTemp[1] = GcodeDataArray[ByteIdx+2];
	LengthTemp[2] = GcodeDataArray[ByteIdx+3];

		/*Call the Set Feed Rate Here */
	if(GcodeDataArray[ByteIdx] == 'F')
	{
		FeedRate = (uint32_t)Service_u32Concat(LengthTemp, 3);

		ByteIdx+=4;

		/*Get the Material Extrusion Length Bytes */
		LengthTemp[0] = GcodeDataArray[ByteIdx+1];
		LengthTemp[1] = GcodeDataArray[ByteIdx+2];
		LengthTemp[2] = GcodeDataArray[ByteIdx+3];

		action->action=GcodeParser_ChangeFeedRate;
	}

		MaterialLength = (uint32_t)Service_u32Concat(LengthTemp, 3);
		/*if the current material is not the same as the previous material-->  material swap */
		if (GcodeDataArray[ByteIdx] != OldMaterial )
		{
			action->OldMaterial = OldMaterial - 'X';
			action->action = GcodeParser_SwapMaterial;
			OldMaterial = GcodeDataArray[ByteIdx];
		}
		else
		{
			action->action = GcodeParser_ExtrudeMaterial;
		}
		action->FeedRate = FeedRate;
		action->MaterialLength_um = MaterialLength;
		action->Material= GcodeDataArray[ByteIdx] - 'X';
		action->Direction = EXTRUDER_DIR_CW;


	/*Go to the next Gcode line */
	ByteIdx +=4;

	return APP_GcodeNotEnd;
}

