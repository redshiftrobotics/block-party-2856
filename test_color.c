#pragma config(Sensor, S4,     ,               sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "libraries/saas_common.h"
task main()
{

tByteArray I2Crequest;

tByteArray I2Cresponse;

ubyte I2Caddress = 0x02; //standard address for Lego sensor

I2Crequest[0] = 2;		// two bytes will follow this	 initial byte (this is called the message size

I2Crequest[1] = I2Caddress;	 // first byte is ALWAYS the address

	 I2Crequest[2] = 0x42;	//standard Lego Register address

while(true)

{

eraseDisplay();

writeI2C(S4, I2Crequest, I2Cresponse, 1); //writei2C(Port, i2CMessage, I2Creply, length of reply)
nxtDisplayString(1, "%i", I2Cresponse);
Sleep(100);
}
}
