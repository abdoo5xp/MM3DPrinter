/*
 * GcodeReceiver_cfg.h
 *
 *  Created on: Jun 21, 2021
 *      Author: abdoo
 */

#ifndef GCODERECEIVER_CFG_H_
#define GCODERECEIVER_CFG_H_

/*
 * 	usart_1
	usart_2
	usart_3
	uart_4
	uart_5
	usart_6
 */
#define UART_INSTANCE 						usart_2
#define COUNT_OF_DATA_BYTES_NUMBER			2
#define MAX_NUMBER_OF_GCODE_BYTES			4096
#define GCODERECEIVER_MODULES_NUM 			1
#define GCODERECEIVER_SELECTED_MODULE_IDX	0
#define GCODERECEIVER_GPIO_CLK				RCC_AHB1_PERI_CLOCK_GPIOA


typedef struct{
	Pincfg_t tx_pin_cfg;
	Pincfg_t rx_pin_cfg;
	usart_Id_e Uart_Channel;
}GcodeReceiver_cfg_t;

extern GcodeReceiver_cfg_t GcodeReceiver_Uart_Module[GCODERECEIVER_MODULES_NUM];

#endif /* GCODERECEIVER_CFG_H_ */
