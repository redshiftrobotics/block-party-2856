#pragma config(Sensor, S1,     M_CONTROL,      sensorI2CCustom)

#include "libraries/saas_common.h"

task main()
{

	tByteArray I2Crequest;
	tByteArray I2Cresponse;
	ubyte I2Caddress = 0x02; //standard address for Lego sensor

	I2Crequest[0] = 2;
  I2Crequest[1] = I2Caddress;
  I2Crequest[2] = 0x42;  //standard Lego Register address

  while(true)
  {
  	eraseDisplay();
  	writeI2C(S1, I2Crequest, I2Cresponse, 4);
  	nxtDisplayString(3, "%i", I2Cresponse[0]);  // color
  	nxtDisplayString(4, "%i", I2Cresponse[1]);  // red component
  	nxtDisplayString(5, "%i", I2Cresponse[2]);  // green component
  	nxtDisplayString(6, "%i", I2Cresponse[3]);	// blue component
  	wait1Msec(10);
	}
}
