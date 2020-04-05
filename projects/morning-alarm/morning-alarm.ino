
const int pResistorPin = A0;
const int tiltSwitchPin = A1;
// const int passiveBuzzerPin = 12; // Unused
const int activeBuzzerPin = 13;

const long delayTime = 60000; // 60 seconds

long alarm = 1;
long currentTime = 0;
boolean enableAlarm = false;

void setup() 
{
  Serial.begin(9600);

  pinMode(pResistorPin, INPUT);
  pinMode(tiltSwitchPin, INPUT);
  // pinMode(passiveBuzzerPin, OUTPUT);
  pinMode(activeBuzzerPin, OUTPUT);

  // Synchronize time
  currentTime = syncTime();
}

void loop() 
{
  Serial.println("currentTime ");
  Serial.println(currentTime);
  
  Serial.println("alarm ");
  Serial.println(alarm);
  
  Serial.println("enableAlarm ");
  Serial.println(enableAlarm);
  
  Serial.println("------------");
  
  if(currentTime == (alarm - 1) && !enableAlarm)
  { 
    Serial.println("currentTime == alarm - 1");
    delay(60000); // Trigger on minute before alarm is set, wait one minute and then trigger to avoid alarm trigger, then turned of before time updates, causing the alarm to trigger again.
    enableAlarm = true;
  }

  if(enableAlarm)
  {
    Serial.println("enableAlarm true");
    soundAlarm(); // Causes alarm sound
    checkDisableAlarm(); // Will disable alarm if requirements are met
    return;
  }
  
  Serial.println("delayTime");
  delay(delayTime);
  
  // Synchronize time // Can be done with a counter so it's only done every x minutes in case of internet usage to save some bandwidth
  currentTime = syncTime();
}

void soundAlarm()
{
  // analogWrite
  // digitalWrite

  for(int i = 0; i < 3; i++)
  {
    digitalWrite(activeBuzzerPin, HIGH);
    delay(100);
    digitalWrite(activeBuzzerPin, LOW);
    delay(100);
  }
  
  delay(1000);
}

long syncTime()
{
  // Return whatever is the current real time
  return 0;
}

void checkDisableAlarm()
{
  int pResistorValue = analogRead(pResistorPin);
  int tiltSwitchValue = analogRead(tiltSwitchPin);
  
  Serial.print("Photoresistor value: ");
  Serial.println(pResistorValue);
  Serial.print("Tilt ball switch value: ");
  Serial.println(tiltSwitchValue);
  
  // Disable alarm
  if(pResistorValue > 1000 && tiltSwitchValue > 500)
    enableAlarm = false;
}
