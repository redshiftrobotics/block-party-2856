//Arduino to Hitechnic Protoboard
// Wiring:
//  Arduino   to     Hitechnic
//    D0                A0
//    D1                A1
//    D2                A2
//    D3                A3
//    D4                A4
//    D5                B0
//    D6                B1
//    D7                B2
//    D8                B3
//////////////////////////////////
 
int randNumber = 0;

void setup() {                
  // initialize the digital pin as an output.
  randomSeed(analogRead(0));
  for (int dPin = 0; dPin < 9; dPin++)
  {
    pinMode(dPin, OUTPUT);
  } 
}

// the loop routine runs over and over again forever:
void loop() {
  randNumber = random(512);
  
  for (int dPin = 0; dPin < 9; dPin++)
  {
    int value = randNumber&(1<<dPin);
    value = value >> dPin;
    digitalWrite((8-dPin), value);

  }
  delay(2000);
}
