
task Update;
task main()
{
	StartTask(Update);
		while(true)
		{
			hogCPU();
			for(int s = 0; s < 10000; s++)
			{
			}
			releaseCPU();
			sleep(20);
		}
		//sleep(1000);
		//releaseCPU();
}

task Update()
{
	int i = 0;
	while(true)
	{
		hogCPU();
		i+=1;
		eraseDisplay();
		nxtDisplayString(1, "%i", i);
		releaseCPU();
		sleep(20);
	}
}
