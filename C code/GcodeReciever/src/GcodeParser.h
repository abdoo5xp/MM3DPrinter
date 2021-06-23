/*
 * GcodeParser.h
 *
 *  Created on: Jun 22, 2021
 *      Author: abdoo
 */

#ifndef GCODEPARSER_H_
#define GCODEPARSER_H_




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
void GcodeParser_enuStartParsing(uint8_t *GcodeArray,uint32_t NumberOfBytes);

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
Status_e GcodeParser_enuParseGcode();

#endif /* GCODEPARSER_H_ */
