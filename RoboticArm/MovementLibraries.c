#include "../libraries/Servos.h"

//SUMARRY: Converts Degree to a coordinate that can be used by the servo
int MovementLibraries_ToServoCoordinate(float Degree)
{
	return (int)(Degree * ((float)255 / (float)191));
}

//SUMARRY: converts the servo coordinates to a degree
//Rotation of a servo is 191 degrees
int MovementLibraries_ToDegree(float ServoCoordinate)
{
	return (int)(ServoCoordinate / ((float)255 / (float)191));
}

//SUMARRY: Moves the bottom turret. Goes from degrees (93, -83)
void MovementLibraries_MoveTurret(int Degree)
{
	Degree += 90;
	if(Degree <= MovementLibraries_ToDegree(245) && Degree >= MovementLibraries_ToDegree(10))
	{
		Servos_SetPosition(S1, 1, 3, MovementLibraries_ToServoCoordinate(Degree));
	}
}

//SUMARRY: Moves the top arm joint. Goes from degrees (103, -65)
void MovementLibraries_MoveTopJoint(int Degree)
{
	Degree += 65;
	if(Degree <= MovementLibraries_ToDegree(255) && Degree >= MovementLibraries_ToDegree(0))
	{
		Servos_SetPosition(S1, 1, 1, MovementLibraries_ToServoCoordinate(Degree));
	}
}

//SUMARRY: Moves the middle joint. Goes from degrees(54, -44)
void MovementLibraries_MoveMiddleJoint(int Degree)
{
	Degree += 58;
	if(Degree <= MovementLibraries_ToDegree(150) && Degree >= MovementLibraries_ToDegree(20))
	{
		Servos_SetPosition(S1, 1, 2, MovementLibraries_ToServoCoordinate(Degree));
	}
}
