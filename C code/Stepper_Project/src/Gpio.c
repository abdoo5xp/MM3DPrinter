/*
 * Gpio.c
 *
 *  Created on: Feb 5, 2021
 *      Author: micro
 */


#include <stdint.h>
#include <stddef.h>
#include "diag/Trace.h"
#include "../../../lib/src/Bits.h"
#include "../../../lib/src/Bit_Math.h"
#include "../../../lib/src/RT_Debug.h"
#include "../../../lib/src/stm32f407_Registers.h"
#include "Gpio_int.h"


// Clear Mask for MODE Register**************************************************
#define 	GPIO_MODE_CLR	 				(uint32_t)(BIT_0 | BIT_1)

//	Clear Mask for OTYPE Register************************************************
#define 	GPIO_OTYPE_CLR					((uint32_t)BIT_0)

// Clear Mask for OSPEDD Register************************************************
#define 	GPIO_OSPEED_CLR	 				(uint32_t)(BIT_0 | BIT_1)

// Clear Mask for PUPD Register***************************************************
#define		GPIO_PUPD_CLR					(uint32_t)(BIT_0 | BIT_1)

// Clear Mask for AF Registers***************************************************
#define		GPIO_AF_CLR						(uint32_t)(BIT_0 | BIT_1 | BIT_2 | BIT_3)


// BSRR SET Mask***********************************************************************
#define     GPIO_BSRR_SET	                          BIT_0

// BSRR RESET Mask***********************************************************************
#define     GPIO_BSRR_RESET                           BIT_16

// IDR Read Mask*************************************************************************
#define     GPIO_IDR_READ                             BIT_0

// LOCK Mask*************************************************************************
#define     GPIO_LCKR_LCKK                            BIT_16

// READ Mask for MODE Register*******************************************************
#define 	GPIO_MODE_READ			  				 (uint32_t)(BIT_0 | BIT_1)

// GPIO_PIN Mask ********************************************************************
#define 	GPIO_PIN_MASK							 (uint32_t)0x0000FFFF



/* Public Function:  Gpio_Init														      				*
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

 **********************************************************************************************************/
uint8_t Gpio_Init(const Pincfg_t* Pincfg){

	if (Pincfg != NULL){

		volatile Gpio_t* Port   	= (Pincfg -> Gpio_Port)  ;
		uint32_t Pin    			= Pincfg -> Gpio_PinNum  ;
		uint32_t Mode   			= Pincfg -> Gpio_Mode 	 ;
		uint32_t OType  			= Pincfg -> Gpio_OType 	 ;
		uint32_t OType_Addr 		= (uint32_t)Port + 0x04  ;
		uint32_t OSpeed 			= Pincfg -> Gpio_OSpeed  ;
		uint32_t PUPD   			= Pincfg -> Gpio_PUPD 	 ;
		uint32_t AF    	    		= Pincfg -> Gpio_AF      ;
		uint32_t Local_Reg			= 0 ;

		if ( Pin <= GPIO_PIN15 && (Port == GPIOA || Port == GPIOB
						|| Port == GPIOC || Port == GPIOD
						|| Port == GPIOE || Port == GPIOH) ){


			if ( Mode == GPIO_MODE_OUTPUT || Mode == GPIO_MODE_INPUT ||  Mode == GPIO_MODE_ANALOG ||  Mode == GPIO_MODE_AF  ){
				Local_Reg		= Port -> MODER ;
				Local_Reg	 	&= ~(GPIO_MODE_CLR << (Pin << 1))  ;
				Local_Reg	 	|= (Mode << (Pin << 1)) ;
				Port -> MODER   =  Local_Reg ;
			}
			else{
				return RT_PARAM ;
			}

			if (Mode == GPIO_MODE_OUTPUT || Mode == GPIO_MODE_AF){
				if( OType == GPIO_OTYPE_PUSH_PULL || OType == GPIO_OTYPE_OPEN_DRAIN){

					BIT_BAND(OType_Addr,Pin) = OType;
				}
				else{
					return RT_PARAM ;
				}

				if ( OSpeed == GPIO_OSPEED_LOW_SPEED
						|| OSpeed == GPIO_OSPEED_MEDIUM_SPEED
						||  OSpeed == GPIO_OSPEED_HIGH_SPEED
						||  OSpeed == GPIO_OSPEED_VERY_HIGH_SPEED ){

					Local_Reg		= Port -> OSPEEDR ;
					Local_Reg		&= ~(GPIO_OSPEED_CLR << (Pin << 1))  ;
					Local_Reg 		|= (OSpeed << (Pin << 1)) ;
					Port -> OSPEEDR = Local_Reg ;
				}
				else{
					return RT_PARAM ;
				}
			}

			switch (Mode){
			case  GPIO_MODE_ANALOG:
				Local_Reg		=  Port -> PUPDR ;
				Local_Reg  	 	&= ~(GPIO_PUPD_CLR << (Pin << 1))  ;
				Local_Reg   	|= ( GPIO_PUPD_FLOATING << (Pin << 1)) ;
				Port -> PUPDR	=  Local_Reg ;
				break;
			default :
				if ( PUPD == GPIO_PUPD_FLOATING
						||  PUPD == GPIO_PUPD_PULL_UP
						||  PUPD == GPIO_PUPD_PULL_DOWN ){

					Local_Reg		=  Port -> PUPDR ;
					Local_Reg  	 	&= ~(GPIO_PUPD_CLR << (Pin << 1))  ;
					Local_Reg   	|= ( PUPD << (Pin << 1)) ;
					Port -> PUPDR	=  Local_Reg ;
				}
				else{
					return RT_PARAM ;
				}
				break;
			}

			if (Mode == GPIO_MODE_AF){
				if (AF <= GPIO_AF15){

					Local_Reg			  = Port -> AFR[Pin >> 3] ;
					Local_Reg 			  &= ~(GPIO_AF_CLR << ((Pin << 2) % 32)) ;
					Local_Reg			  |= (AF << ((Pin << 2) % 32)) ;
					Port -> AFR[Pin >> 3] = Local_Reg ;
				}
				else{
					return RT_PARAM ;
				}
			}
		}
		else
			return RT_PARAM ;
	}
	else
		return RT_PARAM ;

	return RT_SUCCESS ;
}

