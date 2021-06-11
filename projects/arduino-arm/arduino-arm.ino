#include <Servo.h>
#include <ResponsiveAnalogRead.h>

// https://create.arduino.cc/projecthub/MisterBotBreak/how-to-use-a-joystick-with-serial-monitor-1f04f0

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

const int servo1Pin = 11;
const int servo2Pin = 10;
const int servo3Pin = 9;
const int servo4Pin = 6;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
int servo1Pos = 90;
int servo2Pos = 90;
int servo3Pos = 90;
int servo4Pos = 0;

ResponsiveAnalogRead analog(potPin, false);
void setup()
{
  Serial.begin(9600);

  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT);

  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo3.attach(servo3Pin);
  servo4.attach(servo4Pin);
  servo1.write(servo1Pos);
  servo2.write(servo2Pos);
  servo3.write(servo3Pos);
  servo4.write(servo4Pos);
}

void loop()
{
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  //zPosition = analogRead(potPin);
  analog.update();
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, 0, 180);
  mapY = map(yPosition, 0, 1023, 0, 180);
  mapZ = map(analog.getValue(), 0, 1023, 0, 180);

  Serial.print("X: ");
  Serial.print(mapX);
  Serial.print(" | Y: ");
  Serial.print(mapY);
  Serial.print(" | Button: ");
  Serial.println(SW_state);

  servo1Pos = mapY;
  servo2Pos = mapX;
  servo3Pos = mapZ;

  servo1.write(servo1Pos);
  servo2.write(servo2Pos);
  servo3.write(servo3Pos);
  servo4.write(servo4Pos);

  delay(25);
}
