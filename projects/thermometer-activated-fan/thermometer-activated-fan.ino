#include <dht.h>

dht DHT;

const int tempPin = 2;
const int fanPin = 4;

void setup() 
{
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


  // Relay to get 5v?
  // Engage fan
  if(DHT.temperature >  25)
  {
    digitalWrite(fanPin, HIGH);
  }
  else
  {
    digitalWrite(fanPin, LOW);
  }
  
  delay(1000);
}
