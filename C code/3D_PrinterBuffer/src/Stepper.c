/*
 * Stepper.c
 *
 *  Created on: Jun 20, 2021
 *      Author: Islam
 */

/*
 * Led.c
 *
 *  Created on: Feb 17, 2021
 *      Author: micro
 */

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "../../../lib/src/Bits.h"
#include "../../lib/Bit_Mask.h"
#include "../../../lib/src/Bit_Math.h"
#include "../../../lib/src/RT_Debug.h"
#include <stm32f4xx_hal.h>
#include <stm32f4xx_hal_conf.h>
#include <stm32f4xx_hal_tim.h>
#include "Gpio_int.h"
#include "Rcc_int.h"
#include "Stepper.h"
#include "Stepper_types.h"


uint64_t Stepper_Gpio[5] =
{
		RCC_AHB1_PERI_CLOCK_GPIOA ,
		RCC_AHB1_PERI_CLOCK_GPIOB,
		RCC_AHB1_PERI_CLOCK_GPIOC,
		RCC_AHB1_PERI_CLOCK_GPIOD,
		RCC_AHB1_PERI_CLOCK_GPIOE
};

uint64_t Stepper_TimerPwm[4] =
{
		RCC_APB1_PERI_CLOCK_TIM2,
		RCC_APB1_PERI_CLOCK_TIM3,
		RCC_APB1_PERI_CLOCK_TIM4,
		RCC_APB1_PERI_CLOCK_TIM5
};

PtrNotify AppNotify ;

volatile uint32_t *AppNotifyFlag  = NULL ;

uint32_t StepperWorking_Id[STEPPER_NUM];

/************************************************Stepper Speed*************************************************************/
uint32_t StepperFrequencyPeriodTicks  = STEPPER_FREQUENCY_PERIOD_TICKS ;

/*************************************************Timer Base***************************************************************/
uint32_t StepperTimerBasePeriodTicks =  0 ;//12000//6563

static TIM_HandleTypeDef    TimerBaseConfigs;
static TIM_Base_InitTypeDef TimerBaseTimerInitConfigs;
/*************************************************************************************************************************/


static RT_Debug Stepper_TimerBaseInit(void)
{
	RT_Debug Return_status;

	TimerBaseTimerInitConfigs.Prescaler     = STEPPER_TIMER_BASE_PRESCALER;
	TimerBaseTimerInitConfigs.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	TimerBaseTimerInitConfigs.CounterMode   = TIM_COUNTERMODE_UP;

	/* 84,000,000 / desired frequency */
	TimerBaseTimerInitConfigs.Period        = StepperTimerBasePeriodTicks;

	/*TimerBaseTimerInitConfigs.RepetitionCounter parameter is valid only for TIM1 and TIM8.*/


	TimerBaseConfigs.Channel  =             HAL_TIM_ACTIVE_CHANNEL_1;
	TimerBaseConfigs.Instance =             TIM12_BASE;
	TimerBaseConfigs.Lock     =             HAL_UNLOCKED;
	TimerBaseConfigs.State    =             HAL_TIM_STATE_RESET;
	TimerBaseConfigs.Init     =             TimerBaseTimerInitConfigs;

	Return_status   =    HAL_TIM_Base_Init(&TimerBaseConfigs);
	trace_printf("HAL_TIM_Base_Init = %d\n",Return_status);

	//TIM_Base_SetConfig already exist inside 'HAL_TIM_Base_Init' function implementation
	return Return_status;
}


/* disables both the interrupt then the periperal*/
//static RT_Debug Stepper_TimerBaseStop_INT(void)
//{
//	RT_Debug Return_status;
//	Return_status = HAL_TIM_Base_Stop_IT(&TimerBaseConfigs); //passing htim pointer to struct
//	//trace_printf("HAL_TIM_Base_Stop_IT = %d\n",Return_status);
//
//	return Return_status;
//}



