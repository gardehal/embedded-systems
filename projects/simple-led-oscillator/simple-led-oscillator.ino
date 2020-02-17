// Created from AnalogInOutSerial Sketch


const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int lightValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
boolean increment = true;

void setup() 
{
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() 
{
  if(increment && lightValue < 1023)
  {
    lightValue = lightValue + 5;
    if(lightValue > 1020)
      increment = false;
  }
  else
  {
    lightValue = lightValue - 50;
    
    if(lightValue < 50)
      increment = true;
  }
  
  // map it to the range of the analog out:
  outputValue = map(lightValue, 0, 1023, 0, 255);
  // change the analog out value:
  analogWrite(analogOutPin, outputValue);

  // print the results to the Serial Monitor:
  Serial.print("light = ");
  Serial.print(lightValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(2);
}
