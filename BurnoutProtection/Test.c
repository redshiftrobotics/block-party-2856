#pragma config(Sensor, S1, A, sensorI2CCustom)

#include "../libraries/I2C.h";

task main()
{
	for(int i = 0; i <= 100; i+=5)
	{

		int StartEncoder = I2C_GetEncoderPosition(S1, 2, 2);

		ClearTimer(T1);
		while(time1[T1] < 5000)
		{
			I2C_SetMotorSpeed(S1, 2, 2, i);
		}

		int EndEncoder = I2C_GetEncoderPosition(S1, 2, 2);

		writeDebugStreamLine("%i, %i", i, abs(StartEncoder - EndEncoder));

		I2C_SetMotorSpeed(S1, 2, 2, 0);
		sleep(1500);
	}
}
