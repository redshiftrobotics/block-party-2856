#pragma config(Sensor, S1,     ServoController,               sensorI2CCustom)
#include "MovementLibraries.c"
#include "InverseKinematics.c"

task main()
{
	//setting y
	int y = 90;
	//creating a variable to store a pointer
	int *p;
	//creating a pointer to the variable Y and setting p to its value
	p = &y;

	//writing y
	writeDebugStream("%i", y);
	//dereferencing p and writing it
	writeDebugStreamLine(", %i", *p);

	//AJ();
	//MovementLibraries_MoveMiddleJoint(-43);
	//MovementLibraries_MoveTopJoint(100);
	//writeDebugStreamLine("%f", InverseKinematics_ToRadians(180));

	while(true)
	{
	}
}
