#pragma config(Sensor, S1,     M_CONTROL,      sensorI2CCustom)

#include "./drivers/common.h"
#include "libraries/libi2cmotor.h"

//void RotateDegrees(bool DisplayTargetPosition, bool DisplayCurrentPosition, long TargetPosition)
//{
//	int TargetPosition = EncoderValue() + 1440;
//	SetEncoderPosition(
//}



task main()
{
	i2cmotor_debug = true;

	int encoderTarget = getEncoderPosition(2, S1) + 1440;

	while(true)
	{
		gotoEncoderPosition(2, S1, encoderTarget);
		Sleep(10);
	}

	/*
	setEncoderPosition(2, S1, TargetPosition);

  while(true)
  {
  	eraseDisplay();
  	nxtDisplayString(0, "%i", TargetPosition);
  	nxtDisplayString(1, "%i", getEncoderValue(2, S1));
  	if (isBusy(2, S1))
  		{
  			nxtDisplayString(2, "Still working, yo!");
  		} else {
  			nxtDisplayString(2, "Done!");
  		}
  	Sleep(10);

	}*/
}
