/*
 * Rcc.c
 *
 *  Created on: Jan 29, 2021
 *      Author: micro
 */

#include <stdint.h>
#include <stddef.h>
#include "diag/Trace.h"
#include "../../../lib/src/Bits.h"
#include "../../../lib/src/Bits.h"
#include "../../../lib/src/RT_Debug.h"
#include "../../../lib/src/stm32f407_Registers.h"
#include "Rcc_int.h"


// RCC Peripheral Base Address*************************************************************************
#define 	Rcc						    ((volatile Rcc_t *)(uint32_t)0x40023800)

// RCC Clear Mask for SW  Bits*************************************************************************************************
#define 	RCC_CFGR_SW_CLEAR 			(uint32_t)(~(BIT_0 | BIT_1))

// RCC Clear Mask for MCO1 , MCO2 , MCO1PRE , MCO2PRE Bits*********************************************************************
#define 	RCC_CFGR_MCO_1_CLEAR		(uint32_t)(~(BIT_21 | BIT_22))
#define		RCC_CFGR_MCO_2_CLEAR		(uint32_t)(~(BIT_30 | BIT_31))
#define 	RCC_CFGR_MCO1PRE_CLEAR      (uint32_t)(~(BIT_24 | BIT_25 | BIT_26))
#define 	RCC_CFGR_MCO2PRE_CLEAR      (uint32_t)(~(BIT_27 | BIT_28 | BIT_29))

// RCC Clear Mask for AHB_Peri , APB1_Peri , APB2_Peri Bits********************************************************************
#define 	RCC_AHB_PRE_CLEAR			(uint32_t)(~(BIT_4 | BIT_5 | BIT_6 | BIT_7))
#define 	RCC_APB1_PRE_CLEAR			(uint32_t)(~(BIT_10 | BIT_11 | BIT_12))
#define 	RCC_APB2_PRE_CLEAR			(uint32_t)(~(BIT_13 | BIT_14 | BIT_15))

// RCC Read Mask for AHB_Peri********************************************************************
#define 	RCC_AHB_PRE_READ			(uint32_t)(BIT_4 | BIT_5 | BIT_6 | BIT_7)

// RCC Read Mask for SWS Bits**************************************************************************************************
#define 	RCC_CFGR_SWS				(uint32_t)(BIT_2 | BIT_3)

// RCC Read Mask for HSI as System Clock***************************************************************************************
#define 	RCC_SWS_HSI					BIT_CLR

// RCC Read Mask for HSE as System Clock***************************************************************************************
#define 	RCC_SWS_HSE					BIT_2

// RCC Read Mask for PLL as System Clock***************************************************************************************
#define 	RCC_SWS_PLL					BIT_3

// RCC Read Mask for PLL Configuration Parameters******************************************************************************
#define 	RCC_PLL_READ_M				(uint32_t)(BIT_0 | BIT_1 | BIT_2 | BIT_3 | BIT_4 | BIT_5)
#define 	RCC_PLL_READ_N				(uint32_t)(BIT_6 | BIT_7 | BIT_8 | BIT_9 |BIT_10 | BIT_11 | BIT_12 | BIT_13 | BIT_14)
#define 	RCC_PLL_READ_P				(uint32_t)(BIT_16 | BIT_17)
#define 	RCC_PLL_READ_SRC			(uint32_t)(BIT_22)
#define 	RCC_PLL_READ_Q				(uint32_t)(BIT_24 | BIT_25 | BIT_26 | BIT_27)

// RCC Read Mask for Ready Flags of Systems Clocks*****************************************************************************
#define		RCC_HSI_RDY 				BIT_1
#define		RCC_HSE_RDY 				BIT_17
#define		RCC_PLL_RDY 				BIT_25
#define 	CLOCK_RDY_L					BIT_CLR

#define 	RCC_AHB1_PERI__CLEAR_MASK  ((uint32_t)~BIT_13)
#define 	RCC_AHB2_PERI__CLEAR_MASK  ((uint32_t)~BIT_24)
#define 	RCC_AHB3_PERI__CLEAR_MASK  ((uint32_t)~(BIT_13 | BIT_24))
#define 	RCC_APB1_PERI__CLEAR_MASK  ((uint32_t)~BIT_31)
#define 	RCC_APB2_PERI__CLEAR_MASK  ((uint32_t)~(BIT_13 | BIT_31))


