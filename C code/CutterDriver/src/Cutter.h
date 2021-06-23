/*
 * Cutter.h
 *
 *  Created on: Jun 23, 2021
 *      Author: Mohsen
 */

#ifndef CUTTER_H_
#define CUTTER_H_

/* might be needed*/
//typedef enum
//{
//	Cutter_ANGLE_ZERO_DUTY_CYCLE =  3 ,
//	Cutter_ANGLE_180_DUTY_CYCLE  =  8 ,
//	Cutter_ANGLE_90_DUTY_CYCLE   =  12
//}Cutter_Angles_e;


extern Status_e Cutter_enuInit (void);
extern Status_e Cutter_enuperformCut  (void);

//extern Status_e Cutter_enuChangeAngle(Cutter_Angles_e Cutter_Angle);
//extern Status_e Cutter_enuTurnOn  (void);
//extern Status_e Cutter_enuTurnOff (void);


#endif /* CUTTER_H_ */
