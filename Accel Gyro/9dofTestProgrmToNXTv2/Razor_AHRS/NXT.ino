void setupNXTpin()
{

  for(int i=4; i<11; i++) {
    pinMode(i, OUTPUT); }
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);

  //attachInterrupt(0, interruptFunction, RISING);  // setup pin 2 as an interrupt
}

void sendNXTdata(int numberToSend)
{
  int value = numberToSend&(1<<0);
  value = value >> 0;
  digitalWrite(A1, value);
  
  value = numberToSend&(1<<1);
  value = value >> 1;
  digitalWrite(A0, value);
  
  for (int dPin = 4; dPin < 11; dPin++)
  {
    int bitShift = dPin - 2;
    int value = numberToSend&(1<<bitShift);
    value = value >> bitShift;
    digitalWrite((14-dPin), value);
  }
}

void interruptFunction()
{
  //what should be done when the interrupt is triggered goes here
}