/* Public Function: Rcc_SetClock_Status												   							*
 * Description: This function is used to Enable and Disable Clocks
 * Input parameters:
 *					- clock		:	in range { RCC_CLOCK_xx }
 * 					- status	:	in range { RCC_CLOCK_STATE_ENABLE -> RCC_CLOCK_STATE_DISABLE}
 * Return:
 * 					- Status (uint8_t)
 * 					  RT_SUCCESS
 *                    RT_PARAM
 *                    RT_ERROR
 *                    RT_TIME_OUT
 *
 * Input/Output Parameter:
 * 					- Not Applicable
 *
 ****************************************************************************************************************/
uint8_t Rcc_SetClock_Status( uint32_t clock, uint32_t status){

	uint32_t Time_out ;
	if ( status == RCC_CLOCK_STATE_ENABLE){
		Time_out =  0x000009C4 ;
		if (clock == RCC_CLOCK_LSE ){
			clock = (uint32_t)BIT_0 ;
			(Rcc -> BDCR) |= clock ;
			while ((Time_out) && ((Rcc -> BDCR & (clock << 1))) != (clock << 1)){  	 //Check if LSE Clock Ready Flage is High
				Time_out-- ;
			}
			if (!Time_out){
				return RT_TIME_OUT ;
			}
		}
		else if (clock == RCC_CLOCK_LSI){
			clock = (uint32_t)BIT_0 ;
			(Rcc -> CSR) |= clock ;
			while ((Time_out) && ((Rcc -> CSR & (clock << 1)) != (clock << 1))){ 	//Check if LSI Clock Ready Flage is High
				Time_out-- ;
			}
			if (!Time_out){
				return RT_TIME_OUT ;
			}
		}
		else if (clock == RCC_CLOCK_HSE || clock == RCC_CLOCK_HSI || clock == RCC_CLOCK_PLL ){
			Rcc -> CR  |= clock ;
			while ((Time_out) && ((Rcc -> CR & (clock << 1)) != (clock << 1))){ 	//Check if HSE or HSI or PLL  Clock Ready Flage is HIGH
				Time_out-- ;
			}
			if (!Time_out){
				return RT_TIME_OUT ;
			}
		}
		else
			return RT_PARAM ;
	}
	else if( status == RCC_CLOCK_STATE_DISABLE ){
		Time_out =  0x000007D0 ;
		if (clock == RCC_CLOCK_LSE ){
			clock = (uint32_t)BIT_0 ;
			(Rcc -> BDCR) &= ~clock ;
			while ((Time_out) && ((Rcc -> BDCR & (clock << 1))) != CLOCK_RDY_L){
				Time_out-- ;
			}
			if (!Time_out){
				return RT_TIME_OUT ;
			}
		}
		else if (clock == RCC_CLOCK_LSI){
			clock = (uint32_t)BIT_0 ;
			(Rcc -> CSR) &= ~clock ;
			while ((Time_out) && ((Rcc -> CSR & (clock << 1)) != CLOCK_RDY_L)){
				Time_out-- ;
			}
			if (!Time_out){
				return RT_TIME_OUT ;
			}
		}
		else if ((clock == RCC_CLOCK_HSE) || (clock == RCC_CLOCK_HSI) || (clock == RCC_CLOCK_PLL)){
			Rcc -> CR  &= ~clock ;
			while ((Time_out) && ((Rcc -> CR & (clock << 1)) != CLOCK_RDY_L)){
				Time_out-- ;
			}
			if (!Time_out){
				return RT_TIME_OUT ;
			}
		}
		else
			return RT_PARAM ;
	}
	else
		return RT_PARAM ;
	return RT_SUCCESS ;
}

/* Public Function: Rcc_AHB1_PeriClockStatus										   							*
 * Description: This function is used to Enable and Disable AHB1 Preipherals Clocks
 * Input parameters:
 *					- clock		:	in range { AHB1_PERI_CLOCK_xx }
 * 					- status	:	in range { RCC_PERI_CLOCK_ENABLE -> RCC_PERI_CLOCK_DISABLE}
 *
 * Return:
 * 					- Status (uint8_t)
 *                    RT_SUCCESS
 *                    RT_PARAM
 *                    RT_ERROR
 *                    RT_TIME_OUT
 *
 * Input/Output Parameter:
 * 					- Not Applicable
 *
 *****************************************************************************************************************/
