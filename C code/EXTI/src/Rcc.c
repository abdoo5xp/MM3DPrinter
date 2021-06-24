/*
 * Rcc.c
 *
 *  Created on: Jan 29, 2021
 *      Author: abdoo
 */

#include <stdlib.h>
#include <stdint.h>
#include "../../lib/Bit_Mask.h"
#include "../../lib/Bit_Math.h"
#include "../../lib/STM32_F407_Registers.h"
#include "../../lib/Error_codes.h"
#include "Rcc.h"

#define SW_CLEAR			(BIT_MASK_CLEAR_0 & BIT_MASK_CLEAR_1)
#define SWS_MASK			(BIT_MASK_2  | BIT_MASK_3			)
#define PLL_RDY_MASK		(BIT_MASK_25 | BIT_MASK_27 			)
#define PLL_SHIFT_M_POS		0
#define PLL_SHIFT_N_POS		6
#define PLL_SHIFT_P_POS		16
#define PLL_SHIFT_Q_POS		24
#define PLL_SHIFT_SRC_POS	22

#define PLL_MASK_M			(BIT_MASK_0 | BIT_MASK_1 | BIT_MASK_2 | BIT_MASK_3 | BIT_MASK_4 | BIT_MASK_5)
#define PLL_MASK_N			(BIT_MASK_6 | BIT_MASK_7 | BIT_MASK_8 | BIT_MASK_9 | BIT_MASK_10 \
							|BIT_MASK_11 | BIT_MASK_12 | BIT_MASK_13 | BIT_MASK_14)
#define PLL_MASK_P			(BIT_MASK_17 | BIT_MASK_16)
#define PLL_MASK_Q			(BIT_MASK_24 | BIT_MASK_25 | BIT_MASK_26 | BIT_MASK_27)
#define PLL_MASK_SRC		(BIT_MASK_22)


#define MCO1_SRC_CLR_MASK	(BIT_MASK_CLEAR_21 | BIT_MASK_CLEAR_22)
#define MCO1_PRE_CLR_MASK	(BIT_MASK_CLEAR_24 | BIT_MASK_CLEAR_25 | BIT_MASK_CLEAR_26)
#define MCO2_SRC_CLR_MASK	(BIT_MASK_CLEAR_30 | BIT_MASK_CLEAR_31)
#define MCO2_PRE_CLR_MASK   (BIT_MASK_CLEAR_27 | BIT_MASK_CLEAR_28 | BIT_MASK_CLEAR_29)

#define RCC_IS_HSE_ON		(RCC->CR & BIT_MASK_17)
#define RCC_IS_HSI_ON		(RCC->CR & BIT_MASK_1)
#define RCC_IS_PLL_ON		(RCC->CR & BIT_MASK_25)
#define RCC_IS_LSE_ON		(RCC->BDCR & BIT_MASK_1)
#define RCC_IS_LSI_ON		(RCC->CSR & BIT_MASK_1)


#define RCC      ((volatile RCC_Reg_t *) RCC_BASE_ADDRESS)

/* **************************************************************************************************************
 * Public Function: RCC_ControlClk
 * Input: a clock control macro --> RCC_HSI_ON,RCC_HSI_OFF,
 * 									RCC_HSE_ON,RCC_HSE_OFF,
 * 									RCC_PLL_ON,RCC_PLL_OFF,
 * 									RCC_LSI_ON,RCC_LSI_OFF,
 * 									RCC_LSE_ON,RCC_LSE_OFF
 *
 * Output: the operation state --> RT_PARAM,
 * 								   RT_ERROR,
 * 								   RT_SUCCESS
 * */
