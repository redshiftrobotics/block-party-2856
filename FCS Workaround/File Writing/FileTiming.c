void ReadFile(string *PointerToString, string *FileName)
{
	TFileHandle   hFileHandle;              // will keep track of our file
  TFileIOResult nIOResult;                // will store our IO results
  string        sFileName = *FileName;   // the name of our file
  int           nFileSize = 100;          // will store our file size
  char          incomingChar;                          // this will store each char as we read back in from the file
  string        incomingString[5];                     // this will store the final, fully-read strings (with new strings getting put into new indexes

	OpenRead(hFileHandle, nIOResult, sFileName, nFileSize);     // open our file 'sFileName' for reading

	for(int i = 0; i < nFileSize; i++)                          // iterate through the file until we've hit the end:
	{
		ReadByte(hFileHandle, nIOResult, incomingChar);
		strncatSingleChar(incomingString, incomingChar, sizeof(incomingString));
	}

	Close(hFileHandle, nIOResult);
	*PointerToString = incomingString;
}

void WriteFile(string *FileName, string *MessageToWrite)
{
	TFileHandle   hFileHandle;              // will keep track of our file
  TFileIOResult nIOResult;                // will store our IO results
  string        sFileName = *FileName;   // the name of our file
  int           nFileSize = 100;          // will store our file size

  string        sMessageToWrite = *MessageToWrite;    // we will write this to the file

  Delete(sFileName, nIOResult);
  OpenWrite(hFileHandle, nIOResult, sFileName, nFileSize);    // open the file for writing (creates the file if it does not exist)
  WriteText(hFileHandle, nIOResult, sMessageToWrite);
  Close(hFileHandle, nIOResult);
}

void AddTime(int Time)
{
	string WriteInto = "";
  string MessageToWrite = "";
  string FileN = "TimerFile.txt";

  ReadFile(&WriteInto, &FileN);

	int Value = atoi(WriteInto);

  Value += Time;

  StringFormat(MessageToWrite, "%i", Value);

  WriteFile(&FileN, &MessageToWrite);
}

void ClearTime()
{
  string MessageToWrite = "0";
  string FileN = "TimerFile.txt";

  WriteFile(&FileN, &MessageToWrite);
}

int GetTime()
{
	string WriteInto = "";
  string FileN = "TimerFile.txt";

  ReadFile(&WriteInto, &FileN);

  return atoi(WriteInto);
}
