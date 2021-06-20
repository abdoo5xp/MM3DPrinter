


#include <stdint.h>
#include "../../lib/Bit_Math.h"
#include "../../lib/Bit_Mask.h"
#include "../../lib/Error_codes.h"
#include "Servo.h"



int main(int argc, char* argv[])
{
  // At this stage the system clock should have already been configured
  // at high speed.
	SERVO_enuInit(SERVO_ANGLE_ZERO_DUTY_CYCLE );
	SERVO_enuStart();

  // Infinite loop
  while (1)
    {
       // Add your code here.
    }
}
