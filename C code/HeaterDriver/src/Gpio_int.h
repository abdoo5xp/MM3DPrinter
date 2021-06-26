/*
 * Gpio_int.h
 *
 *  Created on: Feb 5, 2021
 *      Author: micro
 */

#ifndef GPIO_INT_H_
#define GPIO_INT_H_


// BaseAdrress of GPIOA Peripheral*****************************************************
#define 	GPIOA								   ((void *)0x40020000)

// BaseAdrress of GPIOB Peripheral*****************************************************
#define 	GPIOB								   ((void *)0x40020400)

// BaseAdrress of GPIOC Peripheral*****************************************************
#define 	GPIOC						           ((void *)0x40020800)

// BaseAdrress of GPIOD Peripheral*****************************************************
#define 	GPIOD						           ((void *)0x40020C00)

// BaseAdrress of GPIOE Peripheral*****************************************************
#define 	GPIOE					 	           ((void *)0x40021000)

// BaseAdrress of GPIOH Peripheral*****************************************************
#define 	GPIOH						           ((void *)0x40021C00)


// GPIO Pin_Num Configurations*********************************************************
#define 	GPIO_PIN0                               0
#define 	GPIO_PIN1                               1
#define 	GPIO_PIN2                               2
#define 	GPIO_PIN3                               3
#define 	GPIO_PIN4                               4
#define 	GPIO_PIN5                               5
#define 	GPIO_PIN6                               6
#define 	GPIO_PIN7                               7
#define 	GPIO_PIN8                               8
#define 	GPIO_PIN9                               9
#define 	GPIO_PIN10                              10
#define 	GPIO_PIN11                              11
#define 	GPIO_PIN12                              12
#define 	GPIO_PIN13                              13
#define 	GPIO_PIN14                              14
#define 	GPIO_PIN15                              15


//	Input Mode Mask *******************************************************************
#define 	GPIO_MODE_INPUT						    BIT_CLR

//	Output Mode Mask ******************************************************************
#define 	GPIO_MODE_OUTPUT					    BIT_0

//	AF Mode Mask **********************************************************************
#define 	GPIO_MODE_AF						    BIT_1

//	Analog Mode Mask ******************************************************************
#define 	GPIO_MODE_ANALOG					    (BIT_0 | BIT_1)


//	Push-Pull OType Mask *************************************************************
#define 	GPIO_OTYPE_PUSH_PULL					BIT_CLR

//	Open Drain OType Mask ************************************************************
#define 	GPIO_OTYPE_OPEN_DRAIN				    BIT_0


// Low_speed OSPEED Mask***************************************************************
#define		GPIO_OSPEED_LOW_SPEED			 	    BIT_CLR

// Medium_speed OSPEED Mask************************************************************
#define		GPIO_OSPEED_MEDIUM_SPEED				BIT_0

// High_speed OSPEED Mask**************************************************************
#define		GPIO_OSPEED_HIGH_SPEED				    BIT_1

// Veryhigh_speed OSPEED Mask**********************************************************
#define		GPIO_OSPEED_VERY_HIGH_SPEED			    (BIT_0 | BIT_1)


// Floating PUPD Mask******************************************************************
#define		GPIO_PUPD_FLOATING					    BIT_CLR

// PullUp PUPD Mask********************************************************************
#define		GPIO_PUPD_PULL_UP					    BIT_0

// PullDown PUPD Mask******************************************************************
#define		GPIO_PUPD_PULL_DOWN					    BIT_1


