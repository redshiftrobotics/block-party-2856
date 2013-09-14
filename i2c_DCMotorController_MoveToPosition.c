#pragma config(Sensor, S1,     M_CONTROL,      sensorI2CCustom)

#include "libraries/libi2cmotor.h"
#include "libraries/Write.h"
#include "libraries/SetSpeed.h"

task main()
{
		SetSpeed(S1, 1, 1, 10);
		SetSpeed(S1, 1, 2, 10);
		InitializeWrite();

		while(true)
		{
		}
}

		//setEncoderPosition(2, S1, 0, (long)0);
		//nxtDisplayString(0, "%i", getEncoderPosition(2, S1, 0));

	//setMotorSpeed(2, S1, 0, -50);

	//setMotorSpeed(S1, 2, 1, -50);
	//setMotorSpeed(S1, 1, 2, -50);

		//gotoEncoderPosition(2, S1, 0, encoderTarget);
		//Sleep(10);
