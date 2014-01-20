#pragma config(Sensor, S2,     IR,             sensorI2CCustom)
#pragma config(Sensor, S3,     Gyro,             sensorI2CCustom)

#include "libraries/Turning.c";
//#include "libraries/Motors.h";

//void Move(int RightPower, int LeftPower)
//{
//	Motors_SetSpeed(S1, 2, 1, RightPower);
//	Motors_SetSpeed(S1, 2, 2, -LeftPower);
//}

task main()
{
	Turning_StraightToIR(20);

	PlayImmediateTone(100, 100);
	Sleep(1000);
}
