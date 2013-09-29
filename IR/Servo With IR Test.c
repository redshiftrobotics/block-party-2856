#pragma config(Sensor, S1, ,sensorI2CCustom)
#pragma config(Sensor, S2, IR, sensorI2CCustom)
#include "../libraries/Servos.h"
#include "HitecnicInfaredLibrary.h"

int A, B, C, D, E = 0;
int DegreesOfRotation = 210;

byte ToServoValue(float Input)
{

	return (byte)(255 * Input / DegreesOfRotation);
}

int FindDegree()
{
	bool FirstTime = true;
	int GreatestValue = 0;
	int GreatestValueDegree = 0;
	//writeDebugStreamLine("--New Test--");

	for(int Degree = DegreesOfRotation - 180; Degree < DegreesOfRotation; Degree += 5)
	{
		Servos_SetPosition(S1, 1, 1, ToServoValue(Degree));
		HTIRS2readAllACStrength(IR, A, B, C, D, E);



		if(B < 10 && D < 10 && C > GreatestValue)
		{
			GreatestValue = C;
			GreatestValueDegree = Degree - (DegreesOfRotation - 180);
			writeDebugStream("%i = ", Degree - (DegreesOfRotation - 180));
			writeDebugStream("B: %i, ", B);
			writeDebugStream("C: %i, ", C);
			writeDebugStreamLine("D: %i", D);
			writeDebugStreamLine("%i", Degree - (DegreesOfRotation - 180));

		}



		if(FirstTime)
		{
			Sleep(1000);
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
		writeDebugStreamLine("--%i--", FindDegree());
	}
}