uint8_t Rcc_AHB1_PeriClockStatus(uint64_t peri ,uint32_t status){

	if ((( peri & RCC_AHB1_PERI_MASK ) == RCC_AHB1_PERI_MASK )			//Check if user enter vaild AHB1 Peripheral and not Peripheral of other Buses
			&& (( peri & RCC_AHB2_PERI_MASK ) != RCC_AHB2_PERI_MASK )
			&& (( peri & RCC_AHB3_PERI_MASK ) != RCC_AHB3_PERI_MASK )
			&& (( peri & RCC_APB1_PERI_MASK ) != RCC_APB1_PERI_MASK )
			&& (( peri & RCC_APB2_PERI_MASK ) != RCC_APB2_PERI_MASK ) ){


		switch (status){
		case RCC_PERI_CLOCK_ENABLE :
			Rcc -> AHB1ENR |= (uint32_t)peri;
			break;

		case RCC_PERI_CLOCK_DISABLE :
			Rcc -> AHB1ENR &= ~((uint32_t)peri) ;
			break;
		default:
			return RT_PARAM;
		}
	}
	else
		return RT_PARAM;

	return RT_SUCCESS ;
}

/* Public Function: Rcc_AHB2_PeriClockStatus											     				     *
 * Description: This function is used to Enable and Disable AHB2 Preipherals Clocks
 * Input parameters:
 *					- clock		:	in range { AHB2_PERI_CLOCK_xx }
 * 					- status	:	in range { RCC_PERI_CLOCK_ENABLE -> RCC_PERI_CLOCK_DISABLE}
 *
 * Return:
 * 					- Status (uint8_t)
 *                    RT_SUCCESS
 *                    RT_PARAM
 *                    RT_ERROR
 *                    RT_TIME_OUT
 *
 * Input/Output Parameter:
 * 					- Not Applicable
 *
 ******************************************************************************************************************/
uint8_t Rcc_AHB2_PeriClockStatus(uint64_t peri, uint32_t status){

	if ((( peri & RCC_AHB2_PERI_MASK ) == RCC_AHB2_PERI_MASK )			//Check if user enter vaild AHB2 Peripheral and not Peripheral of other Buses
			&& (( peri & RCC_AHB1_PERI_MASK ) != RCC_AHB1_PERI_MASK )
			&& (( peri & RCC_AHB3_PERI_MASK ) != RCC_AHB3_PERI_MASK )
			&& (( peri & RCC_APB1_PERI_MASK ) != RCC_APB1_PERI_MASK )
			&& (( peri & RCC_APB2_PERI_MASK ) != RCC_APB2_PERI_MASK ) ){

		switch (status){
		case RCC_PERI_CLOCK_ENABLE :
			Rcc -> AHB2ENR |= (uint32_t)peri;
			break;

		case RCC_PERI_CLOCK_DISABLE :
			Rcc -> AHB2ENR &= ~((uint32_t)peri) ;
			break;
		default:
			return RT_PARAM;
		}
	}
	else
		return RT_PARAM;

	return RT_SUCCESS ;
}

/* Public Function: Rcc_AHB3_PeriClockStatus										   							   *
 * Description: This function is used to Enable and Disable AHB3 Preipherals Clocks
 * Input parameters:
 *					- clock		:	in range { AHB3_PERI_CLOCK_xx }
 * 					- status	:	in range { RCC_PERI_CLOCK_ENABLE -> RCC_PERI_CLOCK_DISABLE}
 *
 * Return:
 * 					- Status (uint8_t)
 *                    RT_SUCCESS
 *                    RT_PARAM
 *                    RT_ERROR
 *                    RT_TIME_OUT
 *
 * Input/Output Parameter:
 * 					- Not Applicable
 *
 ******************************************************************************************************************/
