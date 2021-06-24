/*
 * GcodeParser.c
 *
 *  Created on: Jun 22, 2021
 *      Author: abdoo
 */


#include <stdint.h>
#include "diag/Trace.h"
#include "../../lib/Bits.h"
#include "../../lib/Bit_Math.h"
#include "../../lib/Error_codes.h"
#include "../../../lib/src/RT_Debug.h"
#include <stm32f4xx_hal.h>
#include <stm32f4xx_hal_conf.h>
#include <stm32f4xx_hal_tim.h>
#include "Rcc_int.h"
#include "Gpio_int.h"
#include "Service.h"
#include "Stepper.h"
#include "Stepper_types.h"
#include "Extruder.h"
#include "GcodeParser.h"
#include "GcodeParser_cfg.h"
#include "IR.h"
#include "Cutter.h"
#include "Heater.h"

uint8_t *GcodeDataArray;
uint32_t Size;

/*************************************************Timer Base***************************************************************/
uint32_t Heater_CutterTimerBasePeriodTicks =  0 ;//12000//6563

static TIM_HandleTypeDef    TimerBaseConfigs;
static TIM_Base_InitTypeDef TimerBaseTimerInitConfigs;
/*************************************************************************************************************************/

static RT_Debug Cutter_Delay(uint32_t Cutter_delay)
{
	RT_Debug Return_Status = RT_SUCCESS ;
	/*************************************Heater_Timer_Delay_Reconfigure********************************/
	TimerBaseTimerInitConfigs.Period = Cutter_delay;
	TimerBaseConfigs.Init    		 = TimerBaseTimerInitConfigs;
	Return_Status = HAL_TIM_Base_Init(&TimerBaseConfigs);
	/********************************************************Timer Base Start********************************************************************/
	(TimerBaseConfigs.Instance->SR) &= ~(TIM_IT_UPDATE);
	Return_Status = HAL_TIM_Base_Start_IT(&TimerBaseConfigs);//passing htim pointer to struct
	while((TimerBaseConfigs.Instance->SR & TIM_FLAG_UPDATE) != TIM_FLAG_UPDATE);
	Return_Status = HAL_TIM_Base_Stop_IT(&TimerBaseConfigs); //passing htim pointer to struct

	return Return_Status ;
}

static RT_Debug Heater_Delay(uint32_t Heater_delay)
{
	RT_Debug Return_Status = RT_SUCCESS ;
	/*************************************Heater_Timer_Delay_Reconfigure********************************/
	TimerBaseTimerInitConfigs.Period = Heater_delay;
	TimerBaseConfigs.Init    		 = TimerBaseTimerInitConfigs;
	Return_Status = HAL_TIM_Base_Init(&TimerBaseConfigs);
	/********************************************************Timer Base Start********************************************************************/
	(TimerBaseConfigs.Instance->SR) &= ~(TIM_IT_UPDATE);
	Return_Status = HAL_TIM_Base_Start_IT(&TimerBaseConfigs);//passing htim pointer to struct
	while((TimerBaseConfigs.Instance->SR & TIM_FLAG_UPDATE) != TIM_FLAG_UPDATE);
	Return_Status = HAL_TIM_Base_Stop_IT(&TimerBaseConfigs); //passing htim pointer to struct

	return Return_Status ;
}


static void GcodeParser_vidMaterialSwap(uint8_t OldMaterial, uint8_t CurrentMaterial,uint32_t MaterialLength ,uint32_t FeedRate)
{
	IR_State_e IRHasNewMaterialReached = IR_State_Off;
	/*Perform the Cut Action
	 * TODO: configure the wait time */
	/*Cutter_enuTurnOn();
	Cutter_Delay(GCODEPARSER_CUTTING_TIME);
	Cutter_enuTurnOff();*/

	/*Reverse the old material with the reverse speed */
	Stepper_SetDirection(OldMaterial,STEPPER_DIR_CCW);
	Extruder_SetFeedRate(OldMaterial, GCODEPARSER_REVERSE_FEEDRATE);
	Extruder_SetMaterialLength(OldMaterial, GCODEPARSER_MATERIAL_OFFSET_um,Stepper_CallBack_Off);
	Stepper_SetDirection(OldMaterial,STEPPER_DIR_CW);

	/**********************************Wait till Retraction******************************************/
	Stepper_Hold();

	/*Run the new material */
	Extruder_SetFeedRate(CurrentMaterial, FeedRate);
	Extruder_SetMaterialLength(CurrentMaterial, GCODEPARSER_MATERIAL_OFFSET_um + MaterialLength,Stepper_CallBack_On);

	/*Wait till it reaches to the heater */
	/*do
	{
	IR_enuGetState(&IRHasNewMaterialReached);
	}while(IRHasNewMaterialReached == IR_State_Off);*/

	/*Pause the Feed of the new material */
	Extruder_Pause(CurrentMaterial);

	/*join the two material to together */
	/*HEATER_enuStart();
	Heater_Delay(GCODEPARSER_HEATING_TIME);
	HEATER_enuStop();*/

	/*Continue the Feed of the new material */
	Extruder_Continue(CurrentMaterial);
}


