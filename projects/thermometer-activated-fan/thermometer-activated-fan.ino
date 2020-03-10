const int tempPin = A0;

boolean engageFan = false;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  int tempReading = analogRead(tempPin);
  delay(500);
}
