/*
 * NVIC.h
 *
 *  Created on: Feb 22, 2021
 *      Author: abdoo
 */

#ifndef NVIC_H_
#define NVIC_H_

typedef enum
{
/******  Cortex-M4 Processor Exceptions Numbers ****************************************************************/
//  NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                                          */
//  MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M4 Memory Management Interrupt                           */
//  BusFault_IRQn               = -11,    /*!< 5 Cortex-M4 Bus Fault Interrupt                                   */
//  UsageFault_IRQn             = -10,    /*!< 6 Cortex-M4 Usage Fault Interrupt                                 */
//  SVCall_IRQn                 = -5,     /*!< 11 Cortex-M4 SV Call Interrupt                                    */
//  DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M4 Debug Monitor Interrupt                              */
//  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M4 Pend SV Interrupt                                    */
//  SysTick_IRQn                = -1,     /*!< 15 Cortex-M4 System Tick Interrupt                                */
/******  STM32 specific Interrupt Numbers **********************************************************************/
  _WWDG_IRQn                   = 0,      /*!< Window WatchDog Interrupt                                         */
  _PVD_IRQn                    = 1,      /*!< PVD through EXTI Line detection Interrupt                         */
  _TAMP_STAMP_IRQn             = 2,      /*!< Tamper and TimeStamp interrupts through the EXTI line             */
  _RTC_WKUP_IRQn               = 3,      /*!< RTC Wakeup interrupt through the EXTI line                        */
  _FLASH_IRQn                  = 4,      /*!< FLASH global Interrupt                                            */
  _RCC_IRQn                    = 5,      /*!< RCC global Interrupt                                              */
  _EXTI0_IRQn                  = 6,      /*!< EXTI Line0 Interrupt                                              */
  _EXTI1_IRQn                  = 7,      /*!< EXTI Line1 Interrupt                                              */
  _EXTI2_IRQn                  = 8,      /*!< EXTI Line2 Interrupt                                              */
  _EXTI3_IRQn                  = 9,      /*!< EXTI Line3 Interrupt                                              */
  _EXTI4_IRQn                  = 10,     /*!< EXTI Line4 Interrupt                                              */
  _DMA1_Stream0_IRQn           = 11,     /*!< DMA1 Stream 0 global Interrupt                                    */
  _DMA1_Stream1_IRQn           = 12,     /*!< DMA1 Stream 1 global Interrupt                                    */
  _DMA1_Stream2_IRQn           = 13,     /*!< DMA1 Stream 2 global Interrupt                                    */
  _DMA1_Stream3_IRQn           = 14,     /*!< DMA1 Stream 3 global Interrupt                                    */
  _DMA1_Stream4_IRQn           = 15,     /*!< DMA1 Stream 4 global Interrupt                                    */
  _DMA1_Stream5_IRQn           = 16,     /*!< DMA1 Stream 5 global Interrupt                                    */
  _DMA1_Stream6_IRQn           = 17,     /*!< DMA1 Stream 6 global Interrupt                                    */
  _ADC_IRQn                    = 18,     /*!< ADC1, ADC2 and ADC3 global Interrupts                             */
  _CAN1_TX_IRQn                = 19,     /*!< CAN1 TX Interrupt                                                 */
  _CAN1_RX0_IRQn               = 20,     /*!< CAN1 RX0 Interrupt                                                */
  _CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                                */
  _CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                                */
  _EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                                     */
  _TIM1_BRK_TIM9_IRQn          = 24,     /*!< TIM1 Break interrupt and TIM9 global interrupt                    */
  _TIM1_UP_TIM10_IRQn          = 25,     /*!< TIM1 Update Interrupt and TIM10 global interrupt                  */
  _TIM1_TRG_COM_TIM11_IRQn     = 26,     /*!< TIM1 Trigger and Commutation Interrupt and TIM11 global interrupt */
  _TIM1_CC_IRQn                = 27,     /*!< TIM1 Capture Compare Interrupt                                    */
  _TIM2_IRQn                   = 28,     /*!< TIM2 global Interrupt                                             */
  _TIM3_IRQn                   = 29,     /*!< TIM3 global Interrupt                                             */
  _TIM4_IRQn                   = 30,     /*!< TIM4 global Interrupt                                             */
  _I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                              */
  _I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                              */
  _I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                              */
  _I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                              */
  _SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                             */
  _SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                             */
  _USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                                           */
  _USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                                           */
  _USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                                           */
  _EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                                   */
  _RTC_Alarm_IRQn              = 41,     /*!< RTC Alarm (A and B) through EXTI Line Interrupt                   */
  _OTG_FS_WKUP_IRQn            = 42,     /*!< USB OTG FS Wakeup through EXTI line interrupt                     */
  _TIM8_BRK_TIM12_IRQn         = 43,     /*!< TIM8 Break Interrupt and TIM12 global interrupt                   */
  _TIM8_UP_TIM13_IRQn          = 44,     /*!< TIM8 Update Interrupt and TIM13 global interrupt                  */
  _TIM8_TRG_COM_TIM14_IRQn     = 45,     /*!< TIM8 Trigger and Commutation Interrupt and TIM14 global interrupt */
  _TIM8_CC_IRQn                = 46,     /*!< TIM8 Capture Compare Interrupt                                    */
  _DMA1_Stream7_IRQn           = 47,     /*!< DMA1 Stream7 Interrupt                                            */
  _FSMC_IRQn                   = 48,     /*!< FSMC global Interrupt                                             */
  _SDIO_IRQn                   = 49,     /*!< SDIO global Interrupt                                             */
  _TIM5_IRQn                   = 50,     /*!< TIM5 global Interrupt                                             */
  _SPI3_IRQn                   = 51,     /*!< SPI3 global Interrupt                                             */
  _UART4_IRQn                  = 52,     /*!< UART4 global Interrupt                                            */
  _UART5_IRQn                  = 53,     /*!< UART5 global Interrupt                                            */
  _TIM6_DAC_IRQn               = 54,     /*!< TIM6 global and DAC1&2 underrun error  interrupts                 */
  _TIM7_IRQn                   = 55,     /*!< TIM7 global interrupt                                             */
  _DMA2_Stream0_IRQn           = 56,     /*!< DMA2 Stream 0 global Interrupt                                    */
  _DMA2_Stream1_IRQn           = 57,     /*!< DMA2 Stream 1 global Interrupt                                    */
  _DMA2_Stream2_IRQn           = 58,     /*!< DMA2 Stream 2 global Interrupt                                    */
  _DMA2_Stream3_IRQn           = 59,     /*!< DMA2 Stream 3 global Interrupt                                    */
  _DMA2_Stream4_IRQn           = 60,     /*!< DMA2 Stream 4 global Interrupt                                    */
  _ETH_IRQn                    = 61,     /*!< Ethernet global Interrupt                                         */
  _ETH_WKUP_IRQn               = 62,     /*!< Ethernet Wakeup through EXTI line Interrupt                       */
  _CAN2_TX_IRQn                = 63,     /*!< CAN2 TX Interrupt                                                 */
  _CAN2_RX0_IRQn               = 64,     /*!< CAN2 RX0 Interrupt                                                */
  _CAN2_RX1_IRQn               = 65,     /*!< CAN2 RX1 Interrupt                                                */
  _CAN2_SCE_IRQn               = 66,     /*!< CAN2 SCE Interrupt                                                */
  _OTG_FS_IRQn                 = 67,     /*!< USB OTG FS global Interrupt                                       */
  _DMA2_Stream5_IRQn           = 68,     /*!< DMA2 Stream 5 global interrupt                                    */
  _DMA2_Stream6_IRQn           = 69,     /*!< DMA2 Stream 6 global interrupt                                    */
  _DMA2_Stream7_IRQn           = 70,     /*!< DMA2 Stream 7 global interrupt                                    */
  _USART6_IRQn                 = 71,     /*!< USART6 global interrupt                                           */
  _I2C3_EV_IRQn                = 72,     /*!< I2C3 event interrupt                                              */
  _I2C3_ER_IRQn                = 73,     /*!< I2C3 error interrupt                                              */
  _OTG_HS_EP1_OUT_IRQn         = 74,     /*!< USB OTG HS End Point 1 Out global interrupt                       */
  _OTG_HS_EP1_IN_IRQn          = 75,     /*!< USB OTG HS End Point 1 In global interrupt                        */
  _OTG_HS_WKUP_IRQn            = 76,     /*!< USB OTG HS Wakeup through EXTI interrupt                          */
  _OTG_HS_IRQn                 = 77,     /*!< USB OTG HS global interrupt                                       */
  _DCMI_IRQn                   = 78,     /*!< DCMI global interrupt                                             */
  _HASH_RNG_IRQn               = 80,     /*!< Hash and RNG global interrupt                                     */
  _FPU_IRQn                    = 81      /*!< FPU global interrupt
                                          */
} irqn_t;

