/*
 * GPIO.c
 *
 *  Created on: Feb 6, 2021
 *      Author: abdoo
 */
#include <stdint.h>
#include "../../lib/Bit_Mask.h"
#include "../../lib/Bit_Math.h"
#include "../../lib/STM32_F407_Registers.h"
#include "../../lib/Error_codes.h"
#include "GPIO.h"

#define NULL 		(void *)0
#define GPIO_LCK_MASK					    (uint32_t) 0x0000FFFF
#define IS_GPIO_LCK_PINS(pins)				(pins <= GPIO_LCK_MASK )

/* we could have done that but this would consume memory (.data section ),so the macros way is better.
 *
uint32_t*const gpio_handler[8]={
		(gpio_t*)GPIOA_BASE_ADDRESS,
		(gpio_t*)GPIOB_BASE_ADDRESS,
		(gpio_t*)GPIOC_BASE_ADDRESS,
		(gpio_t*)GPIOD_BASE_ADDRESS,
		(gpio_t*)GPIOE_BASE_ADDRESS,
		(gpio_t*)GPIOF_BASE_ADDRESS,
		(gpio_t*)GPIOG_BASE_ADDRESS,
		(gpio_t*)GPIOH_BASE_ADDRESS
};
 */

typedef struct {
	uint32_t GPIO_MODER        ;
	uint32_t GPIO_OTYPER       ;
	uint32_t GPIO_OSPEEDR      ;
	uint32_t GPIO_PUPDR	    	;
	uint32_t GPIO_IDR	        ;
	uint32_t GPIO_ODR	        ;
	uint32_t GPIO_BSSR	        ;
	uint32_t GPIO_LCKR	        ;
	uint32_t GPIO_AFRL	        ;
	uint32_t GPIO_AFRH	        ;
}gpio_t;

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
uint32_t GPIO_InitPin(gpio_pinConfig_t* pinConfig){
	if(pinConfig == NULL){
		return RT_PARAM;
	}
	if(
			(
					pinConfig->mode != GPIO_MODE_INPUT 			  &&
					pinConfig->mode != GPIO_MODE_OUTPUT			  &&
					pinConfig->mode != GPIO_MODE_AF				  &&
					pinConfig->mode != GPIO_MODE_ANALOGE      )
					||
					(pinConfig->pinNum >15)
					||
					(
					pinConfig->pupd  != GPIO_NO_PULL	  &&
					pinConfig->pupd  != GPIO_PULL_UP	  &&
					pinConfig->pupd  != GPIO_PULL_DOWN   )
					||
					(
					pinConfig->port  != GPIO_PORTA       &&
					pinConfig->port  != GPIO_PORTB       &&
					pinConfig->port  != GPIO_PORTC       &&
					pinConfig->port  != GPIO_PORTD       &&
					pinConfig->port  != GPIO_PORTE       &&
					pinConfig->port  != GPIO_PORTF       &&
					pinConfig->port  != GPIO_PORTG       &&
					pinConfig->port  != GPIO_PORTH	      )
	){
		return RT_PARAM;
	}
	gpio_t *port  =(gpio_t*) pinConfig->port;
	/*Check if the pin is locked or not it is locked return error
	 *
	 * Turky said it is not our business here to check if the pin is locked or not  */
//	if ((pinConfig -> port -> GPIO_LCKR & BIT_MASK_16) && (pinConfig -> port -> GPIO_LCKR & (BIT_MASK_0 << pinConfig->pinNum))){
//		return RT_ERROR;
//	}
	pinConfig->pupd &= 0x0FFFFFFF;

	uint32_t modePinsPos  = (pinConfig -> pinNum << 1);
	uint32_t clearPinsPos = ( (BIT_MASK_0 | BIT_MASK_1) << modePinsPos );
	/*Set the mode */
	/*Reset the pins you are going to set */
	port->GPIO_MODER &= ~ clearPinsPos;
	/*set the wanted mode register value with pinConfig->mode  after multiplying the pin number by 2*/
	port->GPIO_MODER |= ( pinConfig->mode << modePinsPos);

	/*Set the PUPD*/
	port->GPIO_PUPDR &=~   clearPinsPos;
	port->GPIO_PUPDR |=   (pinConfig->pupd	<< modePinsPos);

	if ((pinConfig->mode  == GPIO_MODE_OUTPUT) 			  	    &&
		(
		(pinConfig->otype != GPIO_OTYPE_PUSH_PULL  	  	    &&
		pinConfig->otype != GPIO_OTYPE_OPEN_DRAIN)
		||
		(
		pinConfig->ospeed != GPIO_OSPEED_LOW				&&
		pinConfig->ospeed != GPIO_OSPEED_MED				&&
		pinConfig->ospeed != GPIO_OSPEED_HIGH				&&
		pinConfig->ospeed != GPIO_OSPEED_VERY_HIGH )
		)
		){
		return RT_PARAM;
	}
	else {
		pinConfig -> otype &= 0x0FFFFFFF;
		pinConfig ->ospeed &= 0x0FFFFFFF;
		/*Set the Otype */
		port->GPIO_OTYPER &= ~ (BIT_MASK_0) << pinConfig->pinNum;
		port->GPIO_OTYPER |= pinConfig->otype << pinConfig->pinNum;

		/*Set the Ospeed */
		port->GPIO_OSPEEDR&=~  clearPinsPos;
		port->GPIO_OSPEEDR|=  (pinConfig->ospeed << modePinsPos);
	}


	/*now i am trying to set the AF register value but i have to make sure that the mode is AF
	 * and the AF value is less than 15 */
	if ( (pinConfig->mode == GPIO_MODE_AF)  ){
		if((pinConfig->AF & 0x0000000F)>15){
			return RT_PARAM;
		}
		else {
			modePinsPos  = (modePinsPos << 1) % 32 ;
			clearPinsPos = ( (BIT_MASK_3 | BIT_MASK_2 | BIT_MASK_1 | BIT_MASK_0  ) << modePinsPos );

			if(pinConfig->pinNum < 8){
				/*Set the AFL */
				port->GPIO_AFRL   &=~  clearPinsPos ;
				port->GPIO_AFRL   |=  (pinConfig->AF << (modePinsPos) );
			}
			else {
				/*Set the AFH */
				port->GPIO_AFRH   &=~  clearPinsPos;
				port->GPIO_AFRH   |=  (pinConfig->AF << modePinsPos);
			}

		}
	}


	return RT_SUCCESS;
}

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
uint32_t GPIO_WritePin(void* port,uint32_t pinNumber,uint32_t status){
	if(port == NULL || pinNumber > 15 || (status != GPIO_STATUS_HIGH && status != GPIO_STATUS_LOW )){
		return RT_PARAM;
	}
	/*you have to reset the BR and set the BS to output high and vice versa in output low */
	if(status == GPIO_STATUS_HIGH){
		((gpio_t*)port)->GPIO_BSSR &=~ (BIT_MASK_0 << (pinNumber+16));
		((gpio_t*)port)->GPIO_BSSR |=  (BIT_MASK_0 << pinNumber);
	}
	else {
		((gpio_t*)port)->GPIO_BSSR &=~  (BIT_MASK_0 << pinNumber);
		((gpio_t*)port)->GPIO_BSSR |=   (BIT_MASK_0 << (pinNumber+16));
	}

	/*we could have read the IDR here to make sure that the value is correctly set */
	return RT_SUCCESS;
}

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
uint32_t GPIO_ReadPin(void* port, uint32_t pinNumber,uint32_t* pinValue){
	if(port == NULL || pinNumber > 15 ){
		return RT_PARAM;
	}
	*pinValue = (((volatile gpio_t*)port)->GPIO_IDR >> pinNumber) & BIT_MASK_0 ;
	*pinValue = (((volatile gpio_t*)port)->GPIO_IDR >> pinNumber) & BIT_MASK_0 ;

	return RT_SUCCESS;
}

