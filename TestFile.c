#pragma config(Sensor, S1,     M_CONTROL,      sensorI2CCustom)
#pragma config(Sensor, S2,     M_CONTROL,      sensorI2CCustom)
#pragma config(Sensor, S3,     M_CONTROL,      sensorI2CCustom)
#pragma config(Sensor, S4,     M_CONTROL,      sensorI2CCustom)

#include "Libraries/Motors.h"
#include "Libraries/Servos.h"

task main()
{
	Servos_SetPosition(S1, 1, 1, 150);
	//Servos_SetPosition(S2, 1, 1, 150);
	while(true)
	{
	}
}

//Todo:
//Make setEncoderPosition speed Argument Work
