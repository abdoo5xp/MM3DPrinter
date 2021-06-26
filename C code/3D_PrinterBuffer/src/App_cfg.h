/*
 * App_cfg.h
 *
 *  Created on: Jun 24, 2021
 *      Author: abdoo
 */

#ifndef APP_CFG_H_
#define APP_CFG_H_


#define APP_FEEDER_HEATER_OFFSET_um		240000/*21 CM*/

#define APP_CUTTER_HEATER_OFFSET_um		70000/*7 CM*/

#define APP_MATERIAL_OFFSET_um			150000

#define APP_REVERSE_FEEDRATE			500

#define APP_TIMER_BASE_PRESCALER		39999

#define APP_NUMBER_OF_HEATING_TIMES		5

#define APP_HEATING_TIME				3600  /*********1 Sec --> 4200*************/

#define APP_COOLINGS_TIME				12600  /*********3 Sec*************/

#define APP_CUTTING_TIME				29400  /********7 Sec*************/

#define HEATER_DUTYCYCLE				78

#endif /* APP_CFG_H_ */
