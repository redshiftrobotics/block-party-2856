#pragma config(Sensor, S1,     ServoController,               sensorI2CCustom)
#include "InverseKinematics.c"

task main()
{
	//MovementLibraries_MoveMiddleJoint(76);
	//MovementLibraries_MoveTopJoint(-65);
		int X = 0;
		int Y = -5;
		int Z = 20;

		InverseKinematics_ThreeJoint(21, 18, X, Y, Z);
}
