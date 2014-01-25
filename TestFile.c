#pragma config(Sensor, S1,  ,  sensorI2CCustom)
#pragma config(Sensor, S2,     IR,             sensorI2CCustom)
#pragma config(Sensor, S3,     Gyro,             sensorI2CCustom)

#include "libraries/Turning.c";
#include "libraries/Arm.c";

//void Move(int RightPower, int LeftPower)
//{
//	Motors_SetSpeed(S1, 2, 1, RightPower);
//	Motors_SetSpeed(S1, 2, 2, -LeftPower);
//}

task UpdateArm()
{
	while(true)
	{
		Arm_Update();
	}
}

task main()
{
	StartTask(UpdateArm);

	Turning_StraightToIR(10);

	PlayImmediateTone(100, 100);
	Sleep(1000);

	while(true)
	{
		Arm_SetSpeed(50);
	}
}
