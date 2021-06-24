/*
 * App.h
 *
 *  Created on: Jun 24, 2021
 *      Author: abdoo
 */

#ifndef APP_H_
#define APP_H_


typedef enum {
	APP_DataNotReceived,
	APP_DataReceived
}APP_DataReceiveStatus_e;

extern APP_DataReceiveStatus_e DataReceiveState;

void App_vidInit();

void App_vidParseGcode(GcodeParser_Action_t* ExtruderAction);

void App_vidTakeAction(GcodeParser_Action_t* ExtruderAction);

//void App_vidStartParsing();




#endif /* APP_H_ */
