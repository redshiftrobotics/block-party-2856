#pragma config(Sensor, S1,     M_CONTROL,      sensorI2CCustom)

#include "./drivers/common.h"

long EncoderValue()
{
		//initializes the arrays
		tByteArray I2Crequest;
		tByteArray I2Cresponse;

		//sets the number of bytes to send:
		I2Crequest[0] = 2;

		//sends the adress as the first byte
	  I2Crequest[1] = 0x02;

	  //sets the starting position to start sending data at
	  I2Crequest[2] = 0x50;

	  //writes the data, and gets the response
	  writeI2C(S1, I2Crequest, I2Cresponse, 4);

	  //creates a long out of the bytes
	  long EncoderValue = (I2Cresponse[0] << 24) + (I2Cresponse[1] << 16) + (I2Cresponse[2] << 8) + (I2Cresponse[3] << 0);

	  //returns the long
  	return EncoderValue;
}

void SetEncoderPosition(long Input)
{
	//initializes the arrays
	tByteArray I2Crequest;

	//sets the number of bytes to send:
	I2Crequest[0] = 8;

	//sends the adress as the first byte
  I2Crequest[1] = 0x02;

	//sets the starting position to start sending data at
  I2Crequest[2] = 0x46;

  //sets the motor power
  I2Crequest[3] = 0b00010000;

  //sets the motor mode
  I2Crequest[4] = 0b00000010;

  I2Crequest[5] = (byte)((Input >> 24) & 0x000000ff);
  I2Crequest[6] = (byte)((Input >> 16) & 0x000000ff);
  I2Crequest[7] = (byte)((Input >> 8) & 0x000000ff);
  I2Crequest[8] = (byte)(Input & 0x000000ff);

  writeI2C(S1, I2Crequest);
}

//void RotateDegrees(bool DisplayTargetPosition, bool DisplayCurrentPosition, long TargetPosition)
//{
//	int TargetPosition = EncoderValue() + 1440;
//	SetEncoderPosition(
//}


task main()
{
	int TargetPosition = EncoderValue() + 1440;

	SetEncoderPosition(TargetPosition);

  while(true)
  {
  	eraseDisplay();
  	nxtDisplayString(0, "%i", TargetPosition);
  	nxtDisplayString(1, "%i", EncoderValue());
  	Sleep(10);
	}
}
