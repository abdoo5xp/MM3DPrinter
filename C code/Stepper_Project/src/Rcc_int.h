/*
 * Rcc_int.h
 *
 *  Created on: Jan 29, 2021
 *      Author: micro
 */

#ifndef RCC_INT_H_
#define RCC_INT_H_



// System Clock Frequencies****************************************************************************
#define 	RCC_HSE_CLOCK_FREQ			            (uint32_t)8000000
#define		RCC_HSI_CLOCK_FREQ						(uint32_t)16000000
#define		RCC_PLL_CLOCK_FREQ						(uint32_t)168000000

// RCC Clock Status************************************************************************************
#define 	RCC_CLOCK_STATE_ENABLE		            (uint32_t)1
#define 	RCC_CLOCK_STATE_DISABLE		            (uint32_t)0

// RCC Clock Status************************************************************************************
#define 	RCC_PERI_CLOCK_ENABLE		            (uint32_t)1
#define 	RCC_PERI_CLOCK_DISABLE		            (uint32_t)0

//AHB1 peripheral Enable Configuration (RCC_AHB1LPENR)*************************************************
#define		RCC_AHB1_PERI_MASK						((uint64_t)0x0100000000)
#define     RCC_AHB1_PERI_CLOCK_GPIOA 				((uint64_t)((uint64_t)BIT_0  |  RCC_AHB1_PERI_MASK))
#define     RCC_AHB1_PERI_CLOCK_GPIOB				((uint64_t)((uint64_t)BIT_1  |  RCC_AHB1_PERI_MASK))
#define     RCC_AHB1_PERI_CLOCK_GPIOC				((uint64_t)((uint64_t)BIT_2  |  RCC_AHB1_PERI_MASK))
#define     RCC_AHB1_PERI_CLOCK_GPIOD				((uint64_t)((uint64_t)BIT_3  |  RCC_AHB1_PERI_MASK))
#define     RCC_AHB1_PERI_CLOCK_GPIOE				((uint64_t)((uint64_t)BIT_4  |  RCC_AHB1_PERI_MASK))
#define     RCC_AHB1_PERI_CLOCK_GPIOF				((uint64_t)((uint64_t)BIT_5  |  RCC_AHB1_PERI_MASK))
#define     RCC_AHB1_PERI_CLOCK_GPIOG				((uint64_t)((uint64_t)BIT_6  |  RCC_AHB1_PERI_MASK))
#define     RCC_AHB1_PERI_CLOCK_GPIOH				((uint64_t)((uint64_t)BIT_7  |  RCC_AHB1_PERI_MASK))
#define     RCC_AHB1_PERI_CLOCK_GPIOI				((uint64_t)((uint64_t)BIT_8  |  RCC_AHB1_PERI_MASK))
#define     RCC_AHB1_PERI_CLOCK_CRC			        ((uint64_t)((uint64_t)BIT_12 |  RCC_AHB1_PERI_MASK))
#define     RCC_AHB1_PERI_CLOCK_BKPSRAM		        ((uint64_t)((uint64_t)BIT_18 |  RCC_AHB1_PERI_MASK))
#define     RCC_AHB1_PERI_CLOCK_CCMDATARAM			((uint64_t)((uint64_t)BIT_20 |  RCC_AHB1_PERI_MASK))
#define     RCC_AHB1_PERI_CLOCK_DMA1				((uint64_t)((uint64_t)BIT_21 |  RCC_AHB1_PERI_MASK))
#define     RCC_AHB1_PERI_CLOCK_DMA2				((uint64_t)((uint64_t)BIT_22 |  RCC_AHB1_PERI_MASK))
#define     RCC_AHB1_PERI_CLOCK_ETHMAC				((uint64_t)((uint64_t)BIT_25 |  RCC_AHB1_PERI_MASK))
#define     RCC_AHB1_PERI_CLOCK_ETHMACTEX			((uint64_t)((uint64_t)BIT_26 |  RCC_AHB1_PERI_MASK))
#define     RCC_AHB1_PERI_CLOCK_ETHMACRX			((uint64_t)((uint64_t)BIT_27 |  RCC_AHB1_PERI_MASK))
#define     RCC_AHB1_PERI_CLOCK_ETHMACPTP		    ((uint64_t)((uint64_t)BIT_28 |  RCC_AHB1_PERI_MASK))
#define     RCC_AHB1_PERI_CLOCK_OTGHS				((uint64_t)((uint64_t)BIT_29 |  RCC_AHB1_PERI_MASK))
#define     RCC_AHB1_PERI_CLOCK_OTGHSULPI		    ((uint64_t)((uint64_t)BIT_30 |  RCC_AHB1_PERI_MASK))

