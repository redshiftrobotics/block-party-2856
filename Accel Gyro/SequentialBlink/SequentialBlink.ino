//Arduino to Hitechnic Protoboard
// Wiring:
//  Arduino   to     Hitechnic
//    D0                A0
//    D1                A1
//    D9                A2
//    D3                A3
//    D4                A4
//    D5                B0 
//    D6                B1 
//    D7                B2
//    D8                B3
//    D2 (interupt)     B4 (output)
//////////////////////////////////
 
int randNumber = 0;

void setup() {                
  // initialize the digital pin as an output.
  randomSeed(analogRead(0));
  for (int dPin = 0; dPin < 10; dPin++)
  {
    if(dPin != 2) pinMode(dPin, OUTPUT);
    else pinMode(dPin, INPUT);
  } 
  attachInterrupt(0, makeRandom, RISING);  // setup pin 2 as an interrupt
}

void makeRandom()
{
  randNumber = random(512);
}


// the loop routine runs over and over again forever:
void loop() {
  
  
  for (int dPin = 0; dPin < 9; dPin++)
  {
    int value = randNumber&(1<<dPin);
    value = value >> dPin;
    if(dPin != 6)      
      digitalWrite((8-dPin), value);
    else 
      digitalWrite(9, value);
  }
  delay(50);
}
