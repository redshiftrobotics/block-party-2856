
task main()
{
	//int MessageInt[100];
	//int MessageIntLength = 0;

	//clears all messages from mailbox
	while(bQueuedMsgAvailable())
	{
		ClearMessage();
	}

	while(true)
	{
		if(bQueuedMsgAvailable())
		{
			eraseDisplay();

			//MessageInt[MessageIntLength] = (byte)message;
			//MessageInt[MessageIntLength + 1] = (byte)(message >> 8);
			//MessageInt[MessageIntLength + 2] = (byte)(message >> 16);
			//MessageInt[MessageIntLength + 3] = (byte)(message >> 24);
			//MessageIntLength += 4;

			//for(int i = 0; i < MessageIntLength; i++)
			//{
			//	nxtDisplayString(i + 1, "%i", MessageInt[i]);
			//}
			nxtDisplayString(1, "%i", messageParm[0]);
			nxtDisplayString(2, "%i", messageParm[1]);
			nxtDisplayString(3, "%i", messageParm[2]);

			ClearMessage();
		}
	}
}
