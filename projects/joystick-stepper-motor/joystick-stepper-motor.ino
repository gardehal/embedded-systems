#include <Stepper.h>

// https://create.arduino.cc/projecthub/MisterBotBreak/how-to-use-a-joystick-with-serial-monitor-1f04f0

#define STEPS 64

int VRx = A0;
int VRy = A1;
int SW = 2;

int stepper1 = 10;
int stepper2 = 11;
int stepper3 = 12;
int stepper4 = 13;

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

  stepper.setSpeed(200);
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
  
  if (mapX > 20 || mapX < -20)
  {
    val = mapX;
    stepper.step(val);
    Serial.println(val); //for debugging
  }

  delay(1);
  
}
