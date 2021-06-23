/*
 * Uart.c
 *
 *  Created on: Mar 14, 2021
 *      Author: abdoo
 */
#include <stdint.h>
#include <diag/Trace.h>
#include "../../Lib/Error_codes.h"
#include "../../Lib/Bit_Mask.h"
#include "../../Lib/Bit_Math.h"
#include "SwTimer.h"
#include "Uart.h"

#include "Uart_cfg.h"


#define 	NULL 						    (void*)0

#define 	USART_TXE_MASK				    BIT_MASK_7
#define 	USART_TXC_MASK				    BIT_MASK_6

#define 	USART_TXCIE_MASK			    BIT_MASK_6

#define 	USART_RXNEIE_MASK			    BIT_MASK_5
#define 	USART_RXNEIE_CLEAR_MASK 	    BIT_MASK_CLEAR_5

#define 	USART_RXNE_CLEAR_MASK 		    BIT_MASK_CLEAR_5
#define 	USART_RXNE_MASK 		        BIT_MASK_5

#define 	USART_LIN_SBK_MASK				BIT_MASK_0
#define 	USART_LIN_SBK_CLEAR_MASK		BIT_MASK_CLEAR_0

#define 	USART_LIN_LBD_MASK				BIT_MASK_8
#define 	USART_LIN_LBD_CLEAR_MASK		BIT_MASK_CLEAR_8

#define 	USART_LIN_LBDIE_MASK			BIT_MASK_6
#define 	USART_LIN_LBDIE_CLEAR_MASK		BIT_MASK_CLEAR_6

#define 	USART_LIN_LINEN_MASK			BIT_MASK_14
#define 	USART_LIN_LINEN_CLEAR_MASK		BIT_MASK_CLEAR_14

typedef struct {
	uint32_t SR;
	/*The peripheral registers are word or half word accessible
	 * so you can't put uint8_t DR */
	uint32_t DR;
	uint32_t BRR;
	uint32_t CR1;
	uint32_t CR2;
	uint32_t CR3;
	uint32_t GTPR;
}usart_t;


typedef struct {
	 uint8_t   *data_buf;
	 uint16_t   buffer_counter;
	 uint16_t   buffer_size ;
	 usart_Id_e usart_channel ;

	 uint8_t    Tx_busy;
	 uint8_t	Rx_busy;
	 uartCbf	uart_RecvCbf;
	 uartCbf 	uart_SendCbf;
}usart_buff_t;


/************************************************ Static Functions Declaration ************************************************************/
/**************************************************************************************************************
 * static Function: Uart_SendData
 * Description: This function is used to write a byte of data to the Transmit data register of a specific USART channel.
 * Input Parameters:
 * 					 - usart_Id_e usartId : the usart channel in range {usart_1,usart_2,usart_3,uart_4 ,uart_5 ,usart_6,  }
 *
 *					 - uint8_t data
 *
 * Return:           -Not Applicable (void)
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
static void Uart_SendData(usart_Id_e usartId,uint8_t data);

/**************************************************************************************************************
 * static Function:Uart_RecvData
 * Description: This function is used to read data from a specific uart channel data register.
 * Input Parameters:
 * 					-usart_Id_e usartId:the usart channel in range {usart_1,usart_2,usart_3,uart_4 ,uart_5 ,usart_6,  }
 *
 *
 * Return:           -Not Applicable (void)
 *
 * Input/Output Parameters:
 * 					-uint8_t *data : the container that contains the read value.
 * ***************************************************************************************************************/
static void Uart_RecvData(usart_Id_e usartId,uint8_t *data);

/************************************************ Static Functions Implementation ************************************************************/
static void Uart_SendData(usart_Id_e usartId,uint8_t data)
{
	/* Set the data in the register to be sent on the line ,
	 * we have to cast it here because the register is word or half word accessible only */
	// trace_printf("data = %d",data);
	((volatile usart_t *)usart_instances[usartId].usartAddress)->DR = (uint32_t )data;
}

static void Uart_RecvData(usart_Id_e usartId,uint8_t *data)
{
	/* Set the data in the register to be sent on the line ,
	 * we have to cast it here because the register is word or half word accessible only */
	 *data = (uint8_t)((volatile usart_t *)usart_instances[usartId]. usartAddress)->DR ;
	// trace_printf("data = %d",*data);
}