/* Public Function:  Gpio_WritePin														      *
 * Description: This function is used to Configure Pin Status (HIGH ,LOW)
 * Input parameters:
 *      - Gpio_Port		in range : { GPIOxx (xx : A , B , C , D , E , H)}
 *      - Gpio_PinNum	in range : { GPIO_PINXX (xx :  0 .. 15)}
 * 		- Gpio_PinStatus 	in range : { GPIO_PIN_HIGH - GPIO_PIN_LOW }
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
uint8_t Gpio_WritePin(void* Gpio_Port, uint32_t Gpio_PinNum, uint32_t Gpio_PinStatus){

	volatile Gpio_t* Port   =	 Gpio_Port  ;

	if (Gpio_PinNum <= GPIO_PIN15 && (Gpio_Port == GPIOA || Gpio_Port == GPIOB
					|| Gpio_Port == GPIOC || Gpio_Port == GPIOD
					|| Gpio_Port == GPIOE || Gpio_Port == GPIOH) ){

		switch (Gpio_PinStatus){
		case GPIO_PIN_SET:
			Port -> BSRR =  GPIO_BSRR_SET << Gpio_PinNum ;
			break;

		case GPIO_PIN_RESET:
			Port -> BSRR =  GPIO_BSRR_RESET << Gpio_PinNum  ;
			break;
		default:
			return RT_PARAM;
			break;
		}
	}
	else
		return RT_PARAM ;

	return RT_SUCCESS;
}


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
uint8_t Gpio_TogglePin(void* Gpio_Port, uint32_t Gpio_PinNum){

	volatile Gpio_t* Port   =	 Gpio_Port  ;

	if (Gpio_PinNum <= GPIO_PIN15 && (Gpio_Port == GPIOA || Gpio_Port == GPIOB
					|| Gpio_Port == GPIOC || Gpio_Port == GPIOD
					|| Gpio_Port == GPIOE || Gpio_Port == GPIOH) ){

		Port->ODR ^= 1 << Gpio_PinNum;
	}
	else
		return RT_PARAM ;

	return RT_SUCCESS;
}


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
uint8_t Gpio_ReadPin(void* Gpio_Port , uint32_t Gpio_PinNum , uint32_t* Gpio_PinStatus){

	volatile Gpio_t * Port   =	 Gpio_Port ;
	uint32_t Current_IDR = 0 ;

	if ( Gpio_PinNum <= GPIO_PIN15 && (Gpio_Port == GPIOA || Gpio_Port == GPIOB
					|| Gpio_Port == GPIOC || Gpio_Port == GPIOD
					|| Gpio_Port == GPIOE || Gpio_Port == GPIOH) && (Gpio_PinStatus != NULL) ){

		Current_IDR = (Port -> IDR) >> Gpio_PinNum ;
		// IDR take time to be read
		*Gpio_PinStatus = (uint32_t)(Current_IDR & (uint32_t)GPIO_IDR_READ)  ;
	}
	else{
		return RT_PARAM ;
	}

	return RT_SUCCESS;
}


/* Public Function:  Gpio_LockPin														      *
 * Description: This function is used to Lock Gpio Pins at a specific configuration.
 * Input parameters:
 *      - Gpio_Port		in range : { GPIOxx (xx : A , B , C , D , E , H)}
 *      - Gpio_PinsNum	in range : { GPIO_PINxx_LCK (xx :  0 .. 15)}
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
uint8_t Gpio_LockPin(void* Gpio_Port , uint32_t Gpio_PinsNum){

	volatile Gpio_t *Port   =	Gpio_Port  ;
	uint32_t Lock_Read =  0 ;
	uint32_t Lock  = 0 ;

	if ( Gpio_PinsNum > (uint32_t) 0   &&  Gpio_PinsNum <= GPIO_PIN_MASK
			&& (Gpio_Port == GPIOA || Gpio_Port == GPIOB
					|| Gpio_Port == GPIOC || Gpio_Port == GPIOD
					|| Gpio_Port == GPIOE || Gpio_Port == GPIOH)) {

		Lock_Read = Port -> LCKR ;
		if ( !(Lock_Read & GPIO_LCKR_LCKK) ){

			Lock |= GPIO_LCKR_LCKK ;
			Lock = Gpio_PinsNum ;
			Port -> LCKR  = Lock ; 			//‘1’ + LCKR[15:0]	//0x00010003
			Port -> LCKR  = Gpio_PinsNum; 	//‘0’ + LCKR[15:0]	//0x00000003
			Port -> LCKR  = Lock ;			//‘1’ + LCKR[15:0]	//0x00010003
			Lock_Read = Port -> LCKR ;
		}
		else{
			return RT_ERROR;
		}
	}
	else{
		return RT_PARAM;
	}

	Lock_Read = Port -> LCKR ;
	if (!(Lock_Read & GPIO_LCKR_LCKK)){
		return RT_ERROR;
	}

	return RT_SUCCESS;
}


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
uint8_t Gpio_Select_AF(void *Gpio_Port , uint32_t Gpio_PinNum , uint32_t Gpio_AF){

	volatile Gpio_t *Port  = Gpio_Port  ;
	uint32_t Local_Reg	   = 0 ;
	uint32_t Mode 		   = Port -> MODER & (GPIO_MODE_READ << (Gpio_PinNum << 1));
	uint32_t Mode_AF 	   = GPIO_MODE_AF << (Gpio_PinNum << 1) ;

	if (Gpio_PinNum <= GPIO_PIN15 && (Gpio_Port == GPIOA || Gpio_Port == GPIOB
					|| Gpio_Port == GPIOC || Gpio_Port == GPIOD
					|| Gpio_Port == GPIOE || Gpio_Port == GPIOH) && Gpio_AF <= GPIO_AF15 ){

		if (Mode == Mode_AF){

			Local_Reg				      = Port -> AFR[Gpio_PinNum >> 3] ;
			Local_Reg 			  	  	  &= ~(GPIO_AF_CLR << (Gpio_PinNum << 2)) ;
			Local_Reg			  		  |= (Gpio_AF << (Gpio_PinNum << 2)) ;
			Port -> AFR[Gpio_PinNum >> 3] = Local_Reg ;
		}
		else{
			return RT_ERROR ;
		}
	}
	return RT_SUCCESS;
}
