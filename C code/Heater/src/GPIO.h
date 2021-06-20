/*
 * GPIO.h
 *
 *  Created on: Feb 6, 2021
 *      Author: abdoo
 */
/*
 * Each instance of GPIO Driver has the following Registers :
 *
 * 							Configuration Regs   --> GPIOx_MODER
 * 													 GPIOx_OTYPER
 * 													 GPIOx_OSPEEDR
 * 												 	 GPIOx_PUPDR
 *
 * 							Data Regs			 --> GPIOx_IDR
 * 													 GPIOx_ODR
 *
 * 							Set/Reset Reg		 --> GPIOx_BSRR
 *
 * 							Lock Reg			 --> GPIOx_LCKR
 *
 * 							Alternative Fn. Regs --> GPIOx_AFRH
 * 													 GPIOx_AFRL
 * */

#ifndef GPIO_H_
#define GPIO_H_

/*#define GPIOA			(gpio_t *)	GPIOA_BASE_ADD
 * if we do this, we would need to put the typedef struct of type gpio_t here,
 *  but we don't want the user to see it so, we will put it in the .c file.
 *
 */

		/*mode for each pin */
#define GPIO_MODE_INPUT 				    (uint32_t)0X00000000
#define GPIO_MODE_OUTPUT				    (uint32_t)0X00000001
#define GPIO_MODE_AF					    (uint32_t)0X00000002
#define GPIO_MODE_ANALOGE				    (uint32_t)0X00000003

		/*pull up pull down option for each pin ,
		 * the MSB is one to differentiate between it and the other macros  */
#define GPIO_NO_PULL			            (uint32_t)0X10000000
#define GPIO_PULL_UP			            (uint32_t)0X10000001
#define GPIO_PULL_DOWN			            (uint32_t)0X10000002

		/*ports for user selection  */
#define GPIO_PORTA				          ((void*) 0x40020000) //(uint32_t)0X20000000
#define GPIO_PORTB                        ((void*) 0x40020400) //(uint32_t)0X20000001
#define GPIO_PORTC                        ((void*) 0x40020800) //(uint32_t)0X20000002
#define GPIO_PORTD                        ((void*) 0x40020C00) //(uint32_t)0X20000003
#define GPIO_PORTE                        ((void*) 0x40021000) //(uint32_t)0X20000004
#define GPIO_PORTF                        ((void*) 0x40021400) //(uint32_t)0X20000005
#define GPIO_PORTG                        ((void*) 0x40021800) //(uint32_t)0X20000006
#define GPIO_PORTH                        ((void*) 0x40021C00) //(uint32_t)0X20000007

		/*output types for output pins */
#define GPIO_OTYPE_PUSH_PULL		        (uint32_t)0X30000000
#define GPIO_OTYPE_OPEN_DRAIN		        (uint32_t)0X30000001

		/*output speed for output pins */
#define GPIO_OSPEED_LOW				        (uint32_t)0X40000000
#define GPIO_OSPEED_MED				        (uint32_t)0X40000001
#define GPIO_OSPEED_HIGH			        (uint32_t)0X40000002
#define GPIO_OSPEED_VERY_HIGH		        (uint32_t)0X40000003
		/*GPIO pins for each port */
#define GPIO_PIN_0						    (uint32_t)0
#define GPIO_PIN_1  					    (uint32_t)1
#define GPIO_PIN_2  					    (uint32_t)2
#define GPIO_PIN_3  					    (uint32_t)3
#define GPIO_PIN_4  					    (uint32_t)4
#define GPIO_PIN_5  					    (uint32_t)5
#define GPIO_PIN_6  					    (uint32_t)6
#define GPIO_PIN_7  					    (uint32_t)7
#define GPIO_PIN_8  					    (uint32_t)8
#define GPIO_PIN_9  					    (uint32_t)9
#define GPIO_PIN_10 					    (uint32_t)10
#define GPIO_PIN_11 					    (uint32_t)11
#define GPIO_PIN_12 					    (uint32_t)12
#define GPIO_PIN_13 					    (uint32_t)13
#define GPIO_PIN_14 					    (uint32_t)14
#define GPIO_PIN_15 					    (uint32_t)15

		/*GPIO LOCK pins for each port */
#define GPIO_LOCK_PIN_0						    (uint32_t)BIT_MASK_0
#define GPIO_LOCK_PIN_1  					    (uint32_t)BIT_MASK_1
#define GPIO_LOCK_PIN_2  					    (uint32_t)BIT_MASK_2
#define GPIO_LOCK_PIN_3  					    (uint32_t)BIT_MASK_3
#define GPIO_LOCK_PIN_4  					    (uint32_t)BIT_MASK_4
#define GPIO_LOCK_PIN_5  					    (uint32_t)BIT_MASK_5
#define GPIO_LOCK_PIN_6  					    (uint32_t)BIT_MASK_6
#define GPIO_LOCK_PIN_7  					    (uint32_t)BIT_MASK_7
#define GPIO_LOCK_PIN_8  					    (uint32_t)BIT_MASK_8
#define GPIO_LOCK_PIN_9  					    (uint32_t)BIT_MASK_9
#define GPIO_LOCK_PIN_10 					    (uint32_t)BIT_MASK_10
#define GPIO_LOCK_PIN_11 					    (uint32_t)BIT_MASK_11
#define GPIO_LOCK_PIN_12 					    (uint32_t)BIT_MASK_12
#define GPIO_LOCK_PIN_13 					    (uint32_t)BIT_MASK_13
#define GPIO_LOCK_PIN_14 					    (uint32_t)BIT_MASK_14
#define GPIO_LOCK_PIN_15 					    (uint32_t)BIT_MASK_15

		/*GPIO pin status */
