#include "Common.h"
#include "I2C.h"

//Create Task Table
int Motors_ListLength = 0;

int Motors_Sensor[10];
int Motors_DaisyChainLevel[10];
int Motors_MotorNumber[10];
long Motors_Encoder[10];
int Motors_Speed[10];

string Motors_Action[10];

//Initialize Task
task TableExecuter;

bool IsTableExecuterStarted = false;

//Function Starts Tabel Executer
void Motors_StartTableExecuter()
{
	if(IsTableExecuterStarted == false)
	{
		StartTask(TableExecuter);
		IsTableExecuterStarted = true;
	}
}

//Table Executer Loop
task TableExecuter()
{
	while(true)
	{
		for(int i = 0; i < Motors_ListLength; i++)
		{
			if(Motors_Action[i] == "SetSpeed")
			{
				I2C_SetMotorSpeed(Motors_Sensor[i], Motors_DaisyChainLevel[i], Motors_MotorNumber[i], Motors_Speed[i]);
			}
			else if(Motors_Action[i] == "SetPosition")
			{
				I2C_SetEncoderPosition(Motors_Sensor[i], Motors_DaisyChainLevel[i], Motors_MotorNumber[i], Motors_Encoder[i], Motors_Speed[i]);
			}
		}
	}
}

//
void Motors_SetSpeed(tSensors Sensor, int DaisyChainLevel, int MotorNumber, int MotorSpeed)
{
	Motors_StartTableExecuter();

	Motors_Action[Motors_ListLength] = "SetSpeed";
	Motors_Sensor[Motors_ListLength] = Sensor;
	Motors_DaisyChainLevel[Motors_ListLength] = DaisyChainLevel;
	Motors_MotorNumber[Motors_ListLength] = MotorNumber;
	Motors_Speed[Motors_ListLength] = MotorSpeed;

	Motors_ListLength++;
}

void Motors_SetPosition(int DaisyChainLevel, int MotorNumber, long MotorEncoder, int MotorSpeed, tSensors Sensor)
{
	writeDebugStreamLine("Second Value: %i", 	MotorEncoder);
	//The above value reads wrong.

	Motors_StartTableExecuter();

	Motors_Action[Motors_ListLength] = "SetPosition";
	Motors_Sensor[Motors_ListLength] = Sensor;
	Motors_DaisyChainLevel[Motors_ListLength] = DaisyChainLevel;
	Motors_MotorNumber[Motors_ListLength] = MotorNumber;
	Motors_Encoder[Motors_ListLength] = MotorEncoder;
	Motors_Speed[Motors_ListLength] = MotorSpeed;

	Motors_ListLength++;
}
