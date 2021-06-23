/*
 * stm32f407_Registers.h
 *
 *  Created on: Feb 2, 2021
 *      Author: micro
 */

#ifndef STM32F407_REGISTERS_H_
#define STM32F407_REGISTERS_H_



// Registers Of Rcc Peripheral***********************************************************
typedef struct {
	uint32_t    CR  		;
	uint32_t    PLLCFGR     ;
	uint32_t    CFGR  		;
	uint32_t    CIR  		;
	uint32_t    AHB1RSTR    ;
	uint32_t    AHB2RSTR    ;
	uint32_t    AHB3RSTR    ;
	uint32_t    Reserved0  	;
	uint32_t    APB1RSTR    ;
	uint32_t    APB2RSTR    ;
	uint32_t    Reserved1  	;
	uint32_t    Reserved2  	;
	uint32_t    AHB1ENR     ;
	uint32_t    AHB2ENR     ;
	uint32_t    AHB3ENR     ;
	uint32_t    Reserved3  	;
	uint32_t    APB1ENR     ;
	uint32_t    APB2ENR     ;
	uint32_t    Reserved4  	;
	uint32_t    Reserved5  	;
	uint32_t    AHB1LPENR   ;
	uint32_t    AHB2LPENR   ;
	uint32_t    AHB3LPENR   ;
	uint32_t    Reserved6  	;
	uint32_t    APB1LPENR   ;
	uint32_t    APB2LPENR   ;
	uint32_t    Reserved7  	;
	uint32_t    Reserved8  	;
	uint32_t    BDCR  		;
	uint32_t    CSR  		;
	uint32_t    Reserved9  	;
	uint32_t    Reserved10  ;
	uint32_t    SSCGR  	    ;
	uint32_t    PLLI2SC     ;
}Rcc_t;


// Registers of GPIOx Peripherals****************************************************

typedef struct {
	uint32_t	MODER    ;
	uint32_t	OTYPER   ;
	uint32_t	OSPEEDR  ;
	uint32_t	PUPDR    ;
	uint32_t	IDR      ;
	uint32_t	ODR	     ;
	uint32_t	BSRR     ;
	uint32_t	LCKR     ;
	uint32_t 	AFR[2]	 ;
}Gpio_t;


#endif /* STM32F407_REGISTERS_H_ */
