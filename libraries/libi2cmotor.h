#include "drivers/common.h"

// doesn't support daisychains
// also TODO: setting a constant speed and a rotating a certain amount



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
		I2Crequest[3] = 0b00010001;
		I2Crequest[4] = Speed;
	}
	else
	{
		I2Crequest[2] = 0x46;
		// ...but if we're on motor 2, speed comes first.
		I2Crequest[3] = Speed;
		I2Crequest[4] = 0b00010001;
	}

	writeI2C(port, I2Crequest);
}

// pass this 1 or 2 for the motor and S[1-4] for the port
long getEncoderValue(int motor, tSensors port)
{
		//initializes the arrays
		tByteArray I2Crequest;
		tByteArray I2Cresponse;

		//sets the number of bytes to send:
		I2Crequest[0] = 2;

		//sends the adress as the first byte
	  I2Crequest[1] = 0x02;

	  //sets the starting position to start sending data at
	  if (motor == 1)
	  {
	  	I2Crequest[2] = 0x49;
		} else {
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
void setEncoderPosition(int motor, tSensors port, long Input)
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

// see getEncoderValue() for args
bool isBusy(int motor, tSensors port)
{
	tByteArray I2Crequest;
	tByteArray I2Cresponse;

	ubyte busy;

	// number of additional bytes to send
	I2Crequest[0] = 2;

	// standard lego sensor address
	I2Crequest[1] = 0x02;

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
		return true;
	} else {
		return false;
	}
}
