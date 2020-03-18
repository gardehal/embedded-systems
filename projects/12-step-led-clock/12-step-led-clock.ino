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
  lightTopLeft();
  delay(1000);
  lightTopRight();
  delay(1000);
  lightMiddleLeft();
  delay(1000);
  lightMiddleRight();
  delay(1000);
  lightBottomLeft();
  delay(1000);
  lightBottomRight();
  delay(1000);
}

void test()
{
  test();
  // digitalEleven
  // digitalTwelve
  // digitalThirteen
  pinMode(digitalThirteen, INPUT);
  pinMode(digitalTwelve, OUTPUT);
  pinMode(digitalEleven, OUTPUT);
  digitalWrite(digitalTwelve, HIGH);
  digitalWrite(digitalEleven, LOW);
}

void lightTopLeft()
{
  pinMode(digitalTwelve, INPUT);
  pinMode(digitalEleven, OUTPUT);
  pinMode(digitalThirteen, OUTPUT);
  digitalWrite(digitalEleven, HIGH);
  digitalWrite(digitalThirteen, LOW);
}

void lightTopRight()
{
  pinMode(digitalTwelve, INPUT);
  digitalWrite(digitalThirteen, HIGH);
  digitalWrite(digitalEleven, LOW);
}

void lightMiddleLeft()
{
  pinMode(digitalEleven, INPUT);
  pinMode(digitalTwelve, OUTPUT);
  pinMode(digitalThirteen, OUTPUT);
  digitalWrite(digitalTwelve, HIGH);
  digitalWrite(digitalThirteen, LOW);
}

void lightMiddleRight()
{
  pinMode(digitalThirteen, INPUT);
  pinMode(digitalEleven, OUTPUT);
  pinMode(digitalTwelve, OUTPUT);
  digitalWrite(digitalEleven, HIGH);
  digitalWrite(digitalTwelve, LOW);
}

void lightBottomLeft()
{
  pinMode(digitalEleven, INPUT);
  pinMode(digitalThirteen, OUTPUT);
  pinMode(digitalTwelve, OUTPUT);
  digitalWrite(digitalThirteen, HIGH);
  digitalWrite(digitalTwelve, LOW);
}

void lightBottomRight()
{
  pinMode(digitalThirteen, INPUT);
  pinMode(digitalTwelve, OUTPUT);
  pinMode(digitalEleven, OUTPUT);
  digitalWrite(digitalTwelve, HIGH);
  digitalWrite(digitalEleven, LOW);
}
