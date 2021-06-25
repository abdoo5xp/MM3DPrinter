// ----------------------------------------------------------------------------

#include <stdio.h>
#include "../../../lib/src/Bits.h"
#include "../../lib/Error_codes.h"
#include "../../../lib/src/RT_Debug.h"
#include "App_Types.h"
#include "App.h"



int main(void)
{
	GcodeParser_Action_t ExtruderAction;

	/*Initialize the Whole System and open the Receiving */
	App_vidInit();

	/*Wait till the Gcode is Received */
	App_vidWaitForDataReception();

	while(1)
	{
		/*Start Parsing and get the Action */
		App_vidParseGcode(&ExtruderAction);

		/*Execute that action */
		App_vidTakeAction(&ExtruderAction);

		/*Wait till this Action is executed */
		App_vidWaitForActionExecution();

		/*Check if the GCode has ended */
		if(APP_GcodeEnd == App_HasGcodeEnded() )
		{
			/*Cut the power from your motors,
			 *  and Set the System in sleep mode  */
			App_vidSystemSleep();

			/*Wait till the Gcode is Received */
			App_vidWaitForDataReception();

			/*Initialize the Whole System */
			App_vidInit();
		}
	}

	return 0;
}

/* pulse-  => PD 15  => Blue   led
 * DIR-    => PD 14  => Red    Led
 * ENA-    => PD 13  => Orange led*/


