/*
 * Service.h
 *
 *  Created on: Jun 23, 2021
 *      Author: abdoo
 */

#ifndef SERVICE_H_
#define SERVICE_H_

/**************************************************************************************************************
 * Public Function:Service_u32Concat
 * Description: This function is used to concatenate the array elements
 * Input Parameters:
 * 					 -uint8_t *NumbersArray: a pointer to the array
 * 					  uint8_t ArraySize: the number of elements in the array
 *
 *
 * Return:           -uint32_t : the concatenation of the array elements
 *
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
uint32_t Service_u32Concat(uint8_t *NumbersArray, uint8_t ArraySize);

#endif /* SERVICE_H_ */
