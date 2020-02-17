


const int rgbRedPin = 4;
const int rgbGreenPin = 3;
const int rgbBluePin = 2;
const int rbgPins[] = {rgbRedPin, rgbGreenPin, rgbBluePin};

const int redPin = 9;
const int yellowPin = 10;
const int greenPin = 11;

int onValue = 255;
int offValue = 0;
int blinkCycle = 1000;
int changeCycleTime = 8000;

void setup() 
{
  Serial.begin(9600);
}

void comments(int pins[], int pinOnValues[], int pinOffValues[])
{
  int size = sizeof(pins);
  if(sizeof(pinOnValues) < size || sizeof(pinOffValues) < size )
  {
    for(int i = 0; i < size; i++)
    {
      pinOnValues[i] = onValue;
      pinOffValues[i] = offValue;
    }
  }
  
  
  analogWrite(rgbRedPin, onValue);
  analogWrite(rgbGreenPin, 123);
  delay(500);
  analogWrite(rgbRedPin, offValue);
  analogWrite(rgbGreenPin, offValue);
  analogWrite(rgbBluePin, offValue);
  delay(500);
}

void loop() 
{ 
  int ons[] = {onValue};
  int offs[] = {offValue};
  int reds[1] = {rgbRedPin};
  blink(rbgPins, ons, offs);

  return;
  startTraffic();
  delay(changeCycleTime);
  
  haltTraffic();
  delay(changeCycleTime / 2);
  
  stopTraffic();
  
  delay(changeCycleTime);
}

void haltPedestrians()
{
}

void stopPedestrians()
{
  analogWrite(rgbGreenPin, offValue);
  analogWrite(rgbBluePin, offValue);
  analogWrite(rgbRedPin, onValue);
}

void startPedestrians()
{
  analogWrite(rgbRedPin, offValue);
  analogWrite(rgbBluePin, offValue);
  analogWrite(rgbGreenPin, onValue);
}

void haltTraffic()
{
  analogWrite(greenPin, offValue);
  analogWrite(yellowPin, onValue);
}

void stopTraffic()
{
  analogWrite(yellowPin, offValue);
  analogWrite(redPin, onValue);
}

void startTraffic()
{
  analogWrite(yellowPin, offValue);
  analogWrite(redPin, offValue);
  analogWrite(greenPin, onValue);
}

void blink(int pins[], int pinOnValues[], int pinOffValues[])
{    
  int size = sizeof(pins);
  
  for(int i = 0; i < size; i++)
  {
    analogWrite(pins[i], pinOffValues[i]);
  }
  delay(blinkCycle / 2);
  
  for(int i = 0; i < size; i++)
  {
    analogWrite(pins[i], pinOnValues[i]);
  }
  delay(blinkCycle / 2);
}