static RT_Debug Stepper_TimerPwmInit(void)
{
	RT_Debug Return_status;

	for (uint8_t Stepper_Idx = 0 ; Stepper_Idx < STEPPER_NUM ; Stepper_Idx++)
	{
		Return_status = HAL_TIM_PWM_Init(&StepperChannelcfg[Stepper_Idx].StepperConfigs);
		trace_printf("HAL_TIM_PWM_Init = %d\n",Return_status);

		Return_status |= HAL_TIM_PWM_ConfigChannel(&StepperChannelcfg[Stepper_Idx].StepperConfigs, &StepperChannelcfg[Stepper_Idx].StepperOCInitConfigs, StepperChannelcfg[Stepper_Idx].StepperChannel);
		trace_printf("HAL_TIM_PWM_ConfigChannel = %d\n",Return_status);
	}

	return Return_status;
}

extern RT_Debug Stepper_Continue(void)
{
	RT_Debug Return_status;


	/********************************************************Timer Base Start********************************************************************/
	(TimerBaseConfigs.Instance->SR) &= ~(TIM_IT_UPDATE);
	Return_status = HAL_TIM_Base_Start_IT(&TimerBaseConfigs);//passing htim pointer to struct

	/*****************PWM Start******************************************************************************************************************/
	for(uint32_t Stepper_Idx = 0  ; Stepper_Idx < STEPPER_NUM ; Stepper_Idx++)
	{
		if (StepperWorking_Id[Stepper_Idx] == Stepper_Working)
		{
			trace_printf("PWM_Stop = %d\n",HAL_TIM_PWM_Start(&StepperChannelcfg[Stepper_Idx].StepperConfigs,StepperChannelcfg[Stepper_Idx].StepperChannel));
			trace_printf("StepperId = %d\n",Stepper_Idx);
		}
	}

	return Return_status;
}


extern RT_Debug Stepper_Pause(void)
{
	RT_Debug Return_status;

	for(uint32_t Stepper_Idx = 0  ; Stepper_Idx < STEPPER_NUM ; Stepper_Idx++)
	{
		if (StepperWorking_Id[Stepper_Idx] == Stepper_Working)
		{
			trace_printf("PWM_Stop = %d\n",HAL_TIM_PWM_Stop(&StepperChannelcfg[Stepper_Idx].StepperConfigs,StepperChannelcfg[Stepper_Idx].StepperChannel));
			trace_printf("StepperId = %d\n",Stepper_Idx);
		}
	}
	Return_status  = HAL_TIM_Base_Stop_IT(&TimerBaseConfigs); //passing htim pointer to struct
	trace_printf("Counter= %x\n",TimerBaseConfigs.Instance->CNT);

	return Return_status;
}

/* Public Function:  Stepper_Init															      *
 * Description: This function is used to Configure Pins that connected to Stepper_Driver
 * Input parameters:
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
 **********************************************************************************************/
uint8_t Stepper_Init(){

	uint32_t Stepper_Gpio_Idx ;
	uint32_t Stepper_Timer_Idx ;

	for (uint8_t Stepper_Idx = 0 ; Stepper_Idx < STEPPER_NUM ; Stepper_Idx++)
	{
		for (uint8_t Stepper_Pin_Idx = 0 ; Stepper_Pin_Idx < STEPPER_PINS_NUM ; Stepper_Pin_Idx++)
		{
			Stepper_Gpio_Idx = (uint32_t)((uint32_t)Steppercfg[Stepper_Idx].Stepper_Pin[Stepper_Pin_Idx].Gpio_Port - (uint32_t)0x40020000) / (uint32_t)0x400;
			Stepper_Timer_Idx = (uint32_t)((uint32_t)StepperChannelcfg[Stepper_Idx].StepperConfigs.Instance - (uint32_t)0x40000000) / (uint32_t)0x400;
			Rcc_AHB1_PeriClockStatus(Stepper_Gpio[Stepper_Gpio_Idx],RCC_PERI_CLOCK_ENABLE);
			Rcc_APB1_PeriClockStatus(Stepper_TimerPwm[Stepper_Timer_Idx], RCC_PERI_CLOCK_ENABLE);
			Gpio_Init(&Steppercfg[Stepper_Idx].Stepper_Pin[Stepper_Pin_Idx]);
		}
	}

	Rcc_APB1_PeriClockStatus(RCC_APB1_PERI_CLOCK_TIM12, RCC_PERI_CLOCK_ENABLE);

	Stepper_TimerPwmInit();
	Stepper_TimerBaseInit();
	HAL_NVIC_SetPriority(TIM8_BRK_TIM12_IRQn, 1, 0);///* Set Interrupt Group Priority */
	HAL_NVIC_ClearPendingIRQ(TIM8_BRK_TIM12_IRQn);
	HAL_NVIC_EnableIRQ(TIM8_BRK_TIM12_IRQn);/* Enable the TIMx global Interrupt */

	return RT_SUCCESS ;
}



