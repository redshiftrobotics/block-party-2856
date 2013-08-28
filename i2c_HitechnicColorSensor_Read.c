#pragma config(Sensor, S1,     M_CONTROL,      sensorI2CCustom)

#include "./drivers/common.h"

task main()
{

	tByteArray I2Crequest;
	tByteArray I2Cresponse;

	//set sets the adress of the byte to the default adress for sending data
	ubyte I2Caddress = 0x02;

	//sets the number of bytes to send:
	I2Crequest[0] = 4;

	//sends the adress as the first byte
  I2Crequest[1] = I2Caddress;

  //sets the starting position to start sending data at
  I2Crequest[2] = 0x46;

  //sets the motor power
  I2Crequest[3] = 0b00010000;

  //sets the motor mode
  I2Crequest[4] = 0b00000001;


  while(true)
  {
  	//sends the command to the motor controller in a loop
  	writeI2C(S1, I2Crequest, I2Cresponse, 4);

  	//erases the display and writes the responses
  	eraseDisplay();
  	nxtDisplayString(0, "%i", I2Cresponse[0]);
  	nxtDisplayString(1, "%i", I2Cresponse[1]);
  	nxtDisplayString(2, "%i", I2Cresponse[2]);
  	nxtDisplayString(3, "%i", I2Cresponse[3]);
  	nxtDisplayString(4, "%i", I2Cresponse[4]);
  	Sleep(10);
	}
}