uint8_t RCC_ControlClk(uint32_t RCC_Clk_Ctrl){

	uint32_t RdyPintimeOut = 2500;
	if( RCC_Clk_Ctrl == (RCC_HSI_ON) ||RCC_Clk_Ctrl == (RCC_HSE_ON) ||RCC_Clk_Ctrl == (RCC_PLL_ON) ){
		/*set the selected bit with the use option on or off */
		RCC ->CR |=  RCC_Clk_Ctrl;

		/*should loop and wait on the RDY bit here using timer */
		while( (RdyPintimeOut) && !(RCC->CR & (RCC_Clk_Ctrl << 1) ) ){
			RdyPintimeOut--;
		}
		if(!RdyPintimeOut){
			return RT_TIMEOUT;
		}

		return RT_SUCCESS;
	}
	else if( RCC_Clk_Ctrl == (RCC_HSI_OFF) ||RCC_Clk_Ctrl == (RCC_HSE_OFF) ||RCC_Clk_Ctrl == (RCC_PLL_OFF) ){
		/*clear the selected bit */
		RCC->CR &= RCC_Clk_Ctrl;

		/*should loop and wait on the RDY bit here using timer  */
		while( (RdyPintimeOut) && (RCC->CR & (~RCC_Clk_Ctrl << 1)) ){
				RdyPintimeOut--;
			}

			if(!RdyPintimeOut){
				return RT_TIMEOUT;
			}

		return RT_SUCCESS;
	}
	else if( RCC_Clk_Ctrl == (RCC_LSI_ON) ){
		/*set the selected bit with the use option on or off */
		RCC ->CSR |=  BIT_MASK_0;

		/*should loop and wait on the RDY bit here using timer */
		while( (RdyPintimeOut) && !(RCC->CSR & (BIT_MASK_0 << 1)) ){
			RdyPintimeOut--;
		}

		if(!RdyPintimeOut){
			return RT_TIMEOUT;
		}

		return RT_SUCCESS;
	}
	else if( RCC_Clk_Ctrl == (RCC_LSI_OFF) ){
		/*clear the selected bit */
		RCC ->CSR &= BIT_MASK_CLEAR_0;

		/*should loop and wait on the RDY bit here using timer */
		while( (RdyPintimeOut) && (RCC->CSR & (~BIT_MASK_CLEAR_0 << 1)) ){
			RdyPintimeOut--;
		}

		if(!RdyPintimeOut){
			return RT_TIMEOUT;
		}

		return RT_SUCCESS;
	}
	else if( RCC_Clk_Ctrl == (RCC_LSE_ON) ){
		/*set the selected bit with the use option on or off */
		RCC ->BDCR |=  BIT_MASK_0;

		/*should loop and wait on the RDY bit here using timer */
		while( (RdyPintimeOut) && !(RCC->BDCR & (BIT_MASK_0 << 1) ) ){
			RdyPintimeOut--;
		}

		if(!RdyPintimeOut){
			return RT_TIMEOUT;
		}

		return RT_SUCCESS;
	}
	else if(RCC_Clk_Ctrl == (RCC_LSE_OFF) ){
		/*clear the selected bit */
		RCC ->BDCR &= BIT_MASK_CLEAR_0;

		/*should loop and wait on the RDY bit here using timer */
		while( (RdyPintimeOut) && (RCC->BDCR & (~BIT_MASK_CLEAR_0 << 1) ) ){
			RdyPintimeOut--;
		}

		if(!RdyPintimeOut){
			return RT_TIMEOUT;
		}

		return RT_SUCCESS;
	}
	return RT_PARAM;
}

/* **************************************************************************************************************
 * Public Function: RCC_SelectSysClk
 * Description: This function is used to Select a System clock from the provided RCC clocks
 * Input Parameters:
 * 					-uint32_t RCC_Clk_Ctrl : in range { RCC_HSI,
 *                                                      RCC_HSE,
 *			                                            RCC_PLL }
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
uint8_t RCC_SelectSysClk(uint32_t RCC_Clk){
	if( 	RCC_Clk != RCC_PLL &&
			RCC_Clk != RCC_HSE &&
			RCC_Clk != RCC_HSI){
		return RT_PARAM;
	}
	RCC ->CFGR &= SW_CLEAR;
	RCC ->CFGR |= RCC_Clk;

	/*loop to make sure that SWS are set correctly */
	if((RCC ->CFGR & SWS_MASK ) != (RCC_Clk << 2) ){
		return RT_ERROR;
	}

	return RT_SUCCESS;
}

/* **************************************************************************************************************
 * Public Function: RCC_ConfigPll
 * Description: This function is used to configure the PLL clock
 * Input Parameters:
 * 					-uint32_t RCC_Clk_Ctrl : in range { RCC_pllConfig_t }
 *
 * Return:           -uint8_t : in range {  RT_PARAM,
 *											RT_ERROR,
 *											RT_SUCCESS }
 *
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
uint8_t RCC_ConfigPll(RCC_pllConfig_t * RCC_PllConfig){

	uint32_t pll_CFGR =0 ;

	/*Fixed a bug here: when using != in two conditions on the same variable
	 * use && between them not ||  */
	if(		RCC_PllConfig == NULL ||RCC_PllConfig->pll_M > 63 || RCC_PllConfig->pll_M < 2  ||
			RCC_PllConfig->pll_N > 432|| RCC_PllConfig->pll_N < 50 ||
			(RCC_PllConfig->pll_P != 2  && RCC_PllConfig->pll_P != 4  &&
					RCC_PllConfig->pll_P != 6  && RCC_PllConfig->pll_P != 8 ) ||
					RCC_PllConfig->pll_Q > 15  || RCC_PllConfig->pll_Q < 2    ||
					(RCC_PllConfig->pll_Src != RCC_PLL_SRC_HSE &&
							RCC_PllConfig->pll_Src != RCC_PLL_SRC_HSI )
	)
	{
		return RT_PARAM;
	}
	if(RCC->CR & PLL_RDY_MASK){
		return RT_ERROR;
	}
	if( RCC_PllConfig->pll_Src == RCC_PLL_SRC_HSE && (RCC_PllConfig->pll_M != (RCC_HSE_OSC/2) && RCC_PllConfig->pll_M != RCC_HSE_OSC)){
		return RT_ERROR;
	}
	else if(RCC_PllConfig->pll_Src == RCC_PLL_SRC_HSI && (RCC_PllConfig->pll_M != RCC_HSI_OSC/2 && RCC_PllConfig->pll_M != RCC_HSI_OSC)){
		return RT_ERROR;
	}


	pll_CFGR  = RCC_PllConfig -> pll_M;
	pll_CFGR |= RCC_PllConfig -> pll_N   << 6;
	pll_CFGR |= RCC_PllConfig -> pll_P   << 16;
	pll_CFGR |= RCC_PllConfig -> pll_Q   << 24;
	pll_CFGR |= RCC_PllConfig -> pll_Src << 22;
	//pll_CFGR |= (1 << 29);		//the reserved bit value
	RCC -> PLLCFGR = pll_CFGR;
	return RT_SUCCESS;
}

