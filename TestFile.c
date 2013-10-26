#pragma config(Sensor, S1,     M_CONTROL,      sensorI2CCustom)
#pragma config(Sensor, S2,     M_CONTROL,      sensorI2CCustom)
#pragma config(Sensor, S3,     M_CONTROL,      sensorI2CCustom)
#pragma config(Sensor, S4,     M_CONTROL,      sensorI2CCustom)

#include "libraries/Motors.h"
#include "libraries/Servos.h"
#include "libraries/I2C.h"

task main()
{
	Motors_MoveRotations(S1, 1, 1, 10, 10);
	Motors_MoveRotations(S1, 1, 2, 10, 10);
	Motors_MoveRotations(S1, 2, 1, -10, 10);
	Motors_MoveRotations(S1, 2, 2, -10, 10);
	while(true)
	{
	}
}
