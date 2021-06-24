/*
 * Uart_cfg.c
 *
 *  Created on: Mar 20, 2021
 *      Author: abdoo
 */



#include <stdint.h>
#include "../../lib/Bit_Mask.h"
#include "../../lib/Bit_Math.h"
#include "../../lib/Error_codes.h"
#include "Uart.h"
#include "Uart_cfg.h"

/*
 * For APB2 clock frequency -> 84 Mhz
 * to get a baud rate of 115200
 * over8 = zero
 * mantissa = 45
 * fraction = 0.5625 * 16 = 9
 *
 * */
/*connected on APB2 */
#define USART_ADDRESS_1  	((void *) 0x40011000)
#define USART_ADDRESS_6  	((void *) 0x40011400)
/*connected on APB1 */
#define USART_ADDRESS_2  	((void *) 0x40004400)
#define USART_ADDRESS_3  	((void *) 0x40004800)
#define UART_ADDRESS_4  	((void *) 0x40004C00)
#define UART_ADDRESS_5  	((void *) 0x40005000)
#define UART_ADDRESS_7  	((void *) 0x40007800)
#define UART_ADDRESS_8  	((void *) 0x40007C00)

#define USART_BRR_FPCK_16_9600				(0x68  << 4)|(0x03 ) //(45  << 4)|(9 )

#define USART_BRR_FPCK_84_115200			(0x2D  << 4)|(0x9 ) //(45  << 4)|(9 )
#define USART_BRR_FPCK_84_9600				(0x222 << 4)|(0xE)//(546 << 4)|(14)

#define USART_BRR_FPCK_42_115200			(22  << 4)|(13)
#define USART_BRR_FPCK_42_9600				(273 << 4)|(7 )

/*OPTIONS : LIN_ENABLE
 *			LIN_DISABLE
 * */

/*TODO: Add usart_Enable function and disable function */
usart_config_t usart_instances[_usart_Id_Length_] = {
/*WARNING : BE CAREFUL PA2 IS RESERVED FOR STM USASGE, WE 7ASBY ALLAH W NA3M EL WAKEEL */
//		[usart_1]={
//			.usartAddress      = USART_ADDRESS_1,
//			.parityEnable      = usartDisable,
//			.paritySelection   = evenParity,
//			.stopBit           = oneStopBit,
//			.frameSize         = eightBits,
//			.txEnable          = usartEnable,
//			.rxEnable          = usartEnable,
//			.txDmaEnable       = usartDisable,
//			.rxDmaEnable       = usartDisable,
//			.usartBaudRate	   = USART_BRR_FPCK_16_9600,
//
//			/*will get into the interrupt once the controller is up because
//			 * the tx send buffer is empty, so use txc */

//			.interrupts.pe  = usartDisable,
//			.interrupts.eie = usartDisable,
//		},
		[usart_2]={
			.usartAddress      = USART_ADDRESS_2,
			.parityEnable      = usartDisable,
			.paritySelection   = evenParity,
			.stopBit           = oneStopBit,
			.frameSize         = eightBits,
			.txEnable          = usartEnable,
			.rxEnable          = usartEnable,
			.txDmaEnable       = usartDisable,
			.rxDmaEnable       = usartDisable,
			.usartBaudRate	   = USART_BRR_FPCK_42_9600,
			.linEnable		   = LIN_DISABLE,
			/*will get into the interrupt once the controller is up because
			 * the tx send buffer is empty, so use txc */

			.interrupts.pe  = usartDisable,
			.interrupts.eie = usartDisable,
		},
};
