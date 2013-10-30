#pragma config(Sensor, S1,     IR,             sensorI2CCustom)
#include "../libraries/Motors.h"
#include "../libraries/IrLobf.h"
task main()
{
	while (true)
	{
		while (slopeLOBF(20,false) > 0)
		{
			Motors_SetSpeed(S1,1,1,50);
			Motors_SetSpeed(S1,1,2,50);
			Motors_SetSpeed(S1,2,1,-50);
			Motors_SetSpeed(S1,2,2,-50);
		}

		Motors_SetSpeed(S1,1,1,0);
		Motors_SetSpeed(S1,1,2,0);
		Motors_SetSpeed(S1,2,1,0);
		Motors_SetSpeed(S1,2,2,0);
	}
}
