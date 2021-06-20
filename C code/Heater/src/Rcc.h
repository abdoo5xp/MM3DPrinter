/*
 * Rcc.h
 *
 *  Created on: Jan 29, 2021
 *      Author: abdoo
 */

#ifndef RCC_H_
#define RCC_H_
/*we could have used */
/*oscillators values */
#define RCC_HSE_OSC			8
#define RCC_HSI_OSC			16

/*System Clock Macros*/
#define RCC_HSI		    (uint32_t)0
#define RCC_HSE		    BIT_MASK_0
#define RCC_PLL		    BIT_MASK_1
/*Note we could have used a uint64_t for these macros and use the last 3 bits to differentiate between them
 * we would only need to cast them to uint32_t when assigning them to any register value
 *   */

/*Clock Control Macros */
#define RCC_HSI_ON		                        BIT_MASK_0
#define RCC_HSI_OFF		                        BIT_MASK_CLEAR_0
#define RCC_HSE_ON		                        BIT_MASK_16
#define RCC_HSE_OFF		                        BIT_MASK_CLEAR_16
#define RCC_PLL_ON		                        BIT_MASK_24
#define RCC_PLL_OFF		                        BIT_MASK_CLEAR_24
/*These are not the real values that turns them but i had to do it because they conflict with HSI */
#define RCC_LSI_ON		                        BIT_MASK_1
#define RCC_LSI_OFF		                        BIT_MASK_CLEAR_1
#define RCC_LSE_ON		                        BIT_MASK_2
#define RCC_LSE_OFF								BIT_MASK_CLEAR_2
//res: 29 ->1 ,the rest are zeros
/*PLL SRC config */
#define RCC_PLL_SRC_HSI			                (uint32_t)0
#define RCC_PLL_SRC_HSE			                BIT_MASK_0

/*PLLI2S SRC config */
#define RCC_PLLI2S_SRC_HSI		                BIT_MASK_CLEAR_22
#define RCC_PLLI2S_SRC_HSE		                BIT_MASK_22

	/*MCO Config*/
#define RCC_MCO1_SRC_HSI			           (uint32_t)0
#define RCC_MCO1_SRC_HSE			           (BIT_MASK_22)
#define RCC_MCO1_SRC_PLL			           (BIT_MASK_22 |BIT_MASK_21)
#define RCC_MCO1_SRC_LSE			           (BIT_MASK_21)

#define RCC_MCO2_SRC_SYSCLK			           (uint32_t)0
#define RCC_MCO2_SRC_HSE			           (BIT_MASK_31)
#define RCC_MCO2_SRC_PLL			           (BIT_MASK_31 |BIT_MASK_30)
#define RCC_MCO2_SRC_PLLI2S			           (BIT_MASK_30)

#define RCC_MCO1_NO_PRE				           (uint32_t)0
#define RCC_MCO1_PRE_DIV_2			           (BIT_MASK_26)
#define RCC_MCO1_PRE_DIV_3			           (BIT_MASK_26 | BIT_MASK_24)
#define RCC_MCO1_PRE_DIV_4			           (BIT_MASK_26 | BIT_MASK_25)
#define RCC_MCO1_PRE_DIV_5			           (BIT_MASK_26 | BIT_MASK_25 | BIT_MASK_24)

#define RCC_MCO2_NO_PRE				           (uint32_t)0
#define RCC_MCO2_PRE_DIV_2			           (BIT_MASK_29)
#define RCC_MCO2_PRE_DIV_3			           (BIT_MASK_29 | BIT_MASK_27)
#define RCC_MCO2_PRE_DIV_4			           (BIT_MASK_29 | BIT_MASK_28)
#define RCC_MCO2_PRE_DIV_5			           (BIT_MASK_29 | BIT_MASK_28 | BIT_MASK_27)

#define RCC_MCO1_Config				           (BIT_MASK_1)
#define RCC_MCO2_Config				           (BIT_MASK_2)
#define RCC_MCO1_AND_MCO2_Config			   (BIT_MASK_1 | BIT_MASK_2)

			/*PERIPHERALS CONTROL MACROS */
