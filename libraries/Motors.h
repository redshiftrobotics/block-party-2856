#include "Common.h"
#include "I2C.h"

tSensors Sensors[100];
int Motors_Length = 0;
int Motors_DaisyChainLevel[100];
int Motors_Number[100];
int Motors_Speed[100];
int Motors_Encoder[100];
bool Motors_MovingToPosition[100];
bool Motors_UpdateMotorsInitialized = false;
task Motors_UpdateMotors;



void Motors_SetAction(tSensors Sensor, int DaisyChain, int MNumber, int MSpeed, int MEncoder, bool MovingToList)
{
	bool NewValueAdded = false;

	if(Motors_UpdateMotorsInitialized == false)
	{
		Motors_UpdateMotorsInitialized = true;
		StartTask(Motors_UpdateMotors);
	}

	for(int i = 0; i < Motors_Length; i++)
	{
		writeDebugStreamLine("%i", Motors_Length);
		if(Sensor == Sensors[i] && DaisyChain == Motors_DaisyChainLevel[i] && MNumber == Motors_Number[i])
		{
			Sensors[i] = Sensor;
			Motors_Encoder[i] = MEncoder;
			Motors_DaisyChainLevel[i] = DaisyChain;
			Motors_Number[i] = MNumber;
			Motors_Speed[i] = MSpeed;
			Motors_MovingToPosition[i] = MovingToList;
			NewValueAdded = true;
		}
	}
	if(!NewValueAdded)
	{
		Sensors[Motors_Length] = Sensor;
		Motors_DaisyChainLevel[Motors_Length] = DaisyChain;
		Motors_Number[Motors_Length] = MNumber;
		Motors_Encoder[Motors_Length] = MEncoder;
		Motors_Speed[Motors_Length] = MSpeed;
		Motors_MovingToPosition[Motors_Length] = MovingToList;
		Motors_Length++;
	}
}

void Motors_SetSpeed(tSensors Sensor, int DaisyChain, int MNumber, int MSpeed)
{
	Motors_SetAction(Sensor, DaisyChain, MNumber, MSpeed, 0, false);
}

void Motors_SetPosition(tSensors Sensor, int DaisyChain, int MNumber, int Encoder, int MSpeed)
{
	Motors_SetAction(Sensor, DaisyChain, MNumber, MSpeed, Encoder, true);
}

task Motors_UpdateMotors()
{
	while(true)
	{
		for(int i = 0; i < Motors_Length; i++)
		{
			if(Motors_MovingToPosition[i] == false)
			{
				I2C_SetMotorSpeed(Sensors[i], Motors_DaisyChainLevel[i], Motors_Number[i], Motors_Speed[i]);
			}
			else if(Motors_MovingToPosition[i] == true)
			{
				I2C_SetEncoderPosition(Sensors[i], Motors_DaisyChainLevel[i], Motors_Number[i], Motors_Encoder[i], Motors_Speed[i]);
			}
		}
	}
}
