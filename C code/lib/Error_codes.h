/*
 * Error_codes.h
 *
 *  Created on: Jan 29, 2021
 *      Author: abdoo
 */

#ifndef ERROR_CODES_H_
#define ERROR_CODES_H_

///*Error in the selection of system clock */
//#define RT_TIMEOUT		3
///*Error in the execution of the function */
//#define RT_ERROR		2
///*Error in the passed parameters */
//#define RT_PARAM		1
///*Function successfully executed */
//#define RT_SUCCESS		0


/*I made this enum, and didn't delete the old macros to provide backward compatibility*/
typedef enum{
	_SUCCESS,
	_PARAM,
	_ERROR,
	_TIMEOUT,
	_PENDING,
}Status_e;


#define NULL  	 (void*)0

#endif /* ERROR_CODES_H_ */