#define  RCC_AHB1_PREPH_GPIOA 				   ((uint32_t)BIT_MASK_0 )
#define  RCC_AHB1_PREPH_GPIOB				   ((uint32_t)BIT_MASK_1 )
#define  RCC_AHB1_PREPH_GPIOC				   ((uint32_t)BIT_MASK_2 )
#define  RCC_AHB1_PREPH_GPIOD				   ((uint32_t)BIT_MASK_3 )
#define  RCC_AHB1_PREPH_GPIOE				   ((uint32_t)BIT_MASK_4 )
#define  RCC_AHB1_PREPH_GPIOF				   ((uint32_t)BIT_MASK_5 )
#define  RCC_AHB1_PREPH_GPIOG				   ((uint32_t)BIT_MASK_6 )
#define  RCC_AHB1_PREPH_GPIOH				   ((uint32_t)BIT_MASK_7 )
#define  RCC_AHB1_PREPH_GPIOI				   ((uint32_t)BIT_MASK_8 )
#define  RCC_AHB1_PREPH_CRC					   ((uint32_t)BIT_MASK_12)
#define  RCC_AHB1_PREPH_BKPSRAM				   ((uint32_t)BIT_MASK_18)
#define  RCC_AHB1_PREPH_CCMDATARAM			   ((uint32_t)BIT_MASK_20)
#define  RCC_AHB1_PREPH_DMA1				   ((uint32_t)BIT_MASK_21)
#define  RCC_AHB1_PREPH_DMA2				   ((uint32_t)BIT_MASK_22)
#define  RCC_AHB1_PREPH_ETHMAC				   ((uint32_t)BIT_MASK_25)
#define  RCC_AHB1_PREPH_ETHMACTEX			   ((uint32_t)BIT_MASK_26)
#define  RCC_AHB1_PREPH_ETHMACRX			   ((uint32_t)BIT_MASK_27)
#define  RCC_AHB1_PREPH_ETHMACPTP		       ((uint32_t)BIT_MASK_28)
#define  RCC_AHB1_PREPH_OTGHS				   ((uint32_t)BIT_MASK_29)
#define  RCC_AHB1_PREPH_OTGHSULPI		       ((uint32_t)BIT_MASK_30)

//AHB2 peripheral (RCC_AHB2EBR)
#define  RCC_AHB2_PREPH_DCMI 				   ((uint32_t)BIT_MASK_0)
#define  RCC_AHB2_PREPH_CRYP			       ((uint32_t)BIT_MASK_4)
#define  RCC_AHB2_PREPH_HASH				   ((uint32_t)BIT_MASK_5)
#define  RCC_AHB2_PREPH_RNG					   ((uint32_t)BIT_MASK_6)
#define  RCC_AHB2_PREPH_OTGFS				   ((uint32_t)BIT_MASK_7)

//AHB3 peripheral (RCC_AHB3EBR)
#define RCC_AHB3_PREPH_FSMCEN				   ((uint32_t)BIT_MASK_0)

//APB1 peripheral (RCC_APB1EBR)
#define  RCC_APB1_PREPH_TIM2				   ((uint32_t)BIT_MASK_0  )
#define  RCC_APB1_PREPH_TIM3				   ((uint32_t)BIT_MASK_1  )
#define  RCC_APB1_PREPH_TIM4				   ((uint32_t)BIT_MASK_2  )
#define  RCC_APB1_PREPH_TIM5				   ((uint32_t)BIT_MASK_3  )
#define  RCC_APB1_PREPH_TIM6				   ((uint32_t)BIT_MASK_4  )
#define  RCC_APB1_PREPH_TIM7				   ((uint32_t)BIT_MASK_5  )
#define  RCC_APB1_PREPH_TIM12				   ((uint32_t)BIT_MASK_6  )
#define  RCC_APB1_PREPH_TIM13				   ((uint32_t)BIT_MASK_7  )
#define  RCC_APB1_PREPH_TIM14				   ((uint32_t)BIT_MASK_8  )
#define  RCC_APB1_PREPH_WWDG		     	   ((uint32_t)BIT_MASK_11 )
#define  RCC_APB1_PREPH_SPI2			 	   ((uint32_t)BIT_MASK_14 )
#define  RCC_APB1_PREPH_SPI3				   ((uint32_t)BIT_MASK_15 )
#define  RCC_APB1_PREPH_USART2				   ((uint32_t)BIT_MASK_17 )
#define  RCC_APB1_PREPH_USART3				   ((uint32_t)BIT_MASK_18 )
#define  RCC_APB1_PREPH_USART4			       ((uint32_t)BIT_MASK_19 )
#define  RCC_APB1_PREPH_USART5		           ((uint32_t)BIT_MASK_20 )
#define  RCC_APB1_PREPH_I2C1			       ((uint32_t)BIT_MASK_21 )
#define  RCC_APB1_PREPH_I2C2			 	   ((uint32_t)BIT_MASK_22 )
#define  RCC_APB1_PREPH_I2C3 		           ((uint32_t)BIT_MASK_23 )
#define  RCC_APB1_PREPH_CAN1				   ((uint32_t)BIT_MASK_25 )
#define  RCC_APB1_PREPH_CAN2				   ((uint32_t)BIT_MASK_26 )
#define  RCC_APB1_PREPH_PWR			           ((uint32_t)BIT_MASK_28 )
#define  RCC_APB1_PREPH_DAC			           ((uint32_t)BIT_MASK_29 )


