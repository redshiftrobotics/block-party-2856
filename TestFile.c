
typedef ubyte tByteArray[17];

void writeI2C(tSensors link, tByteArray &request)
{
	sendI2CMsg(link, &request[0], 0);
}

void writeI2C(tSensors link, tByteArray &request, tByteArray &reply, int replylen)
{
	sendI2CMsg(link, &request[0], replylen);
	readI2CReply(link, &reply[0], replylen);
}

void setMotorSpeed(sbyte Speed, tSensors port, int MotorNumber)
{
	tByteArray I2Crequest;
	I2Crequest[0] = 3;
	I2Crequest[1] = 0x2;
	if(MotorNumber == 1)
	{
		I2Crequest[2] = 0x45;
	}
	else
	{
		I2Crequest[2] = 0x46;
	}
	I2Crequest[3] = Speed;
	writeI2C(port, I2Crequest);
}

long getEncoderPosition(int motor, tSensors port, int daisychainLevel = 0)
{
		tByteArray I2Crequest;
		tByteArray I2Cresponse;
		I2Crequest[0] = 2;
	  I2Crequest[1] = 0x02 + daisychainLevel*2;
	  if (motor == 1)
	  {
	  	I2Crequest[2] = 0x49;
		} else {
		  I2Crequest[2] = 0x50;
		}
	  writeI2C(port, I2Crequest, I2Cresponse, 4);
	  long EncoderValue = (I2Cresponse[0] << 24) + (I2Cresponse[1] << 16) + (I2Cresponse[2] << 8) + (I2Cresponse[3] << 0);
  	return EncoderValue;
}

void setEncoderPosition(int motor, tSensors port, long Input)
{
	int daisychainLevel = 1;
	tByteArray I2Crequest;
	I2Crequest[0] = 8;
  I2Crequest[1] = 0x02 + daisychainLevel*2;
  if (motor == 1)
  {
  	I2Crequest[2] = 0x45;
	} else {
  	I2Crequest[2] = 0x46;
  }
  I2Crequest[3] = 0b00010000;
  I2Crequest[4] = 0b00000010;
  I2Crequest[5] = (byte)((Input >> 24) & 0x000000ff);
  I2Crequest[6] = (byte)((Input >> 16) & 0x000000ff);
  I2Crequest[7] = (byte)((Input >> 8) & 0x000000ff);
  I2Crequest[8] = (byte)(Input & 0x000000ff);
  writeI2C(S1, I2Crequest);
}
task main() {
Sleep(5);
}