uint8_t Rcc_AHB3_PeriClockStatus(uint64_t peri ,uint32_t status){

	if ((( peri & RCC_AHB3_PERI_MASK ) == RCC_AHB3_PERI_MASK )			//Check if user enter vaild AHB3 Peripheral and not Peripheral of other Buses
			&& (( peri & RCC_AHB1_PERI_MASK ) != RCC_AHB1_PERI_MASK )
			&& (( peri & RCC_AHB2_PERI_MASK ) != RCC_AHB2_PERI_MASK )
			&& (( peri & RCC_APB1_PERI_MASK ) != RCC_APB1_PERI_MASK )
			&& (( peri & RCC_APB2_PERI_MASK ) != RCC_APB2_PERI_MASK ) ){


		switch (status){
		case RCC_PERI_CLOCK_ENABLE :
			Rcc -> AHB3ENR |= (uint32_t)peri;
			break;

		case RCC_PERI_CLOCK_DISABLE :
			Rcc -> AHB3ENR &= ~((uint32_t)peri) ;
			break;
		default:
			return RT_PARAM;
		}
	}
	else
		return RT_PARAM;

	return RT_SUCCESS ;
}

/* Public Function: Rcc_APB1_PeriClockStatus																       *
 * Description: This function is used to Enable and Disable APB1 Preipherals Clocks
 * Input parameters:
 *					- clock		:	in range { APB1_PERI_CLOCK_xx }
 * 					- status	:	in range { RCC_PERI_CLOCK_ENABLE -> RCC_PERI_CLOCK_DISABLE}
 *
 * Return:
 * 					- Status (uint8_t)
 *                    RT_SUCCESS
 *                    RT_PARAM
 *                    RT_ERROR
 *                    RT_TIME_OUT
 *
 * Input/Output Parameter:
 * 					- Not Applicable
 *
 ********************************************************************************************************************/
uint8_t Rcc_APB1_PeriClockStatus(uint64_t peri ,uint32_t status){

	if ((( peri & RCC_APB1_PERI_MASK ) == RCC_APB1_PERI_MASK )			//Check if user enter vaild APB1 Peripheral and not Peripheral of other Buses
			&& (( peri & RCC_AHB1_PERI_MASK ) != RCC_AHB1_PERI_MASK )
			&& (( peri & RCC_AHB2_PERI_MASK ) != RCC_AHB2_PERI_MASK )
			&& (( peri & RCC_AHB3_PERI_MASK ) != RCC_AHB3_PERI_MASK )
			&& (( peri & RCC_APB2_PERI_MASK ) != RCC_APB2_PERI_MASK ) ){

		switch (status){
		case RCC_PERI_CLOCK_ENABLE :
			Rcc -> APB1ENR |= (uint32_t)peri;
			break;

		case RCC_PERI_CLOCK_DISABLE :
			Rcc -> APB1ENR &= ~((uint32_t)peri) ;
			break;
		default:
			return RT_PARAM;
		}
	}
	else
		return RT_PARAM;

	return RT_SUCCESS ;
}

/* Public Function: Rcc_APB2_PeriClockStatus										   								*
 * Description: This function is used to Enable and Disable APB2 Preipherals Clocks
 * Input parameters:
 *					- clock		:	in range { APB2_PERI_CLOCK_xx }
 * 					- status	:	in range { RCC_PERI_CLOCK_ENABLE -> RCC_PERI_CLOCK_DISABLE}
 *
 * Return:
 * 					- Status (uint8_t)
 *                    RT_SUCCESS
 *                    RT_PARAM
 *                    RT_ERROR
 *                    RT_TIME_OUT
 *
 * Input/Output Parameter:
 * 					- Not Applicable
 *
 *********************************************************************************************************************/
uint8_t Rcc_APB2_PeriClockStatus(uint64_t peri ,uint32_t status){

	if ((( peri & RCC_APB2_PERI_MASK ) == RCC_APB2_PERI_MASK )				//Check if user enter vaild APB2 Peripheral and not Peripheral of other Buses
			&& (( peri & RCC_AHB1_PERI_MASK ) != RCC_AHB1_PERI_MASK )
			&& (( peri & RCC_AHB2_PERI_MASK ) != RCC_AHB2_PERI_MASK )
			&& (( peri & RCC_AHB3_PERI_MASK ) != RCC_AHB3_PERI_MASK )
			&& (( peri & RCC_APB1_PERI_MASK ) != RCC_APB1_PERI_MASK ) ){


		switch (status){
		case RCC_PERI_CLOCK_ENABLE :
			Rcc -> APB2ENR |= (uint32_t)peri;
			break;

		case RCC_PERI_CLOCK_DISABLE :
			Rcc -> APB2ENR &= ~((uint32_t)peri) ;
			break;
		default:
			return RT_PARAM;
		}
	}
	else
		return RT_PARAM;

	return RT_SUCCESS ;
}

