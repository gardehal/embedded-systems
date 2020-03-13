#include <dht.h>

dht DHT;

const int tempPin = 2;
const int fanRelayPin = 3;

const int collectionSet = 8;

void setup() 
{
  pinMode(fanRelayPin, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  float averageT = 0;

  for(int i = 0; i < collectionSet; i++)
  { 
    int chk = DHT.read11(tempPin);
  
    // chk fluxes between -1 (plausible readings) and -2 (-999 or 999). Ignore -2.
    if(chk == -2)
    {
      i--;
      continue;
    }

    float t = DHT.temperature;
    float h = DHT.humidity;
    
    Serial.println(i);
    Serial.print("Temperature = ");
    Serial.println(t);
    Serial.print("Humidity = ");
    Serial.println(h);

    averageT += t;
  }

  averageT = averageT / collectionSet;
  
  Serial.print("Average Temperature = ");
  Serial.println(averageT);
  Serial.println("--------------------------------------------");

  if(averageT > 25)
    digitalWrite(fanRelayPin, HIGH);
  else
    digitalWrite(fanRelayPin, LOW);
}
