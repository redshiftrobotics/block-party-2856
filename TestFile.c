#pragma config(Sensor, S1,     ,               sensorI2CCustom)
#pragma config(Sensor, S4,     ,               sensorTouch)

//#include "libraries/Motors.h"
#include "libraries/Servos.h"
//#include "libraries/I2C.h"
#include "libraries/Arm.c"
#include "JoystickDriver.c"

task main()
{
	while(true)
	{
	Servos_SetPosition(S1, 3, 1, 255);
	//Motors_SetPosition(S1, 1, 1, 4000, 20);
	//while(true)
	//{
	//Arm_SetSpeed(-30);
	//Arm_Update();


	//}
	//Motors_SetSpeed(S1, 1, 1, -10);

	//while(true)
	//{
	//	writeDebugStreamLine("%i", I2C_GetEncoderPosition(S1, 1, 1));
	//}
}
}
