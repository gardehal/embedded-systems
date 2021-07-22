#include "Servo.h"
#include "IRremote.h"

// Elegoo remote
#include "ElegooIrRemote.h"
ElegooIrRemote irRemote;

const int initialState = 90;
const int moveSteps = 1;
const int minDegreesSegment = 0;
const int maxDegreesSegment = 180;
const int minDegreesFinger = 45;
const int maxDegreesFinger = 135;
int preivousMove = 0;
float moveMultiplier = 1;
bool useMoveMultiplier = true;

const int irRecPin = 2;
const int servo1Pin = 11;
const int servo2Pin = 10;
const int servo3Pin = 9;
const int servo4Pin = 6;
const int servo5Pin = 5;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
int servo1Pos = initialState;
int servo2Pos = initialState;
int servo3Pos = initialState;
int servo4Pos = initialState;
int servo5Pos = initialState;

void setup()
{
  IrReceiver.begin(irRecPin);
  
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo3.attach(servo3Pin);
  servo4.attach(servo4Pin);
  servo5.attach(servo5Pin);
  
  servo1.write(servo1Pos);
  servo2.write(servo2Pos);
  servo3.write(servo3Pos);
  servo4.write(servo4Pos);
  servo5.write(servo5Pos);
  
  Serial.begin(9600);
}

void loop()
{ 
  if(IrReceiver.decode())
  {
    if(useMoveMultiplier && preivousMove == IrReceiver.decodedIRData.command)
      moveMultiplier += 0.1;
    else
      moveMultiplier = 1;
      
    switch(IrReceiver.decodedIRData.command)
    {
      case irRemote.keyPower:
        Serial.println("Power");
        break;
      case irRemote.keyVolumePlus:
        Serial.println("VOL+");
        break;
      case irRemote.keyFuncStop:
        Serial.println("FUNC/STOP");
        break;
      case irRemote.keyBack:
        Serial.println("Back");
        break;
      case irRemote.keyPlayPause:
        Serial.println("Play/Pause");
        break;
      case irRemote.keyForward:
        Serial.println("Forward");
        break;
      case irRemote.keyDown:
        Serial.println("Down");
        break;
      case irRemote.keyVolumeMinus:
        Serial.println("VOL-");
        break;
      case irRemote.keyUp:
        Serial.println("Up");
        break;
      case irRemote.key0:
        Serial.println("0");
        servo5Pos = calcMove(moveSteps * moveMultiplier, servo5Pos, minDegreesFinger, maxDegreesFinger);
        servo5.write(servo5Pos * moveMultiplier);
        // TODO holding 0 then pressing 5 shoots fingers close, but 5 thne 0 does not apply. Multiplier?
        Serial.print("IrReceiver.decodedIRData.command ");
        Serial.println(IrReceiver.decodedIRData.command);
        Serial.print("preivousMove ");
        Serial.println(preivousMove);
        Serial.print("useMoveMultiplier ");
        Serial.println(useMoveMultiplier);
        Serial.print("servo5Pos ");
        Serial.println(servo5Pos);
        Serial.print("moveMultiplier ");
        Serial.println(moveMultiplier);
        Serial.print("servo5Pos * moveMultiplier ");
        Serial.println(servo5Pos * moveMultiplier);
        break;
      case irRemote.keyEq:
        Serial.println("EQ");
        break;
      case irRemote.keyStRept:
        Serial.println("ST/REPT");
        useMoveMultiplier = !useMoveMultiplier;
        break;
      case irRemote.key1:
        Serial.println("1");
        servo2Pos = calcMove(moveSteps, servo2Pos, minDegreesSegment, maxDegreesSegment);
        servo2.write(servo2Pos * moveMultiplier);
        break;
      case irRemote.key2:
        Serial.println("2");
        servo3Pos = calcMove(moveSteps, servo3Pos, minDegreesSegment, maxDegreesSegment);
        servo3.write(servo3Pos * moveMultiplier);
        break;
      case irRemote.key3:
        Serial.println("3");
        servo4Pos = calcMove(moveSteps * moveMultiplier, servo4Pos, minDegreesSegment, maxDegreesSegment);
        servo4.write(servo4Pos);
        break;
      case irRemote.key4:
        Serial.println("4");
        servo1Pos = calcMove(moveSteps * moveMultiplier, servo1Pos, minDegreesSegment, maxDegreesSegment);
        servo1.write(servo1Pos);
        break;
      case irRemote.key5:
        Serial.println("5");
        servo5Pos = calcMove(-1 * moveSteps * moveMultiplier, servo5Pos, minDegreesFinger, maxDegreesFinger);
        servo5.write(servo5Pos);
        Serial.print("IrReceiver.decodedIRData.command ");
        Serial.println(IrReceiver.decodedIRData.command);
        Serial.print("preivousMove ");
        Serial.println(preivousMove);
        Serial.print("useMoveMultiplier ");
        Serial.println(useMoveMultiplier);
        Serial.print("servo5Pos ");
        Serial.println(servo5Pos);
        Serial.print("moveMultiplier ");
        Serial.println(moveMultiplier);
        Serial.print("servo5Pos * moveMultiplier ");
        Serial.println(servo5Pos * moveMultiplier);
        break;
      case irRemote.key6:
        Serial.println("6");
        servo1Pos = calcMove(-1 * moveSteps, servo1Pos, minDegreesSegment, maxDegreesSegment);
        servo1.write(servo1Pos * moveMultiplier);
        break;
      case irRemote.key7:
        Serial.println("7");
        servo2Pos = calcMove(-1 * moveSteps, servo2Pos, minDegreesSegment, maxDegreesSegment);
        servo2.write(servo2Pos * moveMultiplier);
        break;
      case irRemote.key8:
        Serial.println("8");
        servo3Pos = calcMove(-1 * moveSteps, servo3Pos, minDegreesSegment, maxDegreesSegment);
        servo3.write(servo3Pos * moveMultiplier);
        break;
      case irRemote.key9:
        Serial.println("9");
        servo4Pos = calcMove(-1 * moveSteps, servo4Pos, minDegreesSegment, maxDegreesSegment);
        servo4.write(servo4Pos * moveMultiplier);
        break;
      default:
        Serial.print(" - value: ");
        Serial.println(IrReceiver.decodedIRData.command);
    }

    preivousMove = IrReceiver.decodedIRData.command;
    IrReceiver.resume(); 
    delay(100);
  }
}

float calcMove(float toMove, float current, int minDegrees, int maxDegrees)
{
    float steps = current + toMove;
    if(steps > minDegrees && steps < maxDegrees)
      return steps;
    else if(steps <= minDegrees)
      return minDegrees;
    else if(steps >= maxDegrees)
      return maxDegrees;
      
    return current; 
}