/************************************************ API Functions Implementation ************************************************************/
/*this function should take a struct containing the configuration of the uart ,
 *   there a lot of pins connected to the same uart channel,
 *   so you have to choose which pin for e.g PA9 -> TX uart0 ,PA10 RX -> uart0
 *   uart pclk1 -> on APB1 max-> 42 MHz
 *   uart pclk2 -> on APB2 max-> 84 MHz
 *
 *   baudRate = Fpclk / (8 * (2- OVER8) * USARTDIV )  --> in standard mode
 *   baudRate = Fpclk / (16 * USARTDIV )  --> in LIN and smart card modes (because the OVER8 bit is forced to zero by HW)
 *
 *   All the USART interrupts are handled by one handler, so you have to check inside of it what caused the interrupt.
 *
 * */
/**************************************************************************************************************
 * Public Function: Usart_Init
 * Description: This function is used to
 * Input Parameters:
 * 					 -usart_Id_e usartId: the usart channel
 * 					 					in range { usart_1,usart_2,
 * 					 							   usart_3,uart_4 ,
 * 					 							   uart_5 ,usart_6,  }
 *
 *
 * Return:           -uint8_t : in range {  RT_PARAM,
 *											RT_ERROR,
 *											RT_SUCCESS }
 *
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
uint8_t Usart_Init(usart_Id_e  usart_Id)
{
	uint32_t usart_CR1 =0;
	uint32_t usart_CR2 =0;
	uint32_t usart_CR3 =0;

	if(usart_Id > _usart_Id_Length_){
		return RT_PARAM;
	}

	/*USART Enable */
	SET_BIT(usart_CR1,13);
	usart_CR1|= usart_instances[usart_Id].frameSize       << 12;
//	((volatile usart_t *)usart_instances[usart_Id].usartAddress)-> CR1 = usart_CR1;
//	((volatile usart_t *)usart_instances[usart_Id].usartAddress)-> CR1 |= usart_instances[usart_Id].frameSize       << 12;

	/*USART_CR2 configuration */
//	((volatile usart_t *)usart_instances[usart_Id].usartAddress)-> CR2  |= usart_instances[usart_Id].stopBit	       << 12;
	usart_CR1 |= usart_instances[usart_Id].stopBit	       << 12;

	/*Assigning the baud Rate */
	((volatile usart_t *) usart_instances[usart_Id].usartAddress )->BRR = usart_instances[usart_Id].usartBaudRate;

	/*USART_CR1 Register configuration */
//	((volatile usart_t *)usart_instances[usart_Id].usartAddress)-> CR1  |= usart_instances[usart_Id].txEnable        << 3;
//	((volatile usart_t *)usart_instances[usart_Id].usartAddress)-> CR1  |= usart_instances[usart_Id].rxEnable        << 2;
	usart_CR1 |=  usart_instances[usart_Id].txEnable        << 3;
	usart_CR1 |= usart_instances[usart_Id].rxEnable         << 2;

	/* Interrupts control */
	usart_CR1 |= usart_instances[usart_Id].interrupts.pe   << 8 ;
	usart_CR1 |= usart_instances[usart_Id].parityEnable    << 10;
	usart_CR1 |= usart_instances[usart_Id].paritySelection << 9 ;

//	usart_CR1 |= usart_instances[usart_Id].interrupts.rxne <<  5;
//	usart_CR1 |= usart_instances[usart_Id].interrupts.txe  <<  7;
#if UART_MODE   == UART_MODE_EVENT_BASED
//	usart_CR1 |= USART_TXCIE_MASK;
#endif

	/*USART_CR3 configuration */
	  usart_CR3 |= usart_instances[usart_Id].txDmaEnable	 <<  7;
	  usart_CR3 |= usart_instances[usart_Id].rxDmaEnable     <<  6;
 	  usart_CR3 |= usart_instances[usart_Id].interrupts.eie  <<  0;

#if UART_BREAK_ONLY_MODE  == UART_BREAK_ONLY_MODE_ON
 	  /*Enable the LIN mode */
 	  usart_CR2 |= USART_LIN_LINEN_MASK;
#endif
 	 if(usart_instances[usart_Id].linEnable == LIN_ENABLE)
 	 {
 		 usart_CR2 |= USART_LIN_LINEN_MASK;
 		 /*TODO: Enable the LBDIE here */
 	 }

	((volatile usart_t *)usart_instances[usart_Id].usartAddress)-> CR1 = usart_CR1;
	((volatile usart_t *)usart_instances[usart_Id].usartAddress)-> CR2 = usart_CR2;
	((volatile usart_t *)usart_instances[usart_Id].usartAddress)-> CR3 = usart_CR3;

	((volatile usart_t *)usart_instances[usart_Id].usartAddress)-> SR &= ~ USART_TXC_MASK ;

	return RT_SUCCESS;
}



