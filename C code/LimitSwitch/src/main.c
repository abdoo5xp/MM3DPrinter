

#include <stdint.h>
#include "../../lib/Bit_Math.h"
#include "../../lib/Bit_Mask.h"
#include "../../lib/Error_codes.h"
#include "LS.h"
#include "Rcc.h"

int main(int argc, char* argv[])
{
  // At this stage the system clock should have already been configured
  // at high speed.
	RCC_ControlAHB1PeriClk(RCC_AHB1_PREPH_GPIOA, RCC_PREPH_ENABLE);

  // Infinite loop
  while (1)
    {
       // Add your code here.
    }
}

