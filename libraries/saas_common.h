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