// AF Configurations Mask*****************************************************************
#define  GPIO_AF0_SYSTEM				  BIT_CLR
#define  GPIO_AF1_TIM1_TIM2               BIT_0
#define  GPIO_AF2_TIM3_5                  BIT_1
#define  GPIO_AF3_TIM8_11                 (BIT_0 | BIT_1)
#define  GPIO_AF4_I2C1_3                  BIT_2
#define  GPIO_AF5_SPI1_SPI2               (BIT_0 | BIT_2)
#define  GPIO_AF6_SPI3                    (BIT_1 | BIT_2)
#define  GPIO_AF7_USART1_3                (BIT_0 | BIT_1 | BIT_2)
#define  GPIO_AF8_USART4_6                BIT_3
#define  GPIO_AF9_CAN1_CAN2_TIM12_14      (BIT_0 | BIT_3)
#define  GPIO_AF10_OTG_FS__OTG_HS         (BIT_1 | BIT_3)
#define  GPIO_AF11_ETH                    (BIT_0 | BIT_1 | BIT_3)
#define  GPIO_AF12_FSMC_SDIO__OTG_HS1     (BIT_2 | BIT_3)
#define  GPIO_AF13_DCMI                   (BIT_0 | BIT_2 | BIT_3)
#define  GPIO_AF14                        (BIT_1 | BIT_2 | BIT_3)
#define  GPIO_AF15_EVENTOUT               (BIT_0 | BIT_1 | BIT_2 | BIT_3)



// LCKR Configuration Mask****************************************************************
#define     GPIO_PIN0_LCK                           BIT_0
#define     GPIO_PIN1_LCK                           BIT_1
#define     GPIO_PIN2_LCK                           BIT_2
#define     GPIO_PIN3_LCK                           BIT_3
#define     GPIO_PIN4_LCK                           BIT_4
#define     GPIO_PIN5_LCK                           BIT_5
#define     GPIO_PIN6_LCK                           BIT_6
#define     GPIO_PIN7_LCK                           BIT_7
#define     GPIO_PIN8_LCK                           BIT_8
#define     GPIO_PIN9_LCK                           BIT_9
#define     GPIO_PIN10_LCK                          BIT_10
#define     GPIO_PIN11_LCK                          BIT_11
#define     GPIO_PIN12_LCK                          BIT_12
#define     GPIO_PIN13_LCK                          BIT_13
#define     GPIO_PIN14_LCK                          BIT_14
#define     GPIO_PIN15_LCK                          BIT_15


// PIN HIGH/LOW Mask****************************************************************
#define		GPIO_PIN_SET							(BIT_0)
#define		GPIO_PIN_RESET							(BIT_CLR)




// Configuration Parameters for each Pin **************************************************
typedef struct {
	uint32_t Gpio_Mode 		;
	uint32_t Gpio_OType 	;
	uint32_t Gpio_OSpeed 	;
	uint32_t Gpio_PUPD 		;
	uint32_t Gpio_AF 		;
	void * Gpio_Port 		;
	uint32_t Gpio_PinNum 	;
}Pincfg_t;


/* Public Function:  Gpio_Init														      *
 * Description: This function is used to Configure Gpio Pins
 * Input parameters:
 *  	- Address of object of (Pincfg_t)
 *
 * Options:
 * 		- Gpio_Mode 	in range : { GPIO_MODE_xx  ( xx : - OUTPUT  - INPUT - ANALOG - AF )}
 * 		- Gpio_OType   	in range : { - GPIO_OTYPE_PUSH_PULL	 - GPIO_OTYPE_OPEN_DRAIN }
 * 		- Gpio_OSpeed  	in range : { GPIO_OSPEED_xx  ( xx : - LOW_SPEED     - MEDIUM_SPEED
 * 														    - HIGH_SPEE	   - VERY_HIGH_SPEED)}
 * 		- Gpio_PUPD 	in range : { GPIO_PUPD_xx ( xx : - FLOATING	- PULL_UP  - PULL_DOWN )}
 * 		- Gpio_AF 	  	in range : { GPIO_AFxx  (xx :  0 .. 15)}
 *      - Gpio_Port		in range : { GPIOxx (xx : A , B , C , D , E , H)}
 *      - Gpio_PinNum	in range : { GPIO_PINXX (xx :  0 .. 15)}
 *
 * Return:
 * 		- Status (uint8_t)
 *         RT_SUCCESS
 *         RT_PARAM
 *         RT_ERROR
 *         RT_TIME_OUT
 *
 * Input/Output Parameter:
 * 		- Not Applicable

 ***************************************************************************************************/
uint8_t Gpio_Init(const Pincfg_t *Pincfg);


