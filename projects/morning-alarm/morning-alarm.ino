
const int pResistorPin = A0;
const int tiltSwitchPin = A1;
const int passiveBuzzerPin = 12;
const int activeBuzzerPin = 13;

const long minute = 60000; // 60 seconds
const int delayMinutes = 1;

int alarm = 0600;
int currentTime = 0;
boolean enableAlarm = false;

void setup() 
{
  Serial.begin(9600);

  pinMode(pResistorPin, INPUT);
  pinMode(tiltSwitchPin, INPUT);
  pinMode(passiveBuzzerPin, OUTPUT);
  pinMode(activeBuzzerPin, OUTPUT);

  // Synchronize time
  currentTime = syncTime();
}

void loop() 
{
  if(currentTime == alarm - 1)
  { 
    delay(minute); // Trigger on minute before alarm is set, wait one minute and then trigger to avoid alarm trigger, then turned of before time updates, causing the alarm to trigger again.
    enableAlarm = true;
  }

  if(enableAlarm)
  {
    soundAlarm(); // Causes alarm sound
    checkDisableAlarm(); // Will disable alarm if requirements are met
    return;
  }
  
  delay(minute * delayMinutes);
  
  // Synchronize time // Can be done with a counter so it's only done every x minutes in case of internet usage to save some bandwidth
  currentTime = syncTime();
}

void soundAlarm()
{
  // analogWrite
  // digitalWrite
  digitalWrite(passiveBuzzerPin, HIGH);
  delay(500);
  digitalWrite(passiveBuzzerPin, LOW);
  delay(500);
}

int syncTime()
{
  
}

void checkDisableAlarm()
{
  int pResistorValue = analogRead(pResistorPin);
  int tiltSwitchValue = analogRead(tiltSwitchPin);
  
  Serial.print("Photoresistor value: ");
  Serial.println(pResistorValue);
  Serial.print("Tilt ball switch value: ");
  Serial.println(tiltSwitchPin);
  
  // Disable alarm
  if(pResistorValue > 1000 && tiltSwitchPin > 500)
    enableAlarm = false;
}
