#pragma config(Sensor, S1,     ,               sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
#include "../libraries/Motors.h"

//int PreviousTime = 0;

void SetMotorPower(int LeftPower, int RightPower)
{
	Motors_SetSpeed(S1, 1, 1, LeftPower / 2);
	Motors_SetSpeed(S1, 1, 2, LeftPower / 2);
	Motors_SetSpeed(S1, 2, 1, -RightPower / 2);
	Motors_SetSpeed(S1, 2, 2, -RightPower / 2);

	writeDebugStream("SetMotorPower(%i", LeftPower);
	writeDebugStreamLine(", %i);", RightPower);
}

void DelayForTime()
{
	WriteDebugStreamLine("wait1Msec(10);");
	//WriteDebugStreamLine(");");
	//PreviousTime = time1[T1];
}

task main()
{
	//write first method which is called by text later
	writeDebugStreamLine("#pragma config(Sensor, S1,     ,               sensorI2CCustom)");
	writeDebugStreamLine("//have to include the location of your motors.h here:");
	writeDebugStream("void SetMotorPower(int LeftPower, int RightPower){");
	writeDebugStream("Motors_SetSpeed(S1, 1, 1, LeftPower / 2);Motors_SetSpeed(S1, 1, 2, LeftPower / 2);");
	writeDebugStreamLine("Motors_SetSpeed(S1, 2, 1, -RightPower / 2);Motors_SetSpeed(S1, 2, 2, -RightPower / 2);}");
	writeDebugStreamLine("task main(){");


	while(true)
	{
		getJoystickSettings(joystick);

		int RightPower = joystick.joy1_y1;
		int LeftPower = joystick.joy1_y2;
		SetMotorPower(LeftPower, RightPower);

		wait1Msec(10);
		DelayForTime();
	}
}
