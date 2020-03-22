
#include <Time.h>

#define TIME_HEADER 255
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

const int delayMinute = 60000; // 60 000 milliseconds = 1 minute

void setup() 
{  
  Serial.begin(9600);

  reset();
}
void loop() 
{
  // Hours = (DateTime.Hour,DEC);
  // Minutes = DateTime.Minute;
  // Seconds = DateTime.Second;
  //Serial.print((DateTime.Hour,DEC));
  
  blinkAll();

  // Get time of day?
  // set hour to current hour
  // set minutes to closes minute in 5 minute steps, set difference as delay time
  // enter infinite loop where every 5 minutes, increment minute led steps, every hour (12 minute steps) increment hours and set minutes back to 0
}



void blinkAll()
{
  // digitalTwo
  // digitalThree
  // digitalFour
  // digitalFive
  // digitalSix
  // digitalSeven
  // digitalEight
  // digitalNine
  // digitalTen
  // digitalEleven
  // digitalTwelve
  // digitalThirteen
  
  // Top left cluster
  delay(1000);
  lightLed(digitalEight, digitalTen); // Grid 0, 0
  delay(1000);
  lightLed(digitalTen, digitalEight); // Grid 0, 1
  delay(1000);
  lightLed(digitalNine, digitalTen); // Grid 1, 0
  delay(1000);
  lightLed(digitalEight, digitalNine); // Grid 1, 1
  delay(1000);
  lightLed(digitalTen, digitalNine); // Grid 2, 0
  delay(1000);
  lightLed(digitalNine, digitalEight); // Grid 2, 1

  // Bottom left cluster
  delay(1000);
  lightLed(digitalThirteen, digitalTwelve); // Grid 3, 0
  delay(1000);
  lightLed(digitalTwelve, digitalEleven); // Grid 3, 1
  delay(1000);
  lightLed(digitalTwelve, digitalThirteen); // Grid 4, 0
  delay(1000);
  lightLed(digitalEleven, digitalTwelve); // Grid 4, 1
  delay(1000);
  lightLed(digitalEleven, digitalThirteen); // Grid 5, 0
  delay(1000);
  lightLed(digitalThirteen, digitalEleven); // Grid 5, 1

  // Top right cluster
  delay(1000);
  lightLed(digitalFive, digitalSeven); // Grid 0, 2
  delay(1000);
  lightLed(digitalSeven, digitalFive); // Grid 0, 3
  delay(1000);
  lightLed(digitalSix, digitalSeven); // Grid 1, 2
  delay(1000);
  lightLed(digitalFive, digitalSix); // Grid 1, 3
  delay(1000);
  lightLed(digitalSeven, digitalSix); // Grid 2, 2
  delay(1000);
  lightLed(digitalSix, digitalFive); // Grid 2, 3

  // Bottom rightt cluster
  delay(1000);
  lightLed(digitalFour, digitalThree); // Grid 3, 2
  delay(1000);
  lightLed(digitalThree, digitalTwo); // Grid 3, 3
  delay(1000);
  lightLed(digitalThree, digitalFour); // Grid 4, 2
  delay(1000);
  lightLed(digitalTwo, digitalThree); // Grid 4, 3
  delay(1000);
  lightLed(digitalTwo, digitalFour); // Grid 5, 2
  delay(1000);
  lightLed(digitalFour, digitalTwo); // Grid 5, 3
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
