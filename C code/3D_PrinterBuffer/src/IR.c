/*
 * IR.c
 *
 *  Created on: Jun 20, 2021
 *      Author: abdoo
 */


#include <stdint.h>
#include "../../lib/Bits.h"
#include "../../lib/Bit_Math.h"
#include "../../lib/Error_codes.h"
#include "../../../lib/src/RT_Debug.h"
#include "GPIO_int.h"
#include "Rcc_int.h"
#include "IR.h"
#include "IR_types.h"


uint64_t IR_Gpio[5] =
{
		RCC_AHB1_PERI_CLOCK_GPIOA ,
		RCC_AHB1_PERI_CLOCK_GPIOB,
		RCC_AHB1_PERI_CLOCK_GPIOC,
		RCC_AHB1_PERI_CLOCK_GPIOD,
		RCC_AHB1_PERI_CLOCK_GPIOE
};

/* Public Function:  IR_Init															      *
 * Description: This function is used to Configure Pins that connected to IRs
 * Input parameters:
 *
 * Return:
 * 		-void
 *
 * Input/Output Parameter:
 * 		- Not Applicable
 **********************************************************************************************/
void IR_Init(void)
{
	uint32_t IR_Gpio_Idx ;

	for (uint8_t IR_Idx = 0 ; IR_Idx < IR_NUM ; IR_Idx++)
	{
		IR_Gpio_Idx = (uint32_t)((uint32_t)IRcfg[IR_Idx].Led_Pin.Gpio_Port - (uint32_t)0x40020000) / (uint32_t)0x400;
		Rcc_AHB1_PeriClockStatus(IR_Gpio[IR_Gpio_Idx],RCC_PERI_CLOCK_ENABLE);
		Gpio_Init(&IRcfg[IR_Idx].Led_Pin);
	}
}



/**************************************************************************************************************
 * Public Function:IR_enuGetState
 * Description: This function is used to get the status of the IR sensor if it has detected something or not
 * Input Parameters:
 * 					 -IR_State_e *IRState: the value of the IR sensor is returned in this variable
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
RT_Debug IR_enuGetState(IR_State_e *IRState)
{
	uint32_t pinVal;
	if(IRState == NULL)
	{
		return _PARAM;
	}

	/*Read the GPIO Pin value */
	Gpio_ReadPin(IR_GPIO_PORT,IR_GPIO_PINNUM, &pinVal);

	/*Return the IR Sensor status to the User in the input pointer */
	if(pinVal == IR_STATE_ON)
	{
		*IRState = IR_State_On;
	}
	else
	{
		*IRState = IR_State_Off;
	}

	return _SUCCESS;
}
