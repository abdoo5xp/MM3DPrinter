/*
 * EXTI.h
 *
 *  Created on: Jun 23, 2021
 *      Author: abdoo
 */

#ifndef LIMIT_SW_H_
#define LIMIT_SW_H_

#include "Limit_SW_cfg.h"

typedef void (*pfun)(void);

void LimitSW_vidInit();

RT_Debug LimitSW_enuEnableINT(EXTI_config_t * pinConfig);

RT_Debug LimitSW_SetCallBack(pfun cbf, uint8_t EXTINum);

#endif /* LIMIT_SW_H_ */
