#pragma config(Sensor, S1, A, sensorI2CCustom)
#include "../libraries/I2C.h";

float Speeds[21] = {0, 1187,7869,10937,12861.33333,14114,14954.66667,15517.33333,15940.66667,16233.33333,16442,16613.66667,16769.66667,16906.33333,17016,17084,17197.33333,17234.66667,17300.66667,17326,17442.66667};

float GetSpeed(int Speed)
{
	return Speeds[Speed / 5] / 5;
}

void MoveProtected(int Speed, int Miliseconds)
{
	int StartEncoder = I2C_GetEncoderPosition(S1, 2, 1);

	ClearTimer(T1);
	while(time1[T1] < Miliseconds)
	{
		int FinalEncoder = I2C_GetEncoderPosition(S1, 2, 1);

		if(abs(StartEncoder - FinalEncoder) / (float)(T1 / 1000) < GetSpeed(Speed) + 1000)
		{
			I2C_SetMotorSpeed(S1, 2, 1, Speed);
		}
		else
		{
			I2C_SetMotorSpeed(S1, 2, 1, 0);
			PlayImmediateTone(100, 100);
			sleep(1000);
		}
	}
}

task main()
{
	MoveProtected(20, 5000);
}
