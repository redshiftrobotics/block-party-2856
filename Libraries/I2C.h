#include "Common.h"

// doesn't support daisychains
// also TODO: setting a constant speed and a rotating a certain amount

// TODO: look at isaac's library for this

/*

IMPORTANT:

A. THIS CODE REQUIRES ENCODERS!

B. Standard method argument order is:

   	void foo(tSensors port, int daisychainLevel, int motorNumber, sbyte bar)

   Where foo is your method name and bar is any variable that you need in addition to the standard three.
   Bar is optional, but your method must always respect motorNumber, port and daisychainLevel.

*/

void I2C_MoveServo(tSensors port, int DaisyChainLevel, int ServoNumber, byte Position)
{
	tByteArray I2Crequest;
	I2Crequest[0] = 3;
	I2Crequest[1] = 0x02 * DaisyChainLevel;
	I2Crequest[2] = 0x41 + ServoNumber;
	I2Crequest[3] = Position;

	writeI2C(port, I2Crequest);
}

void I2C_WritePMW(tSensors port, int DaisyChainLevel, byte Status)
{
	tByteArray I2Crequest;
	tByteArray I2Cresponse;
	I2Crequest[0] = 3;
	I2Crequest[1] = 0x02 * DaisyChainLevel;
	I2Crequest[2] = 0x48;
	I2Crequest[3] = Status;
	writeI2C(port, I2Crequest, I2Cresponse, 1);
}

void I2C_SetMotorSpeed(tSensors port, int daisychainLevel, int MotorNumber, sbyte Speed)
{
	daisychainLevel --;
	tByteArray I2Crequest;

	I2Crequest[0] = 4;

	// daisychain level 0 will add 0, daisychain level 1 will add 2 to get 0x04, etc.
	I2Crequest[1] = 0x02 + daisychainLevel*2;


	if(MotorNumber == 1)
	{
		I2Crequest[2] = 0x44;
		// if we're on motor 1 mode comes first...
		I2Crequest[3] = 0b00000001;
		I2Crequest[4] = Speed;
	}
	else
	{
		I2Crequest[2] = 0x46;
		// ...but if we're on motor 2, speed comes first.
		I2Crequest[3] = Speed;
		I2Crequest[4] = 0b00000001;
	}

	writeI2C(port, I2Crequest);
}

// pass this 1 or 2 for the motor and S[1-4] for the port
long I2C_GetEncoderPosition(tSensors port, int daisychainLevel, int MotorNumber)
{
		daisychainLevel--;
		//initializes the arrays
		tByteArray I2Crequest;
		tByteArray I2Cresponse;

		//sets the number of bytes to send:
		I2Crequest[0] = 2;

		//sends the adress as the first byte
		//daisychain level 0 will add 0, daisychain level 1 will add 2 to get 0x04, etc.
	  I2Crequest[1] = 0x02 + daisychainLevel*2;

	  //sets the starting position to start sending data at
	  if (MotorNumber == 1)
	  {
	  	I2Crequest[2] = 0x4C;
		}
		else
		{
		  I2Crequest[2] = 0x50;
		}

	  //writes the data, and gets the response
	  writeI2C(port, I2Crequest, I2Cresponse, 4);

	  //creates a long out of the bytes
	  //note: when debugging with any %i construct, this will be cast to an integer and will overflow at 32767!
	  long EncoderValue = (I2Cresponse[0] << 24) + (I2Cresponse[1] << 16) + (I2Cresponse[2] << 8) + (I2Cresponse[3] << 0);

	  //returns the long
  	return EncoderValue;
}

// motor should be 1 or 2, port should be S[1-4], Input should be the position to move to
void I2C_SetEncoderPosition(tSensors port, int daisychainLevel, int MotorNumber, long EncoderPosition, byte MotorSpeed)
{
	daisychainLevel--;

	//initializes the arrays
	tByteArray I2Crequest;

	//sets the number of bytes to send:
	I2Crequest[0] = 8;

	//sends the adress as the first byte
  I2Crequest[1] = 0x02 + daisychainLevel*2;

	//sets the starting position to start sending data at
  if (MotorNumber == 1)
  {
  	//sets the starting position
  	I2Crequest[2] = 0x40;

  	//passes in the target position
  	I2Crequest[3] = (byte)((EncoderPosition >> 24) & 0x000000ff);
	  I2Crequest[4] = (byte)((EncoderPosition >> 16) & 0x000000ff);
	  I2Crequest[5] = (byte)((EncoderPosition >> 8) & 0x000000ff);
	  I2Crequest[6] = (byte)(EncoderPosition & 0x000000ff);

  	//sets the motor mode
	  I2Crequest[7] = 0b00000010;

  	//sets the motor power
	  I2Crequest[8] = MotorSpeed;
	}
	else if (MotorNumber == 2)
	{
		//sets the starting position
  	I2Crequest[2] = 0x46;

	  //sets the motor power
	  I2Crequest[3] = MotorSpeed;

	  //sets the motor mode
	  I2Crequest[4] = 0b00000010;

	  //passes in the target position
	  I2Crequest[5] = (byte)((EncoderPosition >> 24) & 0x000000ff);
	  I2Crequest[6] = (byte)((EncoderPosition >> 16) & 0x000000ff);
	  I2Crequest[7] = (byte)((EncoderPosition >> 8) & 0x000000ff);
	  I2Crequest[8] = (byte)(EncoderPosition & 0x000000ff);
  }

  writeI2C(port, I2Crequest);
}
