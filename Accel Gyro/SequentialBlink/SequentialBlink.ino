/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 


// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  for (int dPin = 0; dPin < 9; dPin++)
  {
    pinMode(dPin, OUTPUT);
  } 
}

// the loop routine runs over and over again forever:
void loop() {
  
  
  for (int dPin = 0; dPin < 9; dPin++)
  {
    digitalWrite(dPin, HIGH);
    delay(100);
    digitalWrite(dPin, LOW);
  }
}