/* Public Function:  Stpper_SetStep															   *
 * Description: This function is used to Set No. of steps to Stepper
 *  * Input parameters:
 * 		- Stepper_Steps		#Number of steps
 *
 * Return:
 * 		- void
 *
 * Input/Output Parameter:
 * 		- Not Applicable
 **********************************************************************************************/
RT_Debug Stepper_StepsTime(uint32_t StepperId ,uint32_t Copy_TimerBasePeriodTicks,StepperWorking_enu Stepper_Status){

	RT_Debug Return_status = RT_SUCCESS ;

	/************************These Two lines Should be in this irder to Enable Extruder only**************************/
	StepperWorking_Id[STEPPER_NUM-1] = Stepper_Status ;
	StepperWorking_Id[StepperId] = Stepper_Working ;
	if (AppNotifyFlag)
	{
		*AppNotifyFlag = StepperAction_NotDone ;
	}


	/* 84,000,000 / desired frequency */
	trace_printf("Copy_TimerBasePeriodTicks = %d\n",Copy_TimerBasePeriodTicks);
	TimerBaseTimerInitConfigs.Period = Copy_TimerBasePeriodTicks;
	TimerBaseConfigs.Init    		 = TimerBaseTimerInitConfigs;
	Return_status   =    HAL_TIM_Base_Init(&TimerBaseConfigs);
	trace_printf("HAL_TIM_Base_Init = %d\n",Return_status);

	/********************************************************Timer Base Start********************************************************************/
	(TimerBaseConfigs.Instance->SR) &= ~(TIM_IT_UPDATE);
	Return_status = HAL_TIM_Base_Start_IT(&TimerBaseConfigs);//passing htim pointer to struct

	/*****************PWM Start******************************************************************************************************************/
	Return_status = HAL_TIM_PWM_Start(&StepperChannelcfg[StepperId].StepperConfigs,StepperChannelcfg[StepperId].StepperChannel);
	if (Stepper_Status == Stepper_Working)
	{
		Return_status = HAL_TIM_PWM_Start(&StepperChannelcfg[STEPPER_NUM-1].StepperConfigs,StepperChannelcfg[STEPPER_NUM-1].StepperChannel);
	}

	/*****************PWM Start***********************************************/
	//trace_printf("HAL_TIM_PWM_Start = %d\n",Return_status);

	return Return_status;
}

/* Public Function:  Stepper_SetSpeed															   *
 * Description: This function is used to Set Speed of Stepper
 *  * Input parameters:
 * 		- Stepper_Speed
 *
 * Return:
 * 		- void
 *
 * Input/Output Parameter:
 * 		- Not Applicable
 **********************************************************************************************/
