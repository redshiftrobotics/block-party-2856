#pragma config(Sensor, S1,     ,               sensorI2CCustom)
#pragma config(Sensor, S2,     ,               sensorI2CCustom)
#include "../libraries/I2C.h"

int StartPosition;

void Allign_Calibrate()
{
	StartPosition = I2C_GetEncoderPosition(S2, 1, 1);
}

int Allign_Offset()
{
	return (I2C_GetEncoderPosition(S2, 1, 1) - StartPosition);
}

task main()
{
	Allign_Calibrate();

	while(true)
	{
		eraseDisplay();
		int Offset = Allign_Offset();
		nxtDisplayString(1, "Offset: %i", Offset);

		//change dependant on direction of encoder
		if(abs(Offset) < 100)
		{
			I2C_SetMotorSpeed(S1, 1, 1, (50 - Offset / 2));
			I2C_SetMotorSpeed(S1, 1, 2, (-50 - Offset / 2));

			nxtDisplayString(2, "%i", 50 - Offset / 2);
			nxtDisplayString(3, "%i", -50 - Offset / 2);
		}
		else
		{
			I2C_SetMotorSpeed(S1, 1, 1, (50 - (Offset / abs(Offset)) * 50));
			I2C_SetMotorSpeed(S1, 1, 2, (-50 - (Offset / abs(Offset)) * 50));

			nxtDisplayString(2, "%i", 50 - (Offset / abs(Offset)) * 50);
			nxtDisplayString(3, "%i", -50 - (Offset / abs(Offset)) * 50);
		}

		sleep(10);
	}
}
