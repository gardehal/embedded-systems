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

const long delayTime = 60000; // 60 000 milliseconds = 1 minute
int hours = 0;
int minutes = 0;

void setup() 
{  
  Serial.begin(9600);

  // TODO Get time programtically
  // Adjust time on startup due to lack of synchronization  to computer clock or RTC module
  hours = 19; // Current hour value, 0 to 23
  minutes = 43; // Current minute value, 0 to 59

  int startupMinutesAdjust = minutes % 5; // Calculate modulo of minutes
  if(hours > 11) // Adjust 24 hour times to 12
    hours = hours - 12;
  //minutes = map(minutes, 0, 59, 0, 11);
  minutes = minutes / 5;
  
  lightHourLeds(hours);
  lightMinuteLeds(minutes);
  
  // On startup, adjust minutes to 5 minute steps but waiting until
  if(startupMinutesAdjust > 0)
    delay(delayTime * (5 - startupMinutesAdjust)); // Use modulo to figure out how long to wait to syncronize 5 minute step value
}

void loop() 
{
  // blinkAll();
  clockLoop();
}

void clockLoop()
{
  minutes++;
    
  if(minutes > 11)
  {
    minutes = 0; 
    hours++;
    
    if(hours > 11)
      hours = 0;
  }
  
  lightHourLeds(hours);
  lightMinuteLeds(minutes);
  
  delay(delayTime * 5);
}

void reset()
{
  for(int i = 0; i < 14; i++)
  {
    pinMode(i, INPUT);
  }
}

void resetMinuteLeds()
{
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
}

void resetHourLeds()
{
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
}

void lightLed(int firstPin, int secondPin, boolean doReset = false)
{
  if(doReset)
    reset();
  
  pinMode(firstPin, OUTPUT);
  pinMode(secondPin, OUTPUT);
  digitalWrite(firstPin, HIGH);
  digitalWrite(secondPin, LOW);
}

void lightHourLeds(int hour)
{
  // digitalEight
  // digitalNine
  // digitalTen
  // digitalEleven
  // digitalTwelve
  // digitalThirteen
  resetHourLeds();
  
  switch(hour)
  {
    case(0):
      lightLed(digitalEight, digitalTen);
      break;
    case(1):
      lightLed(digitalNine, digitalTen);
      break;
    case(2):
      lightLed(digitalTen, digitalNine);
      break;
    case(3):
      lightLed(digitalThirteen, digitalTwelve);
      break;
    case(4):
      lightLed(digitalTwelve, digitalThirteen);
      break;
    case(5):
      lightLed(digitalEleven, digitalThirteen);
      break;
    case(6):
      lightLed(digitalTen, digitalEight);
      break;
    case(7):
      lightLed(digitalEight, digitalNine);
      break;
    case(8):
      lightLed(digitalNine, digitalEight);
      break;
    case(9):
      lightLed(digitalTwelve, digitalEleven);
      break;
    case(10):
      lightLed(digitalEleven, digitalTwelve);
      break;
    case(11):
      lightLed(digitalThirteen, digitalEleven);
      break;
  }
}

void lightMinuteLeds(int minuteStep)
{
  // digitalTwo
  // digitalThree
  // digitalFour
  // digitalFive
  // digitalSix
  // digitalSeven

  resetMinuteLeds();
  
  switch(minuteStep)
  {
    case(0):
      lightLed(digitalFive, digitalSeven);
      break;
    case(1):
      lightLed(digitalSix, digitalSeven);
      break;
    case(2):
      lightLed(digitalSeven, digitalSix);
      break;
    case(3):
      lightLed(digitalFour, digitalThree);
      break;
    case(4):
      lightLed(digitalThree, digitalFour);
      break;
    case(5):
      lightLed(digitalTwo, digitalFour);
      break;
    case(6):
      lightLed(digitalSeven, digitalFive);
      break;
    case(7):
      lightLed(digitalFive, digitalSix);
      break;
    case(8):
      lightLed(digitalSix, digitalFive);
      break;
    case(9):
      lightLed(digitalThree, digitalTwo);
      break;
    case(10):
      lightLed(digitalTwo, digitalThree);
      break;
    case(11):
      lightLed(digitalFour, digitalTwo);
      break;
  }
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
  lightLed(digitalEight, digitalTen, true); // Grid 0, 0
  delay(1000);
  lightLed(digitalTen, digitalEight, true); // Grid 0, 1
  delay(1000);
  lightLed(digitalNine, digitalTen, true); // Grid 1, 0
  delay(1000);
  lightLed(digitalEight, digitalNine, true); // Grid 1, 1
  delay(1000);
  lightLed(digitalTen, digitalNine, true); // Grid 2, 0
  delay(1000);
  lightLed(digitalNine, digitalEight, true); // Grid 2, 1

  // Bottom left cluster
  delay(1000);
  lightLed(digitalThirteen, digitalTwelve, true); // Grid 3, 0
  delay(1000);
  lightLed(digitalTwelve, digitalEleven, true); // Grid 3, 1
  delay(1000);
  lightLed(digitalTwelve, digitalThirteen, true); // Grid 4, 0
  delay(1000);
  lightLed(digitalEleven, digitalTwelve, true); // Grid 4, 1
  delay(1000);
  lightLed(digitalEleven, digitalThirteen, true); // Grid 5, 0
  delay(1000);
  lightLed(digitalThirteen, digitalEleven, true); // Grid 5, 1

  // Top right cluster
  delay(1000);
  lightLed(digitalFive, digitalSeven, true); // Grid 0, 2
  delay(1000);
  lightLed(digitalSeven, digitalFive, true); // Grid 0, 3
  delay(1000);
  lightLed(digitalSix, digitalSeven, true); // Grid 1, 2
  delay(1000);
  lightLed(digitalFive, digitalSix, true); // Grid 1, 3
  delay(1000);
  lightLed(digitalSeven, digitalSix, true); // Grid 2, 2
  delay(1000);
  lightLed(digitalSix, digitalFive, true); // Grid 2, 3

  // Bottom rightt cluster
  delay(1000);
  lightLed(digitalFour, digitalThree, true); // Grid 3, 2
  delay(1000);
  lightLed(digitalThree, digitalTwo, true); // Grid 3, 3
  delay(1000);
  lightLed(digitalThree, digitalFour, true); // Grid 4, 2
  delay(1000);
  lightLed(digitalTwo, digitalThree, true); // Grid 4, 3
  delay(1000);
  lightLed(digitalTwo, digitalFour, true); // Grid 5, 2
  delay(1000);
  lightLed(digitalFour, digitalTwo, true); // Grid 5, 3
}