//AHB2 peripheral Enable Configuration (RCC_AHB2LPENR)*************************************************
#define 	RCC_AHB2_PERI_MASK						((uint64_t)0x0200000000)
#define     RCC_AHB2_PERI_CLOCK_DCMI 				(uint64_t)((uint64_t)BIT_0 | RCC_AHB2_PERI_MASK)
#define     RCC_AHB2_PERI_CLOCK_CRYP		    	(uint64_t)((uint64_t)BIT_4 | RCC_AHB2_PERI_MASK)
#define     RCC_AHB2_PERI_CLOCK_HASH			    (uint64_t)((uint64_t)BIT_5 | RCC_AHB2_PERI_MASK)
#define     RCC_AHB2_PERI_CLOCK_RNG			        (uint64_t)((uint64_t)BIT_6 | RCC_AHB2_PERI_MASK)
#define     RCC_AHB2_PERI_CLOCK_OTGFS				(uint64_t)((uint64_t)BIT_7 | RCC_AHB2_PERI_MASK)

//AHB3 peripheral Enable Configuration (RCC_AHB3LPENR)*************************************************
#define 	RCC_AHB3_PERI_MASK						((uint64_t)0x0400000000)
#define     RCC_AHB3_PERI_CLOCK_FSMC				((uint64_t)((uint64_t)BIT_0  | RCC_AHB3_PERI_MASK))

//APB1 peripheral Enable Configuration (RCC_APB1LPENR)*************************************************
#define 	RCC_APB1_PERI_MASK						((uint64_t)0x0800000000)
#define     RCC_APB1_PERI_CLOCK_TIM2				((uint64_t)((uint64_t)BIT_0  | RCC_APB1_PERI_MASK))
#define     RCC_APB1_PERI_CLOCK_TIM3				((uint64_t)((uint64_t)BIT_1  | RCC_APB1_PERI_MASK))
#define     RCC_APB1_PERI_CLOCK_TIM4				((uint64_t)((uint64_t)BIT_2  | RCC_APB1_PERI_MASK))
#define     RCC_APB1_PERI_CLOCK_TIM5				((uint64_t)((uint64_t)BIT_3  | RCC_APB1_PERI_MASK))
#define     RCC_APB1_PERI_CLOCK_TIM6				((uint64_t)((uint64_t)BIT_4  | RCC_APB1_PERI_MASK))
#define     RCC_APB1_PERI_CLOCK_TIM7				((uint64_t)((uint64_t)BIT_5  | RCC_APB1_PERI_MASK))
#define     RCC_APB1_PERI_CLOCK_TIM12		        ((uint64_t)((uint64_t)BIT_6  | RCC_APB1_PERI_MASK))
#define     RCC_APB1_PERI_CLOCK_TIM13		        ((uint64_t)((uint64_t)BIT_7  | RCC_APB1_PERI_MASK))
#define     RCC_APB1_PERI_CLOCK_TIM14		        ((uint64_t)((uint64_t)BIT_8  | RCC_APB1_PERI_MASK))
#define     RCC_APB1_PERI_CLOCK_WWDG		     	((uint64_t)((uint64_t)BIT_11 | RCC_APB1_PERI_MASK))
#define     RCC_APB1_PERI_CLOCK_SPI2		 	    ((uint64_t)((uint64_t)BIT_14 | RCC_APB1_PERI_MASK))
#define     RCC_APB1_PERI_CLOCK_SPI3				((uint64_t)((uint64_t)BIT_15 | RCC_APB1_PERI_MASK))
#define     RCC_APB1_PERI_CLOCK_USART2				((uint64_t)((uint64_t)BIT_17 | RCC_APB1_PERI_MASK))
#define     RCC_APB1_PERI_CLOCK_USART3				((uint64_t)((uint64_t)BIT_18 | RCC_APB1_PERI_MASK))
#define     RCC_APB1_PERI_CLOCK_USART4			    ((uint64_t)((uint64_t)BIT_19 | RCC_APB1_PERI_MASK))
#define     RCC_APB1_PERI_CLOCK_USART5		        ((uint64_t)((uint64_t)BIT_20 | RCC_APB1_PERI_MASK))
#define     RCC_APB1_PERI_CLOCK_I2C1			    ((uint64_t)((uint64_t)BIT_21 | RCC_APB1_PERI_MASK))
#define     RCC_APB1_PERI_CLOCK_I2C2			    ((uint64_t)((uint64_t)BIT_22 | RCC_APB1_PERI_MASK))
#define     RCC_APB1_PERI_CLOCK_I2C3 		        ((uint64_t)((uint64_t)BIT_23 | RCC_APB1_PERI_MASK))
#define     RCC_APB1_PERI_CLOCK_CAN1				((uint64_t)((uint64_t)BIT_25 | RCC_APB1_PERI_MASK))
#define     RCC_APB1_PERI_CLOCK_CAN2			    ((uint64_t)((uint64_t)BIT_26 | RCC_APB1_PERI_MASK))
#define     RCC_APB1_PERI_CLOCK_PWR		            ((uint64_t)((uint64_t)BIT_28 | RCC_APB1_PERI_MASK))
#define     RCC_APB1_PERI_CLOCK_DAC		            ((uint64_t)((uint64_t)BIT_29 | RCC_APB1_PERI_MASK))

