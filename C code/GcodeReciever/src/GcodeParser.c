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
#include "GcodeParser.h"
//#include "Extruder.h"
uint8_t *GcodeDataArray;
uint32_t Size;


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
	/* TODO:Set the call back function of the pointer to fun to be called inside
	 * its interrupt with GcodeParser_enuParseGcode */
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
Status_e GcodeParser_enuParseGcode()
{	/* 'X' '5''5''6' */
	static uint32_t ByteIdx;
	uint8_t temp[4];

	temp[0] = GcodeDataArray[ByteIdx+1];
	temp[1] = GcodeDataArray[ByteIdx+2];
	temp[2] = GcodeDataArray[ByteIdx+3];

	if(GcodeDataArray[ByteIdx] == 'F')
	{
		/*Call the Set Feed Rate Here */

		/* Extruder_SetFeedRate(GcodeDataArray[ByteIdx], (uint32_t)atoi(temp));  */
		trace_printf("setting the feed rate with %d \n",(uint32_t)Service_u32Concat(temp, 3));
	}
	else
	{
		/* Call the Set Material  */

		/* Extruder_SetMaterial(GcodeDataArray[ByteIdx], (uint32_t)atoi(temp));  */
		trace_printf("setting the motor %c rate with %d \n",GcodeDataArray[ByteIdx] ,(uint32_t)Service_u32Concat(temp, 3));
	}

	ByteIdx +=4;

	if(ByteIdx > Size )
	{
		/*TODO: stop the timer or return error then stop the timer in the caller function the BASE TIMER ISR */
		return _ERROR;
	}

	return _SUCCESS;
}

