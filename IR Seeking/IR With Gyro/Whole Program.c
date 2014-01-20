#pragma config(Sensor, S2,     IR,             sensorI2CCustom)
#include "libraries/IR.c";
#include "libraries/Turning.c";

void Move(int RightPower, int LeftPower)
{
	Motors_SetSpeed(S1, 2, 1, RightPower);
	Motors_SetSpeed(S1, 2, 2, -LeftPower);
}

task main()
{
	IR_Reset();

	while(!IR_InFront())
	{
	}

	PlayImmediateTone(100, 100);
	Sleep(1000);
}