//APB2 peripheral (RCC_APB2EBR)                             MASK_
#define  RCC_APB2_PREPH_TIM1				   ((uint32_t)BIT_MASK_0 )
#define  RCC_APB2_PREPH_TIM8				   ((uint32_t)BIT_MASK_1 )
#define  RCC_APB2_PREPH_USART1				   ((uint32_t)BIT_MASK_4 )
#define  RCC_APB2_PREPH_USART6				   ((uint32_t)BIT_MASK_5 )
#define  RCC_APB2_PREPH_ADC1				   ((uint32_t)BIT_MASK_8 )
#define  RCC_APB2_PREPH_ADC2				   ((uint32_t)BIT_MASK_9 )
#define  RCC_APB2_PREPH_ADC3				   ((uint32_t)BIT_MASK_10)
#define  RCC_APB2_PREPH_SDIO				   ((uint32_t)BIT_MASK_11)
#define  RCC_APB2_PREPH_SPI1				   ((uint32_t)BIT_MASK_12)
#define  RCC_APB2_PREPH_SYSCFG	   	           ((uint32_t)BIT_MASK_14)
#define  RCC_APB2_PREPH_TIM9				   ((uint32_t)BIT_MASK_16)
#define  RCC_APB2_PREPH_TIM10				   ((uint32_t)BIT_MASK_17)
#define  RCC_APB2_PREPH_TIM11				   ((uint32_t)BIT_MASK_18)

#define  RCC_PREPH_ENABLE					  	   ((uint8_t) 1)
#define  RCC_PREPH_DISABLE                  	   ((uint8_t) 0)

									/*MACROS FOR BUSES PRESCALERS ADJUSTMENT */
#define RCC_AHB_PRE_CLEAR_MASK				   ((uint32_t) BIT_MASK_CLEAR_4 & BIT_MASK_CLEAR_5 & BIT_MASK_CLEAR_6 & BIT_MASK_CLEAR_7)
#define RCC_AHB_PRE_NO_DIV					   ((uint32_t) 0)
#define RCC_AHB_PRE_DIV_2					   ((uint32_t) BIT_MASK_7)
#define RCC_AHB_PRE_DIV_4					   ((uint32_t) BIT_MASK_7 | BIT_MASK_4 )
#define RCC_AHB_PRE_DIV_8					   ((uint32_t) BIT_MASK_7 | BIT_MASK_5 )
#define RCC_AHB_PRE_DIV_16					   ((uint32_t) BIT_MASK_7 | BIT_MASK_4 | BIT_MASK_5 )
#define RCC_AHB_PRE_DIV_64					   ((uint32_t) BIT_MASK_7 | BIT_MASK_6 )
#define RCC_AHB_PRE_DIV_128					   ((uint32_t) BIT_MASK_7 | BIT_MASK_6 | BIT_MASK_4 )
#define RCC_AHB_PRE_DIV_256					   ((uint32_t) BIT_MASK_7 | BIT_MASK_6 | BIT_MASK_5 )
#define RCC_AHB_PRE_DIV_512					   ((uint32_t) BIT_MASK_7 | BIT_MASK_6 | BIT_MASK_5 | BIT_MASK_4)
									//i used this reserved  bit to differentiate between AHB & APB1 & APB2
#define RCC_APB1_PRE_CLEAR_MASK				   ((uint32_t) BIT_MASK_CLEAR_12 & BIT_MASK_CLEAR_11 & BIT_MASK_CLEAR_10 )
#define RCC_APB1_PRE_NO_DIV					   ((uint32_t) BIT_MASK_8 )
#define RCC_APB1_PRE_DIV_2					   ((uint32_t) BIT_MASK_8 | BIT_MASK_12 )
#define RCC_APB1_PRE_DIV_4					   ((uint32_t) BIT_MASK_8 | BIT_MASK_12 | BIT_MASK_10)
#define RCC_APB1_PRE_DIV_8					   ((uint32_t) BIT_MASK_8 | BIT_MASK_12 | BIT_MASK_11 )
#define RCC_APB1_PRE_DIV_16					   ((uint32_t) BIT_MASK_8 | BIT_MASK_12 | BIT_MASK_11 | BIT_MASK_10 )
									//i used this reserved  bit to differentiate between AHB & APB1 & APB2
