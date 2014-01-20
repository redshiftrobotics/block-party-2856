#pragma config(Sensor, S2,     ,               sensorI2CCustom)
#pragma config(Sensor, S1,     ,               sensorI2CCustom)
#pragma config(Sensor, S4,     ,               sensorTouch)

#include "../libraries/Servos.h"
#include "../libraries/Motors.h"
#include "../libraries/Arm.c"
#include "JoystickDriver.c"

//sets global variables
int PresetLocation = 0;
bool APressed = false;

//two posative powers take jarvis forward
void MoveLeft(int LeftPower)
{
	nxtDisplayString(1, "LeftPower: %i", -LeftPower);
	Motors_SetSpeed(S1, 2, 2, -LeftPower);
}
void MoveRight(int RightPower)
{
	nxtDisplayString(2, "LeftPower: %i", RightPower);
	Motors_SetSpeed(S1, 2, 1, RightPower);
}

//posative moves arm up
void MoveArm(int Power)
{
	nxtDisplayString(3, "ArmPower: %i", Power);
	Arm_SetSpeed(Power);
}

void LockArm()
{
	//sets the position to its current position, then stops all other activity
	I2C_SetEncoderPosition(S1, 1, 1, I2C_GetEncoderPosition(S1, 1, 1), 10);
	sleep(1000);
	while(joy2Btn(4) == 1)
	{
	}
}

void PickupBlocks(int Power)
{
	nxtDisplayString(4, "Pikcup-power: %i", Power);
	//moves motor
	Motors_SetSpeed(S1, 3, 1, Power);
}

task main()
{
	bDisplayDiagnostics = false;
	float Multiplier = .5;
	while(true)
	{
		//updates each loop
		getJoystickSettings(joystick);
		Arm_Update();
		eraseDisplay();

		//moves robot
		if(joy1Btn(7) == 1)
		{
			MoveLeft(100 * Multiplier / 2);
			MoveRight(-100 * Multiplier / 2);
		}
		else if(joy1Btn(8) == 1)
		{
			MoveLeft(-100 * Multiplier / 2);
			MoveRight(100 * Multiplier / 2);
		}
		else
		{
			//moves left side
			if(abs(joystick.joy1_y1) > 10)
			{
				MoveLeft((joystick.joy1_y1 / 1.28) * Multiplier);
			}
			else
			{
				MoveLeft(0);
			}

			//moves right side
			if(abs(joystick.joy1_y2) > 10)
			{
				MoveRight((joystick.joy1_y2 / 1.28) * Multiplier);
			}
			else
			{
				MoveRight(0);
			}
		}
		//moves arm
		if(abs(joystick.joy2_y1) > 10)
		{
			MoveArm(-(joystick.joy2_y1 / 1.28));
		}
		else
		{
			MoveArm(0);
		}

		//moves block picker-upper
		if(abs(joystick.joy2_y2) > 10)
		{
			PickupBlocks(-(joystick.joy2_y2 / 2));
		}
		else
		{
			PickupBlocks(0);
		}

		//if the right trigger is pressed, raise the flag
		if(joy2Btn(8) == 1)
		{
			writeDebugStreamLine("Press Right");
			Motors_SetSpeed(S1, 1, 2, 100);
		}
		//if the left trigger is pressed, lower the flag
		else if(joy2Btn(7) == 1)
		{
			writeDebugStreamLine("Press Left");
			Motors_SetSpeed(S1, 1, 2, -100);
		}
		//if the right bumper is pressed, lower the flag slowly
		else if(joy2Btn(5) == 1)
		{
			writeDebugStreamLine("Press Right");
			Motors_SetSpeed(S1, 1, 2, -5);
		}
		//if the left bumper is pressed, lower the flag slowly
		else if(joy2Btn(6) == 1)
		{
			writeDebugStreamLine("Press Left");
			Motors_SetSpeed(S1, 1, 2, 5);
		}
		else
		{
			Motors_SetSpeed(S1, 1, 2, 0);
		}

		//if the a button is pressed, reinitialize the arm
		if(joy2Btn(2) == 1)
		{
			Arm_Reinitialize();
		}

		if(joy2Btn(4) == 1)
		{
			LockArm();
		}

		//changes the mode to turbo if either bumper on driver joystick is pressed
		if(joy1Btn(5) == 1)
		{
			Multiplier = 1;
		}
		else if(joy1Btn(6) == 1)
		{
			Multiplier = .25;
		}
		else
		{
			Multiplier = .5;
		}
	}
}