RT_Debug Stepper_SetSpeed(uint32_t StepperId,uint32_t Stepper_Speed){

	RT_Debug Return_status = RT_SUCCESS ;

	trace_printf("Stepper_Speed =  %d\n",Stepper_Speed);
	StepperChannelcfg[StepperId].StepperTimerInitConfigs.Period = Stepper_Speed; 		/* 84,000,000 / 128 --> Ans /50 , where 50 is the desired frequency */
	trace_printf("Stepper_Speed / 2 =  %d\n",Stepper_Speed / 2 );
	StepperChannelcfg[StepperId].StepperOCInitConfigs.Pulse = Stepper_Speed / 2;

	StepperChannelcfg[StepperId].StepperConfigs.Init = StepperChannelcfg[StepperId].StepperTimerInitConfigs;


	Return_status = HAL_TIM_PWM_Init(&StepperChannelcfg[StepperId].StepperConfigs);
	trace_printf("HAL_TIM_PWM_Init = %d\n",Return_status);

	Return_status |= HAL_TIM_PWM_ConfigChannel(&StepperChannelcfg[StepperId].StepperConfigs, &StepperChannelcfg[StepperId].StepperOCInitConfigs, StepperChannelcfg[StepperId].StepperChannel);
	trace_printf("HAL_TIM_PWM_ConfigChannel = %d\n",Return_status);
	return Return_status;
}

/* Public Function:  Stepper_SetDirection															   *
 * Description: This function is used to Set Direction of Stepper
 *  * Input parameters:
 * 		- Stepper_Direction		in range :{- STEPPER_DIR_CW		-STEPPER_DIR_CCW}
 *
 * Return:
 * 		- void
 *
 * Input/Output Parameter:
 * 		- Not Applicable
 **********************************************************************************************/
RT_Debug Stepper_SetDirection(uint32_t Copy_StepperId,uint32_t Stepper_Direction){

	RT_Debug Return_Status = RT_SUCCESS ;

	if (Copy_StepperId < STEPPER_NUM && (Stepper_Direction == STEPPER_DIR_CW || Stepper_Direction == STEPPER_DIR_CCW ))
	{
		Gpio_WritePin(Steppercfg[Copy_StepperId].Stepper_Pin[STEPPER_DIR_PIN].Gpio_Port,Steppercfg[Copy_StepperId].Stepper_Pin[STEPPER_DIR_PIN].Gpio_PinNum,Stepper_Direction);
	}
	else
	{
		Return_Status = RT_PARAM ;
	}
	return Return_Status ;
}


/* Public Function:  Stepper_SetALLDirection															   *
 * Description: This function is used to Set Direction of Stepper
 *  * Input parameters:
 * 		- Stepper_Direction		in range :{- STEPPER_DIR_CW		-STEPPER_DIR_CCW}
 *
 * Return:
 * 		- void
 *
 * Input/Output Parameter:
 * 		- Not Applicable
 **********************************************************************************************/
RT_Debug Stepper_SetALLDirection(uint32_t Stepper_Direction)
{
	RT_Debug Return_Status = RT_SUCCESS ;

	if (Stepper_Direction == STEPPER_DIR_CW || Stepper_Direction == STEPPER_DIR_CCW )
	{
		for (uint32_t StepperIdx = 0 ; StepperIdx < STEPPER_NUM ; StepperIdx++)
		{
			Gpio_WritePin(Steppercfg[StepperIdx].Stepper_Pin[STEPPER_DIR_PIN].Gpio_Port,Steppercfg[StepperIdx].Stepper_Pin[STEPPER_DIR_PIN].Gpio_PinNum,Stepper_Direction);
		}
	}
	else
	{
		Return_Status = RT_PARAM ;
	}
	return Return_Status ;
}


/* Public Function:  Stepper_SetStatus															   *
 * Description: This function is used to Enable/Disable of Stepper
 *  * Input parameters:
 * 		- Stepper_Direction		in range :{- STEPPER_ENABLE	-STEPPER_DISABLE}
 *
 * Return:
 * 		- void
 *
 * Input/Output Parameter:
 * 		- Not Applicable
 **********************************************************************************************/
RT_Debug Stepper_SetStatus(uint32_t Copy_StepperId,uint32_t Stepper_Status){

	RT_Debug Return_Status = RT_SUCCESS ;;

	if (Copy_StepperId < STEPPER_NUM && (Stepper_Status == STEPPER_ENABLE || Stepper_Status == STEPPER_DISABLE))
	{
		Gpio_WritePin(Steppercfg[Copy_StepperId].Stepper_Pin[STEPPER_ENABLE_PIN].Gpio_Port,Steppercfg[Copy_StepperId].Stepper_Pin[STEPPER_ENABLE_PIN].Gpio_PinNum,Stepper_Status);
	}
	else
	{
		Return_Status = RT_PARAM ;
	}
	return Return_Status ;
}


