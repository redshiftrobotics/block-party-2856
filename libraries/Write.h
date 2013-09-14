string DebugList[200];
int DebugListCount = 0;
string StaticListText[200];
int StaticListNumber[200];
int StaticListCount = 0;
int ScrollValue = 0;
bool ButtonUp = true;
task ButtonUpdate;
task ConsoleDraw;
bool DebugMode = false;

void InitializeWrite()
{
	StartTask(ConsoleDraw);
	StartTask(ButtonUpdate);
}

void WriteDebug(char *ToWrite)
{
	DebugList[DebugListCount] = ToWrite;
  DebugListCount++;
}

void WriteDebugInt(int ToWrite)
{
	string S = "";
	StringFormat(S, "%i", ToWrite);
	DebugList[DebugListCount] = ToWrite;
  DebugListCount++;
}

void WriteLine(int Position, char *ToWrite)
{
	StaticListText[StaticListCount] = ToWrite;
	StaticListNumber[StaticListCount] = Position;
	StaticListCount++;
}

task ButtonUpdate()
{
	while(true)
	{
		if(DebugMode)
		{
			if(nNxtButtonPressed == 1 && ButtonUp == true && ScrollValue <= -1)
			{
				ButtonUp = false;
				ScrollValue++;
			}

			if(nNxtButtonPressed == 2 && ButtonUp == true)
			{
				ButtonUp = false;
				ScrollValue --;
			}
		}

		if(nNxtButtonPressed == 3 && ButtonUp == true)
		{
			DebugMode =!DebugMode;
			ButtonUp = false;
		}

		if(nNxtButtonPressed == -1)
		{
			ButtonUp = true;
		}
	}
}

task ConsoleDraw()
{
	while(true)
	{
		eraseDisplay();
		//draws debug lingo
		if(DebugMode)
		{
			for(int i = 0; i < DebugListCount; i++)
			{
				if(i + ScrollValue < 8)
				{
					if(i + ScrollValue >= 0 && i + ScrollValue <= 7)
					{
						nxtDisplayString(i + ScrollValue, DebugList[i]);
					}
				}
			}
		}
		else
		{
			for(int i = 0; i < StaticListCount; i++)
			{
				nxtDisplayString(StaticListNumber[i], StaticListText[i]);
			}
		}
		Sleep(50);
	}

}
