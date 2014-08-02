#pragma config(Sensor, S1,     M_CONTROL,      sensorI2CCustom)
#pragma config(Sensor, S2,     M_CONTROL,      sensorI2CCustom)
#pragma config(Sensor, S3,     M_CONTROL,      sensorI2CCustom)
#pragma config(Sensor, S4,     M_CONTROL,      sensorI2CCustom)

#include "JoystickDriver.c"
#include "libraries/Motors.h"

task main()
{
	float Timer = 0;

	while(true)
	{
		getJoystickSettings(joystick);
		eraseDisplay();
		//ready: UserMode = 1, StopPgm = 1
		//running: UserMode = 1, StopPgm = 0

		if(joystick.UserMode == 1 && joystick.StopPgm == 1)
		{
			//ready
			//ClearTimer(T1);


		}
		else if(joystick.UserMode == 1 && joystick.StopPgm == 0)
		{
			//running
			//Timer += time1[T1];
			//ClearTimer(T1);
			PlayTone(10, 1);
			//PlayTone(10, 0);
		}
		else if(joystick.UserMode == 0 && joystick.StopPgm == 1)
		{
			//stopped
		}

		writeDebugStreamLine("%i", Timer);

		//nxtDisplayString(1, "User Mode: %i", joystick.UserMode);
		//nxtDisplayString(2, "Stop Program: %i", joystick.StopPgm);

		sleep(10);
	}
}
