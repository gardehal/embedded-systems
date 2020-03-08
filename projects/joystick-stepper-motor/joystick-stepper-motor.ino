#include <Stepper.h>

// https://create.arduino.cc/projecthub/MisterBotBreak/how-to-use-a-joystick-with-serial-monitor-1f04f0

#define STEPS 128

const int VRx = A0;
const int VRy = A1;
const int SW = 2;

const int stepper1 = 10;
const int stepper2 = 11;
const int stepper3 = 12;
const int stepper4 = 13;

Stepper stepper (STEPS, 10, 12, 11, 13);

int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;

void setup() 
{
  Serial.begin(9600); 
  
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP); 

  stepper.setSpeed(256);
}

void loop() 
{
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);
  
  Serial.print("X: ");
  Serial.print(mapX);
  Serial.print(" | Y: ");
  Serial.print(mapY);
  Serial.print(" | Button: ");
  Serial.println(SW_state);

  int val = 0; 

  // Half rotation
  if (mapY > 256)
    stepper.step(1024);
    
  // Full rotation
  else if (mapY < -256)
    stepper.step(2048);

  // Rotation based on the tilt of the joystick
  // Minimum is 32 to prevent interference from wires wiggling
  else if (mapX > 32 || mapX < -32)
    stepper.step(mapX);

  delay(10);
}