// what should this function do ???!!
//uint32_t GPIO_SelectAF(gpio_t* port,uint32_t pinNumber,uint32_t AF){
//	if(port == NULL || pinNumber > 15
//		||(
//		  AF != GPIO_AF0_SYSTEM				&&
//		  AF != GPIO_AF1_TIM1_TIM2          &&
//	      AF != GPIO_AF2_TIM3_5             &&
//	      AF != GPIO_AF3_TIM8_11            &&
//	      AF != GPIO_AF4_I2C1_3             &&
//	      AF != GPIO_AF5_SPI1_SPI2          &&
//	      AF != GPIO_AF6_SPI3               &&
//	      AF != GPIO_AF7_USART1_3           &&
//	      AF != GPIO_AF8_USART4_6           &&
//	      AF != GPIO_AF9_CAN1_CAN2_TIM12_14 &&
//	      AF != GPIO_AF10_OTG_FS__OTG_HS    &&
//	      AF != GPIO_AF11_ETH               &&
//	      AF != GPIO_AF12_FSMC_SDIO__OTG_HS1&&
//	      AF != GPIO_AF13_DCMI              &&
//	      AF != GPIO_AF14                   &&
//	      AF != GPIO_AF15_EVENTOUT 			)
//	){
//		return RT_PARAM;
//	}
//
//
//}

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
uint32_t GPIO_Lock(void* port,uint32_t lockPins){
	if(port == NULL || !IS_GPIO_LCK_PINS(lockPins)){
		return RT_PARAM;
	}
	volatile uint32_t lock_reg=0;
							/*the lock pin */
	lock_reg = lockPins | BIT_MASK_16;
	((gpio_t*)port)->GPIO_LCKR = lock_reg;

	lock_reg &= BIT_MASK_CLEAR_16;
	((gpio_t*)port)->GPIO_LCKR = lock_reg;

	lock_reg |= BIT_MASK_16;
	((gpio_t*)port)->GPIO_LCKR = lock_reg;

	lock_reg = ((gpio_t*)port)->GPIO_LCKR;

	if (GET_BIT(((gpio_t*)port)->GPIO_LCKR,16)){
    	return RT_SUCCESS;
    }

    return RT_ERROR;
}