//APB2 peripheral Enable Configuration (RCC_APB2LPENR)*************************************************
#define 	RCC_APB2_PERI_MASK						((uint64_t)0x1000000000)
#define     RCC_APB2_PERI_CLOCK_TIM1				(uint64_t)((uint64_t)BIT_0  | RCC_APB2_PERI_MASK)
#define     RCC_APB2_PERI_CLOCK_TIM8				(uint64_t)((uint64_t)BIT_1  | RCC_APB2_PERI_MASK)
#define     RCC_APB2_PERI_CLOCK_USART1	            (uint64_t)((uint64_t)BIT_4  | RCC_APB2_PERI_MASK)
#define     RCC_APB2_PERI_CLOCK_USART6	            (uint64_t)((uint64_t)BIT_5  | RCC_APB2_PERI_MASK)
#define     RCC_APB2_PERI_CLOCK_ADC1				(uint64_t)((uint64_t)BIT_8  | RCC_APB2_PERI_MASK)
#define     RCC_APB2_PERI_CLOCK_ADC2				(uint64_t)((uint64_t)BIT_9  | RCC_APB2_PERI_MASK)
#define     RCC_APB2_PERI_CLOCK_ADC3				(uint64_t)((uint64_t)BIT_10 | RCC_APB2_PERI_MASK)
#define     RCC_APB2_PERI_CLOCK_SDIO				(uint64_t)((uint64_t)BIT_11 | RCC_APB2_PERI_MASK)
#define     RCC_APB2_PERI_CLOCK_SPI1				(uint64_t)((uint64_t)BIT_12 | RCC_APB2_PERI_MASK)
#define     RCC_APB2_PERI_CLOCK_SYSCFG	   	        (uint64_t)((uint64_t)BIT_14 | RCC_APB2_PERI_MASK)
#define     RCC_APB2_PERI_CLOCK_TIM9			    (uint64_t)((uint64_t)BIT_16 | RCC_APB2_PERI_MASK)
#define     RCC_APB2_PERI_CLOCK_TIM10				(uint64_t)((uint64_t)BIT_17 | RCC_APB2_PERI_MASK)
#define     RCC_APB2_PERI_CLOCK_TIM11				(uint64_t)((uint64_t)BIT_18 | RCC_APB2_PERI_MASK)

