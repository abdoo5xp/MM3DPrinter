

#include <stdlib.h>
#include <stdint.h>
#include "../../lib/Bit_Mask.h"
#include "../../lib/Bit_Math.h"
#include "../../lib/Error_codes.h"
#include "GcodeParser.h"
#include "GcodeReceiver.h"

void dataReceivedCallback(void)
{
	uint8_t * GcodeBytes;
	uint8_t GcodeNumberOfBytes;
	GcodeBytes = GcodeReceiver_GetGcodeData(&GcodeNumberOfBytes);
	GcodeParser_enuStartParsing(GcodeBytes, GcodeNumberOfBytes);
	trace_printf("The End elhamdullah ");
}



int main()
{
  // At this stage the system clock should have already been configured
  // at high speed.

	GcodeReceiver_vidInit(dataReceivedCallback);

  // Infinite loop
  while (1)
    {
       // Add your code here.
    }

  return 0;

}

