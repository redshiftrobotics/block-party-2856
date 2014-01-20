//must change this
#include "drivers/HitecnicInfaredLibrary.h"

int IR_A, IR_B, IR_C, IR_D, IR_E = 0;
float IR_CValue[20];

void IR_Reset()
{
	for(int i = 0; i < 20; i++)
	{
		IR_CValue[i] = 0;
	}
}

void ReadSensorValues()
{
	HTIRS2readAllACStrength(IR, IR_A, IR_B, IR_C, IR_D, IR_E);
}

bool IR_InFront()
{
	ReadSensorValues();

	for(int i = 19; i >= 1; i--)
	{
		IR_CValue[i] = IR_CValue[i - 1];
	}
	IR_CValue[0] = IR_C;

	bool Return = true;

	for(int i = 1; i <= 19; i++)
	{
		if(IR_CValue[0] >= IR_CValue[i])
		{
			Return = false;
		}
	}

	return Return;
}