/* **************************************************************************************************************
 * Public Function: RCC_GetCurrentSysClkFreq
 * Description: This function is used to get the current running System clock frequency
 * Input Parameters:
 * 					-Not Applicable (void)
 *
 *
 * Return:           -uint8_t : in range {  RT_PARAM,
 *											RT_ERROR,
 *											RT_SUCCESS }
 *
 *
 * Input/Output Parameters:
 * 					- uint32_t* : CurrentSysClkFreq
 * ***************************************************************************************************************/
uint8_t RCC_GetCurrentSysClkFreq(uint32_t* CurrentSysClkFreq){
	volatile uint32_t SystemClkType;
	SystemClkType = (RCC->CFGR & SWS_MASK) >> 2;
	if(SystemClkType == RCC_HSI){
		*CurrentSysClkFreq = RCC_HSI_OSC;
	}
	else if(SystemClkType == RCC_HSE){
		*CurrentSysClkFreq = RCC_HSE_OSC;
	}
	else if (SystemClkType == RCC_PLL){
		volatile RCC_pllConfig_t RCC_PllConfig;
		volatile uint32_t pllcfg_reg;
		pllcfg_reg = RCC ->PLLCFGR;
		RCC_PllConfig.pll_M =    pllcfg_reg & PLL_MASK_M;
		RCC_PllConfig.pll_N =   (pllcfg_reg & PLL_MASK_N  ) >> PLL_SHIFT_N_POS    ;
		RCC_PllConfig.pll_P =   (pllcfg_reg & PLL_MASK_P  ) >> PLL_SHIFT_P_POS    ;
//		RCC_PllConfig.pll_Q =   (pllcfg_reg & PLL_MASK_Q  ) >> PLL_SHIFT_Q_POS    ;
		RCC_PllConfig.pll_Src = (pllcfg_reg & PLL_MASK_SRC) >> PLL_SHIFT_SRC_POS  ;

		if(RCC_PllConfig.pll_Src == RCC_PLL_SRC_HSE ){
			*CurrentSysClkFreq = ( ( (RCC_HSE_OSC*RCC_PllConfig.pll_N)/RCC_PllConfig.pll_M)/(RCC_PllConfig.pll_P * (uint32_t )2 + (uint32_t ) 2));
		}
		else if(RCC_PllConfig.pll_Src == RCC_PLL_SRC_HSI ){
			*CurrentSysClkFreq = ( ( (RCC_HSI_OSC*RCC_PllConfig.pll_N)/RCC_PllConfig.pll_M)/(RCC_PllConfig.pll_P * (uint32_t )2 + (uint32_t )2));
		}
	}
	return RT_SUCCESS;
}

/* **************************************************************************************************************
 * Public Function: RCC_SetMCOClk
 * Description: This function is used to configure the MCO Clock ,its prescalar and source clock from the provided RCC clocks
 * Input Parameters:
 * 					 -RCC_mcoConfig_t* : RCC_mcoConfig.
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
uint8_t RCC_SetMCOClk(RCC_mcoConfig_t* RCC_mcoConfig ){
	if(RCC_mcoConfig == NULL){
		return RT_PARAM;
	}
	/*if MCO1 configuration is selected */
	if(RCC_mcoConfig -> mco_config == RCC_MCO1_Config || RCC_mcoConfig -> mco_config == RCC_MCO1_AND_MCO2_Config)
	{
		/*validation the source and prescalar of MCO1*/
		if(
				(
						RCC_mcoConfig->mco1_src !=RCC_MCO1_SRC_HSI &&
						RCC_mcoConfig->mco1_src !=RCC_MCO1_SRC_HSE &&
						RCC_mcoConfig->mco1_src !=RCC_MCO1_SRC_PLL &&
						RCC_mcoConfig->mco1_src !=RCC_MCO1_SRC_LSE
				)
				||
				(
						RCC_mcoConfig->mco1_pre != RCC_MCO1_NO_PRE     &&
						RCC_mcoConfig->mco1_pre != RCC_MCO1_PRE_DIV_2  &&
						RCC_mcoConfig->mco1_pre != RCC_MCO1_PRE_DIV_3  &&
						RCC_mcoConfig->mco1_pre != RCC_MCO1_PRE_DIV_4  &&
						RCC_mcoConfig->mco1_pre != RCC_MCO1_PRE_DIV_5
				)
		)
		{
			return RT_PARAM;
		}

		RCC -> CFGR &= (MCO1_PRE_CLR_MASK & MCO1_SRC_CLR_MASK);
		RCC -> CFGR |= (RCC_mcoConfig ->mco1_pre | RCC_mcoConfig ->mco1_src);
	}
	/*if MCO2 configuration is selected */
	if(RCC_mcoConfig -> mco_config == RCC_MCO2_Config || RCC_mcoConfig -> mco_config == RCC_MCO1_AND_MCO2_Config)
	{
		/*validation the source and prescalar of MCO2*/
		if(
				(
						RCC_mcoConfig->mco2_src !=RCC_MCO2_SRC_SYSCLK &&
						RCC_mcoConfig->mco2_src !=RCC_MCO2_SRC_HSE &&
						RCC_mcoConfig->mco2_src !=RCC_MCO2_SRC_PLL &&
						RCC_mcoConfig->mco2_src !=RCC_MCO2_SRC_PLLI2S
				)
				||
				(
						RCC_mcoConfig->mco2_pre != RCC_MCO2_NO_PRE     &&
						RCC_mcoConfig->mco2_pre != RCC_MCO2_PRE_DIV_2  &&
						RCC_mcoConfig->mco2_pre != RCC_MCO2_PRE_DIV_3  &&
						RCC_mcoConfig->mco2_pre != RCC_MCO2_PRE_DIV_4  &&
						RCC_mcoConfig->mco2_pre != RCC_MCO2_PRE_DIV_5)
		)
		{
			return RT_PARAM;
		}
		RCC -> CFGR &= (MCO2_PRE_CLR_MASK & MCO2_SRC_CLR_MASK);
		RCC -> CFGR |= (RCC_mcoConfig ->mco2_pre | RCC_mcoConfig ->mco2_src);
	}
	return RT_SUCCESS;
}

