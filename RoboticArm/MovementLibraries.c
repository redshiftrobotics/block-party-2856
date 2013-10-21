#pragma config(Sensor, S1,     ,               sensorI2CCustom)
#include "../libraries/Servos.h"

//SUMARRY: Converts Degree to a coordinate that can be used by the servo
int ToServoCoordinate(float Degree)
{
	return (int)(Degree * ((float)255 / (float)191));
}

//SUMARRY: converts the servo coordinates to a degree
//Rotation of a servo is 191 degrees
int ToDegree(float ServoCoordinate)
{
	return (int)(ServoCoordinate / ((float)255 / (float)191));
}

//SUMARRY: Moves the bottom turret. Goes from degrees (93, -83)
void MoveTurret(int Degree)
{
	Degree += 90;
	if(Degree <= ToDegree(245) && Degree >= ToDegree(10))
	{
		Servos_SetPosition(S1, 1, 3, ToServoCoordinate(Degree));
	}
}

//SUMARRY: Moves the top arm joint. Goes from degrees (103, -65)
void MoveTopJoint(int Degree)
{
	Degree += 65;
	if(Degree <= ToDegree(255) && Degree >= ToDegree(0))
	{
		Servos_SetPosition(S1, 1, 1, ToServoCoordinate(Degree));
	}
}

//SUMARRY: Moves the middle joint. Goes from degrees(54, -44)
void MoveMiddleJoint(int Degree)
{
	Degree += 58;
	if(Degree <= ToDegree(150) && Degree >= ToDegree(20))
	{
		Servos_SetPosition(S1, 1, 2, ToServoCoordinate(Degree));
	}
}



task main()
{
	MoveMiddleJoint(-43);
	MoveTopJoint(100);
	while(true)
	{
	}
}
