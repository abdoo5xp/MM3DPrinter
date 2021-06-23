/*
 * SystickTimer.h
 *
 *  Created on: Mar 7, 2021
 *      Author: abdoo
 */
/**
 *
 * Number of cycles = required time in ms * cpu frequency /1000;
 *
 *
 */

#ifndef SYSTICKTIMER_H_
#define SYSTICKTIMER_H_

typedef void (*pfun)(void);

typedef enum {
	systick_ahb_8_clk_src ,
	systick_ahb_clk_src = BIT_MASK_2
}systickclk_t;


extern void     Systick_Init (void);
extern uint32_t Systick_Start(void);
extern uint32_t Systick_Stop (void);
extern uint32_t Systick_SelectClkSrc (systickclk_t clksrc );
extern uint32_t Systick_SetTimer_ms(uint32_t time_ms,uint32_t AHBBusClkMhz);
extern uint32_t Systick_SetCbf(pfun callBackFn);



#endif /* SYSTICKTIMER_H_ */