#define RCC_APB2_PRE_CLEAR_MASK				   ((uint32_t) BIT_MASK_CLEAR_15 & BIT_MASK_CLEAR_14 & BIT_MASK_CLEAR_13 )
#define RCC_APB2_PRE_NO_DIV					   ((uint32_t) BIT_MASK_9 )
#define RCC_APB2_PRE_DIV_2					   ((uint32_t) BIT_MASK_9 | BIT_MASK_15 )
#define RCC_APB2_PRE_DIV_4					   ((uint32_t) BIT_MASK_9 | BIT_MASK_15 | BIT_MASK_13)
#define RCC_APB2_PRE_DIV_8					   ((uint32_t) BIT_MASK_9 | BIT_MASK_15 | BIT_MASK_14 )
#define RCC_APB2_PRE_DIV_16					   ((uint32_t) BIT_MASK_9 | BIT_MASK_15 | BIT_MASK_14 | BIT_MASK_13 )
									//BUS MACROS to get current bus prescaler
#define RCC_AHB_BUS			                   ((uint32_t) BIT_MASK_4 |BIT_MASK_5 |BIT_MASK_6 |BIT_MASK_7)
#define RCC_APB1_BUS 		                   ((uint32_t) BIT_MASK_10 |BIT_MASK_11 |BIT_MASK_12 )
#define RCC_APB2_BUS 		                   ((uint32_t) BIT_MASK_13 |BIT_MASK_14 |BIT_MASK_15 )

typedef struct {
	uint32_t pll_Src;
	uint32_t pll_M;
	uint32_t pll_N;
	uint32_t pll_P;
	uint32_t pll_Q;
}RCC_pllConfig_t;

typedef struct {
	uint32_t mco1_src;
	uint32_t mco1_pre;
	uint32_t mco2_src;
	uint32_t mco2_pre;
	uint32_t mco_config;
}RCC_mcoConfig_t;





/* **************************************************************************************************************
 * Public Function: RCC_ControlClk
 * Description: This function is used to turn the RCC clocks ON/OFF
 * Input Parameters:
 * 					-uint32_t RCC_Clk_Ctrl : in range { RCC_HSI_ON,RCC_HSI_OFF,
 *                                                      RCC_HSE_ON,RCC_HSE_OFF,
 *			                                            RCC_PLL_ON,RCC_PLL_OFF,
 * 											            RCC_LSI_ON,RCC_LSI_OFF,
 *                                                      RCC_LSE_ON,RCC_LSE_OFF }
 * Return:           -uint8_t : in range {  RT_PARAM,
 *											RT_ERROR,
 *											RT_SUCCESS }
 *
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
uint8_t RCC_ControlClk(uint32_t RCC_Clk_Ctrl);

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
uint8_t RCC_SelectSysClk(uint32_t RCC_Clk);

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
uint8_t RCC_ConfigPll(RCC_pllConfig_t * RCC_PllConfig);

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
uint8_t RCC_GetCurrentSysClkFreq(uint32_t* CurrentSysClkFreq);

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
uint8_t RCC_SetMCOClk(RCC_mcoConfig_t* RCC_mcoConfig );

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
uint8_t RCC_ControlAHB1PeriClk(uint32_t RCC_AHB1Perph,uint8_t Status);

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
uint8_t RCC_ControlAHB2PeriClk(uint32_t RCC_AHB2Perph,uint8_t Status);

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
uint8_t RCC_ControlAHB3PeriClk(uint32_t RCC_AHB3Perph,uint8_t Status);

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
uint8_t RCC_ControlAPB1PeriClk(uint32_t RCC_APB1Perph,uint8_t Status);

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
uint8_t RCC_ControlAPB2PeriClk(uint32_t RCC_APB2Perph,uint8_t Status);

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
uint8_t RCC_SetBusPrescaler(uint32_t RCC_bus_prescaler);

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
uint8_t RCC_GetBusPrescaler(uint32_t RCC_bus,uint32_t* RCC_bus_prescaler);
#endif /* RCC_H_ */
