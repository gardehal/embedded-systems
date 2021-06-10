#include <Servo.h>

// https://create.arduino.cc/projecthub/MisterBotBreak/how-to-use-a-joystick-with-serial-monitor-1f04f0

const int VRx = A0;
const int VRy = A1;
const int SW = 2;

int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;

Servo servo;
int servoPos = 0;
const int servo1 = 11;

void setup() 
{
  Serial.begin(9600); 
  
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP); 
  
  servo.attach(servo1);
  servo.write(90);
}

void loop() 
{
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, 0, 180);
  mapY = map(yPosition, 0, 1023, 0, 180);
  
  Serial.print("X: ");
  Serial.print(mapX);
  Serial.print(" | Y: ");
  Serial.print(mapY);
  Serial.print(" | Button: ");
  Serial.println(SW_state);

  // Minimum
  if (mapY > 150)
    servoPos = 0;
    
  // Maximum
  else if (mapY < 30)
    servoPos = 180;
    
  // Rotation based on the tilt of the joystick
  // Minimum is 32 to prevent interference from wires wiggling
  else if (mapX > 85 || mapX < 95)
    servoPos = mapX;

  else
    servoPos = servoPos;

  Serial.print("servoPos: ");
  Serial.println(servoPos);
  servo.write(servoPos);
  
  delay(10);
}
