#pragma config(Sensor, S1,     ,               sensorI2CCustom)
#pragma config(Sensor, S2,     ,               sensorI2CCustom)

#include "../libraries/I2C.h"
#include "JoystickDriver.c"

//moves robot left
void MoveLeft(int LeftPower)
{
	I2C_SetMotorSpeed(S1, 2, 2, -LeftPower);
}

//moves robot right
void MoveRight(int RightPower)
{
	I2C_SetMotorSpeed(S1, 2, 1, RightPower);
}

//move arm function: negative moves arm up
void MoveArm(int Power)
{
	I2C_SetMotorSpeed(S1, 1, 1, Power);
}

//pick up blocks funciton
void PickupBlocks(int Power)
{
	nxtDisplayString(4, "Pikcup-power: %i", Power);
	//moves motor
	I2C_SetMotorSpeed(S1, 3, 1, Power);
}

task main()
{
	while(true)
	{
		//updates each loop
		getJoystickSettings(joystick);

		//moves left side of robot
		if(abs(joystick.joy1_y1) > 10)
		{
			MoveLeft((joystick.joy1_y1 / 1.28));
		}
		else
		{
			MoveLeft(0);
		}

		//moves right side of robot
		if(abs(joystick.joy1_y2) > 10)
		{
			MoveRight((joystick.joy1_y2 / 1.28));
		}
		else
		{
			MoveRight(0);
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
			PickupBlocks(-(joystick.joy2_y2 / 1.28));
		}
		else
		{
			PickupBlocks(0);
		}

		//if the right trigger is pressed, raise the flag
		if(joy2Btn(8) == 1)
		{
			I2C_SetMotorSpeed(S1, 1, 2, 100);
		}
		//if the left trigger is pressed, lower the flag
		else if(joy2Btn(7) == 1)
		{
			I2C_SetMotorSpeed(S1, 1, 2, -100);
		}
		//if the right bumper is pressed, lower the flag slowly
		else if(joy2Btn(5) == 1)
		{
			I2C_SetMotorSpeed(S1, 1, 2, -5);
		}
		//if the left bumper is pressed, lower the flag slowly
		else if(joy2Btn(6) == 1)
		{
			I2C_SetMotorSpeed(S1, 1, 2, 5);
		}
		//otherwise stop the flag raiser
		else
		{
			I2C_SetMotorSpeed(S1, 1, 2, 0);
		}
	}
}