RT_Debug GcodeParser_TimerBaseInit(void)
{
	RT_Debug Return_status;

	Rcc_APB2_PeriClockStatus(RCC_APB2_PERI_CLOCK_TIM9, RCC_PERI_CLOCK_ENABLE);

	TimerBaseTimerInitConfigs.Prescaler     = GCODEPARSER_TIMER_BASE_PRESCALER;
	TimerBaseTimerInitConfigs.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	TimerBaseTimerInitConfigs.CounterMode   = TIM_COUNTERMODE_UP;

	/* 84,000,000 / desired frequency */
	TimerBaseTimerInitConfigs.Period        = Heater_CutterTimerBasePeriodTicks;

	/*TimerBaseTimerInitConfigs.RepetitionCounter parameter is valid only for TIM1 and TIM8.*/


	TimerBaseConfigs.Channel  =             HAL_TIM_ACTIVE_CHANNEL_1;
	TimerBaseConfigs.Instance =             TIM9_BASE;
	TimerBaseConfigs.Lock     =             HAL_UNLOCKED;
	TimerBaseConfigs.State    =             HAL_TIM_STATE_RESET;
	TimerBaseConfigs.Init     =             TimerBaseTimerInitConfigs;


	Return_status   =    HAL_TIM_Base_Init(&TimerBaseConfigs);
	trace_printf("HAL_TIM_Base_Init = %d\n",Return_status);

	//TIM_Base_SetConfig already exist inside 'HAL_TIM_Base_Init' function implementation
	return Return_status;
}

/**************************************************************************************************************
 * Public Function:GcodeParser_enuStartParsing()
 * Description: This function is used to start the parsing process
 * Input Parameters:
 * 					 -uint8_t *GcodeArray : a pointer to The data to be parsed
 * 					  uint32_t NumberOfBytes: Size of this array
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
void GcodeParser_enuStartParsing(uint8_t *GcodeArray,uint32_t NumberOfBytes)
{
	GcodeDataArray = GcodeArray;
	Size = NumberOfBytes;

	GcodeParser_TimerBaseInit();
	Extruder_SetCallBackFunction(GcodeParser_enuParseGcode);
	Stepper_SetStatus(EXTRUDER_M_1,STEPPER_ENABLE);
	Stepper_SetStatus(EXTRUDER_M_2,STEPPER_ENABLE);
	//Stepper_SetStatus(EXTRUDER_M_3,STEPPER_ENABLE);
	//Stepper_SetStatus(EXTRUDER_E,STEPPER_ENABLE);
	Stepper_SetDirection(EXTRUDER_M_1,STEPPER_DIR_CW);
	Stepper_SetDirection(EXTRUDER_M_2,STEPPER_DIR_CW);
	//Stepper_SetDirection(EXTRUDER_M_3,STEPPER_DIR_CW);
	//Stepper_SetDirection(EXTRUDER_E,STEPPER_DIR_CW);
	GcodeParser_enuParseGcode();
}


/**************************************************************************************************************
 * Public Function:GcodeParser_enuParseGcode
 * Description: This function is used to parse the Gcode and take actions by calling the extruder functions
 * 				**This function is made to be called after the motors perform their actions**
 *
 * Input Parameters:
 * 					 -uint8_t *GcodeDataArray: a pointer to the Gcode Data array
 * 					  uint16_t Size : the number of elements of this array
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
void GcodeParser_enuParseGcode()
{	/* 'X' '5''5''6' */
	static uint32_t ByteIdx;
	static uint8_t OldMaterial ;/*At first set the old material with the first material to be printed */
	static uint32_t FeedRate;
	uint8_t LengthTemp[4];
	uint32_t MaterialLength;

	if(OldMaterial == 0)
	{
		OldMaterial = GcodeDataArray[ByteIdx+4];
	}
	if(ByteIdx >= Size )
	{
		trace_printf("End of GCode\n");

		/*TODO: stop the timer or return error then stop the timer in the caller function the BASE TIMER ISR */
		return ;
	}

	/*Get the Material Extrusion Length Bytes */
	LengthTemp[0] = GcodeDataArray[ByteIdx+1];
	LengthTemp[1] = GcodeDataArray[ByteIdx+2];
	LengthTemp[2] = GcodeDataArray[ByteIdx+3];

		/*Call the Set Feed Rate Here */
	if(GcodeDataArray[ByteIdx] == 'F')
	{
		FeedRate = (uint32_t)Service_u32Concat(LengthTemp, 3);

		Extruder_SetFeedRate(EXTRUDER_M_1, FeedRate);
		Extruder_SetFeedRate(EXTRUDER_M_2, FeedRate);
		/*Extruder_SetFeedRate(EXTRUDER_M_3, FeedRate);
		Extruder_SetFeedRate(EXTRUDER_E, FeedRate);
		*/
		ByteIdx+=4;
		/*Get the Material Extrusion Length Bytes */
		LengthTemp[0] = GcodeDataArray[ByteIdx+1];
		LengthTemp[1] = GcodeDataArray[ByteIdx+2];
		LengthTemp[2] = GcodeDataArray[ByteIdx+3];


		//		trace_printf("setting the feed rate with %d \n",(uint32_t)Service_u32Concat(LengthTemp, 3));
	}
//	else
//	{
		MaterialLength = (uint32_t)Service_u32Concat(LengthTemp, 3);
		/*if the current material is not the same as the previous material--> call material swap */
		if (GcodeDataArray[ByteIdx] != OldMaterial )
		{
			GcodeParser_vidMaterialSwap(OldMaterial-'X', GcodeDataArray[ByteIdx]-'X', MaterialLength,FeedRate);
			OldMaterial = GcodeDataArray[ByteIdx];
		}
		else
		{
			/* Call the Set Material to run the Material Extruder and the main extruder   */
			Extruder_SetMaterialLength(GcodeDataArray[ByteIdx] - 'X', MaterialLength,Stepper_CallBack_On);
		}
		//Extruder_SetMaterialLength(EXTRUDER_E, MaterialLength);

		//		trace_printf("setting the motor %c rate with %d \n",GcodeDataArray[ByteIdx], MaterialLength);
//	}

	/*Go to the next Gcode line */
	ByteIdx +=4;
}

