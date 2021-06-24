/*
 * Limit_SW_cfg.h
 *
 *  Created on: Jun 24, 2021
 *      Author: Islam
 */


typedef struct {
	Pincfg_t btn_config;
	EXTI_config_t exti_config;
	irqn_t	EXINT_Line ;
}LimitSW_cfg_s;

#define 	LIMIT_SW_NUM			2

#define 	LIMIT_SW_1				0
#define 	LIMIT_SW_2				1


extern const LimitSW_cfg_s LimitSWcfg[LIMIT_SW_NUM] ;
