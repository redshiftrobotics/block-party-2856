//must change this
#include "drivers/HitecnicInfaredLibrary.h"

int IR_A, IR_B, IR_C, IR_D, IR_E = 0;
float IR_CValue[10];

void ReadSensorValues()
{
	HTIRS2readAllACStrength(IR, IR_A, IR_B, IR_C, IR_D, IR_E);
}

bool IR_InFront()
{
	ReadSensorValues();

	for(int i = 9; i >= 1; i--)
	{
		IR_CValue[i] = IR_CValue[i - 1];
	}
	IR_CValue[0] = IR_C;

	bool Return = true;

	for(int i = 1; i <= 9; i++)
	{
		if(IR_CValue[0] >= IR_CValue[i])
		{
			Return = false;
		}
	}

	return Return;
}

task main()
{
	while(!IR_InFront())
	{
	}

	PlayImmediateTone(100, 100);

	sleep(1000);
}
