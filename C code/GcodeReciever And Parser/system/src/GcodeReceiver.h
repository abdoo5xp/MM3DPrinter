/*
 * GcodeReceiver.h
 *
 *  Created on: Jun 21, 2021
 *      Author: abdoo
 */

#ifndef GCODERECEIVER_H_
#define GCODERECEIVER_H_

typedef void (*pfun)(void);

/**************************************************************************************************************
 * Public Function: GcodeReceiver_vidInit()
 * Description: This function is used to
 * Input Parameters:
 * 					 -pfun dataReceivedCallback: the call back function to be called when the receiving is done
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
extern Status_e GcodeReceiver_vidInit(pfun dataReceivedCallback);

/**************************************************************************************************************
 * Public Function:GcodeReceiver_GetGcodeData
 * Description: This function is used to return a pointer to the Gcode data and the Gcode number of bytes
 * Input Parameters:
 * 					 -uint16_t *GcodeNumberOfBytes: this variable is used to get the number of elements of the Gcode data array
 *
 *
 * Return:           -uint8_t* : a pointer to the Gcode Data Array
 *
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
extern uint8_t* GcodeReceiver_GetGcodeData(uint16_t *GcodeNumberOfBytes);



#endif /* GCODERECEIVER_H_ */