// HSE Clock ON Source Configuration********************************************************************
#define 	RCC_CLOCK_HSE				            BIT_16

// HSI Clock ON Source Configuration********************************************************************
#define 	RCC_CLOCK_HSI 				            BIT_0

// PLL Clock ON Source Configuration********************************************************************
#define 	RCC_CLOCK_PLL				            BIT_24

// LSI Clock ON Source Configuration********************************************************************
#define 	RCC_CLOCK_LSI				            BIT_1

// LSE Clock ON Source Configuration********************************************************************
#define 	RCC_CLOCK_LSE				            BIT_2

// System Clock Source Configuration********************************************************************
#define 	RCC_SYS_CLK_HSI				            BIT_CLR
#define 	RCC_SYS_CLK_HSE				            BIT_0
#define	 	RCC_SYS_CLK_PLL				            BIT_1


// MCO1 clock Source Configuration**********************************************************************
#define		RCC_MC0_1_SRC_HSI			            BIT_CLR
#define		RCC_MC0_1_SRC_LSE			            BIT_21
#define		RCC_MC0_1_SRC_HSE			            BIT_22
#define		RCC_MC0_1_SRC_PLL			            (uint32_t)(BIT_21 | BIT_22)

// MCO2 clock Source Configuration**********************************************************************
#define		RCC_MC0_2_SRC_SYSCLK		            BIT_0
#define		RCC_MC0_2_SRC_PLLI2S		            BIT_30
#define		RCC_MC0_2_SRC_HSE			            BIT_31
#define		RCC_MC0_2_SRC_PLL			            (uint32_t)(BIT_30 | BIT_31)

// MCO1 clock Prescaler Configuration*******************************************************************
#define     RCC_MCO1PRE_2				            BIT_26
#define     RCC_MCO1PRE_3				            (uint32_t)(BIT_24 | BIT_26)
#define     RCC_MCO1PRE_4				            (uint32_t)(BIT_25 | BIT_26)
#define     RCC_MCO1PRE_5				            (uint32_t)(BIT_24 | BIT_25 | BIT_26)

// MCO2 clock Prescaler Configuration*******************************************************************
#define     RCC_MCO2PRE_2				            BIT_29
#define     RCC_MCO2PRE_3				            (uint32_t)(BIT_27 | BIT_29)
#define     RCC_MCO2PRE_4				            (uint32_t)(BIT_28 | BIT_29)
#define     RCC_MCO2PRE_5				            (uint32_t)(BIT_27 | BIT_28 | BIT_29)

// P parameter in PLL Configuration*********************************************************************
#define 	RCC_PLL_P_2  				            (uint32_t)0
#define 	RCC_PLL_P_4  				            (uint32_t)1
#define 	RCC_PLL_P_6  				            (uint32_t)2
#define 	RCC_PLL_P_8  				            (uint32_t)3

// PLL Clock Source parameter in PLL Configuration******************************************************
#define		RCC_PLL_SRC_HSI				            (uint32_t)0
#define		RCC_PLL_SRC_HSE				            (uint32_t)1


// AHB Bus Prescaler Configuration**********************************************************************
#define		RCC_AHB_PRE_1				            (uint32_t)(BIT_4 | BIT_5 | BIT_6)
#define 	RCC_AHB_PRE_2				            BIT_7
#define 	RCC_AHB_PRE_4				            (uint32_t)(BIT_4 | BIT_7)
#define 	RCC_AHB_PRE_8				            (uint32_t)(BIT_5 | BIT_7)
#define 	RCC_AHB_PRE_16				            (uint32_t)(BIT_4 | BIT_5 | BIT_7)
#define 	RCC_AHB_PRE_64				            (uint32_t)(BIT_6 | BIT_7)
#define 	RCC_AHB_PRE_128				            (uint32_t)(BIT_4 | BIT_6 | BIT_7)
#define 	RCC_AHB_PRE_256				            (uint32_t)(BIT_5 | BIT_6 | BIT_7)
#define 	RCC_AHB_PRE_512				            (uint32_t)(BIT_4 | BIT_5 | BIT_6 | BIT_7)

