/*
 * GcodeReceiver_cfg.c
 *
 *  Created on: Jun 21, 2021
 *      Author: abdoo
 */


#include <stdint.h>
#include "../../lib/Bit_Mask.h"
#include "../../lib/Bit_Math.h"
#include "../../lib/Error_codes.h"
#include "GPIO.h"
#include "GcodeReceiver_cfg.h"
#include "Uart_A.h"



GcodeReceiver_cfg_t GcodeReceiver_Uart_Module[GCODERECEIVER_MODULES_NUM]={
		[0]={
				{
						/*Tx pin config*/
						.mode    = GPIO_MODE_AF,
						.port    = GPIO_PORTA,
						.pinNum  = GPIO_PIN_2,
						.pupd    = GPIO_PULL_UP,
						.AF      = GPIO_AF7_USART1_3,
						.otype   = GPIO_OTYPE_PUSH_PULL,
						.ospeed  = GPIO_OSPEED_HIGH,
				},
				{
						/*Rx pin config*/
						.mode   =  GPIO_MODE_AF,
						.port   =  GPIO_PORTA,
						.pinNum =  GPIO_PIN_3,
						.pupd   =  GPIO_PULL_UP,
						.AF     =  GPIO_AF7_USART1_3,
						.otype  =  GPIO_OTYPE_PUSH_PULL,
						/*try very high*/
						.ospeed =  GPIO_OSPEED_HIGH,

				},
//				{
//						/*uart channel config*/
//						usart_2
//				}
		}
};
