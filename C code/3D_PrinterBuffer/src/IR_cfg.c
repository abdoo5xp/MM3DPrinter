/*
 * Led_cfg.c
 *
 *  Created on: Feb 11, 2021
 *      Author: micro
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../lib/src/RT_Debug.h"
#include "../../../lib/src/Bits.h"
#include "Gpio_int.h"
#include "IR.h"
#include "IR_types.h"



/* Configuration Parameters for each Led ************************************************************																		*
 *
 * 		- Gpio_Mode 	in range : { GPIO_MODE_xx  ( xx : - OUTPUT  - INPUT - ANALOG - AF )}
 * 		- Gpio_OType   	in range : { - GPIO_OTYPE_PUSH_PULL	 - GPIO_OTYPE_OPEN_DRAIN }
 * 		- Gpio_OSpeed  	in range : { GPIO_OSPEED_xx  ( xx : - LOW_SPEED     - MEDIUM_SPEED
 * 														    - HIGH_SPEE	   - VERY_HIGH_SPEED)}
 * 		- Gpio_PUPD 	in range : { GPIO_PUPD_xx ( xx : - FLOATING	- PULL_UP  - PULL_DOWN )}
 * 		- Gpio_AF 	  	in range : { GPIO_AFxx  (xx :  0 .. 15)}
 *      - Gpio_Port		in range : { GPIOxx (xx : A , B , C , D , E , H)}
 *      - Gpio_PinNum	in range : { GPIO_PINXX (xx :  0 .. 15)}
 *
 *		- Led_Mode 		in range : { LED_ACTIVE_HIGH - LED_ACTIVE_LOW }
 *
 ***************************************************************************************************/
const IRcfg_t IRcfg[IR_NUM] = {

		[IR_1]	=	{
			 	 	 	 	 	   {  .Gpio_Mode  	 = GPIO_MODE_OUTPUT 		    	,
									  .Gpio_OType 	 = GPIO_OTYPE_PUSH_PULL    			,
									  .Gpio_OSpeed   = GPIO_OSPEED_VERY_HIGH_SPEED		,
									  .Gpio_PUPD 	 = GPIO_PUPD_PULL_UP 				,
									  .Gpio_Port  	 = GPIOD							,
									  .Gpio_PinNum 	 = GPIO_PIN14
			 	 	 	 	 	   }
		}

};