/* 0000 0000
 *
 * implemented 4 -> 7*/
#define NVIC_PRIO_0				(uint8_t) 0x00
#define NVIC_PRIO_1				(uint8_t) 0x10
#define NVIC_PRIO_2				(uint8_t) 0x20
#define NVIC_PRIO_3				(uint8_t) 0x30
#define NVIC_PRIO_4				(uint8_t) 0x40
#define NVIC_PRIO_5				(uint8_t) 0x50
#define NVIC_PRIO_6				(uint8_t) 0x60
#define NVIC_PRIO_7				(uint8_t) 0x70
#define NVIC_PRIO_8				(uint8_t) 0x80
#define NVIC_PRIO_9				(uint8_t) 0x90
#define NVIC_PRIO_10			(uint8_t) 0xA0
#define NVIC_PRIO_11			(uint8_t) 0xB0
#define NVIC_PRIO_12			(uint8_t) 0xC0
#define NVIC_PRIO_13			(uint8_t) 0xD0
#define NVIC_PRIO_14			(uint8_t) 0xE0
#define NVIC_PRIO_15			(uint8_t) 0xF0


#define NVIC_GROUP_0			(uint32_t)0x5FA00000
#define NVIC_GROUP_1			(uint32_t)0x5FA00100
#define NVIC_GROUP_2			(uint32_t)0x5FA00200
#define NVIC_GROUP_3			(uint32_t)0x5FA00300
#define NVIC_GROUP_4			(uint32_t)0x5FA00400
#define NVIC_GROUP_5			(uint32_t)0x5FA00500
#define NVIC_GROUP_6			(uint32_t)0x5FA00600
#define NVIC_GROUP_7			(uint32_t)0x5FA00700


