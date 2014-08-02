#pragma config(Sensor, S1,     ,               sensorI2CCustom)
#pragma config(Sensor, S2,     Gyro,          sensorI2CCustom)

#include "../libraries/Turning.c"


task main()
{
	Move(20, 20);
	//Calibrate();
	//Straight(20, 5000);
	//Turn(180);
	//Straight(20, 5000);
}