/* Public Function:  RCC_SelectSysClk												   								  *
 * Description: This function is used to Select System clock
 * Input parameters:
 * 					- sysclk	:	in range {  RCC_SYS_CLK_xx }
 *
 * Return:
 * 					- Status (uint8_t)
 *                    RT_SUCCESS
 *                    RT_PARAM
 *                    RT_ERROR
 *                    RT_TIME_OUT
 *
 * Input/Output Parameter:
 * 					- Not Applicable
 *
 **********************************************************************************************************************/
uint8_t Rcc_SelectSysClk(uint32_t sysclk){
	switch(sysclk) {
	case RCC_SYS_CLK_HSE :
		if ((Rcc -> CR & RCC_HSE_RDY) != RCC_HSE_RDY){			//Check if HSE Clock Ready Flage is high
			return RT_ERROR ;
		}
		break;
	case RCC_SYS_CLK_HSI :
		if ((Rcc -> CR & RCC_HSI_RDY) != RCC_HSI_RDY){			//Check if HSI Clock Ready Flage is high
			return RT_ERROR ;
		}
		break;
	case RCC_SYS_CLK_PLL :
		if ((Rcc -> CR & RCC_PLL_RDY) != RCC_PLL_RDY){			//Check if PLL Clock Ready Flage is high
			return RT_ERROR ;
		}
		break;
	default:
		return RT_PARAM ;
	}
	uint32_t  current_clk ;
	uint32_t CFGR_local = Rcc -> CFGR ;
	CFGR_local &= RCC_CFGR_SW_CLEAR ;
	CFGR_local |= sysclk ;
	Rcc -> CFGR = CFGR_local;
	current_clk = Rcc -> CFGR & RCC_CFGR_SWS ;
	if (sysclk != (current_clk >> 2)){
		return RT_ERROR ;
	}

	return RT_SUCCESS ;
}

/* Public Function:  RCC_ConfigurePLL																				   *
 * Description: This function is used to Configure PLL Parameters
 * Input parameters:
 * 					- Object of (PLLcfg_t)
 * Options:
 * 					- pllcfg.PLL_M    :  in range : { 2  ->  63 }
 * 					- pllcfg.PLL_N    :  in range : { 50  -> 432 }
 * 					- pllcfg.PLL_P    :  in range : { RCC_PLL_P_xx  (xx : {2, 4, 6, 8}) }
 * 					- pllcfg.PLL_src  :  in range : { RCC_PLL_SRC_HSI -> RCC_PLL_SRC_HSE }
 * 					- pllcfg.PLL_Q	  :  in range : { 2  -> 15 }
 *
 * Return:
 * 					- Status (uint8_t)
 *                    RT_SUCCESS
 *                    RT_PARAM
 *                    RT_ERROR
 *                    RT_TIME_OUT
 *
 * Input/Output Parameter:
 * 					- Not Applicable
 *
 ***********************************************************************************************************************/
