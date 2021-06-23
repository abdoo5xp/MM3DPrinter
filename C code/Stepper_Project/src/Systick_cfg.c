/*
 * Systick_cfg.c
 *
 *  Created on: Mar 10, 2021
 *      Author: micro
 */

#include <stdint.h>
#include <stddef.h>
#include "../../../lib/src/Bits.h"
#include "Systick_types.h"
#include "Systick_cfg.h"



/*Systick Clock Source*************************************************************
-options:
===================================================================================
- CLK_SOURCE_PROCESSOR_CLOCK
- CLK_SOURCE_EXTERNAL_REFERENCE_CLOCK\
**********************************************************************************/


/*Systick Interrupt*************************************************************
-options:
===================================================================================
- SYSTICK_INT_ENABLE
- SYSTICK_INT_DISSABLE
**********************************************************************************/
const Systick_cfg_t Systick_cfg = {.SysTick_Int =  SYSTICK_INT_ENABLE ,
								   .SysTickCLK_Source = SYSTICK_CLK_SOURCE_PROCESSOR_CLOCK };



