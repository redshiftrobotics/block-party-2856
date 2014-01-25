#include "I2C.h"

//sets globals
bool Arm_Initialized = false;
long Arm_BottomEncoderLimit = 0;
long Arm_TopEncoderLimit = 0;
long Arm_Encoder = 0;
int Arm_Speed = 0;

void Arm_Reinitialize()
{
	hogCPU();
	Arm_Initialized = false;
	Arm_BottomEncoderLimit = 0;
	Arm_TopEncoderLimit = 0;
	Arm_Encoder = 0;
	Arm_Speed = 0;
	releaseCPU();
}

void Arm_SetSpeed(int Speed)
{
	hogCPU();
	if(Arm_Initialized)
	{
		writeDebugStreamLine("Change Speed to %i", Speed);
		Arm_Speed = Speed;
	}
	releaseCPU();
}

void Arm_Update()
{
	Arm_Encoder = I2C_GetEncoderPosition(S1, 1, 1);

	//if the arm isn't initialized yet
	if(!Arm_Initialized)
	{
		//writeDebugStreamLine("%i", SensorValue[S4] == 1);

		//lower it to reset
		I2C_SetMotorSpeed(S1, 1, 1, 50);

		//if the lower limit is triggered, set the upper and lower encoder bounds
		if(SensorValue[S4] == 1)
		{
			Arm_Initialized = true;
			Arm_BottomEncoderLimit = Arm_Encoder + (0 * 1440); //the amount of distance from the buttom press down. This lets it go below the button press.
			Arm_TopEncoderLimit = Arm_Encoder - (10 * 1440);
		}
	}

	//if the arm is initialized
	else
	{
		writeDebugStream("Encoder: %i", Arm_Encoder);
		writeDebugStream(", Upper: %i", Arm_TopEncoderLimit);
		writeDebugStreamLine(", Lower: %i", Arm_BottomEncoderLimit);

		//if the arm is with in the encoder range
		if(Arm_Encoder >= Arm_TopEncoderLimit && Arm_Encoder <= Arm_BottomEncoderLimit)
		{
			//writeDebugStreamLine("in");
			I2C_SetMotorSpeed(S1, 1, 1, Arm_Speed);
		}

		//if the arm is below the bottom encoder and trying to go up
		else if(Arm_Encoder > Arm_BottomEncoderLimit && Arm_Speed < 0)
		{
			//writeDebugStreamLine("below ok");
			I2C_SetMotorSpeed(S1, 1, 1, Arm_Speed);
		}

		//if the arm is above the top encoder and trying to go down
		else if(Arm_Encoder < Arm_TopEncoderLimit && Arm_Speed > 0)
		{
			//writeDebugStreamLine("above ok");
			I2C_SetMotorSpeed(S1, 1, 1, Arm_Speed);
		}

		//if the arm is out of the encoder range and trying to go the wrong direction
		else
		{
			//writeDebugStreamLine("not ok");
			I2C_SetMotorSpeed(S1, 1, 1, 0);
		}
	}
}