uint8_t	Rcc_ConfigurePLL(PLLcfg_t *pllcfg)
{
	if ( ( Rcc -> CR & RCC_PLL_RDY ) == CLOCK_RDY_L ){			//Check if PLL Clock Ready Flage is Low

		if (pllcfg != NULL){									//Check if Passing valid address

			uint32_t Freq_out ;
			switch (pllcfg -> PLL_src){
			case RCC_PLL_SRC_HSI :
				Freq_out = ((RCC_HSI_CLOCK_FREQ / (uint32_t)1000000 / pllcfg -> PLL_M) * pllcfg -> PLL_N) / pllcfg -> PLL_P ;
				if (Freq_out > (uint32_t)168)					//Check that Output Frequancy of PLL does not exceed 168 MHz
				{
					return RT_ERROR;
				}
				break;
			case RCC_PLL_SRC_HSE :
				Freq_out = ((RCC_HSE_CLOCK_FREQ / (uint32_t)1000000 / pllcfg -> PLL_M) * pllcfg -> PLL_N) / pllcfg -> PLL_P ;
				if (Freq_out > (uint32_t)168)					//Check that Output Frequancy of PLL does not exceed 168 MHz
				{
					return RT_ERROR;
				}
				break;
			default:
				return RT_PARAM;
			}

			uint32_t PLLCFGR_local = Rcc -> PLLCFGR ;

			if (pllcfg -> PLL_N >= (uint32_t)50 && pllcfg -> PLL_N <= (uint32_t)216){
				PLLCFGR_local &=  ~RCC_PLL_READ_N ;
				PLLCFGR_local |= pllcfg -> PLL_N << 6 ;
			}
			else
				return RT_PARAM;

			if (pllcfg -> PLL_P == (uint32_t)2 || pllcfg -> PLL_P == (uint32_t)4 || pllcfg -> PLL_P == (uint32_t)6 || pllcfg -> PLL_P == (uint32_t)8){
				PLLCFGR_local &=  ~RCC_PLL_READ_P ;
				PLLCFGR_local |= pllcfg -> PLL_P << 16 ;
			}
			else
				return RT_PARAM;

			if (pllcfg -> PLL_src == RCC_PLL_SRC_HSI|| pllcfg -> PLL_src == RCC_PLL_SRC_HSE){
				PLLCFGR_local &=  ~RCC_PLL_READ_SRC ;
				PLLCFGR_local |= pllcfg -> PLL_src << 22 ;
			}
			else
				return RT_PARAM;

			if ( (Rcc -> PLLCFGR & (pllcfg -> PLL_src << 22)) == RCC_PLL_SRC_HSI ){

				if (pllcfg -> PLL_M == (uint32_t)8 ){
					PLLCFGR_local &=  ~RCC_PLL_READ_M ;
					PLLCFGR_local |= pllcfg -> PLL_M ;
				}
				else
					return RT_PARAM;
			}
			else {
				if (pllcfg -> PLL_M == (RCC_HSE_CLOCK_FREQ / (uint32_t)1000000 / (uint32_t)2)){
					PLLCFGR_local &=  ~RCC_PLL_READ_M ;
					PLLCFGR_local |= pllcfg -> PLL_M ;
				}
				else
					return RT_PARAM;
			}

			if (pllcfg -> PLL_Q >= (uint32_t)2 && pllcfg -> PLL_Q <= (uint32_t)15){
				PLLCFGR_local &=  ~RCC_PLL_READ_Q ;
				PLLCFGR_local |= pllcfg -> PLL_Q << 24 ;
			}
			else
				return RT_PARAM;

			Rcc -> PLLCFGR = PLLCFGR_local ;
			if (Rcc -> PLLCFGR != PLLCFGR_local){					//CHECK If Configurations Parameters Have been written on PLLCFGR Register
				return RT_ERROR ;
			}

		}
		else {
			return RT_PARAM;
		}
	}
	else {
		return RT_ERROR;
	}

	return RT_SUCCESS ;
}

/* Public Function:  Rcc_GetCurrrentSysClk_Frequency								   									*
 * Description: This function is used to Get Current System Clock Frequency
 * Input parameters:
 * 					- *ClkFreq        (uint32_t)
 * 					:  in range : {}
 *
 * Return:
 * 					- Status (uint8_t)
 *                    RT_SUCCESS
 *                    RT_PARAM
 *                    RT_ERROR
 *                    RT_TIME_OUT
 *
 * Input/Output Parameter:
 * 					- *ClkFreq        (uint32_t)
 *
 ***********************************************************************************************************************/
uint8_t	Rcc_GetCurrrentSysClk_Frequency(uint32_t *ClkFreq){
	uint32_t	current_clk ;
	uint32_t	current_M ;
	uint32_t	current_N ;
	uint32_t	current_P ;
	uint32_t	current_Src ;
	if ( ClkFreq != NULL){								//Check if Passing valid address
		current_clk = Rcc -> CFGR & RCC_CFGR_SWS ;

		switch (current_clk){
		case RCC_SWS_HSI :
			*ClkFreq = RCC_HSI_CLOCK_FREQ ;
			break;

		case RCC_SWS_HSE :
			*ClkFreq = RCC_HSE_CLOCK_FREQ ;
			break;

		case RCC_SWS_PLL :
			current_M  	 =  (Rcc -> PLLCFGR) & RCC_PLL_READ_M ;
			current_N  	 = ((Rcc -> PLLCFGR) & RCC_PLL_READ_N)   >> 6 ;
			current_P  	 = ((Rcc -> PLLCFGR) & RCC_PLL_READ_P)   >> 16 ;
			current_Src  = ((Rcc -> PLLCFGR) & RCC_PLL_READ_SRC) >> 22 ;

			if ( current_Src == RCC_PLL_SRC_HSI ){
				*ClkFreq = ((( RCC_HSI_CLOCK_FREQ / current_M ) * current_N ) / ((current_P * (uint32_t)2) + (uint32_t)2) );
			}
			else if ( current_Src == RCC_PLL_SRC_HSE ){
				*ClkFreq = ((( RCC_HSE_CLOCK_FREQ / current_M ) * current_N ) / ((current_P * (uint32_t)2) + (uint32_t)2) );
			}
			break;

		default:
			return RT_ERROR ;
		}

	}
	else
		return RT_PARAM ;

	return RT_SUCCESS ;
}

