#include "saas_common.h"

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
bool i2cmotor_debug = false;

// you should call this at the beginning of every method in this file.
/*void i2cmotor_verifyArgs(int motorNumber, tSensors port, int daisychainLevel)
{
	assert(motorNumber == 1 || motorNumber == 2);
	assert(port == S1 || port == S2 || port == S3 || port == S4);
	assert(daisychainLevel == 0 || daisychainLevel == 1 || daisychainLevel == 2 || daisychainLevel == 3);
}
*/

void setMotorSpeed(tSensors port, int daisychainLevel, int MotorNumber, sbyte Speed)
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
long getEncoderPosition(tSensors port, int daisychainLevel, int MotorNumber)
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
	  long EncoderValue = (I2Cresponse[0] << 24) + (I2Cresponse[1] << 16) + (I2Cresponse[2] << 8) + (I2Cresponse[3] << 0);

	  //returns the long
  	return EncoderValue;
}

// motor should be 1 or 2, port should be S[1-4], Input should be the position to move to
void setEncoderPosition(tSensors port, int daisychainLevel, int MotorNumber, long Input)
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
  	I2Crequest[3] = (byte)((Input >> 24) & 0x000000ff);
	  I2Crequest[4] = (byte)((Input >> 16) & 0x000000ff);
	  I2Crequest[5] = (byte)((Input >> 8) & 0x000000ff);
	  I2Crequest[6] = (byte)(Input & 0x000000ff);

  	//sets the motor mode
	  I2Crequest[7] = 0b00000010;

  	//sets the motor power
	  I2Crequest[8] = 0b00010000;
	}
	else if (MotorNumber == 2)
	{
		//sets the starting position
  	I2Crequest[2] = 0x46;

	  //sets the motor power
	  I2Crequest[3] = 0b00010000;

	  //sets the motor mode
	  I2Crequest[4] = 0b00000010;

	  //passes in the target position
	  I2Crequest[5] = (byte)((Input >> 24) & 0x000000ff);
	  I2Crequest[6] = (byte)((Input >> 16) & 0x000000ff);
	  I2Crequest[7] = (byte)((Input >> 8) & 0x000000ff);
	  I2Crequest[8] = (byte)(Input & 0x000000ff);
  }

  writeI2C(port, I2Crequest);
}

// see getEncoderValue() for args
int isBusy(tSensors port, int daisychainLevel, int motor)
{
	tByteArray I2Crequest;
	tByteArray I2Cresponse;

	ubyte busy;

	// number of additional bytes to send
	I2Crequest[0] = 2;

	// standard lego sensor address
	I2Crequest[1] = 0x02 + daisychainLevel*2;

	// pin address for either motor 1 or motor 2
	if (motor == 1)
	{
		I2Crequest[2] = 0x44;
	} else {
		I2Crequest[2] = 0x47;
	}

	// ask on the port "port" for the data in I2Crequest. get back 1 byte and put it in I2Cresponse.
	writeI2C(port, I2Crequest, I2Cresponse, 1);

	// we want busy to be only the leftmost bit in the response, so we bitshift
	busy = (I2Cresponse[0] >> 7);

	if (busy == 0x01) {
		return 1;
	} else {
		return 0;
	}
}

//goto encoder position is the wraper for all
long gotoEncoderPosition(tSensors port, int daisychainLevel, int motor, int encoderValue)
{
	setEncoderPosition(motor, port, daisychainLevel, encoderValue);
	while (isBusy(motor, port, daisychainLevel))
	{
		eraseDisplay();
		if (i2cmotor_debug) {
			nxtDisplayString(0, "Target  %i", encoderValue);
			nxtDisplayString(1, "Current %i", getEncoderPosition(motor, port, daisychainLevel));
			if (isBusy(motor, port, daisychainLevel))
  		{
  			nxtDisplayString(2, "Busy");
  		} else {
  			nxtDisplayString(2, "Not busy");
  		}
		}
		Sleep(10);
	}
	return getEncoderPosition(motor, port, daisychainLevel);
}
