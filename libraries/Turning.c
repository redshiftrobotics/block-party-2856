#include "../libraries/Gyro.c"
#include "../libraries/IR.c"
#include "../libraries/Motors.h"

float FinalX = 5;
float FinalY = 0;
float Heading = 0;
float ChangePerSecond = 0;
float TotalDrift = 0;

task UpdateHeading;

void Move(int RightPower, int LeftPower)
{
	Motors_SetSpeed(S1, 2, 1, RightPower);
	Motors_SetSpeed(S1, 2, 2, -LeftPower);
}

void Turning_Calibrate()
{
	//reset all variables
	FinalX = 5;
	FinalY = 0;
	Heading = 0;
	ChangePerSecond = 0;
	TotalDrift = 0;

	//stops the task in case it was running
	StopTask(UpdateHeading);

	//starts the thread that updated the gyro in the backgorund
	Gyro_Start();

	//calibration phase
	sleep(5000);
	FinalY = Gyro_Heading();

	//finds drift slope
	ChangePerSecond = abs(FinalY) / FinalX;

	Gyro_Reset();

	StartTask(UpdateHeading);
}

//biggest amount you can turn is +/- 180 degrees, speed is relative, with .5 being normal and 1 being massive
void Turning_Turn(int Degrees)
{
	hogCPU();

	Gyro_Reset();
	TotalDrift = 0;

	releaseCPU();


	while(abs(-Degrees + Heading) > 2)
	{
		//writeDebugStreamLine("%i", Degrees);
		//writeDebugStreamLine("%i", Heading);

		Move((-Degrees + Heading) / 1.5, (Degrees - Heading) / 1.5)
	}

	Move(0, 0);
}

void Turning_Straight(int Power, int  Miliseconds)
{
	hogCPU();

	Gyro_Reset();
	TotalDrift = 0;

	releaseCPU();
	Time1[T4] = 0;

	while(Time1[T4] < Miliseconds)
	{
		Move(Power + Heading, Power - Heading);
	}

	Move(0, 0);
}

task UpdateHeading()
{
	while(true)
	{
		TotalDrift -= ChangePerSecond * Time1[T3] / 1000;
		Time1[T3] = 0;
		Heading = Gyro_Heading() + TotalDrift;
		sleep(100);
	}
}