/* Public Function:  Rcc_SetMco_Clock     											 					  			    *
 * Description: This function is used to Select Mco1 and Mco2 Clock Source and Configure their Prescaler
 * Input parameters:
 * 					-  Mco_ClkSrc       in range : {RCC_MC0_1_SRC_xx  - RCC_MC0_2_SRC_xx}
 * 					-  Mco_Pre          in range : {RCC_MCO1PRE_xx 	  - RCC_MCO2PRE_xx  }
 *
 * Return:
 * 					- Status (uint8_t)
 *                    RT_SUCCESS
 *                    RT_PARAM
 *                    RT_ERROR
 *                    RT_TIME_OUT
 *
 * Input/Output Parameter:
 * 					- Not Applicable
 *
 ***********************************************************************************************************************/
uint8_t Rcc_SetMco_Clock(uint32_t Mco_ClkSrc ,uint32_t Mco_Pre){

	uint32_t McoClk_local = Rcc -> CFGR ;

	if ((Mco_ClkSrc == RCC_MC0_1_SRC_HSI
			|| Mco_ClkSrc  == RCC_MC0_1_SRC_LSE
			|| Mco_ClkSrc  == RCC_MC0_1_SRC_HSE
			|| Mco_ClkSrc  == RCC_MC0_1_SRC_PLL)
			&&
			(Mco_Pre == RCC_MCO1PRE_2
					|| Mco_Pre == RCC_MCO1PRE_3
					|| Mco_Pre == RCC_MCO1PRE_4
					|| Mco_Pre == RCC_MCO1PRE_5)){

		McoClk_local &= RCC_CFGR_MCO_1_CLEAR ;
		McoClk_local &= RCC_CFGR_MCO1PRE_CLEAR  ;
		McoClk_local |= Mco_ClkSrc | Mco_Pre ;
		Rcc -> CFGR = McoClk_local;
		if (Rcc -> CFGR != McoClk_local)
		{
			return RT_ERROR ;
		}
	}
	else if (  (Mco_ClkSrc == RCC_MC0_2_SRC_SYSCLK
			|| Mco_ClkSrc == RCC_MC0_2_SRC_PLLI2S
			|| Mco_ClkSrc == RCC_MC0_2_SRC_HSE
			|| Mco_ClkSrc == RCC_MC0_2_SRC_PLL)
			&& (Mco_Pre == RCC_MCO2PRE_2
					||  Mco_Pre == RCC_MCO2PRE_3
					||  Mco_Pre == RCC_MCO2PRE_4
					||  Mco_Pre == RCC_MCO2PRE_5)){

		if (Mco_ClkSrc == RCC_MC0_2_SRC_SYSCLK){
			Mco_ClkSrc = (uint32_t)BIT_CLR;
		}
		McoClk_local &= RCC_CFGR_MCO_2_CLEAR ;
		McoClk_local &= RCC_CFGR_MCO2PRE_CLEAR  ;
		McoClk_local |= Mco_ClkSrc | Mco_Pre ;
		Rcc -> CFGR = McoClk_local;
		if (Rcc -> CFGR != McoClk_local)
		{
			return RT_ERROR ;
		}
	}
	else {
		return RT_PARAM ;
	}

	return RT_SUCCESS;
}