/*================================================= UART_MODE_TIME_BASED =========================================================*/

#if UART_MODE   == UART_MODE_TIME_BASED

static usart_buff_t usartBuff[_usart_Id_Length_];
static usart_buff_t usartRxBuff[_usart_Id_Length_];
/************************************************ Static Functions Declaration************************************************************/
/**************************************************************************************************************
 * Public Function:
 * Description: This function is used to check if the usart transmit register is ready to receive data to be sent.
 * Input Parameters:
 * 					 -usart_Id_e usartId: the usart channel in range {usart_1,usart_2,usart_3,uart_4 ,uart_5 ,usart_6,  }
 *
 *
 * Return:           -uint8_t : in range {  1 -> ready to send , 0 -> not ready to send  }
 *
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
static uint8_t  Uart_ISReadyToSend(usart_Id_e usartId);


static uint32_t Uart_ISThereDataToRecv(usart_Id_e usartId);

static void Uart_send(void);

static void Uart_recv(void);

/************************************************ Static Functions Implementation ************************************************************/

static uint8_t Uart_ISReadyToSend(usart_Id_e usartId){
 	//return the flag of ready to transmit
 	return (uint8_t)(((volatile usart_t *)usart_instances[usartId].usartAddress)->SR & USART_TXE_MASK) >> 7 ;
 }

static uint32_t Uart_ISThereDataToRecv(usart_Id_e usartId)
{
 	//return the flag of ready to transmit
 	return ((((volatile usart_t *)usart_instances[usartId].usartAddress)->SR & USART_RXNE_MASK)) ;
 }


static void Uart_send(void);


static void Uart_send(void)
{
	uint8_t UnregisterFlag= 0;
	for (uint8_t usart_Id =0;usart_Id < _usart_Id_Length_;usart_Id++)
	{

		if (usartBuff[usart_Id].buffer_size == 0 ){
			continue;
		}
		/*If the Uart data register is ready  */
		if(Uart_ISReadyToSend(usartBuff[usart_Id].usart_channel))
		{
			/*Check if all data is sent,
			 * clear the flags
			 * TODO: Note this may not send the last packet */
			if(usartBuff[usart_Id].buffer_counter == usartBuff[usart_Id].buffer_size )
			{
				usartBuff[usart_Id].buffer_counter = 0;
				usartBuff[usart_Id].buffer_size = 0;
				usartBuff[usart_Id].data_buf = NULL;
			}
			else
			{
				Uart_SendData(usartBuff[usart_Id].usart_channel,usartBuff[usart_Id].data_buf[usartBuff[usart_Id].buffer_counter]);
				usartBuff[usart_Id].buffer_counter++;
				UnregisterFlag = 1;
			}
		}
	}
	if(!UnregisterFlag)
	{
		  SwTimer_UnRegisterCBF(Uart_send);
	}
}

static void Uart_recv(void){
	uint8_t UnregisterFlag= 0;
	uint32_t flag;
	for (uint8_t usart_Id =0;usart_Id < _usart_Id_Length_;usart_Id++)
	{

		if (usartRxBuff[usart_Id].buffer_size == 0 ){
			continue;
		}

		/*If the Uart data register contains data   */
		if(Uart_ISThereDataToRecv(usartRxBuff[usart_Id].usart_channel))
		{
			/*receive the data */
			Uart_RecvData(usartRxBuff[usart_Id].usart_channel, &usartRxBuff[usart_Id].data_buf[usartRxBuff[usart_Id].buffer_counter]);
			usartRxBuff[usart_Id].buffer_counter++;
		}
		/* Check if all data is received ,
		 * clear the flags
		 * TODO: Note this may not receive the last packet */
		if(usartRxBuff[usart_Id].buffer_counter == usartRxBuff[usart_Id].buffer_size )
		{
			usartRxBuff[usart_Id].buffer_counter = 0;
			usartRxBuff[usart_Id].buffer_size = 0;
			usartRxBuff[usart_Id].data_buf = NULL;
			UnregisterFlag ++;
			/*TODO: call the call back function of data is receiveed successfully */
		}
	}
	/*if all the usart channels are done receiving */
	if(UnregisterFlag == _usart_Id_Length_ )
	{
		SwTimer_UnRegisterCBF(Uart_recv);
	}
}

