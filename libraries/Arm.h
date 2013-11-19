#pragma config(Sensor, S1,     ,               sensorI2CCustom)
#pragma config(Sensor, S4,     ,               sensorTouch)

#include "I2C.h"

//sets globals
bool Arm_Initialized = false;
int Arm_BottomEncoderLimit = 0;
int Arm_TopEncoderLimit = 0;
int Arm_Encoder = 0;
int Arm_Speed = 0;

void Arm_SetSpeed(int Speed)
{
	//only lets you change the speed if the robot is initialized
	if(Arm_Initialized)
	{
		Arm_Speed = Speed;
	}
}

void Arm_Update()
{
	Arm_Encoder = I2C_GetEncoderPosition(S1, 1, 1);
	//if the arm isn't initialized yet
	if(!Arm_Initialized)
	{

		//set the speed to 10
		Arm_Speed = 10;

		//if the lower limit is triggered, set the upper and lower encoder bounds
		if(SensorValue[S4] == 1)
		{
			Arm_Initialized = true;
			Arm_Speed = 0;

			Arm_BottomEncoderLimit = Arm_Encoder;
			Arm_TopEncoderLimit = Arm_Encoder - (5 * 1440);
		}
	}

	//if the arm is initialized
	else
	{
		//if the arm is with in the encoder range
		if(Arm_Encoder < Arm_TopEncoderLimit && Arm_Encoder > Arm_BottomEncoderLimit)
		{
			I2C_SetMotorSpeed(S1, 1, 1, Arm_Speed);
		}

		//if the arm is out of the encoder range
		else
		{
			I2C_SetMotorSpeed(S1, 1, 1, 0);
		}
	}
}
