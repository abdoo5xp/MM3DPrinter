/*
 * GcodeReceiver_cfg.c
 *
 *  Created on: Jun 21, 2021
 *      Author: abdoo
 */


#include <stdint.h>
#include "../../lib/Bits.h"
#include "../../lib/Bit_Math.h"
#include "../../lib/Error_codes.h"
#include "../../../lib/src/RT_Debug.h"
#include "GPIO_int.h"
#include "Uart.h"
#include "GcodeReceiver_cfg.h"



GcodeReceiver_cfg_t GcodeReceiver_Uart_Module[GCODERECEIVER_MODULES_NUM]={
		[0]={
				{
						/*Tx pin config*/
						.Gpio_Mode  	 = GPIO_MODE_AF 		    		,
						.Gpio_OType 	 = GPIO_OTYPE_PUSH_PULL    			,
						.Gpio_OSpeed   = GPIO_OSPEED_VERY_HIGH_SPEED		,
						.Gpio_PUPD 	 = GPIO_PUPD_PULL_UP 				,
						.Gpio_Port  	 = GPIOA							,
						.Gpio_PinNum 	 = GPIO_PIN2						,
						.Gpio_AF = GPIO_AF7_USART1_3
				},
				{
						/*Rx pin config*/

						.Gpio_Mode  	 = GPIO_MODE_AF 		    		,
						.Gpio_OType 	 = GPIO_OTYPE_PUSH_PULL    			,
						.Gpio_OSpeed   = GPIO_OSPEED_VERY_HIGH_SPEED		,
						.Gpio_PUPD 	 = GPIO_PUPD_PULL_UP 				,
						.Gpio_Port  	 = GPIOA							,
						.Gpio_PinNum 	 = GPIO_PIN3						,
						.Gpio_AF = GPIO_AF7_USART1_3

				},
						/*uart channel config*/
						.Uart_Channel = usart_2
		}
};
