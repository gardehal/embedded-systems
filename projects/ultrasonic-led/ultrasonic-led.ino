
const int trigPin = 9;
const int echoPin = 10;
const int ledRedPin = 11;
const int ledGreenPin = 12;
const int ledBluePin = 13;

long duration;
int distance;

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
    digitalWrite(ledBluePin, HIGH);
    delay(distance * 10);
    digitalWrite(ledBluePin, LOW);
    delay(distance * 10);
  }
}
