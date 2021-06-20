#include <stdint.h>
#include "../../lib/Bit_Math.h"
#include "../../lib/Bit_Mask.h"
#include "../../lib/Error_codes.h"

#include "Timer.h"

#include "Servo.h"



int main(int argc, char* argv[])
{
	timer_start();

	// At this stage the system clock should have already been configured
	// at high speed.
	SERVO_enuInit(SERVO_ANGLE_ZERO_DUTY_CYCLE );
	SERVO_enuStart();
	while(1){
		trace_printf("angle 0\n");
		timer_sleep(5000);
		SERVO_enuChangeAngle(SERVO_ANGLE_90_DUTY_CYCLE);
		trace_printf("angle 90\n");
		timer_sleep(5000);
		SERVO_enuChangeAngle(SERVO_ANGLE_180_DUTY_CYCLE);
		trace_printf("angle 180\n");
		timer_sleep(5000);
		SERVO_enuChangeAngle(SERVO_ANGLE_ZERO_DUTY_CYCLE);
	}
}
