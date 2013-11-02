#include "I2C.h"

// TODO: add the final method to send the bus messages from the job register

/*
	Table of motor mode numbers:
	0: Move by encoder count
	1: Move by speed
*/

int Motors_MotorMovementMode[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
long Motors_MotorMovementNumber[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

// internal method, do not use
// for a given motor, gets a unique id throughout the entire robot
int _Motors_GetCanonicalMotorId(tSensors SensorPort, int DaisyChainLevel, int MotorNumber)
{
	// initially assume the id is 0. it will be manipulated from here.
	int id = 0;

	// get a port id that we can work with
	int port = _I2C_GetIntFromPort(SensorPort);

	// add in the daisychain level information
	id += (DaisyChainLevel-1)*2;

	// add in the motor information
	id += MotorNumber-1;

	// add in the port information
	id += (port-1)*8;
}

void Motors_SetSpeed(tSensors Port, int DaisyChainLevel, int MotorNumber, int Speed)
{
	// TODO: possible typecasting problem of int Speed to long Motors_MotorMovementNumber
	Motors_MotorMovementMode[_Motors_GetCanonicalMotorId(Port, DaisyChainLevel, MotorNumber)] = 1;
	Motors_MotorMovementNumber[_Motors_GetCanonicalMotorId(Port, DaisyChainLevel, MotorNumber)] = Speed;
}

void Motors_SetPosition(tSensors Port, int DaisyChainLevel, int MotorNumber, long MotorEncoder, int Speed)
{
	// TODO: the Speed argument is silently dropped
	Motors_MotorMovementMode[_Motors_GetCanonicalMotorId(Port, DaisyChainLevel, MotorNumber)] = 0;
	Motors_MotorMovementNumber[_Motors_GetCanonicalMotorId(Port, DaisyChainLevel, MotorNumber)] = MotorEncoder;
}
