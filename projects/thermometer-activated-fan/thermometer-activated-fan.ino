#include <dht.h>

dht DHT;

const int tempPin = 2;
const int fanRelayPin = 3;

void setup() 
{
  pinMode(fanRelayPin, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  int chk = DHT.read11(tempPin);
  
  // chk fluxes between -1 (plausible readings) and -2 (-999 or 999). Ignore -2.
  if(chk == -2)
    return;
    
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);

  if(DHT.temperature >  25)
  {
    digitalWrite(fanRelayPin, HIGH);
  }
  else
  {
    digitalWrite(fanRelayPin, LOW);
  }
  
  delay(1000);
}