/************************************************ APIs Functions Implementation ************************************************************/

uint32_t Uart_SendBuff(usart_Id_e usart_Id,uint8_t *buf,uint16_t size){
	uint8_t return_status = RT_SUCCESS;

	/* we can register the function the first time it gets in and unregister it when its done
	 * */

	/* check if there is no already registered buffer,
	 * then register this buffer in the SW timer  */
	if(usartBuff[usart_Id].buffer_size  == 0)
	{
		usartBuff[usart_Id].buffer_size = size ;
		usartBuff[usart_Id].data_buf    = buf;
		usartBuff[usart_Id].usart_channel = usart_Id;

		/*make the periodic time 1 ms to be sure that the frame is sent successfully */
		if( SwTimer_RegisterCBF(1,SWTimer_TimerMode_Periodic,Uart_send) == SWTimer_Nok)
		{
			return_status  = RT_ERROR;
		}
	}

	return return_status;
}


uint32_t Uart_RecvBuff(usart_Id_e usart_Id,uint8_t *buf,uint16_t size){
	uint8_t return_status = RT_SUCCESS;

	/* check if there is no already registered buffer,
	 * then register this buffer in the SW timer  */
	if(usartRxBuff[usart_Id].buffer_size  == 0)
	{
		usartRxBuff[usart_Id].buffer_size   = size ;
		usartRxBuff[usart_Id].data_buf      = buf;
		usartRxBuff[usart_Id].usart_channel = usart_Id;

		/*make the periodic time 1 ms to be sure that the frame is sent successfully */
		if( SwTimer_RegisterCBF(1,SWTimer_TimerMode_Periodic,Uart_recv) == SWTimer_Nok)
		{
			return_status  = RT_ERROR;
		}
	}

	return return_status;
}
#endif


/*================================================= UART_MODE_EVENT_BASED =========================================================*/


#if UART_MODE == UART_MODE_EVENT_BASED

	/*TODO: make these variables arrays for multi channel working in parallel */
static usart_buff_t Tx_buf[_usart_Id_Length_];
static usart_buff_t Rx_buf[_usart_Id_Length_];
static uartCbf LBD_Cbfs[_usart_Id_Length_];

/************************************************ Static Functions Declaration************************************************************/

/**************************************************************************************************************
 * static Function: Uart_MyHandler
 * Description: This function is used to handle the uart events and call the Call back functions of the user (Notify APP FNs)
 * Input Parameters:
 * 					 -usart_Id_e  usart_Id:the usart channel in range {usart_1,usart_2,usart_3,uart_4 ,uart_5 ,usart_6,  }
 *
 *
 * Return:           -Not Applicable (void)
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
static inline void Uart_MyHandler(usart_Id_e  usart_Id);

/********************************************************** APIs ************************************************************************/

/*
 * we could have copied the while buffer from the user to the driver buffer,
 *  but this would consume a huge memory
 *  uint32_t  HAL_Uart_SendBuff(uint8_t *buf,uint16_t size)
 */
uint32_t Uart_SendBuff(usart_Id_e usart_Id,uint8_t *buf,uint16_t size)
{	uint8_t return_status = RT_ERROR;

	if(!Tx_buf[usart_Id].Tx_busy)
	{
		Tx_buf[usart_Id].data_buf 	   = buf;
		Tx_buf[usart_Id].buffer_size   = size;
		Tx_buf[usart_Id].buffer_counter= 1;

#if UART_MODE   == UART_MODE_EVENT_BASED
		((usart_t*)usart_instances[usart_Id].usartAddress)->CR1 |= USART_TXCIE_MASK;
#endif

#if UART_BREAK_ONLY_MODE  == UART_BREAK_ONLY_MODE_ON
		/*We should send the break frame her by setting the SBK bit */
		((usart_t*)usart_instances[usart_Id].usartAddress)->CR1 |= USART_LIN_SBK_MASK;
#endif
		/*Send the first element in the buffer, to trigger the interrupt */
		Uart_SendData(usart_Id ,Tx_buf[usart_Id].data_buf[0]);
		Tx_buf[usart_Id].Tx_busy = 1;
		return_status = RT_SUCCESS;
	}

	return return_status;
}

