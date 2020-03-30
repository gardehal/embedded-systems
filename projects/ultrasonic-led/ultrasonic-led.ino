
const int trigPin = 9;
const int echoPin = 10;
const int ledRedPin = 11;
const int ledGreenPin = 12;
const int ledBluePin = 13;

long duration;
int distance = 0;
int maxDistance = 64;

void setup() 
{
  Serial.begin(9600);
  
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(ledRedPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
  pinMode(ledBluePin, OUTPUT);
}

void loop() 
{
  mainLoop();
  //displayColours();
}

void displayColours()
{
  colourShift(distance);
  distance += 1;

  if(distance > maxDistance)
    distance = 0;
  delay(500);
}

void mainLoop()
{
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance in centimeters
  distance = duration*0.034/2;

  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  if(distance < 100)
  {
    //blinkLed();
    colourShift(distance);
  }
  
  delay(100);
}

float limit(float value)
{
  if(value < 0)
    return 0;
  else if(value > 255)
    return 255;
  else
    return value;
}

void colourShift(float x)
{  
  float redValue = abs((0.25 * ((x - 32) * (x - 32))));
  float greenValue = abs((-0.25 * ((x - 32) * (x - 32))) + 255);
  float blueValue = abs((x * -4) + 255);

  redValue = limit(redValue);
  greenValue = limit(greenValue);
  blueValue = limit(blueValue);
  
  Serial.print("redValue: ");
  Serial.println(redValue);
  Serial.print("greenValue: ");
  Serial.println(greenValue);
  Serial.print("blueValue: ");
  Serial.println(blueValue);
  Serial.println(" ");

  // Using analog with 255 iinstead of 125 because digitalWrite only does white and primary colours
  analogWrite(ledRedPin, redValue);
  analogWrite(ledGreenPin, greenValue);
  analogWrite(ledBluePin, blueValue);
}

void blinkLed()
{
  digitalWrite(ledBluePin, HIGH);
  delay(distance * 10);
  digitalWrite(ledBluePin, LOW);
  delay(distance * 10);
}
