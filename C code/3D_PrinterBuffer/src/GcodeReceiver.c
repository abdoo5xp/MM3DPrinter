/*
 * GcodeReceiver.c
 *
 *  Created on: Jun 21, 2021
 *      Author: abdoo
 */


#include <stdint.h>
#include "diag/Trace.h"
#include "../../lib/Bits.h"
#include "../../lib/Bit_Math.h"
#include "../../lib/Error_codes.h"
#include "../../lib/src/RT_Debug.h"
#include "GPIO_int.h"
#include "Rcc_int.h"
#include "NVIC.h"
#include "Uart.h"
#include "GcodeReceiver.h"
#include "GcodeReceiver_cfg.h"
#include "Service.h"

#define NUMBER_OF_BYTES_RECEIVED		0
#define DATA_RECEIVED 	 				1
//3456
static uint16_t GcodeBytesCount;
static uint8_t CountOfDataBytes[COUNT_OF_DATA_BYTES_NUMBER];
static uint8_t GcodeData[MAX_NUMBER_OF_GCODE_BYTES];
pfun dataReceivedCBF;

//
//uint32_t atoi(uint8_t* Copy_pu8NumArr){
//	uint8_t Loc_u8NumLoopIdx=0;
//	uint8_t  Loc_u8Digit=0;
//	uint32_t Loc_u32ResultNum=0;
//
//	while (Copy_pu8NumArr[Loc_u8NumLoopIdx] != '\0')
//	{
//		Loc_u8Digit = Copy_pu8NumArr[Loc_u8NumLoopIdx] - '0';
//		Loc_u32ResultNum += Loc_u8Digit;
//		Loc_u32ResultNum *=10;
//		Loc_u8NumLoopIdx++;
//	}
//	return Loc_u32ResultNum /=10;
//}

static void ReceivedCbf(void)
{
	static uint8_t IsNumberOflines =NUMBER_OF_BYTES_RECEIVED;

	switch(IsNumberOflines)
	{
	case NUMBER_OF_BYTES_RECEIVED:
		/*Start Receiving of the Data with the number of bytes */
		GcodeBytesCount = (uint16_t) Service_u32Concat(CountOfDataBytes, 2);
		if(GcodeBytesCount <= MAX_NUMBER_OF_GCODE_BYTES)
		{
			Uart_RecvBuff(UART_INSTANCE, GcodeData, GcodeBytesCount);
//			trace_printf(" Num of Bytes Received = %d  \n", GcodeBytesCount);
		}
		else
		{
			trace_printf(" The number of the bytes of this Gcode file exceeds the maximum buffer limit \n ");
		}
		IsNumberOflines = DATA_RECEIVED;
		break;
	case DATA_RECEIVED :
		/*Start Parsing */
		if(dataReceivedCBF)
		{
			trace_printf("Gcode Data received successfully \n");
			dataReceivedCBF();
		}
		IsNumberOflines = NUMBER_OF_BYTES_RECEIVED;
		break;
	}

}

/**************************************************************************************************************
 * Public Function: GcodeReceiver_vidInit()
 * Description: This function is used to
 * Input Parameters:
 * 					 -pfun dataReceivedCallback: the call back function to be called when the receiving is done
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
Status_e GcodeReceiver_vidInit(pfun dataReceivedCallback)
{
	irqn_t Uart_IRQchannel;

	/*Set the pointer to function */
	dataReceivedCBF = dataReceivedCallback;

	/*Set the last byte with null character for the atoi function */
//	CountOfDataBytes[COUNT_OF_DATA_BYTES_NUMBER] = '\0';


	/*Enbale rcc peripherals for gpio*/
	Rcc_AHB1_PeriClockStatus(GCODERECEIVER_GPIO_CLK, RCC_PERI_CLOCK_ENABLE);

	/*config rx pin , tx pin and uart channel*/
	Gpio_Init(&GcodeReceiver_Uart_Module[GCODERECEIVER_SELECTED_MODULE_IDX].tx_pin_cfg);
	Gpio_Init(&GcodeReceiver_Uart_Module[GCODERECEIVER_SELECTED_MODULE_IDX].rx_pin_cfg);

	/*Uart channel clock enable and NVIC selection */
	switch(GcodeReceiver_Uart_Module[GCODERECEIVER_SELECTED_MODULE_IDX].Uart_Channel)
	{
	case usart_1:
		Rcc_APB2_PeriClockStatus(GCODERECEIVER_GPIO_CLK, RCC_PERI_CLOCK_ENABLE);
		Rcc_APB2_PeriClockStatus(RCC_APB2_PERI_CLOCK_USART1, RCC_PERI_CLOCK_ENABLE);
		Uart_IRQchannel = _USART1_IRQn;
		break;
	case usart_2:
		Rcc_APB1_PeriClockStatus(RCC_APB1_PERI_CLOCK_USART2, RCC_PERI_CLOCK_ENABLE);
		Uart_IRQchannel = _USART2_IRQn;
		break;
	case usart_3:
		Rcc_APB1_PeriClockStatus(RCC_APB1_PERI_CLOCK_USART3, RCC_PERI_CLOCK_ENABLE);
		Uart_IRQchannel = _USART3_IRQn;
		break;
	case usart_6:
		Rcc_APB2_PeriClockStatus(RCC_APB2_PERI_CLOCK_USART6, RCC_PERI_CLOCK_ENABLE);
		Uart_IRQchannel = _USART6_IRQn;
		break;
	case uart_4:
		Rcc_APB1_PeriClockStatus(RCC_APB1_PERI_CLOCK_USART4, RCC_PERI_CLOCK_ENABLE);
		Uart_IRQchannel = _UART4_IRQn;
		break;
	case uart_5:
		Rcc_APB1_PeriClockStatus(RCC_APB1_PERI_CLOCK_USART5, RCC_PERI_CLOCK_ENABLE);
		Uart_IRQchannel = _UART5_IRQn;
		break;

	default:
		return _ERROR;
	}

	/*Initialize the Uart channel */
	Usart_Init(GcodeReceiver_Uart_Module[GCODERECEIVER_SELECTED_MODULE_IDX].Uart_Channel);
	/*Set the Call back function to your states */
	Uart_SetRecvCbf(GcodeReceiver_Uart_Module[GCODERECEIVER_SELECTED_MODULE_IDX].Uart_Channel, ReceivedCbf);
	/*Enable the uart interrupt */
	NVIC_ClearPending(Uart_IRQchannel);
	NVIC_EnableIntr(Uart_IRQchannel);
	/*Enable receiving of the first two bytes (Number of bytes of the Gcode )*/
	Uart_RecvBuff(GcodeReceiver_Uart_Module[GCODERECEIVER_SELECTED_MODULE_IDX].Uart_Channel, CountOfDataBytes, COUNT_OF_DATA_BYTES_NUMBER);

	return _SUCCESS;
}


/**************************************************************************************************************
 * Public Function:GcodeReceiver_GetGcodeData
 * Description: This function is used to return a pointer to the Gcode data and the Gcode number of bytes
 * Input Parameters:
 * 					 -uint16_t *GcodeNumberOfBytes: this variable is used to get the number of elements of the Gcode data array
 *
 *
 * Return:           -uint8_t* : a pointer to the Gcode Data Array
 *
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
uint8_t* GcodeReceiver_GetGcodeData(uint16_t *GcodeNumberOfBytes)
{
	*GcodeNumberOfBytes = GcodeBytesCount;
	return GcodeData;
}