/*This function is used to Clear the PRIMASK which enables all the IRQs*/
void NVIC_EnableAll();

/*This function is used to Set the PRIMASK which disables all the IRQs*/
void NVIC_DisableAll();

/* **************************************************************************************************************
 * Public Function: NVIC_EnableIntr
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
uint32_t NVIC_EnableIntr(irqn_t Nvic_Intr);

uint32_t NVIC_DisableIntr(irqn_t Nvic_Intr);

uint8_t NVIC_SetPriority(irqn_t Nvic_Intr, uint8_t Priority);

uint32_t NVIC_SetPending(irqn_t Nvic_Intr);

uint32_t NVIC_ClearPending(irqn_t Nvic_Intr);

uint32_t NVIC_SetPriorityGrouping(uint32_t PriorityGroup);

uint32_t NVIC_GetPriorityGrouping(uint32_t *PriorityGroup);

/* Here we can use this function to go to from user mode to privilage mode
 *  when we said that we need to throw an exception to switch from user mode to privilage mode  */
uint32_t NVIC_GenerateSWIntr(irqn_t Nvic_Intr);

/*range  = {0->7} */			/*0->127*/		/*0->255*/
uint32_t NVIC_EncodePriority(uint32_t PriorityGroup, uint32_t PreemptPriority,uint32_t SubPriority );

void NVIC_DecodePriority( uint8_t Priority, uint8_t PriorityGroup, uint8_t* PreemptPriority,uint8_t *SubPriority );

#endif /* NVIC_H_ */
