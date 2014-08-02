#pragma config(Sensor, S1,     ,               sensorI2CCustom)

#include "../libraries/Motors.h"

task main()
{
	Motors_SetSpeed(S1, 1, 1, -20);
	Sleep(4000);
	Motors_SetSpeed(S1, 1, 1, 0);
}