void Uart_SendBreak(usart_Id_e usart_Id)
{
	if (usart_instances[usart_Id].linEnable == LIN_ENABLE )
	{
		/*We should send the break frame her by setting the SBK bit */
		((volatile usart_t*)usart_instances[usart_Id].usartAddress)->CR1 |= USART_LIN_SBK_MASK;
	}
}

void Uart_SetSendCbf(usart_Id_e usart_Id,uartCbf cbf){
	Tx_buf[usart_Id].uart_SendCbf = cbf;
}

void Uart_SetRecvCbf(usart_Id_e usart_Id,uartCbf cbf){
	Tx_buf[usart_Id].uart_RecvCbf = cbf;
}

void Uart_SetLBDCbf(usart_Id_e usart_Id,uartCbf cbf){
	if(usart_instances[usart_Id].linEnable == LIN_ENABLE)
	{
		LBD_Cbfs[usart_Id] = cbf;
	}
}

void Uart_EnableLBD_INT(usart_Id_e usart_Id){
	if(usart_instances[usart_Id].linEnable == LIN_ENABLE)
	{
		/*The LBDIE should be enabled, and its flag is cleared before enabling it  */
		((usart_t *)usart_instances[usart_Id].usartAddress)->CR2 |= USART_LIN_LBDIE_MASK;
	}
}

void Uart_DisableLBD_INT(usart_Id_e usart_Id){
	if(usart_instances[usart_Id].linEnable == LIN_ENABLE)
	{
		/*The LBDIE should be enabled, and its flag is cleared before enabling it  */
		((usart_t *)usart_instances[usart_Id].usartAddress)->CR2 &= USART_LIN_LBDIE_CLEAR_MASK;
	}
}

uint32_t Uart_RecvBuff(usart_Id_e usart_Id, uint8_t * recvBuff,uint16_t size){
	uint8_t return_status = RT_ERROR;
	if(!Rx_buf[usart_Id].Rx_busy)
	{
		Rx_buf[usart_Id].data_buf = recvBuff ;
		Rx_buf[usart_Id].buffer_counter = 0;
		Rx_buf[usart_Id].buffer_size = size;
		Rx_buf[usart_Id].Rx_busy = 1;

#if UART_BREAK_ONLY_MODE  == UART_BREAK_ONLY_MODE_ON
		/*The LBDIE should be enabled, and its flag is cleared before enabling it  */
		((usart_t *)usart_instances[usart_Id].usartAddress)->CR2 |= USART_LIN_LBDIE_MASK;

#else
		/*Clear the RXNE flag in case if it received any frames and got raised */
		((volatile usart_t *)usart_instances[usart_Id].usartAddress) -> SR  &= USART_RXNE_CLEAR_MASK ;
		/*Enable the RXNE interrupt enable Interrupt */
		((volatile usart_t *)usart_instances[usart_Id].usartAddress) -> CR1 |= USART_RXNEIE_MASK     ;
#endif
		return_status = RT_SUCCESS;
	}

	return return_status;
}


/*************************************************** Uart_Handlers ***************************************************************/
/* NOTE: Here we made this function inline ,because whenever we call a function from inside the ISR ,
 * the RXNE flag is reset (and we want to check on it ) */
