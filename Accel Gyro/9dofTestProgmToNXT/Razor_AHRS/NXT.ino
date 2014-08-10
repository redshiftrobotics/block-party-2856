void setupNXTpin()
{

  for (int dPin = 0; dPin < 10; dPin++)
  {
    if(dPin != 2) pinMode(dPin, OUTPUT);
    else pinMode(dPin, INPUT);
  } 
  attachInterrupt(0, interruptFunction, RISING);  // setup pin 2 as an interrupt
}

void sendNXTdata(int numberToSend)
{
   for (int dPin = 0; dPin < 9; dPin++)
  {
    int value = numberToSend&(1<<dPin);
    value = value >> dPin;
    if(dPin != 6)      
      digitalWrite((8-dPin), value);
    else 
      digitalWrite(9, value);
  }
}

void interruptFunction()
{
  //what should be done when the interrupt is triggered goes here
}
