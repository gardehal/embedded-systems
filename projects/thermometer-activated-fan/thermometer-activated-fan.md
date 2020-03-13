# Thermometer Activated Fan

A fan that is activated when a certain temperature and/or level of humidity is registered.

I found that the DHT11 is unreliable, usually returning 14 or 28 (+/- 2), though it's likely not more than 25 degrees in the room at most. 
For this reason I added a for loop to get an average of tempratures but it seems the inconsistency is from the sensor itself, not the wireing within the sensor or in the circuit. 
I thought I noticed the sensor returned 14 whenever the fan turned on due to the fan cooling the sensor, but the drop is too much to be from the fan, as well as the fact that the fan does not point at the sensor suggests it's something else. It could be that the surge og power sent to the fan could be altering the signals sent to the Arduino board.

[Code](./thermometer-activated-fan.ino)

[Video](./thermometer-activated-fan.mp4)

## Circuit Diagram

![Circuit Diagram](./thermometer-activated-fan.png)