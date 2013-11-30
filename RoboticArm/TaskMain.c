#pragma config(Sensor, S1,     ServoController,               sensorI2CCustom)
#include "InverseKinematics.c"
#include "../libraries/Bluetooth.c"


task main()
{
	int X = 0;
	int Y = 0;
	int Z = 0;

	while(true)
	{
		if(Bluetooth_ReadMessage(&X, &Y, &Z))
		{
			InverseKinematics_ThreeJoint(21, 18, X, Y, Z);
		}



		sleep(50);
	}
}