/* **************************************************************************************************************
 * Public Function: RCC_ControlAHB1PeriClk
 * Description: This function is used to Control the peripherals connected on AHB1 Bus.
 * Input Parameters:
 * 					-uint32_t RCC_AHB1Perph :in range { RCC_AHB1_PREPH_GPIOA
 *                                                      RCC_AHB1_PREPH_GPIOB
 *			                                            RCC_AHB1_PREPH_GPIOC
 *                                                      RCC_AHB1_PREPH_GPIOD
 *                                                      RCC_AHB1_PREPH_GPIOE
 *                                                      RCC_AHB1_PREPH_GPIOF
 *                                                      RCC_AHB1_PREPH_GPIOG
 *                                                      RCC_AHB1_PREPH_GPIOH
 *                                                      RCC_AHB1_PREPH_GPIOI
 *                                                      RCC_AHB1_PREPH_CRC
 *                                                      RCC_AHB1_PREPH_BKPSRAM
 *                                                      RCC_AHB1_PREPH_CCMDATARAM
 *                                                      RCC_AHB1_PREPH_DMA1
 *                                                      RCC_AHB1_PREPH_DMA2
 *                                                      RCC_AHB1_PREPH_ETHMAC
 *                                                      RCC_AHB1_PREPH_ETHMACTEX
 *                                                      RCC_AHB1_PREPH_ETHMACRX
 *                                                      RCC_AHB1_PREPH_ETHMACPTP
 *                                                      RCC_AHB1_PREPH_OTGHS
 *                                                      RCC_AHB1_PREPH_OTGHSULPI }
 *
 *					 -uint8_t Status        :in range { RCC_PREPH_ENABLE
 *					                                    RCC_PREPH_DISABLE }
 *
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
/*
 * here we could have used reserved bits to differentiate between RCC_AHB1_peris and
 * the rest of buses peripherals because they have values in macros,
 * so to validate that the user entered the correct macro use reserved bits
 * */
uint8_t RCC_ControlAHB1PeriClk(uint32_t RCC_AHB1_Perph,uint8_t Status){
	if(
			(
					(RCC_AHB1_Perph != RCC_AHB1_PREPH_GPIOA     )&&
					(RCC_AHB1_Perph != RCC_AHB1_PREPH_GPIOB		)&&
					(RCC_AHB1_Perph != RCC_AHB1_PREPH_GPIOC		)&&
					(RCC_AHB1_Perph != RCC_AHB1_PREPH_GPIOD		)&&
					(RCC_AHB1_Perph != RCC_AHB1_PREPH_GPIOE		)&&
					(RCC_AHB1_Perph != RCC_AHB1_PREPH_GPIOF		)&&
					(RCC_AHB1_Perph != RCC_AHB1_PREPH_GPIOG		)&&
					(RCC_AHB1_Perph != RCC_AHB1_PREPH_GPIOH		)&&
					(RCC_AHB1_Perph != RCC_AHB1_PREPH_GPIOI		)&&
					(RCC_AHB1_Perph != RCC_AHB1_PREPH_CRC		)&&
					(RCC_AHB1_Perph != RCC_AHB1_PREPH_BKPSRAM	)&&
					(RCC_AHB1_Perph != RCC_AHB1_PREPH_CCMDATARAM)&&
					(RCC_AHB1_Perph != RCC_AHB1_PREPH_DMA1		)&&
					(RCC_AHB1_Perph != RCC_AHB1_PREPH_DMA2		)&&
					(RCC_AHB1_Perph != RCC_AHB1_PREPH_ETHMAC	)&&
					(RCC_AHB1_Perph != RCC_AHB1_PREPH_ETHMACTEX	)&&
					(RCC_AHB1_Perph != RCC_AHB1_PREPH_ETHMACRX	)&&
					(RCC_AHB1_Perph != RCC_AHB1_PREPH_ETHMACPTP	)&&
					(RCC_AHB1_Perph != RCC_AHB1_PREPH_OTGHS		)&&
					(RCC_AHB1_Perph != RCC_AHB1_PREPH_OTGHSULPI	)
			)||
			(Status != RCC_PREPH_ENABLE && Status != RCC_PREPH_DISABLE)
	)
	{
		return RT_PARAM;
	}

	if(Status == RCC_PREPH_ENABLE){
		RCC -> AHB1ENR |= RCC_AHB1_Perph;
	}
	else {
		RCC -> AHB1ENR &= ~RCC_AHB1_Perph;
	}

	return RT_SUCCESS;
}