/* Public Function:  Rcc_SetBus_Prescaler																			    *
 * Description: This function is used to Configure AHB1 and APB1 and APB2 Prescalers
 * Input parameters:
 * 					-  Bus        (uint32_t)
 * 					:  in range : {RCC_AHB_PRE_xx - RCC_APB1_PRE_xx - RCC_APB2_PRE_xx}
 *
 * Return:
 * 					- Status (uint8_t)
 *                    RT_SUCCESS
 *                    RT_PARAM
 *                    RT_ERROR
 *                    RT_TIME_OUT
 *
 * Input/Output Parameter:
 * 					- Not Applicable
 *
 ****************************************************************************************************************/
uint8_t Rcc_SetBus_Prescaler(uint32_t Bus){

	uint32_t BusPre_local = Rcc -> CFGR ;

	if (   Bus == RCC_APB1_PRE_2
			|| Bus == RCC_APB1_PRE_4
			|| Bus == RCC_APB1_PRE_8
			|| Bus == RCC_APB1_PRE_16){

		BusPre_local &= RCC_APB1_PRE_CLEAR ;
		BusPre_local |= Bus ;
		Rcc -> CFGR = BusPre_local;
		if (Rcc -> CFGR != BusPre_local)
		{
			return RT_ERROR ;
		}
	}
	else if (  Bus == RCC_APB2_PRE_2
			|| Bus == RCC_APB2_PRE_4
			|| Bus == RCC_APB2_PRE_8
			|| Bus == RCC_APB2_PRE_16){

		BusPre_local &= RCC_APB2_PRE_CLEAR ;
		BusPre_local |= Bus ;
		Rcc -> CFGR = BusPre_local;
		if (Rcc -> CFGR != BusPre_local)
		{
			return RT_ERROR ;
		}
	}
	else if(   Bus == RCC_AHB_PRE_2
			|| Bus == RCC_AHB_PRE_4
			|| Bus == RCC_AHB_PRE_8
			|| Bus == RCC_AHB_PRE_16
			|| Bus == RCC_AHB_PRE_64
			|| Bus == RCC_AHB_PRE_128
			|| Bus == RCC_AHB_PRE_256
			|| Bus == RCC_AHB_PRE_512){

		BusPre_local &= RCC_AHB_PRE_CLEAR ;
		BusPre_local |= Bus ;
		Rcc -> CFGR = BusPre_local;
		if (Rcc -> CFGR != BusPre_local)
		{
			return RT_ERROR ;
		}
	}
	else {
		return RT_PARAM ;
	}

	return RT_SUCCESS;
}

/* Public Function:  Rcc_GetAHB_Prescaler																	    *
 * Description: This function is used to Get AHB1 Bus Prescaler.
 * Input parameters:
 *
 * Return:
 * 					- Status (uint8_t)
 *                    RT_SUCCESS
 *                    RT_PARAM
 *                    RT_ERROR
 *                    RT_TIME_OUT
 *
 * Input/Output Parameter:
 * 					- Rcc_AHB_Pre (uint32_t)
 *
 ****************************************************************************************************************/
uint8_t Rcc_GetAHB_Prescaler(uint16_t *Rcc_AHB_Pre){

	uint32_t Loc_AHB_Pre = 0 ;
	RT_Debug Status = RT_SUCCESS ;

	if (Rcc_AHB_Pre != NULL)
	{
		Loc_AHB_Pre  = (Rcc -> CFGR & RCC_AHB_PRE_READ);
		switch(Loc_AHB_Pre)
		{
		case	RCC_AHB_PRE_2 :
			*Rcc_AHB_Pre = 2 ;
			break;
		case	RCC_AHB_PRE_4	:
			*Rcc_AHB_Pre = 4 ;
			break;
		case	RCC_AHB_PRE_8	:
			*Rcc_AHB_Pre = 8 ;
			break;
		case	RCC_AHB_PRE_16	:
			*Rcc_AHB_Pre = 16 ;
			break;
		case	RCC_AHB_PRE_64	:
			*Rcc_AHB_Pre = 64 ;
			break;
		case	RCC_AHB_PRE_128 :
			*Rcc_AHB_Pre = 128 ;
			break;
		case	RCC_AHB_PRE_256 :
			*Rcc_AHB_Pre = 256 ;
			break;
		case 	RCC_AHB_PRE_512 :
			*Rcc_AHB_Pre = 512 ;
			break;
		default :
			*Rcc_AHB_Pre = 1 ;
			break;
		}

	}

	else {

		Status = RT_PARAM;
	}


	return
			Status ;
}