/* Public Function:  Stepper_SetAllStatus															   *
 * Description: This function is used to Enable/Disable ALL Stepper
 *  * Input parameters:
 * 		- Stepper_Status		in range :{- STEPPER_ENABLE	-STEPPER_DISABLE}
 *
 * Return:
 * 		- void
 *
 * Input/Output Parameter:
 * 		- Not Applicable
 **********************************************************************************************/
RT_Debug Stepper_SetAllStatus(uint32_t Stepper_Status)
{
	RT_Debug Return_Status = RT_SUCCESS ;

	if (Stepper_Status == STEPPER_ENABLE || Stepper_Status == STEPPER_DISABLE )
	{
		for (uint32_t StepperIdx = 0 ; StepperIdx < STEPPER_NUM ; StepperIdx++)
		{
			Gpio_WritePin(Steppercfg[StepperIdx].Stepper_Pin[STEPPER_ENABLE_PIN].Gpio_Port,Steppercfg[StepperIdx].Stepper_Pin[STEPPER_ENABLE_PIN].Gpio_PinNum,Stepper_Status);
		}
	}
	else
	{
		Return_Status = RT_PARAM ;
	}
	return Return_Status ;

}



/***********************************************Timer Base Interrupt*******************************************************/
void TIM8_BRK_TIM12_IRQHandler()
{

	/* fisrt, clear the flag : UIF */
	if(((TimerBaseConfigs.Instance->DIER & TIM_DIER_UIE) == TIM_DIER_UIE) && ((TimerBaseConfigs.Instance->SR & TIM_FLAG_UPDATE)	== TIM_FLAG_UPDATE))
	{
		(TimerBaseConfigs.Instance->SR) &= ~(TIM_IT_UPDATE);
	}

	for(uint32_t Stepper_Idx = 0  ; Stepper_Idx < STEPPER_NUM ; Stepper_Idx++)
	{
		if (StepperWorking_Id[Stepper_Idx] == Stepper_Working)
		{
			trace_printf("PWM_Stop = %d\n",HAL_TIM_PWM_Stop(&StepperChannelcfg[Stepper_Idx].StepperConfigs,StepperChannelcfg[Stepper_Idx].StepperChannel));
			StepperWorking_Id[Stepper_Idx] = Stepper_NotWorking ;
			trace_printf("StepperId = %d\n",Stepper_Idx);
		}
	}

	HAL_TIM_Base_Stop_IT(&TimerBaseConfigs); //passing htim pointer to struct

	if (AppNotifyFlag)
	{
		*AppNotifyFlag = StepperAction_Done ;
	}

	/*
	if(AppNotify)
	{
		AppNotify();
	}
	 */
}


/* Public Function:  Stepper_SetCallBack														      *
 * Description: This function is used to Call User Function atEnd of feeding Material
 *
 * Input parameters:
 *      - Stepper_StopNotify	in range : pointer to function
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
RT_Debug Stepper_SetCallBack(PtrNotify Stepper_StopNotify)
{
	RT_Debug Return_status = RT_SUCCESS ;

	if (Stepper_StopNotify)
	{
		AppNotify = Stepper_StopNotify ;
	}
	else
	{
		Return_status = RT_ERROR ;
	}

	return Return_status;
}



/* Public Function:  Stepper_SetNotifyFlag														      *
 * Description: This function is used to Set Flag Function at End of feeding Material
 *
 * Input parameters:
 *      - Stepper_StopNotifyFlag	in range : pointer to uint32_t
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
RT_Debug Stepper_SetNotifyFlag(volatile uint32_t* Stepper_StopNotifyFlag)
{
	RT_Debug Return_status = RT_SUCCESS ;

	if (Stepper_StopNotifyFlag)
	{
		AppNotifyFlag = Stepper_StopNotifyFlag ;
	}
	else
	{
		Return_status = RT_ERROR ;
	}

	return Return_status;
}