/* **************************************************************************************************************
 * Public Function: RCC_ControlAHB2PeriClk
 * Description: This function is used to Control the peripherals connected on AHB2 Bus.
 * Input Parameters:
 * 					-uint32_t RCC_AHB2Perph : in range { RCC_AHB2_PREPH_DCMI
 *                                                      RCC_AHB2_PREPH_CRYP
 *			                                            RCC_AHB2_PREPH_HASH
 *                                                      RCC_AHB2_PREPH_RNG
 *                                                      RCC_AHB2_PREPH_OTGFS }
 *
 *
 * 					-uint8_t Status        :in range {  RCC_PREPH_ENABLE,
 *					                                    RCC_PREPH_DISABLE }
 *
 * Return:           -uint8_t : in range {  RT_PARAM,
 *											RT_ERROR,
 *											RT_SUCCESS }
 *
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
uint8_t RCC_ControlAHB2PeriClk(uint32_t RCC_AHB2_Perph,uint8_t Status){
	if(
			(
					(RCC_AHB2_Perph != RCC_AHB2_PREPH_CRYP )&&
					(RCC_AHB2_Perph != RCC_AHB2_PREPH_DCMI	)&&
					(RCC_AHB2_Perph != RCC_AHB2_PREPH_HASH	)&&
					(RCC_AHB2_Perph != RCC_AHB2_PREPH_OTGFS	)&&
					(RCC_AHB2_Perph != RCC_AHB2_PREPH_RNG	)
			)||
			(Status != RCC_PREPH_ENABLE && Status != RCC_PREPH_DISABLE)
	)
	{
		return RT_PARAM;
	}

	if(Status == RCC_PREPH_ENABLE){
		RCC -> AHB2ENR |= RCC_AHB2_Perph;
	}
	else {
		RCC -> AHB2ENR &= ~RCC_AHB2_Perph;
	}
	return RT_SUCCESS;
}

/* **************************************************************************************************************
 * Public Function: RCC_ControlAHB3PeriClk
 * Description: This function is used to Control the peripherals connected on AHB3 Bus.
 * Input Parameters:
 * 					-uint32_t RCC_AHB3Perph : in range { RCC_AHB3_PREPH_FSMCEN
 *                                                      }
 *
 *
 * 					-uint8_t Status        :in range {  RCC_PREPH_ENABLE,
 *					                                    RCC_PREPH_DISABLE }
 *
 * Return:           -uint8_t : in range {  RT_PARAM,
 *											RT_ERROR,
 *											RT_SUCCESS }
 *
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
uint8_t RCC_ControlAHB3PeriClk(uint32_t RCC_AHB3_Perph,uint8_t Status){
	if(
			(RCC_AHB3_Perph != RCC_AHB3_PREPH_FSMCEN )||
			(Status != RCC_PREPH_DISABLE && Status != RCC_PREPH_ENABLE)
	)
	{
		return RT_PARAM;
	}
	if(Status == RCC_PREPH_ENABLE){
		RCC ->AHB3ENR |= RCC_AHB3_Perph;
	}
	else {
		RCC ->AHB3ENR &= ~RCC_AHB3_Perph;
	}
	return RT_SUCCESS;
}

/* **************************************************************************************************************
 * Public Function: RCC_ControlAPB1PeriClk
 * Description: This function is used to Control the peripherals connected on APB1 Bus.
 * Input Parameters:
 * 					-uint32_t RCC_APB1Perph : in range {RCC_APB1_PREPH_TIM2
 *                                                      RCC_APB1_PREPH_TIM3
 *			                                            RCC_APB1_PREPH_TIM4
 *                                                      RCC_APB1_PREPH_TIM5
 *                                                      RCC_APB1_PREPH_TIM6
 *                                                      RCC_APB1_PREPH_TIM7
 *                                                      RCC_APB1_PREPH_TIM12
 *                                                      RCC_APB1_PREPH_TIM13
 *                                                      RCC_APB1_PREPH_TIM14
 *                                                      RCC_APB1_PREPH_WWDG
 *                                                      RCC_APB1_PREPH_SPI2
 *                                                      RCC_APB1_PREPH_SPI3
 *                                                      RCC_APB1_PREPH_USART2
 *                                                      RCC_APB1_PREPH_USART3
 *                                                      RCC_APB1_PREPH_USART4
 *                                                      RCC_APB1_PREPH_USART5
 *                                                      RCC_APB1_PREPH_I2C1
 *                                                      RCC_APB1_PREPH_I2C2
 *                                                      RCC_APB1_PREPH_I2C3
 *                                                      RCC_APB1_PREPH_CAN1
 *                                                      RCC_APB1_PREPH_CAN2
 *                                                      RCC_APB1_PREPH_PWR
 *                                                      RCC_APB1_PREPH_DAC	}
 *
 * 				     -uint8_t Status        :in range { RCC_PREPH_ENABLE,
 *					                                    RCC_PREPH_DISABLE }
 *
 * Return:           -uint8_t : in range {  RT_PARAM,
 *											RT_ERROR,
 *											RT_SUCCESS }
 *
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
uint8_t RCC_ControlAPB1PeriClk(uint32_t RCC_APB1_Perph,uint8_t Status){
	if(
			(
					(RCC_APB1_Perph != RCC_APB1_PREPH_CAN1)&&
					(RCC_APB1_Perph != RCC_APB1_PREPH_CAN2)&&
					(RCC_APB1_Perph != RCC_APB1_PREPH_DAC)&&
					(RCC_APB1_Perph != RCC_APB1_PREPH_I2C1)&&
					(RCC_APB1_Perph != RCC_APB1_PREPH_I2C2)&&
					(RCC_APB1_Perph != RCC_APB1_PREPH_I2C3)&&
					(RCC_APB1_Perph != RCC_APB1_PREPH_PWR)&&
					(RCC_APB1_Perph != RCC_APB1_PREPH_SPI2)&&
					(RCC_APB1_Perph != RCC_APB1_PREPH_SPI3)&&
					(RCC_APB1_Perph != RCC_APB1_PREPH_TIM12)&&
					(RCC_APB1_Perph != RCC_APB1_PREPH_TIM13)&&
					(RCC_APB1_Perph != RCC_APB1_PREPH_TIM14)&&
					(RCC_APB1_Perph != RCC_APB1_PREPH_TIM2)&&
					(RCC_APB1_Perph != RCC_APB1_PREPH_TIM3)&&
					(RCC_APB1_Perph != RCC_APB1_PREPH_TIM4)&&
					(RCC_APB1_Perph != RCC_APB1_PREPH_TIM5)&&
					(RCC_APB1_Perph != RCC_APB1_PREPH_TIM6)&&
					(RCC_APB1_Perph != RCC_APB1_PREPH_TIM7)&&
					(RCC_APB1_Perph != RCC_APB1_PREPH_USART2)&&
					(RCC_APB1_Perph != RCC_APB1_PREPH_USART3)&&
					(RCC_APB1_Perph != RCC_APB1_PREPH_WWDG)

			)||
			(Status != RCC_PREPH_ENABLE && Status != RCC_PREPH_DISABLE)
	)
	{
		return RT_PARAM;
	}

	if(Status == RCC_PREPH_ENABLE){
		RCC -> APB1ENR |= RCC_APB1_Perph;
	}
	else {
		RCC -> APB1ENR &= ~RCC_APB1_Perph;
	}

	return RT_SUCCESS;
}

/* **************************************************************************************************************
 * Public Function: RCC_ControlAPB2PeriClk
 * Description: This function is used to Control the peripherals connected on APB2 Bus.
 * Input Parameters:
 * 					-uint32_t RCC_APB2Perph : in range {RCC_APB2_PREPH_TIM1
 *                                                      RCC_APB2_PREPH_TIM8
 *			                                            RCC_APB2_PREPH_USART1
 *                                                      RCC_APB2_PREPH_USART6
 *                                                      RCC_APB2_PREPH_ADC1
 *                                                      RCC_APB2_PREPH_ADC2
 *                                                      RCC_APB2_PREPH_ADC3
 *                                                      RCC_APB2_PREPH_SDIO
 *                                                      RCC_APB2_PREPH_SPI1
 *                                                      RCC_APB2_PREPH_SYSCFG
 *                                                      RCC_APB2_PREPH_TIM9
 *                                                      RCC_APB2_PREPH_TIM10
 *                                                      RCC_APB2_PREPH_TIM11 }
  *
 * 				     -uint8_t Status        :in range { RCC_PREPH_ENABLE,
 *					                                    RCC_PREPH_DISABLE }
 *
 * Return:           -uint8_t : in range {  RT_PARAM,
 *											RT_ERROR,
 *											RT_SUCCESS }
 *
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
uint8_t RCC_ControlAPB2PeriClk(uint32_t RCC_APB2_Perph,uint8_t Status){
	if(
			(
					(RCC_APB2_Perph != RCC_APB2_PREPH_ADC1  )&&
					(RCC_APB2_Perph != RCC_APB2_PREPH_ADC2  )&&
					(RCC_APB2_Perph != RCC_APB2_PREPH_ADC3  )&&
					(RCC_APB2_Perph != RCC_APB2_PREPH_SDIO  )&&
					(RCC_APB2_Perph != RCC_APB2_PREPH_SPI1  )&&
					(RCC_APB2_Perph != RCC_APB2_PREPH_SYSCFG)&&
					(RCC_APB2_Perph != RCC_APB2_PREPH_TIM1  )&&
					(RCC_APB2_Perph != RCC_APB2_PREPH_TIM10 )&&
					(RCC_APB2_Perph != RCC_APB2_PREPH_TIM11 )&&
					(RCC_APB2_Perph != RCC_APB2_PREPH_TIM8  )&&
					(RCC_APB2_Perph != RCC_APB2_PREPH_TIM9  )&&
					(RCC_APB2_Perph != RCC_APB2_PREPH_USART1)&&
					(RCC_APB2_Perph != RCC_APB2_PREPH_USART6)
			)||
			(Status != RCC_PREPH_ENABLE && Status != RCC_PREPH_DISABLE)
	)
	{
		return RT_PARAM;
	}

	if(Status == RCC_PREPH_ENABLE){
		RCC -> APB2ENR |= RCC_APB2_Perph;
	}
	else {
		RCC -> APB2ENR &= ~RCC_APB2_Perph;
	}

	return RT_SUCCESS;
}

/* **************************************************************************************************************
 * Public Function: RCC_SetBusPrescaler
 *
 * Description: This function is used to Set any bus prescalar value.
 *
 * Caution 1: The software has to set these bits correctly not to exceed 84 MHz on this domain.
 *	The clocks are divided with the new prescaler factor from 1 to 16 AHB cycles after
 *	PPRE2 write.
 *
 * Caution 2:  The software has to set these bits correctly not to exceed 42 MHz on this domain.
 * The clocks are divided with the new prescaler factor from 1 to 16 AHB cycles after
 * PPRE1 write.
 *
 * Caution 3: The AHB clock frequency must be at least 25 MHz when the Ethernet is used.
 *
 * Input Parameters:
 * 					-uint32_t RCC_bus_prescaler : in range { RCC_AHB_PRE_CLEAR_MASK
 * 					                                         RCC_AHB_PRE_NO_DIV
 * 					                                         RCC_AHB_PRE_DIV_2
 * 					                                         RCC_AHB_PRE_DIV_4
 * 					                                         RCC_AHB_PRE_DIV_8
 * 					                                         RCC_AHB_PRE_DIV_16
 * 					                                         RCC_AHB_PRE_DIV_64
 * 					                                         RCC_AHB_PRE_DIV_128
 * 					                                         RCC_AHB_PRE_DIV_256
 * 					                                         RCC_AHB_PRE_DIV_512
 *
 * 					                                         RCC_APB1_PRE_CLEAR_MASK
 * 					                                         RCC_APB1_PRE_NO_DIV
 * 					                                         RCC_APB1_PRE_DIV_2
 * 					                                         RCC_APB1_PRE_DIV_4
 * 					                                         RCC_APB1_PRE_DIV_8
 * 					                                         RCC_APB1_PRE_DIV_16
 *
 * 					                                         RCC_APB2_PRE_CLEAR_MASK
 * 					                                         RCC_APB2_PRE_NO_DIV
 * 					                                         RCC_APB2_PRE_DIV_2
 * 					                                         RCC_APB2_PRE_DIV_4
 * 					                                         RCC_APB2_PRE_DIV_8
 * 					                                         RCC_APB2_PRE_DIV_16}
 *
 * Return:           -uint8_t : in range {  RT_PARAM,
 *											RT_ERROR,
 *											RT_SUCCESS }
 *
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
uint8_t RCC_SetBusPrescaler(uint32_t RCC_bus_prescaler){

	/*OR RCC_bus_prescaler > (RCC_AHB_PRE_NO_DIV |) */
	if(
			RCC_bus_prescaler != RCC_AHB_PRE_NO_DIV		 &&
			RCC_bus_prescaler != RCC_AHB_PRE_DIV_2		 &&
			RCC_bus_prescaler != RCC_AHB_PRE_DIV_4		 &&
			RCC_bus_prescaler != RCC_AHB_PRE_DIV_8		 &&
			RCC_bus_prescaler != RCC_AHB_PRE_DIV_16		 &&
			RCC_bus_prescaler != RCC_AHB_PRE_DIV_64		 &&
			RCC_bus_prescaler != RCC_AHB_PRE_DIV_128	 &&
			RCC_bus_prescaler != RCC_AHB_PRE_DIV_256	 &&
			RCC_bus_prescaler != RCC_AHB_PRE_DIV_512	 &&
			RCC_bus_prescaler != RCC_APB1_PRE_NO_DIV	 &&
			RCC_bus_prescaler != RCC_APB1_PRE_DIV_2		 &&
			RCC_bus_prescaler != RCC_APB1_PRE_DIV_4		 &&
			RCC_bus_prescaler != RCC_APB1_PRE_DIV_8		 &&
			RCC_bus_prescaler != RCC_APB1_PRE_DIV_16	 &&
			RCC_bus_prescaler != RCC_APB2_PRE_NO_DIV	 &&
			RCC_bus_prescaler != RCC_APB2_PRE_DIV_2		 &&
			RCC_bus_prescaler != RCC_APB2_PRE_DIV_4		 &&
			RCC_bus_prescaler != RCC_APB2_PRE_DIV_8		 &&
			RCC_bus_prescaler != RCC_APB2_PRE_DIV_16		)
	{
		return RT_PARAM;
	}
		/*AHB bus option */
	if (!(GET_BIT(RCC_bus_prescaler,8) | GET_BIT(RCC_bus_prescaler,9) ) ){
		RCC -> CFGR &= RCC_AHB_PRE_CLEAR_MASK;
		RCC -> CFGR |= RCC_bus_prescaler;
	}
	else if (GET_BIT(RCC_bus_prescaler,8)){
		CLR_BIT(RCC_bus_prescaler,8);
		RCC -> CFGR &= RCC_APB1_PRE_CLEAR_MASK;
		RCC -> CFGR |= RCC_bus_prescaler;
	}
	else if (GET_BIT(RCC_bus_prescaler,9)){
		CLR_BIT(RCC_bus_prescaler,9);
		RCC -> CFGR &= RCC_APB2_PRE_CLEAR_MASK;
		RCC -> CFGR |= RCC_bus_prescaler;
	}

	return RT_SUCCESS;
}

