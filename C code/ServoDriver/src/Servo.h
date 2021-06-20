/*
 * Servo.h
 *
 *  Created on: Jun 20, 2021
 *      Author: abdoo
 */

#ifndef SERVO_H_
#define SERVO_H_

typedef enum
{
SERVO_ANGLE_ZERO_DUTY_CYCLE =3 ,
SERVO_ANGLE_180_DUTY_CYCLE  =8 ,
SERVO_ANGLE_90_DUTY_CYCLE   =12
}Servo_Angles_e;


extern Status_e SERVO_enuInit(Servo_Angles_e InitAngle);

extern Status_e SERVO_enuChangeAngle(Servo_Angles_e Servo_Angle);

extern Status_e SERVO_enuStart();


#endif /* SERVO_H_ */
