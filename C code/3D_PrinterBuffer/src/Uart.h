/*
 * Uart.h
 *
 *  Created on: Mar 14, 2021
 *      Author: abdoo
 */

#ifndef UART_A_H_
#define UART_A_H_


typedef enum {
	usart_1,
	usart_2,
	usart_3,
	uart_4 ,
	uart_5 ,
	usart_6,
	_usart_Id_Length_
}usart_Id_e;

typedef enum{
	txc,
	rxc,
	txfail,
	rxfail,
	rxtimeout
}uart_event_ID_e;

typedef void (*uartCbf)(void);

extern uint8_t Usart_Init(usart_Id_e  usart_Id);

#if UART_MODE   == UART_MODE_TIME_BASED
extern uint32_t Uart_SendBuff(usart_Id_e usart_Id,uint8_t *buf,uint16_t size);

extern uint32_t Uart_tRecvBuff(usart_Id_e usart_Id,uint8_t *buf,uint16_t size);
//uint8_t  Uart_ISReadyToSend(usart_Id_e usartId);
#endif

#if UART_MODE == UART_MODE_EVENT_BASED

extern uint32_t Uart_SendBuff(usart_Id_e usart_Id,uint8_t *buf,uint16_t size);

extern uint32_t Uart_RecvBuff(usart_Id_e usart_Id,uint8_t *buf,uint16_t size);

extern void Uart_SetSendCbf(usart_Id_e usart_Id,uartCbf cbf);

extern void Uart_SetRecvCbf(usart_Id_e usart_Id,uartCbf cbf);

#endif

extern void Uart_SendBreak(usart_Id_e usart_Id);

extern void Uart_EnableLBD_INT(usart_Id_e usart_Id);

extern void Uart_DisableLBD_INT(usart_Id_e usart_Id);

extern void Uart_SetLBDCbf(usart_Id_e usart_Id,uartCbf cbf);

#endif /* UART_A_H_ */