/* **************************************************************************************************************
 * Public Function: RCC_GetBusPrescaler
 *
 * Description: This function is used to Get any bus prescalar value.
 *
 * Input Parameters:
 *
 *
 * Return:           -uint8_t : in range {  RT_PARAM,
 *											RT_ERROR,
 *											RT_SUCCESS }
 *
 *
 * Input/Output Parameters:
 * 					-uint32_t RCC_bus_prescaler : in range { RCC_AHB_PRE_CLEAR_MASK
 * 					                                         RCC_AHB_PRE_NO_DIV
 * 					                                         RCC_AHB_PRE_DIV_2
 * 					                                         RCC_AHB_PRE_DIV_4
 * 					                                         RCC_AHB_PRE_DIV_8
 * 					                                         RCC_AHB_PRE_DIV_16
 * 					                                         RCC_AHB_PRE_DIV_64
 * 					                                         RCC_AHB_PRE_DIV_128
 * 					                                         RCC_AHB_PRE_DIV_256
 * 					                                         RCC_AHB_PRE_DIV_512
 *
 * 					                                         RCC_APB1_PRE_CLEAR_MASK
 * 					                                         RCC_APB1_PRE_NO_DIV
 * 					                                         RCC_APB1_PRE_DIV_2
 * 					                                         RCC_APB1_PRE_DIV_4
 * 					                                         RCC_APB1_PRE_DIV_8
 * 					                                         RCC_APB1_PRE_DIV_16
 *
 * 					                                         RCC_APB2_PRE_CLEAR_MASK
 * 					                                         RCC_APB2_PRE_NO_DIV
 * 					                                         RCC_APB2_PRE_DIV_2
 * 					                                         RCC_APB2_PRE_DIV_4
 * 					                                         RCC_APB2_PRE_DIV_8
 * 					                                         RCC_APB2_PRE_DIV_16}
 * ***************************************************************************************************************/
