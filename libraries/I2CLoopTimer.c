#pragma config(Sensor, S1,     Gyro,             sensorI2CCustom)

#include "drivers/hitechnic-gyro.h"
//#include "GyroLibrary.h"

task main()
{
	clearDebugStream();
	writeDebugStreamLine("Running");
	int n = 0;
	int reading[250];  //gyro reading
	long TimeStamp = 0;  //
	int CycleTime[250]; //duration of a cycle
	HTGYROstartCal(Gyro); //Calibrate Gyro (Xander)
	writeDebugStreamLine("Waiting");
	wait1Msec(3000);

	while(n<250)  // take 250 readings and determine the cycle time
	{
		TimeStamp = nPgmTime;  //read program time
		reading[n] = HTGYROreadRot(Gyro); //take a sensor reading
		CycleTime[n] = (nPgmTime - TimeStamp);
		n=n+1;

	}
	n = 0;  //
	while(n<250)  // printout cycle times
	{
		writeDebugStreamLine("n: %i, Reading: %i, CycleTime: %i", n, reading[n], CycleTime[n]);
		wait1Msec(50);
		n=n+1;
	}

}

