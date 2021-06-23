/*
 * Service.c
 *
 *  Created on: Jun 23, 2021
 *      Author: abdoo
 */


#include <stdint.h>
#include "../../lib/Bit_Mask.h"
#include "../../lib/Bit_Math.h"
#include "../../lib/Error_codes.h"
#include "Service.h"




uint32_t Service_u32Concat(uint8_t *NumbersArray, uint8_t ArraySize)
{
	uint8_t LoopIdx;
	uint32_t result = 0;
	for(LoopIdx = 0; LoopIdx < ArraySize; LoopIdx++)
	{
		result |= NumbersArray[LoopIdx] << (LoopIdx << 3 );
	}
	return result;
}
