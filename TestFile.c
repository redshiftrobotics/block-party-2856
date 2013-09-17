#pragma config(Sensor, S1,     M_CONTROL,      sensorI2CCustom)
#pragma config(Sensor, S2,     M_CONTROL,      sensorI2CCustom)
#pragma config(Sensor, S3,     M_CONTROL,      sensorI2CCustom)
#pragma config(Sensor, S4,     M_CONTROL,      sensorI2CCustom)

#include "libraries/libi2cmotor.h"

task main()
{
	while(true)
	{
		//nxtDisplayString(0, "%i", getEncoderPosition(S1, 2, 1));
		setEncoderPosition(S1, 2, 2, 1);
	}
}

//Todo:
//Make setEncoderPosition speed Argument Work