/* Public Function:  Gpio_WritePin														      *
 * Description: This function is used to Set Gpio Pins High or Low
 * Input parameters:
 *      - Gpio_Port		in range : { GPIOxx (xx : A , B , C , D , E , H)}
 *      - Gpio_PinNum	in range : { GPIO_PINXX (xx :  0 .. 15)}
 * 		- Gpio_Status 	in range : { GPIO_PIN_SET - GPIO_PIN_RESET }
 *
 * Return:
 * 		- Status (uint8_t)
 *         RT_SUCCESS
 *         RT_PARAM
 *         RT_ERROR
 *         RT_TIME_OUT
 *
 * Input/Output Parameter:
 * 		- Not Applicable

 ***************************************************************************************************/
uint8_t Gpio_WritePin(void* Gpio_Port , uint32_t Gpio_PinNum, uint32_t Gpio_PinStatus);


/* Public Function:  Gpio_TogglePin														      *
 * Description: This function is used to Toggle Pin Status (HIGH <-> LOW)
 * Input parameters:
 *      - Gpio_Port		in range : { GPIOxx (xx : A , B , C , D , E , H)}
 *      - Gpio_PinNum	in range : { GPIO_PINXX (xx :  0 .. 15)}
 *
 * Return:
 * 		- Status (uint8_t)
 *         RT_SUCCESS
 *         RT_PARAM
 *         RT_ERROR
 *         RT_TIME_OUT
 *
 * Input/Output Parameter:
 * 		- Not Applicable

 ***************************************************************************************************/
uint8_t Gpio_TogglePin(void* Gpio_Port, uint32_t Gpio_PinNum);


/* Public Function:  Gpio_ReadPin														      *
 * Description: This function is used to Read Gpio Pin Status ( High or Low)
 * Input parameters:
 *      - Gpio_Port		in range : { GPIOxx (xx : A , B , C , D , E , H)}
 *      - Gpio_PinNum	in range : { GPIO_PINXX (xx :  0 .. 15)}
 *
 * Return:
 * 		- Status (uint8_t)
 *         RT_SUCCESS
 *         RT_PARAM
 *         RT_ERROR
 *         RT_TIME_OUT
 *
 * Input/Output Parameter:
 * 		- Gpio_Status 	in range : { 0x00 - 0x01 }

 ***************************************************************************************************/
uint8_t Gpio_ReadPin(void* Gpio_Port , uint32_t Gpio_PinNum, uint32_t* Gpio_PinStatus);


/* Public Function:  Gpio_LockPin														      *
 * Description: This function is used to Lock Gpio Pins at a specific configuration.
 * Input parameters:
 *      - Gpio_Port		in range : { GPIOxx (xx : A , B , C , D , E , H)}
 *      - Gpio_PinNum	in range : { GPIO_PINxx_LCK (xx :  0 .. 15)}
 *
 * Return:
 * 		- Status (uint8_t)
 *         RT_SUCCESS
 *         RT_PARAM
 *         RT_ERROR
 *         RT_TIME_OUT
 *
 * Input/Output Parameter:
 *

 ***************************************************************************************************/
uint8_t Gpio_LockPin(void* Gpio_Port , uint32_t Gpio_PinsNum);


/* Public Function:  Gpio_Select_AF														      *
 * Description: This function is used to set the Alternative function for Gpio Pins.
 * Input parameters:
 *      - Gpio_Port		in range : { GPIOxx (xx : A , B , C , D , E , H)}
 *      - Gpio_PinNum	in range : { GPIO_PINxx_LCK (xx :  0 .. 15)}
 *      - Gpio_AF		in range : { GPIO_AFxx	(xx :  0 .. 15)}
 *
 * Return:
 * 		- Status (uint8_t)
 *         RT_SUCCESS
 *         RT_PARAM
 *         RT_ERROR
 *         RT_TIME_OUT
 *
 * Input/Output Parameter:
 *

 ***************************************************************************************************/
uint8_t Gpio_Select_AF(void* Gpio_Port , uint32_t Gpio_PinsNum , uint32_t Gpio_AF);





#endif /* GPIO_INT_H_ */