// APB1 Bus Prescaler Configuration*********************************************************************
#define		RCC_APB1_PRE_1				            (uint32_t)(BIT_10 | BIT_11)
#define		RCC_APB1_PRE_2				            BIT_12
#define		RCC_APB1_PRE_4				            (uint32_t)(BIT_10 | BIT_12)
#define		RCC_APB1_PRE_8				            (uint32_t)(BIT_11 | BIT_12)
#define		RCC_APB1_PRE_16				            (uint32_t)(BIT_10 | BIT_11 | BIT_12)

// APB2 Bus Prescaler Configuration*********************************************************************
#define		RCC_APB2_PRE_1				            (uint32_t)(BIT_13 | BIT_14)
#define		RCC_APB2_PRE_2				            BIT_15
#define		RCC_APB2_PRE_4				            (uint32_t)(BIT_13 | BIT_15)
#define		RCC_APB2_PRE_8				            (uint32_t)(BIT_14 | BIT_15)
#define		RCC_APB2_PRE_16				            (uint32_t)(BIT_13 | BIT_14 | BIT_15)




/* Public Function: Rcc_SetClock_Status												 			  	*
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
 ***************************************************************************************************/
uint8_t Rcc_SetClock_Status( uint32_t clock, uint32_t status);


/* Public Function: Rcc_AHB1_PeriClockStatus										   				*
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
 ****************************************************************************************************/
uint8_t Rcc_AHB1_PeriClockStatus(uint64_t peri ,uint32_t status);


/* Public Function: Rcc_AHB2_PeriClockStatus				   								         *
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
 ******************************************************************************************************/
uint8_t Rcc_AHB2_PeriClockStatus(uint64_t peri ,uint32_t status);


/* Public Function: Rcc_AHB3_PeriClockStatus										   				   *
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
 ********************************************************************************************************/
uint8_t Rcc_AHB3_PeriClockStatus(uint64_t peri ,uint32_t status);


/* Public Function: Rcc_APB1_PeriClockStatus				    									     *
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
 ********************************************************************************************************/
uint8_t Rcc_APB1_PeriClockStatus(uint64_t peri ,uint32_t status);


/* Public Function: Rcc_APB2_PeriClockStatus										   					*
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
 *********************************************************************************************************/
uint8_t Rcc_APB2_PeriClockStatus(uint64_t peri ,uint32_t status);


/* Public Function:  RCC_SelectSysClk												   					  *
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
 **********************************************************************************************************/
uint8_t Rcc_SelectSysClk(uint32_t sysclk);


typedef struct {
	uint32_t  PLL_M   ;
	uint32_t  PLL_N   ;
	uint32_t  PLL_P   ;
	uint32_t  PLL_src ;
	uint32_t  PLL_Q   ;
}PLLcfg_t;

/* Public Function:  RCC_ConfigurePLL																	   *
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
 ***********************************************************************************************************/
uint8_t	Rcc_ConfigurePLL(PLLcfg_t *pllcfg);


/* Public Function:  Rcc_GetCurrrentSysClk_Frequency								   						*
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
 *************************************************************************************************************/
uint8_t	Rcc_GetCurrrentSysClk_Frequency(uint32_t *ClkFreq);


/* Public Function:  Rcc_SetMco_Clock												 					  	  *
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
 ***************************************************************************************************************/
uint8_t Rcc_SetMco_Clock(uint32_t Mco_ClkSrc ,uint32_t Mco_Pre);


/* Public Function:  Rcc_SetBus_Prescaler																	    *
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
uint8_t Rcc_SetBus_Prescaler(uint32_t Bus);

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
uint8_t Rcc_GetAHB_Prescaler(uint16_t* Rcc_AHB_Pre);


#endif /* RCC_INT_H_ */
