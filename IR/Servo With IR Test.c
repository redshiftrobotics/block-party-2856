#pragma config(Sensor, S1, ,sensorI2CCustom)
#pragma config(Sensor, S2, IR, sensorI2CCustom)
//#include "../libraries/Servos.h"
#include "../libraries/Motors.h"
#include "HitecnicInfaredLibrary.h"

int A, B, C, D, E = 0;
int DegreesOfRotation = 191;
byte ToServoValue(float Input)
{
	return (byte)(255 * Input / DegreesOfRotation);
}

int FindDegree()
{
	bool FirstTime = true;
	int GreatestValue = 0;
	int GreatestValueDegree = 0;

	for(int Degree = 0; Degree < DegreesOfRotation; Degree += 5)
	{
<<<<<<< HEAD
		Servos_SetPosition(S1, 3, 1, ToServoValue(Degree));
=======
		//Servos_SetPosition(S1, 3, 1, ToServoValue(Degree));
>>>>>>> Debug I2C, rewrite Motors.h
		HTIRS2readAllACStrength(IR, A, B, C, D, E);



		if(B < 10 && D < 10 && C > GreatestValue)
		{
			GreatestValue = C;
			GreatestValueDegree = Degree;
		}

		if(FirstTime)
		{
			Sleep(500);
			FirstTime = false;
		}
		else
		{
			Sleep(100);
		}
	}
	return GreatestValueDegree;
}

int FindBasket()
{
		int Degree = FindDegree();
		writeDebugStreamLine("%i", Degree);
		if(Degree <= 75 && Degree > 50)
		{
			return 1;
		}
		else if(Degree >= 80 && Degree <= 105)
		{
			return 2;
		}
		else if(Degree >= 110 && Degree <= 130)
		{
			return 3;
		}
		else if(Degree >= 135 && Degree <= 155)
		{
			return 4;
		}
		else
		{
			return -1;
		}
}

//void MoveRotations(tSensors Sensor, int DaisyChain, int MotorNumber, int Rotations, int Power)
//{
	//i don't get this, but you need a parenthesis around the 1440 and rotations, otherwise it dosen't obey the order or operations.
	//int TargetEncoder = Motors_EncoderCount(Sensor, DaisyChain, MotorNumber) + (1440 * Rotations);
	//writeDebugStreamLine("Target: %i", TargetEncoder);
	//Motors_SetPosition(Sensor, DaisyChain, MotorNumber, TargetEncoder, Power);
//}

//void MoveByRotations(tSensors Sensor, int DaisyChain, int MotorNumber, int Rotations, int Power)
//{
	//long One = Motors_EncoderCount(Sensor, DaisyChain, MotorNumber) + (long)(Rotations * 1440);
	//Motors_SetPosition(Sensor, DaisyChain, MotorNumber, One, Power);
//}

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
		//writeDebugStreamLine("%i", I2Cresponse[1]);
	  //creates a long out of the bytes
	  //note: when debugging with any %i construct, this will be cast to an integer and will overflow at 32767!
	  long EncoderValue = (I2Cresponse[0] << 24) + (I2Cresponse[1] << 16) + (I2Cresponse[2] << 8) + (I2Cresponse[3] << 0);

	  //returns the long
	  return EncoderValue;
  	//return ConvertBytesToLong(I2Cresponse[0], I2Cresponse[1], I2Cresponse[2], I2Cresponse[3]);
}

task main()
{
<<<<<<< HEAD
		int basket = FindBasket();
		writeDebugStreamLine("%i", basket);
		Sleep(10);
=======


	//long One = I2C_GetEncoderPosition(S1, 1, 1) + 1440;
	//long Two = I2C_GetEncoderPosition(S1, 1, 2) + 1440;
	//long Three = I2C_GetEncoderPosition(S1, 2, 1) - 1440;
	//long Four = I2C_GetEncoderPosition(S1, 2, 2) - 1440;

	//writeDebugStream("First Values: %i", One);
	//writeDebugStream(", %i", Two);
	//writeDebugStream(", %i", Three);
	//writeDebugStreamLine(", %i", Four);

	//Motors_SetPosition(S1, 1, 1, One, 100);
	//Motors_SetPosition(S1, 1, 2, Two, 100);
	//Motors_SetPosition(S1, 2, 1, Three, 100);
	//Motors_SetPosition(S1, 2, 2, Four, 100);

	//writeDebugStream("First Values: %i", I2C_GetEncoderPosition(S1, 1, 1) + 1440);
	//writeDebugStream(", %i", I2C_GetEncoderPosition(S1, 1, 2) + 1440);
	//writeDebugStream(", %i", I2C_GetEncoderPosition(S1, 2, 1) - 1440);
	//writeDebugStreamLine(", %i", I2C_GetEncoderPosition(S1, 2, 2) - 1440);

	//writeDebugStream("First Values: %i", I2C_GetEncoderPosition(S1, 1, 1) + 1440);
	//writeDebugStream(", %i", I2C_GetEncoderPosition(S1, 1, 2) + 1440);
	//writeDebugStream(", %i", I2C_GetEncoderPosition(S1, 2, 1) - 1440);
	//writeDebugStreamLine(", %i", I2C_GetEncoderPosition(S1, 2, 2) - 1440);

	writeDebugStream("First Values: %i", I2C_GetEncoderPosition(S1, 1, 1));
	writeDebugStream(", %i", I2C_GetEncoderPosition(S1, 1, 2));
	writeDebugStream(", %i", I2C_GetEncoderPosition(S1, 2, 1));
	writeDebugStreamLine(", %i", I2C_GetEncoderPosition(S1, 2, 2));

	Motors_SetPosition(1, 1, (long)(I2C_GetEncoderPosition(S1, 1, 1)), 100, S1);
	Motors_SetPosition(1, 2, (long)(I2C_GetEncoderPosition(S1, 1, 2)), 100, S1);
	Motors_SetPosition(2, 1, (long)(I2C_GetEncoderPosition(S1, 2, 1)), 100, S1);
	Motors_SetPosition(2, 2, (long)(I2C_GetEncoderPosition(S1, 2, 2)), 100, S1);

	//Motors_SetPosition(S1, 1, 1, (long)(I2C_GetEncoderPosition(S1, 1, 1) + 1440), 100);
	//Motors_SetPosition(S1, 1, 2, (long)(I2C_GetEncoderPosition(S1, 1, 2) + 1440), 100);
	//Motors_SetPosition(S1, 2, 1, (long)(I2C_GetEncoderPosition(S1, 2, 1) - 1440), 100);
	//Motors_SetPosition(S1, 2, 2, (long)(I2C_GetEncoderPosition(S1, 2, 2) - 1440), 100);


	//Motors_SetPosition(S1, 1, 1, (0 + 1440), 100);
	//Motors_SetPosition(S1, 1, 2, (0 + 1440), 100);
	//Motors_SetPosition(S1, 2, 1, (0 - 1440), 100);
	//Motors_SetPosition(S1, 2, 2, (0 - 1440), 100);

	while(true)
	{
	}
>>>>>>> Debug I2C, rewrite Motors.h
}