#define GPIO_STATUS_HIGH				         BIT_MASK_CLEAR_0
#define GPIO_STATUS_LOW					         BIT_MASK_CLEAR_1

		/*GPIO Alternative function macros */
#define GPIO_AF0_SYSTEM						     (uint32_t)0X50000000
#define GPIO_AF1_TIM1_TIM2                       (uint32_t)0X50000001
#define GPIO_AF2_TIM3_5                          (uint32_t)0X50000002
#define GPIO_AF3_TIM8_11                         (uint32_t)0X50000003
#define GPIO_AF4_I2C1_3                          (uint32_t)0X50000004
#define GPIO_AF5_SPI1_SPI2                       (uint32_t)0X50000005
#define GPIO_AF6_SPI3                            (uint32_t)0X50000006
#define GPIO_AF7_USART1_3                        (uint32_t)0X50000007
#define GPIO_AF8_USART4_6                        (uint32_t)0X50000008
#define GPIO_AF9_CAN1_CAN2_TIM12_14              (uint32_t)0X50000009
#define GPIO_AF10_OTG_FS__OTG_HS                 (uint32_t)0X5000000A
#define GPIO_AF11_ETH                            (uint32_t)0X5000000B
#define GPIO_AF12_FSMC_SDIO__OTG_HS1             (uint32_t)0X5000000C
#define GPIO_AF13_DCMI                           (uint32_t)0X5000000D
#define GPIO_AF14                                (uint32_t)0X5000000E
#define GPIO_AF15_EVENTOUT                       (uint32_t)0X5000000F

typedef struct {
	void* port;
	//gpio_t* port;
	uint32_t pinNum;
	uint32_t mode;
	uint32_t otype;
	uint32_t ospeed;
	uint32_t pupd;
	uint32_t AF;

}gpio_pinConfig_t;


