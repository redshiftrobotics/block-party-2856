#pragma config(Sensor, S1,     M_CONTROL,      sensorI2CCustom)

#include "libraries/libi2cmotor.h"

//void RotateDegrees(bool DisplayTargetPosition, bool DisplayCurrentPosition, long TargetPosition)
//{
//	int TargetPosition = EncoderValue() + 1440;
//	SetEncoderPosition(
//}

void MovePosition()
{
	long Input = 2880;
	tByteArray I2Crequest;

	I2Crequest[0] = 8;

	//sends the adress as the first byte
  I2Crequest[1] = 0x02;

	//sets the starting position to start sending data at
  	//sets the starting position
  	I2Crequest[2] = 0x40;

  	//passes in the target position
  	I2Crequest[3] = (byte)((Input >> 24) & 0x000000ff);
	  I2Crequest[4] = (byte)((Input >> 16) & 0x000000ff);
	  I2Crequest[5] = (byte)((Input >> 8) & 0x000000ff);
	  I2Crequest[6] = (byte)(Input & 0x000000ff);

  	//sets the motor mode
	  I2Crequest[7] = 0b00000010;

  	//sets the motor power
	  I2Crequest[8] = 0b00010000;

	 writeI2C(S1, I2Crequest);
}


void getEncoderPosition2()
{
	//initializes the arrays
		tByteArray I2Crequest;
		tByteArray I2Cresponse;

		//sets the number of bytes to send:
		I2Crequest[0] = 2;

		//sends the adress as the first byte
		//daisychain level 0 will add 0, daisychain level 1 will add 2 to get 0x04, etc.
	  I2Crequest[1] = 0x02;

	  //motor 2
		 I2Crequest[2] = 0x50;

	  //writes the data, and gets the response
	  writeI2C(S1, I2Crequest, I2Cresponse, 4);

	  //creates a long out of the bytes
	  long EncoderValue = (I2Cresponse[0] << 24) + (I2Cresponse[1] << 16) + (I2Cresponse[2] << 8) + (I2Cresponse[3] << 0);

	  eraseDisplay();
		nxtDisplayString(0, "%i", EncoderValue);
}

task main()
{


	long TargetPosition = getEncoderPosition(S1, 1, 2) + 1440;
	long CurrentPosition = getEncoderPosition(S1, 1, 2);
	while(true)
	{
		eraseDisplay();

		nxtDisplayString(0, "%i", CurrentPosition);
		nxtDisplayString(1, "%i", TargetPosition);
		nxtDisplayString(2, "%i", isBusy(2, S1, 0));

		setEncoderPosition(S1, 1, 2, TargetPosition);
		//MovePosition();
		//setEncoderPosition(S1, 2, 1, 2880);
		//getEncoderPosition2();
		//setEncoderPosition(1, S1, 2, 2880);
	}
}

		//setEncoderPosition(2, S1, 0, (long)0);
		//nxtDisplayString(0, "%i", getEncoderPosition(2, S1, 0));

	//setMotorSpeed(2, S1, 0, -50);

	//setMotorSpeed(S1, 2, 1, -50);
	//setMotorSpeed(S1, 1, 2, -50);

		//gotoEncoderPosition(2, S1, 0, encoderTarget);
		//Sleep(10);
