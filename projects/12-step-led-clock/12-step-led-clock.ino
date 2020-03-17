// Pins for charlieplexing
const int digitalTwo = 2;
const int digitalThree = 3;
const int digitalFour = 4;
const int digitalFive = 5;
const int digitalSix = 6;
const int digitalSeven = 7;
const int digitalEight = 8;
const int digitalNine = 9;
const int digitalTen = 10;
const int digitalEleven = 11;
const int digitalTwelve = 12;
const int digitalThirteen = 13;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  reset();
  lightTopLeft();
}

void reset()
{
  for(int i = 2; i < 14; i++)
  {
    pinMode(i, OUTPUT);
  }
}

void lightTopLeft()
{
  digitalWrite(digitalThirteen, HIGH);
  digitalWrite(digitalTwelve, LOW);
}

void lightTopRight()
{
  digitalWrite(digitalEleven, HIGH);
  digitalWrite(digitalThirteen, LOW);
}

void lightMiddleLeft()
{
  digitalWrite(digitalThirteen, HIGH);
  digitalWrite(digitalTwelve, LOW);
}

void lightMiddleRight()
{
  digitalWrite(digitalTwelve, HIGH);
  digitalWrite(digitalThirteen, LOW);
}

void lightBottomLeft()
{
  digitalWrite(digitalThirteen, HIGH);
  digitalWrite(digitalEleven, LOW);
}

void lightBottomRight()
{
  digitalWrite(digitalTwelve, HIGH);
  digitalWrite(digitalThirteen, LOW);
}
