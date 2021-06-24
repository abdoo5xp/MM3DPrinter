
#include <stdint.h>
#include "../../lib/Bit_Mask.h"
#include "../../lib/Bit_Math.h"
#include "../../lib/Error_codes.h"
#include "GPIO.h"
#include "Rcc.h"
#include "NVIC.h"
#include "EXTI.h"


void test(void)
{
	trace_printf("Allah <3 ");
}

int main()
{

	EXTI_enuSetCbf(test, 0);
	EXTI_enuEnableINT(&exti_0_config);

  // Infinite loop
  while (1)
    {
       // Add your code here.
    }
}
