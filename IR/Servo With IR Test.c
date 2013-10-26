#pragma config(Sensor, S1, ,sensorI2CCustom)
#pragma config(Sensor, S2, IR, sensorI2CCustom)
#include "../libraries/Servos.h"
#include "HitecnicInfaredLibrary.h"

int A, B, C, D, E = 0;
int DegreesOfRotation = 191;

byte ToServoValue(float Input)
{
	return (byte)(255 * Input / DegreesOfRotation);
}

int FindDegree()
{
	bool FirstTime = true;
	int GreatestValue = 0;
	int GreatestValueDegree = 0;

	for(int Degree = 0; Degree < DegreesOfRotation; Degree += 5)
	{


		Servos_SetPosition(S1, 3, 1, ToServoValue(Degree));

		HTIRS2readAllACStrength(IR, A, B, C, D, E);

		writeDebugStream("%i", Degree);
		writeDebugStreamLine(", %i", C);

		if(B < 10 && D < 10 && C > GreatestValue)
		{
			GreatestValue = C;
			GreatestValueDegree = Degree;
		}

		if(FirstTime)
		{
			Sleep(500);
			FirstTime = false;
		}
		else
		{
			Sleep(100);
		}
	}
	return GreatestValueDegree;
}


task main()
{
	while(true)
	{
		WriteDebugStreamLine("FIBAL:: %i", FindDegree());
	}
}
