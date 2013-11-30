#pragma config(Sensor, S1,     ,               sensorI2CCustom)
#pragma config(Sensor, S2,     IR,             sensorI2CCustom)
#pragma config(Sensor, S3,     Color,          sensorI2CCustom)
#pragma config(Sensor, S4,     ,               sensorTouch)

#include "../libraries/Servos.h"
#include "../libraries/Motors.h"
#include "../libraries/Arm.c"
#include "JoystickDriver.c"

//two posative powers take jarvis forward
void MoveLeft(int LeftPower)
{
	nxtDisplayString(1, "LeftPower: %i", LeftPower);
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

void SpinServo(int Power)
{
	nxtDisplayString(4, "ServoPower: %i", Power);
	Servos_SetPosition(S1, 3, 1, Power);

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
			MoveLeft(100 * Multiplier);
			MoveRight(100 * Multiplier);
		}
		else if(joy1Btn(8) == 1)
		{
			MoveLeft(-100 * Multiplier);
			MoveRight(-100 * Multiplier);
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

		//moves servo
		//if(joy2Btn(3) == 1 || joy2Btn(1) == 1 || joy2Btn(2) == 1 || joy2Btn(4) == 1)
		//{
		//SpinServo(0);
		//}
		//else
		//{
		//SpinServo(255);
		//}

		if(abs(joystick.joy2_y2) > 10)
		{
		SpinServo(((joystick.joy2_y2 + 127) / 1.28));
		}
		else
		{
		SpinServo(128);
		}
	}
}
