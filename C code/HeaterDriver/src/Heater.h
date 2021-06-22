/*
 * Servo.h
 *
 *  Created on: Jun 22, 2021
 *      Author: Mohsen
 */

#ifndef HEATER_H_
#define HEATER_H_



extern Status_e HEATER_enuInit(uint8_t InitDutyCycle);

Status_e HEATER_enuChangeDutyCycle(uint8_t DutyCycle);

extern Status_e HEATER_enuStart();

extern Status_e HEATER_enuStop();


#endif /* HEATER_H_ */
