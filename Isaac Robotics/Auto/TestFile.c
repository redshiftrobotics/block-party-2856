#pragma config(Sensor, S1,     M_CONTROL,      sensorI2CCustom)
#pragma config(Sensor, S2,     M_CONTROL,      sensorI2CCustom)
#pragma config(Sensor, S3,     M_CONTROL,      sensorI2CCustom)
#pragma config(Sensor, S4,     M_CONTROL,      sensorI2CCustom)

#include "libraries/Motors.h"
#include "libraries/Servos.h"
#include "libraries/I2C.h"
#include "libraries/Arm.c"

task main()
{
	while(true)
	{
		Arm_Update();
		//Arm_SetSpeed(-10);
	}
}
