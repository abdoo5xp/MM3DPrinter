
#include <stdint.h>
#include "diag/Trace.h"

#include "../../lib/Bit_Math.h"
#include "../../lib/Bit_Mask.h"
#include "../../lib/Error_codes.h"

#include "Timer.h"
#include "Heater.h"


int main()
{
	timer_start();

	// At this stage the system clock should have already been configured at high speed.
	HEATER_enuInit(80); /* 50% duty cycle */

	HEATER_enuStart();
	timer_sleep(25000);
	HEATER_enuStop();
	trace_printf("duty cycle at Initialization is 78%\n");

	while(1){
//	/*	trace_printf("duty cycle at Initialization is 30%\n");
//		timer_sleep(10000);
//		/*-----------------------------------------------*/
//		HEATER_enuChangeDutyCycle(40);
//		trace_printf("duty cycle now is 40%\n");
//		timer_sleep(3000);
//		/*-----------------------------------------------*/
//
//
//
//
//		// Testing the PWM stop function
//		HEATER_enuStop();
//		timer_sleep(3000);
//		/*-----------------------------------------------*/
//		HEATER_enuChangeDutyCycle(50);
//		trace_printf("duty cycle now is 50%\n");
//		timer_sleep(3000);
//		/*-----------------------------------------------*/
//		HEATER_enuChangeDutyCycle(60);
//		trace_printf("duty cycle now is 60%\n");
//		timer_sleep(3000);
//		/*-----------------------------------------------*/
//		HEATER_enuChangeDutyCycle(70);
//		trace_printf("duty cycle now is 70%\n");
//		timer_sleep(3000);
//		/*-----------------------------------------------*/
//
//
//
//
//
//		// Testing the PWM stop function again
//		HEATER_enuStop();
//		timer_sleep(3000);
//		/*-----------------------------------------------*/
//		HEATER_enuChangeDutyCycle(80);
//		trace_printf("duty cycle now is 80%\n");
//		timer_sleep(3000);
//		/*-----------------------------------------------*/
//		HEATER_enuChangeDutyCycle(90);
//		trace_printf("duty cycle now is 90%\n");
//		timer_sleep(3000);
//		-----------------------------------------------*/
	}
}
