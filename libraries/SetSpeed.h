#include "saas_common.h"

tSensors Sensors[100];
int MotorSpeedLength = 0;
int DaisyChainLevel[100];
int MotorNumber[100];
int MotorSpeed[100];
bool UpdateMotorSpeedsInitialized = false;
task UpdateMotorSpeeds;

void SetSpeed(tSensors Sensor, int DaisyChain, int MNumber, int MSpeed)
{
	bool NewValueAdded = false;

	if(UpdateMotorSpeedsInitialized == false)
	{
		UpdateMotorSpeedsInitialized = true;
		StartTask(UpdateMotorSpeeds);
	}

	for(int i = 0; i < MotorSpeedLength; i++)
	{
		if(Sensor == Sensors[i] && DaisyChain == DaisyChainLevel[i] && MNumber == MotorNumber[i])
		{
			Sensors[i] = Sensor;
			DaisyChainLevel[i] = DaisyChain;
			MotorNumber[i] = MNumber;
			MotorSpeed[i] = MSpeed;
			NewValueAdded = true;
			MotorSpeedLength++;
		}
	}
	if(!NewValueAdded)
	{
		Sensors[MotorSpeedLength] = Sensor;
		DaisyChainLevel[MotorSpeedLength] = DaisyChain;
		MotorNumber[MotorSpeedLength] = MNumber;
		MotorSpeed[MotorSpeedLength] = MSpeed;
		MotorSpeedLength++;
	}
}

task UpdateMotorSpeeds()
{
	while(true)
	{
		for(int i = 0; i < MotorSpeedLength; i++)
		{
				setMotorSpeed(Sensors[i], DaisyChainLevel[i], MotorNumber[i], MotorSpeed[i]);
				//WriteDebug("Motor Speed Set");
		}
	}
}
