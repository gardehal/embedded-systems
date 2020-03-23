// Pins for charlieplexing
const int digitalEleven = 11;
const int digitalTwelve = 12;
const int digitalThirteen = 13;

void setup() 
{  
  Serial.begin(9600);
}

void loop() 
{
  lightLed(digitalThirteen, digitalEleven); // 0, 2
  delay(1000);
  lightLed(digitalEleven, digitalThirteen); // 1, 2
  delay(1000);
  lightLed(digitalEleven, digitalTwelve); // 0, 1
  delay(1000);
  lightLed(digitalTwelve, digitalThirteen); // 1, 1
  delay(1000);
  lightLed(digitalTwelve, digitalEleven); // 0, 0
  delay(1000);
  lightLed(digitalThirteen, digitalTwelve); // 1, 0
  delay(1000);
}

void reset()
{
  for(int i = 0; i < 14; i++)
  {
    pinMode(i, INPUT);
  }
}

void lightLed(int firstPin, int secondPin)
{
  reset();
  pinMode(firstPin, OUTPUT);
  pinMode(secondPin, OUTPUT);
  digitalWrite(firstPin, HIGH);
  digitalWrite(secondPin, LOW);
}
