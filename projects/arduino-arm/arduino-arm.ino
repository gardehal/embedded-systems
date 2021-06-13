#include <Servo.h>

// Joystick for arm base and and first joint
// Potentiometer for second joint
// Button for fingers
const int VRx = A0;
const int VRy = A1;
const int SW = 2;
const int potPin = A2;

int xPosition = 0;
int yPosition = 0;
int zPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;
int mapZ = 0;
int mapG = 0;

const int initialState = 90;
const int padding = 15;
const int moveSteps = 2;
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
  
  servo1.write(servo1Pos);
  servo2.write(servo2Pos);
  servo3.write(servo3Pos);
  servo4.write(servo4Pos);
  
  Serial.begin(9600);
}

void loop()
{  
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  zPosition = 0;//analogRead(potPin);
  SW_state = 0;//digitalRead(SW);
  
  mapX = map(xPosition, 0, 1023, 0, 180);
  mapY = map(yPosition, 0, 1023, 0, 180);
  mapZ = map(zPosition, 0, 1023, 0, 180);
  mapG = map(SW_state, 0, 1, 0, 1);
  
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
  if(mapX > (initialState + padding) && servo1Pos < (180 - moveSteps - 5))
  {
    servo1Pos += moveSteps; 
    servo1.write(servo1Pos);
    Serial.print("servo1Pos: ");
    Serial.println(servo1Pos);
  }
  else if(mapX < (initialState - padding) && servo1Pos > (0 + moveSteps + 5))
  {
    servo1Pos -= moveSteps; 
    servo1.write(servo1Pos);
    Serial.print("servo1Pos: ");
    Serial.println(servo1Pos);
  }
    
  if(mapY > (initialState + padding) && servo2Pos < (180 - moveSteps - 5))
  {
    servo2Pos += moveSteps; 
    servo2.write(servo2Pos);
    Serial.print("servo2Pos: ");
    Serial.println(servo2Pos);
  }
  else if(mapY < (initialState - padding) && servo2Pos < (0 + moveSteps + 5))
  {
    servo2Pos -= moveSteps; 
    servo2.write(servo2Pos);
    Serial.print("servo2Pos: ");
    Serial.println(servo2Pos);
  }
   
  if(mapZ > (initialState + padding) && servo3Pos < (180 - moveSteps - 5))
  {
    servo3Pos += moveSteps; 
    servo3.write(servo3Pos);
  }
  else if(mapZ < (initialState - padding) && servo3Pos < (0 + moveSteps + 5))
  {
    servo3Pos -= moveSteps; 
    servo3.write(servo3Pos);
  }

  // TODO grabber
  //if(!SW_state)
    //servo4Pos = 0;
  //else
    //servo4Pos = 180;
  
  //servo4.write(servo4Pos);

  delay(100);
}
