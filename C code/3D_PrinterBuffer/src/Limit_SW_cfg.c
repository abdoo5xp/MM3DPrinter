/*
 * Limit_SW_cgf.c
 *
 *  Created on: Jun 24, 2021
 *      Author: Islam
 */

#include <stdint.h>
#include "../../lib/Bits.h"
#include "../../lib/Bit_Math.h"
#include "../../lib/Error_codes.h"
#include "../../../lib/src/RT_Debug.h"
#include "GPIO_int.h"
#include "Rcc_int.h"
#include "NVIC.h"
#include "Limit_SW_types.h"
#include "Limit_SW.h"

const LimitSW_cfg_s LimitSWcfg[LIMIT_SW_NUM] = {

		[LIMIT_SW_1] =
		{
				.btn_config =
				{
				 .Gpio_Mode  	 = GPIO_MODE_INPUT 		    		,
				 //.Gpio_OType 	 = GPIO_OTYPE_PUSH_PULL    			,
				 //.Gpio_OSpeed  	 = GPIO_OSPEED_HIGH_SPEED		,
	  		     .Gpio_PUPD 	 = GPIO_PUPD_FLOATING				,
			     .Gpio_Port  	 = GPIOA							,
				 .Gpio_PinNum    = GPIO_PIN0
				},
				.exti_config =
				{
				 .EXTINum = 0,
				 .EdgeDetectionType = EXTI_EDGE_RISING ,
				 .maskType = EXTI_MASKTYPE_INTERRUPT ,
				 .pinNum = 0 ,
				 .port  = EXTI_PORTA
				},
				.EXINT_Line = _EXTI0_IRQn
		},
		[LIMIT_SW_2] =
		{
				.btn_config =
				{
				 .Gpio_Mode  	 = GPIO_MODE_INPUT 		    		,
				 .Gpio_OType 	 = GPIO_OTYPE_PUSH_PULL    			,
				 .Gpio_OSpeed  	 = GPIO_OSPEED_VERY_HIGH_SPEED		,
	  		     .Gpio_PUPD 	 = GPIO_PUPD_FLOATING 				,
			     .Gpio_Port  	 = GPIOA							,
				 .Gpio_PinNum    = GPIO_PIN1
				},
				.exti_config =
				{
				 .EXTINum = 1 ,
				 .EdgeDetectionType = EXTI_EDGE_RISING ,
				 .maskType = EXTI_MASKTYPE_INTERRUPT ,
				 .pinNum = 1,
				 .port  = EXTI_PORTA
				},
				.EXINT_Line = _EXTI1_IRQn
		}
};
