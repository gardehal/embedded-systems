#include <Servo.h>

// Joystick for arm base and and first joint
// Potentiometer for second joint
// Button for fingers
const int VRx = A0;
const int VRy = A1;
const int SW = 2;
const int potPin = A2;

const int initialState = 90;
const int padding = 15;

const int servo1Pin = 11;
const int servo2Pin = 10;
const int servo3Pin = 9;
const int servo4Pin = 6;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
int servo1Pos = initialState;
int servo2Pos = initialState;
int servo3Pos = initialState;
int servo4Pos = initialState;

void setup()
{
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo3.attach(servo3Pin);
  servo4.attach(servo4Pin);
  pinMode(SW, INPUT); 
  
  servo1.write(servo1Pos);
  servo2.write(servo2Pos);
  servo3.write(servo3Pos);
  servo4.write(servo4Pos);
  
  Serial.begin(9600);
}

void loop()
{  
  int xPosition = analogRead(VRx);
  int yPosition = analogRead(VRy);
  int zPosition = analogRead(potPin);
  int SW_state = digitalRead(SW);
  
  int mapX = map(xPosition, 0, 1023, -90, 90);
  int mapY = map(yPosition, 0, 1023, -90, 90);
  int mapZ = map(zPosition, 0, 1023, -90, 90);
  int mapG = map(SW_state, 0, 1, 0, 1);
  
  Serial.print("X: ");
  Serial.print(mapX);
  Serial.print(" | Y: ");
  Serial.print(mapY);
  Serial.print(" | Z: ");
  Serial.print(mapZ);
  Serial.print(" | G: ");
  Serial.print(mapG);
  Serial.println("");

  // Update servos based on current position +/- joystick input 
  if(abs(mapX) > padding)
  {
    servo1Pos = calcMove(mapX, servo1Pos);
    servo1.write(servo1Pos);
    
    Serial.print("servo1Pos: ");
    Serial.println(servo1Pos);
  }
  
  if(abs(mapY) > padding)
  {
    servo2Pos = calcMove(mapY, servo2Pos);
    servo2.write(servo2Pos);
    
    Serial.print("servo2Pos: ");
    Serial.println(servo2Pos);
  }
  
  if(false && abs(mapZ) > padding)
  {
    servo3Pos = calcMove(mapZ, servo3Pos);
    servo3.write(servo3Pos);
    
    Serial.print("servo3Pos: ");
    Serial.println(servo3Pos);
  }
  
  if(false && !SW_state)
  {
    //servo4.write(servo4Pos);
  }

  delay(100);
}

int calcMove(int mapVar, int current)
{
    int steps = abs(mapVar)/10;
    
    if(mapVar > 0 && current < (180 - steps))
      return (current += steps); 
    else if(mapVar < 0 && current > (0 + steps))
      return (current -= steps); 
}
