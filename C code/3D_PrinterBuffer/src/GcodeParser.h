/*
 * GcodeParser.h
 *
 *  Created on: Jun 22, 2021
 *      Author: abdoo
 */

#ifndef GCODEPARSER_H_
#define GCODEPARSER_H_


typedef enum{
	GcodeParser_ExtrudeMaterial,
	GcodeParser_ChangeFeedRate,
	GcodeParser_SwapMaterial
}GcodeParser_ActionTypes_e;

typedef struct {
	GcodeParser_ActionTypes_e action;
	uint32_t MaterialLength_um;
	uint32_t Direction;  			 /*one of the Extruder DIR Macros*/
	uint32_t FeedRate;
	uint8_t  Material;				 /* EXTRUDER_M_1, EXTRUDER_M_2, EXTRUDER_M_3, EXTRUDER_E */
}GcodeParser_Action_t;

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
void GcodeParser_enuInitParsing(uint8_t *GcodeArray,uint32_t NumberOfBytes);

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
void GcodeParser_enuParseGcode(GcodeParser_Action_t *);


RT_Debug GcodeParser_TimerBaseInit(void);

RT_Debug Heater_Delay(uint32_t Heater_delay);

RT_Debug Cutter_Delay(uint32_t Cutter_delay);

#endif /* GCODEPARSER_H_ */
