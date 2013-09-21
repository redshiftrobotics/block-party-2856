#include "Common.h"
#include "I2C.h"

bool Servos_Initialzied = false;
task Servos_ServoUpdate;

tSensors Servos_ServoPort[100];
int Servos_DaisyChainLevel[100];
int Servos_ServoNumber[100];
int Servos_Position[100];
int Servos_Length = 0;

void Servos_SetPosition(tSensors Port, int DaisyChainLevel, int ServoNumber, byte ServoPosition)
{
	if(Servos_Initialzied == false)
	{
		StartTask(Servos_ServoUpdate);
		Servos_Initialzied = true;
	}

	bool PositionExists = false;
	for(int i = 0; i < Servos_Length; i++)
	{
		if(Port == Servos_ServoPort[i] && DaisyChainLevel == Servos_DaisyChainLevel[i] && ServoNumber == Servos_ServoNumber)
		{
			Servos_Position[i] = ServoPosition;
			PositionExists = true;
		}
	}

	if(PositionExists == false)
	{
		Servos_ServoPort[Servos_Length] = Port;
		Servos_DaisyChainLevel[Servos_Length] = DaisyChainLevel;
		Servos_ServoNumber[Servos_Length] = ServoNumber;
		Servos_Position[Servos_Length] = ServoPosition;
		Servos_Length++;
	}
}

task Servos_ServoUpdate()
{
	while(true)
	{
		for(int i = 0; i < Servos_Length; i++)
		{
			I2C_WritePMW(Servos_ServoPort[i], Servos_DaisyChainLevel[i], 0);
			I2C_MoveServo(Servos_ServoPort[i], Servos_DaisyChainLevel[i], Servos_ServoNumber[i], Servos_Position[i]);
		}
	}
}