uint8_t RCC_GetBusPrescaler(uint32_t RCC_bus,uint32_t* RCC_bus_prescaler){
	if (RCC_bus != RCC_AHB_BUS && RCC_bus != RCC_APB1_BUS  && RCC_bus != RCC_APB2_BUS ){
		return RT_ERROR;
	}

	*RCC_bus_prescaler = RCC -> CFGR & RCC_bus;

	return RT_SUCCESS;
}

/**************************************************************************************************************
 * Public Function: RCC_GetAHBFreqMhz
 * Description: This function is used to get the freqeuncy of the AHB Clock
 * Input Parameters:
 * 					 -Not Applicable (void)
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
uint8_t RCC_GetAHBFreqMhz(uint32_t *freq_Mhz){

	uint32_t AHBBusPrescaler;

	if (freq_Mhz == NULL ){
		return RT_PARAM;
	}

	AHBBusPrescaler =  RCC -> CFGR & RCC_AHB_BUS;

	switch (AHBBusPrescaler){
	case RCC_AHB_PRE_DIV_2:	  *freq_Mhz = *freq_Mhz /2;  	    break;
	case RCC_AHB_PRE_DIV_4:   *freq_Mhz = *freq_Mhz /4;       break;
	case RCC_AHB_PRE_DIV_8:   *freq_Mhz = *freq_Mhz /8;       break;
	case RCC_AHB_PRE_DIV_16:  *freq_Mhz = *freq_Mhz /16;      break;
	case RCC_AHB_PRE_DIV_64:  *freq_Mhz = *freq_Mhz /64;      break;
	case RCC_AHB_PRE_DIV_128: *freq_Mhz = *freq_Mhz /128;     break;
	case RCC_AHB_PRE_DIV_256: *freq_Mhz = *freq_Mhz /256;     break;
	}

	return RT_SUCCESS;

}
