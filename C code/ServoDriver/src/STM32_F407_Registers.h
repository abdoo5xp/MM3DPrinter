/*
 * STM32_F407_Registers.h
 *
 *  Created on: Jan 29, 2021
 *      Author: abdoo
 */

#ifndef STM32_F407_REGISTERS_H_
#define STM32_F407_REGISTERS_H_


#define RCC_BASE_ADDRESS  0x40023800

typedef   struct{
	uint32_t	CR    		    ;
	uint32_t	PLLCFGR 		;
	uint32_t	CFGR   			;
	uint32_t	CIR    			;
	uint32_t	AHB1RSTR		;
	uint32_t	AHB2RSTR	    ;
	uint32_t	AHB3RSTR		;
	uint32_t	Reserved1		;
	uint32_t	APB1RSTR		;
	uint32_t	APB2RSTR		;
	uint32_t	Reserved2		;
	uint32_t	Reserved3		;
	uint32_t	AHB1ENR			;
	uint32_t	AHB2ENR			;
	uint32_t	AHB3ENR			;
	uint32_t	Reserved4		;
	uint32_t	APB1ENR			;
	uint32_t	APB2ENR			;
	uint32_t	Reserved5		;
	uint32_t	Reserved6		;
	uint32_t	AHB1LPENR		;
	uint32_t	AHB2LPENR		;
	uint32_t	AHB3LPENR		;
	uint32_t	Reserved7		;
	uint32_t	APB1LPENR		;
	uint32_t	APB2LPENR		;
	uint32_t	Reserved8		;
	uint32_t	Reserved9		;
	uint32_t	BDCR			;
	uint32_t	CSR				;
	uint32_t	Reserved10		;
	uint32_t	Reserved11		;
	uint32_t	SSCGR			;
	uint32_t	PLLI2SCFGR		;
}RCC_Reg_t;


typedef struct {
	uint32_t GPIO_MODER   ;
	uint32_t GPIO_OTYPER  ;
	uint32_t GPIO_OSPEEDR ;
	uint32_t GPIO_PUPDR	  ;
	uint32_t GPIO_IDR	  ;
	uint32_t GPIO_ODR	  ;
	uint32_t GPIO_BSSR	  ;
	uint32_t GPIO_LCKR	  ;
	uint32_t GPIO_AFRL	  ;
	uint32_t GPIO_AFRH	  ;
}gpio_t;



#endif /* STM32_F407_REGISTERS_H_ */
