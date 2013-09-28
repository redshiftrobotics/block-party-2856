#pragma config(Sensor, S1,     M_CONTROL,      sensorI2CCustom)
#pragma config(Sensor, S2,     M_CONTROL,      sensorI2CCustom)
#pragma config(Sensor, S3,     M_CONTROL,      sensorI2CCustom)
#pragma config(Sensor, S4,     M_CONTROL,      sensorI2CCustom)

#include "Libraries/Motors.h"
#include "Libraries/Servos.h"

task main()
{
	Motors_SetPosition(S1, 1, 1, I2C_GetEncoderPosition(S1, 1, 1) + 1440, 10);

	while(true)
	{
	}
}

//Todo:
//Make setEncoderPosition speed Argument Work