/* **************************************************************************************************************
 * Public Function: GPIO_InitPin
 * Description: This function is used to turn the RCC clocks ON/OFF
 * Input Parameters:
 * 					-gpio_pinConfig_t* pinConfig ->
 *				        void* port     : in range { GPIO_PORTA ,
													GPIO_PORTB ,
													GPIO_PORTC ,
													GPIO_PORTD ,
													GPIO_PORTE ,
													GPIO_PORTF ,
													GPIO_PORTG ,
													GPIO_PORTH  }

 *				        uint32_t pinNum: in range { GPIO_PIN_0	,
													GPIO_PIN_1  ,
													GPIO_PIN_2  ,
													GPIO_PIN_3  ,
													GPIO_PIN_4  ,
													GPIO_PIN_5  ,
													GPIO_PIN_6  ,
													GPIO_PIN_7  ,
													GPIO_PIN_8  ,
													GPIO_PIN_9  ,
													GPIO_PIN_10 ,
													GPIO_PIN_11 ,
													GPIO_PIN_12 ,
													GPIO_PIN_13 ,
													GPIO_PIN_14 ,
													GPIO_PIN_15 }

 *				        uint32_t mode  : in range { GPIO_MODE_INPUT  ,
													GPIO_MODE_OUTPUT ,
													GPIO_MODE_AF	 ,
													GPIO_MODE_ANALOGE }

 *				        uint32_t otype : in range { GPIO_OTYPE_PUSH_PULL ,
 *				        							GPIO_OTYPE_OPEN_DRAIN}

 *				        uint32_t ospeed: in range { GPIO_OSPEED_LOW		 ,
													GPIO_OSPEED_MED		 ,
													GPIO_OSPEED_HIGH	 ,
													GPIO_OSPEED_VERY_HIGH}

 *				        uint32_t pupd  : in range { GPIO_NO_PULL
													GPIO_PULL_UP
													GPIO_PULL_DOWN }

 *				        uint32_t AF;   : in range { GPIO_AF0_SYSTEM
													GPIO_AF1_TIM1_TIM2
													GPIO_AF2_TIM3_5
													GPIO_AF3_TIM8_11
													GPIO_AF4_I2C1_3
													GPIO_AF5_SPI1_SPI2
													GPIO_AF6_SPI3
													GPIO_AF7_USART1_3
													GPIO_AF8_USART4_6
													GPIO_AF9_CAN1_CAN2_TIM12_14
													GPIO_AF10_OTG_FS__OTG_HS
													GPIO_AF11_ETH
													GPIO_AF12_FSMC_SDIO__OTG_HS1
													GPIO_AF13_DCMI
													GPIO_AF14
													GPIO_AF15_EVENTOUT}
 *
 * Return:           -uint8_t : in range {  RT_PARAM,
 *											RT_ERROR,
 *											RT_SUCCESS }
 *
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
uint32_t GPIO_InitPin	(gpio_pinConfig_t* pinConfig);

/* **************************************************************************************************************
 * Public Function: GPIO_WritePin
 * Description: This function is used to turn the RCC clocks ON/OFF
 * Input Parameters:
 *
 *				       - void* port     : in range { GPIO_PORTA ,
 *													GPIO_PORTB ,
 *													GPIO_PORTC ,
 *													GPIO_PORTD ,
 *													GPIO_PORTE ,
 *													GPIO_PORTF ,
 *													GPIO_PORTG ,
 *													GPIO_PORTH  }
 *
 *				       - uint32_t pinNum: in range { GPIO_PIN_0	,
 *													GPIO_PIN_1  ,
 *													GPIO_PIN_2  ,
 *													GPIO_PIN_3  ,
 *													GPIO_PIN_4  ,
 *													GPIO_PIN_5  ,
 *													GPIO_PIN_6  ,
 *													GPIO_PIN_7  ,
 *													GPIO_PIN_8  ,
 *													GPIO_PIN_9  ,
 *													GPIO_PIN_10 ,
 *													GPIO_PIN_11 ,
 *													GPIO_PIN_12 ,
 *													GPIO_PIN_13 ,
 *													GPIO_PIN_14 ,
 *													GPIO_PIN_15 }
 *
 *					   - uint32_t status: in range {GPIO_STATUS_HIGH,
 *													GPIO_STATUS_LOW}
 *
 * Return:         	   -uint8_t       : in range {  RT_PARAM,
 *	 											    RT_ERROR,
 *	 											    RT_SUCCESS }
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
uint32_t GPIO_WritePin	(void* port,uint32_t pinNumber,uint32_t status);

/* **************************************************************************************************************
 * Public Function: GPIO_ReadPin
 * Description: This function is used to turn the RCC clocks ON/OFF
 * Input Parameters:
 *
 *				       - void* port     : in range { GPIO_PORTA ,
 *													GPIO_PORTB ,
 *													GPIO_PORTC ,
 *													GPIO_PORTD ,
 *													GPIO_PORTE ,
 *													GPIO_PORTF ,
 *													GPIO_PORTG ,
 *													GPIO_PORTH  }
 *
 *				       - uint32_t pinNum: in range { GPIO_PIN_0	,
 *													GPIO_PIN_1  ,
 *													GPIO_PIN_2  ,
 *													GPIO_PIN_3  ,
 *													GPIO_PIN_4  ,
 *													GPIO_PIN_5  ,
 *													GPIO_PIN_6  ,
 *													GPIO_PIN_7  ,
 *													GPIO_PIN_8  ,
 *													GPIO_PIN_9  ,
 *													GPIO_PIN_10 ,
 *													GPIO_PIN_11 ,
 *													GPIO_PIN_12 ,
 *													GPIO_PIN_13 ,
 *													GPIO_PIN_14 ,
 *													GPIO_PIN_15 }
 *
 *					   - uint32_t pinValue: in range {0,
 *													  1}
 *
 * Return:         	   -uint8_t       : in range {  RT_PARAM,
 *	 											    RT_ERROR,
 *	 											    RT_SUCCESS }
 *
 * Input/Output Parameters:
 * 					-uint32_t* pinValue :in Range{
 * 												}
 * ***************************************************************************************************************/
uint32_t GPIO_ReadPin   (void* port,uint32_t pinNumber,uint32_t* pinValue);

/* **************************************************************************************************************
 * Public Function: GPIO_Lock
 * Description: This function is used to turn the RCC clocks ON/OFF
 * Input Parameters:
 *
 *				       - void* port     : in range { GPIO_PORTA ,
 *													GPIO_PORTB ,
 *													GPIO_PORTC ,
 *													GPIO_PORTD ,
 *													GPIO_PORTE ,
 *													GPIO_PORTF ,
 *													GPIO_PORTG ,
 *													GPIO_PORTH  }
 *
 *				       - uint32_t pinNum: in range { GPIO_PIN_0	,
 *													GPIO_PIN_1  ,
 *													GPIO_PIN_2  ,
 *													GPIO_PIN_3  ,
 *													GPIO_PIN_4  ,
 *													GPIO_PIN_5  ,
 *													GPIO_PIN_6  ,
 *													GPIO_PIN_7  ,
 *													GPIO_PIN_8  ,
 *													GPIO_PIN_9  ,
 *													GPIO_PIN_10 ,
 *													GPIO_PIN_11 ,
 *													GPIO_PIN_12 ,
 *													GPIO_PIN_13 ,
 *													GPIO_PIN_14 ,
 *													GPIO_PIN_15 }
 *
 * Return:         	   -uint8_t       : in range {  RT_PARAM,
 *	 											    RT_ERROR,
 *	 											    RT_SUCCESS }
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
uint32_t GPIO_Lock		(void* port,uint32_t pinNumber);


#endif /* GPIO_H_ */
