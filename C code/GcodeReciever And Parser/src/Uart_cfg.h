/*
 * Uart_cfg.h
 *
 *  Created on: Mar 19, 2021
 *      Author: abdoo
 */

#ifndef UART_CFG_A_H_
#define UART_CFG_A_H_


#define UART_MODE_TIME_BASED		0
#define UART_MODE_EVENT_BASED		1
#define UART_MODE					UART_MODE_EVENT_BASED

#define UART_BREAK_ONLY_MODE_ON		0
#define UART_BREAK_ONLY_MODE_OFF	1
#define UART_BREAK_ONLY_MODE		UART_BREAK_ONLY_MODE_OFF

#define LIN_ENABLE					0
#define LIN_DISABLE					1

/*PLEASE: keep only the usart channels that you are using */
//#define usart_CH_1				0
#define usart_CH_2					1
//#define usart_CH_3				2
//#define uart_CH_4					3
//#define uart_CH_5					4
//#define usart_CH_6				5

/*TODO:PLEASE GOTO the INTERFACE FILE and change the usart_Id_e  */

/*TODO: in Time based mode add the user can configure after how much time should he send the frame
 * (time_ms of the SWtimer while registering it in Send Buff function )*/
typedef enum {
	oneStopBit,
	halfStopBit,
	twoStopBit,
	oneHalfStopBit,
}usart_stopBits_e;

typedef enum {
	eightBits,
	nineBits
}usart_frameSize_e;

typedef enum {
	usartDisable,
	usartEnable
}usart_featureControl_e;

typedef enum{
	evenParity,
	oddParity
}usart_parityModes_e;
//typedef enum {
//	idleLine,
//	address
//}usart_wakeUp_e;


/* 1- Clear to Send Interrupt
 * 2- LIN Break Detection Interrupt
 * 3- Transmit Data register Empty Interrupt
 * 4- Transmission complete  Interrupt
 * 5- Receive data register not empty Interrupt
 * 6- Idle frame detection Interrupt
 * 7- Over Run Error Interrupt
 * 8- Noise detection Interrupt
 * 9- Frame Error Interrupt
 * 10-Parity Error Interrupt
 * 11-Error Interrupt
 * */
typedef struct {
//	uint8_t cts ;
//	uint8_t lbd ;

//	uint8_t txe ;
//	uint8_t txc  ;
//	uint8_t rxne;
//	uint8_t idle;
	uint8_t pe  ;

	uint8_t eie;
}usart_interrupts_t;


typedef struct {
	void*    usartAddress;

	uint8_t  parityEnable;
	uint8_t  paritySelection;
	uint8_t  stopBit;
	uint8_t  frameSize;
//	uint8_t  halfDuplex;

	uint8_t  txEnable;
	uint8_t  rxEnable;
	uint8_t  txDmaEnable;
	uint8_t  rxDmaEnable;
	uint8_t  linEnable;
//	uint8_t  syncmode;

//	uint8_t  wakeUpMethod;
//	uint8_t  sbk;
//	uint8_t  overSampling;
//	uint8_t  BaudRate_Fraction;
//	uint32_t BaudRate_Mantissa;
	uint32_t usartBaudRate;

	usart_interrupts_t interrupts;
}usart_config_t;


extern usart_config_t usart_instances[_usart_Id_Length_] ;

#endif /* UART_CFG_A_H_ */
