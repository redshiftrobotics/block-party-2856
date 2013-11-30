#pragma config(Sensor, S1,     ,               sensorI2CCustom)
#pragma config(Sensor, S2,     IR,             sensorI2CCustom)
#pragma config(Sensor, S3,     Color,          sensorI2CCustom)
#pragma config(Sensor, S4,     ,               sensorTouch)

#include "../libraries/Arm.c"

task main()
{
while(true)
{
	Arm_Update();
	Arm_SetSpeed(-100);
}
}
