#pragma config(Sensor, S1, ,sensorI2CCustom)
#pragma config(Sensor, S2, IR, sensorI2CCustom)
#include "../libraries/Servos.h"
#include "../libraries/Motors.h"
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

		//writeDebugStream("%i", Degree);
		//writeDebugStreamLine(", %i", C);

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
	return GreatestValueDegree - 20;
	//account for unknown systematic error: will try to solve eventually
}

int BoxNumber()
{
	int Degree = FindDegree();

	//Common values should be:
	//1: 60
	//2: 75
	//3: 105
	//4: 120

	int Lowest = 40;
	int OneUpper = 65;
	int TwoUpper = 95;
	int ThreeUpper = 110;
	int Highest = 140;

	if(Degree >= Lowest && Degree <= OneUpper)
	{
		return 1;
	}
	else if(Degree > OneUpper && Degree <= TwoUpper)
	{
		return 2;
	}
	else if(Degree > TwoUpper && Degree <= ThreeUpper)
	{
		return 3;
	}
	else if(Degree > ThreeUpper && Degree < Highest)
	{
		return 4;
	}
	return -1;
}


task main()
{
	//distance 3' 1"

	int Box = BoxNumber();
	writeDebugStreamLine("%i", Box);

	if(Box == 1)
	{
		Motors_MoveRotations(S1, 1, 1, .25, 10);
		Motors_MoveRotations(S1, 1, 2, .25, 10);
		Motors_MoveRotations(S1, 2, 1, .25, 10);
		Motors_MoveRotations(S1, 2, 2, .25, 10);
		sleep(2000);
		Motors_MoveRotations(S1, 1, 1, 2.5, 10);
		Motors_MoveRotations(S1, 1, 2, 2.5, 10);
		Motors_MoveRotations(S1, 2, 1, -2.5, 10);
		Motors_MoveRotations(S1, 2, 2, -2.5, 10);
	}
	else if(Box == 2)
	{
		Motors_MoveRotations(S1, 1, 1, .15, 10);
		Motors_MoveRotations(S1, 1, 2, .15, 10);
		Motors_MoveRotations(S1, 2, 1, .15, 10);
		Motors_MoveRotations(S1, 2, 2, .15, 10);
		sleep(2000);
		Motors_MoveRotations(S1, 1, 1, 2, 10);
		Motors_MoveRotations(S1, 1, 2, 2, 10);
		Motors_MoveRotations(S1, 2, 1, -2, 10);
		Motors_MoveRotations(S1, 2, 2, -2, 10);
	}
	if(Box == 3)
	{
		Motors_MoveRotations(S1, 1, 1, -.15, 10);
		Motors_MoveRotations(S1, 1, 2, -.15, 10);
		Motors_MoveRotations(S1, 2, 1, -.15, 10);
		Motors_MoveRotations(S1, 2, 2, -.15, 10);
		sleep(2000);
		Motors_MoveRotations(S1, 1, 1, 2, 10);
		Motors_MoveRotations(S1, 1, 2, 2, 10);
		Motors_MoveRotations(S1, 2, 1, -2, 10);
		Motors_MoveRotations(S1, 2, 2, -2, 10);
	}
	else if(Box == 4)
	{
		Motors_MoveRotations(S1, 1, 1, -.25, 10);
		Motors_MoveRotations(S1, 1, 2, -.25, 10);
		Motors_MoveRotations(S1, 2, 1, -.25, 10);
		Motors_MoveRotations(S1, 2, 2, -.25, 10);
		sleep(2000);
		Motors_MoveRotations(S1, 1, 1, 2.5, 10);
		Motors_MoveRotations(S1, 1, 2, 2.5, 10);
		Motors_MoveRotations(S1, 2, 1, -2.5, 10);
		Motors_MoveRotations(S1, 2, 2, -2.5, 10);
	}
}
