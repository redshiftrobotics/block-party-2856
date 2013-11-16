
#include "../libraries/Bluetooth.c"
#include "../libraries/Motors.h"

task main()
{
	while(true)
	{
		int FirstMessage = 0;
		int SecondMessage = 0;
		int ThirdMessage = 0;

		if(Bluetooth_ReadMessage(&FirstMessage, &SecondMessage, &ThirdMessage))
		{
			motor[motorA] = FirstMessage;
			motor[motorB] = SecondMessage;

			Motors_SetSpeed(S1, 2, 1, FirstMessage);
			Motors_SetSpeed(S1, 2, 2, -SecondMessage);

			nxtDisplayString(1, "MotorA: %i", FirstMessage);
			nxtDisplayString(2, "MotorB: %i", SecondMessage);
			nxtDisplayString(3, "MotorC: %i", ThirdMessage);
		}
	}
}
