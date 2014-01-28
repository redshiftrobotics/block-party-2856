#pragma config(Sensor, S1,     ,               sensorI2CCustom)
#pragma config(Sensor, S2,     IR,             sensorI2CCustom)
#pragma config(Sensor, S3,     Gyro,           sensorI2CCustom)
#pragma config(Sensor, S4,     ,               sensorTouch)

#include "../libraries/Arm.c";
#include "../libraries/Motors.h";
#include "../libraries/I2C.h";
#include "../libraries/IR.c";
#include "../libraries/Menu.c"
#include "JoystickDriver.c"

//sets the time to wait before running the program
int TimeToWait = 0;
bool Wait;
bool RobotForward;

void UpdateArm(int Miliseconds)
{
	writeDebugStreamLine("working");
	for(int i = 0; i < Miliseconds / 10; i++)
	{
		Arm_Update();
		sleep(10);
	}
	writeDebugStreamLine("done");
}

void Move(int RightPower, int LeftPower)
{
	Motors_SetSpeed(S1, 2, 1, RightPower);
	Motors_SetSpeed(S1, 2, 2, -LeftPower);
}

void StraightToIR(int Power)
{
	//reset the IR
	IR_Reset();

	//while the robot is not in front of the IR, move forward
	while(!IR_InFront())
	{
		Move(Power, Power);
	}

	//once it is in front or the IR, stop the robot
	Move(0, 0);
}

void PickupBlocks(int Power)
{
	nxtDisplayString(4, "Pikcup-power: %i", Power);
	//moves motor
	Motors_SetSpeed(S1, 3, 1, Power);
}

void WriteEncoder()
{
	writeDebugStreamLine("Encoder: %i", I2C_GetEncoderPosition(S1, 2, 1));
}

void TimeToWaitMenu()
{
	string t = "Wait?";
	string a = "0";
	string b = "5";
	string c = "10";
	int MenuReturn = Menu(t, a, b, c);

	if(MenuReturn == 0)
	{
		TimeToWait = 0;
	}
	else if(MenuReturn == 1)
	{
		TimeToWait = 5;
	}
	else
	{
		TimeToWait = 10;
	}
}

void WaitMenu()
{
	string t = "Wait For Start?";
	string a = "No";
	string b = "Yes";
	int MenuReturn = Menu(t, a, b);

	if(MenuReturn == 0)
	{
		Wait = false;
	}
	else
	{
		Wait = true;
	}
}

void RobotForwardMenu()
{
	string t = "Facing Forward?";
	string a = "Yes";
	string b = "No";
	int MenuReturn = Menu(t, a, b);

	if(MenuReturn == 0)
	{
		RobotForward = true;
	}
	else
	{
		RobotForward = false;
	}
}

task main()
{
	//disables JoystickDriver.c debugging on nxt screen
	bDisplayDiagnostics = false;

	//gets the time to wait
	TimeToWaitMenu();

	//what direction?
	RobotForwardMenu();

	//wait for start?
	WaitMenu();

	//writes the display
	eraseDisplay();
	nxtDisplayString(1, "Resetting.");

	//resets the arm
	UpdateArm(5000);

	eraseDisplay();
	nxtDisplayString(1, "Ready.");

	if(Wait)
	{
		waitForStart();
	}

	eraseDisplay();
	nxtDisplayString(1, "Running.");

	//sleeps for the time set in the menu
	Sleep(TimeToWait * 1000);

	//sets encoder values and constants
	int StartEncoder = I2C_GetEncoderPosition(S1, 2, 1);
	int DistanceToTravel = 5000;
	int DistanceToMid = 3000;

  //go to the ir
	if(RobotForward)
	{
	StraightToIR(25);
}
else
{
	StraightToIR(-25);
}
	WriteEncoder();

	//move back a certain distance based on if the ir is on the near or far side
	if(I2C_GetEncoderPosition(S1, 2, 1) > StartEncoder + DistanceToMid)
	{
		//if its on the far side...
		PlayImmediateTone(100, 100);
		sleep(1000);
		if(RobotForward)
		{
			Move(-15, -15);
		}
		else
		{
			Move(15, 15);
		}
		sleep(1000);
		Move(0, 0);
	}
	else
	{
		//if its on the near side...
		sleep(1000);

		if(RobotForward)
		{
			Move(-15, -15);
		}
		else
		{
			Move(15, 15);
		}

		sleep(500);
		Move(0, 0);
	}

	WriteEncoder();

	//reset arm to make sure...
	UpdateArm(500);

	//run it up
	Arm_SetSpeed(-50);
	UpdateArm(800);

	//run it down
	Arm_SetSpeed(50);
	UpdateArm(800);

	//stop the task
	Arm_SetSpeed(0);
	UpdateArm(100);

	//move until you get to the other side of the field
	if(!RobotForward)
	{
		while(I2C_GetEncoderPosition(S1, 2, 1) > StartEncoder - DistanceToTravel)
		{
			Move(-40, -40);
			//make sure there is minimal comflicting between threads
			sleep(100);
		}
	}
	else
	{
		while(I2C_GetEncoderPosition(S1, 2, 1) < StartEncoder + DistanceToTravel)
		{
			Move(40, 40);
			//make sure there is minimal comflicting between threads
			sleep(100);
		}
	}
	Move(0, 0);

	WriteEncoder();

	//move onto ramp
	if(RobotForward)
	{
		Move(10, 50);
	}
	else
	{
		Move(-10, -50);
	}
	sleep(1500);

	if(RobotForward)
	{
	Move(40, 40);
	}
	else
	{
		Move(-40, -40);
	}
	sleep(1000);

	if(RobotForward)
	{
	Move(40, -40);
	}
	else
	{
		Move(40, -40);
	}
	sleep(700);

	Move(-40, -40);

	sleep(2000);

	Move(0, 0);
}
