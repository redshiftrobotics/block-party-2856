#pragma config(Sensor, S1,     M_CONTROL,      sensorI2CCustom)

#include "libraries/libi2cmotor.h"

//void RotateDegrees(bool DisplayTargetPosition, bool DisplayCurrentPosition, long TargetPosition)
//{
//	int TargetPosition = EncoderValue() + 1440;
//	SetEncoderPosition(
//}



task main()
{
	//i2cmotor_debug = true;
	//int encoderTarget = getEncoderPosition(2, S1) + 1440;

	while(true)
	{
		setMotorSpeed(10, S1, 1);
		//gotoEncoderPosition(2, S1, encoderTarget);
		//Sleep(10);
	}
}
