/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 8;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  for (int i = 0; i < 5; i++)
  {
    pinMode(i, OUTPUT);
  }   
}

// the loop routine runs over and over again forever:
void loop() {
  int dPin;
  for (dPin = 0; dPin < 5; dPin++)
  {
    digitalWrite(dPin, HIGH);
    delay(100);
    digitalWrite(dPin, LOW);
  }
}
