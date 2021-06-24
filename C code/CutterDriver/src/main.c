#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include <stdint.h>
#include <stm32f4xx.h>
#include <stm32f4xx_hal_tim.h>

#include "../../lib/Bit_Mask.h"
#include "../../lib/Bit_Math.h"
#include "../../lib/Error_codes.h"

#include "Cutter.h"
#include "Cutter_cfg.h"


#include "Timer.h"

int main(void)
{
	timer_start();

	Cutter_enuInit();



	Cutter_enuTurnOn();
	timer_sleep(2000);

	Cutter_enuTurnOff();
	timer_sleep(2000);


	Cutter_enuTurnOn();
	timer_sleep(2000);

	Cutter_enuTurnOff();
	timer_sleep(2000);


	Cutter_enuTurnOn();
	timer_sleep(2000);

	Cutter_enuTurnOff();
	timer_sleep(2000);


	Cutter_enuTurnOn();
	timer_sleep(2000);

	Cutter_enuTurnOff();
	timer_sleep(2000);


	Cutter_enuTurnOn();
	timer_sleep(2000);

	Cutter_enuTurnOff();
	timer_sleep(2000);

/* it stops here, test it again*/
	Cutter_enuTurnOn();
	timer_sleep(2000);

	Cutter_enuTurnOff();
	timer_sleep(2000);


	Cutter_enuTurnOn();
	timer_sleep(2000);

	Cutter_enuTurnOff();
	timer_sleep(2000);


	Cutter_enuTurnOn();
	timer_sleep(2000);

	Cutter_enuTurnOff();
	timer_sleep(2000);
	while (1);
}
