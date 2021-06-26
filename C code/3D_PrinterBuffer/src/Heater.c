/*
 * Servo.c
 *
 *  Created on: Jun 22, 2021
 *      Author: Mohsen
 */



#include "../../lib/Bits.h"
#include "../../lib/Bit_Math.h"
#include "../../lib/Error_codes.h"

#include <stdint.h>
#include <stm32f4xx.h>
#include <stm32f4xx_hal_tim.h>
#include "diag/Trace.h"

#include "Rcc_int.h"
#include "GPIO_int.h"
#include "Heater.h"
#include "Heater_cfg.h"

/**********************Heater Connected to PC6**********************/

extern Status_e HEATER_enuInit(uint8_t InitDutyCycle)
{
	uint8_t Return_status;

	Pincfg_t HeaterConfigPin;

	HeaterConfigPin.Gpio_Mode  	 = GPIO_MODE_OUTPUT 		    		;
	HeaterConfigPin.Gpio_OType 	 = GPIO_OTYPE_PUSH_PULL    			;
	HeaterConfigPin.Gpio_OSpeed  = GPIO_OSPEED_VERY_HIGH_SPEED		;
	HeaterConfigPin.Gpio_PUPD 	 = GPIO_PUPD_PULL_DOWN				;
	HeaterConfigPin.Gpio_Port  	 = GPIOC							;
	HeaterConfigPin.Gpio_PinNum  = GPIO_PIN6							;

/*************************************Clocks Enable***********************************************************************************/
	trace_printf("RCC-1  Enable Return = %d\n ",Rcc_AHB1_PeriClockStatus(RCC_AHB1_PERI_CLOCK_GPIOC, RCC_PERI_CLOCK_ENABLE));

	/* Init. the pin in GPIO */
	trace_printf("GPIO Enable Return = %d\n ",Gpio_Init(&HeaterConfigPin));

	return Return_status;
}

/*-----------*/
Status_e HEATER_enuStart()
{
	uint8_t Return_status;

	Return_status = Gpio_WritePin(HEATER_PORT,HEATER_PIN,GPIO_PIN_SET);
	return Return_status;
}

Status_e HEATER_enuStop()
{
	uint8_t Return_status;
	Return_status = Gpio_WritePin(HEATER_PORT,HEATER_PIN,GPIO_PIN_RESET);
	return Return_status;
}