//static uint32_t numberofbytesReceived;
static inline void Uart_MyHandler(usart_Id_e  usart_Id)
{

	  if(
			(((usart_t *) usart_instances[usart_Id].usartAddress)->SR & USART_RXNE_MASK) &&
			(((usart_t *) usart_instances[usart_Id].usartAddress)->CR1 & USART_RXNEIE_MASK)
		)
		{
			if(Rx_buf[usart_Id].buffer_counter < Rx_buf[usart_Id].buffer_size)
			{
				/*Send the next frame, then increase the buffer counter  */
				Uart_RecvData(usart_Id, & Rx_buf[usart_Id].data_buf[Rx_buf[usart_Id].buffer_counter++]);
//				numberofbytesReceived ++;
				if(Rx_buf[usart_Id].buffer_counter == Rx_buf[usart_Id].buffer_size)
				{
					/*Disable the RXNE Interrupt */
					( (volatile usart_t *)usart_instances[usart_Id].usartAddress) -> CR1 &= USART_RXNEIE_CLEAR_MASK;
					Rx_buf[usart_Id].Rx_busy = 0;

					/*Call the user call back function */
					if(Tx_buf[usart_Id].uart_RecvCbf)
					{
						Tx_buf[usart_Id].uart_RecvCbf();
//						trace_printf("num of bytes = %d",numberofbytesReceived);
					}
				}
			}
		}

	  if((usart_instances[usart_Id].linEnable == LIN_ENABLE) &&
	    (((usart_t*)usart_instances[usart_Id].usartAddress)->SR & USART_LIN_LBD_MASK)&&
		(((usart_t*)usart_instances[usart_Id].usartAddress)->CR2 & USART_LIN_LBDIE_MASK)
		)
	  {
			((volatile usart_t *) usart_instances[usart_Id].usartAddress)->SR &= ~USART_TXC_MASK;
		  /*Clear the lin break detected flag */
		  ((volatile usart_t *)usart_instances[usart_Id].usartAddress) -> SR &= USART_LIN_LBD_CLEAR_MASK ;
		 /*Call the user call back function */
		  if (LBD_Cbfs[usart_Id])
		  {
			  LBD_Cbfs[usart_Id]();
		  }
	  }


	if(  ( ( (volatile usart_t *)usart_instances[usart_Id].usartAddress)->CR1 & USART_TXCIE_MASK) &&
	     ( ( (volatile usart_t *)usart_instances[usart_Id].usartAddress)->SR & USART_TXC_MASK) )
	{
			((volatile usart_t *) usart_instances[usart_Id].usartAddress)->SR &= ~USART_TXC_MASK;
//			((usart_t*)usart_instances[usart_Id].usartAddress)->CR1           &=
		if(Tx_buf[usart_Id].buffer_counter < Tx_buf[usart_Id].buffer_size)
		{
			/*Send the next frame, then increase the next */
			Uart_SendData(usart_Id, Tx_buf[usart_Id].data_buf[Tx_buf[usart_Id].buffer_counter++]);
		}
		else
		{
			((volatile usart_t *)usart_instances[usart_Id].usartAddress)->CR1 &=~ USART_TXCIE_MASK;
			Tx_buf[usart_Id].Tx_busy = 0;
//			((volatile usart_t *) usart_instances[usart_Id].usartAddress)->SR &= ~USART_TXC_MASK;

			/*Call the user call back function */
			if(Tx_buf[usart_Id].uart_SendCbf)
			{
				Tx_buf[usart_Id].uart_SendCbf();
			}
		}
	}
	/*check if RXNEIE  FLaG is Enabled first */


#if UART_BREAK_ONLY_MODE == UART_BREAK_ONLY_MODE_ON
  if(
    (((usart_t*)usart_instances[usart_Id].usartAddress)->SR & USART_LIN_LBD_MASK)&&
	(((usart_t*)usart_instances[usart_Id].usartAddress)->CR2 & USART_LIN_LBDIE_MASK)
	)
    {
	  	  	  	  	  /*Clear the LIN LBD Flag, and disable its interrupt  */
		((volatile usart_t *)usart_instances[usart_Id].usartAddress) -> SR &= USART_LIN_LBD_CLEAR_MASK ;
		((volatile usart_t *)usart_instances[usart_Id].usartAddress) -> CR2&= USART_LIN_LBDIE_CLEAR_MASK;
		/*TODO:
		 * Islam says the clearance of LBDIE should be done ,
		 * before the function call back
		 * and reset your values so that you start receiving from the first */

			/*Clear the RXNE flag in case if it received any frames and got raised */
		((volatile usart_t *)usart_instances[usart_Id].usartAddress) -> SR &= USART_RXNE_CLEAR_MASK ;
			/*Enable the RXNE interrupt enable Interrupt */
		((volatile usart_t *)usart_instances[usart_Id].usartAddress) -> CR1|= USART_RXNEIE_MASK     ;

    }

#endif


}


#ifdef usart_CH_1
void USART1_IRQHandler(void){
	Uart_MyHandler(usart_1);
}
#endif

#ifdef usart_CH_2
void USART2_IRQHandler(void){

	Uart_MyHandler(usart_2);
}
#endif

#ifdef usart_CH_3

void USART3_IRQHandler(void){
	Uart_MyHandler(usart_3);
}
#endif

#ifdef uart_CH_4

void UART4_IRQHandler(void){
	Uart_MyHandler(uart_4);
}
#endif

#ifdef uart_CH_5

void UART5_IRQHandler(void){
	Uart_MyHandler(uart_5);
}
#endif

#ifdef usart_CH_6

void USART6_IRQHandler(void){
	Uart_MyHandler(usart_6);
}

#endif

#endif


