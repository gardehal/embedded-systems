#include "Servo.h"
#include "IRremote.h"

// Elegoo remote
#include "ElegooIrRemote.h"
ElegooIrRemote irRemote;

const int initialState = 90;
const int moveSteps = 10;
const int minDegreesSegment = 0;
const int maxDegreesSegment = 180;
const int minDegreesFinger = 45;
const int maxDegreesFinger = 135;

const int irRecPin = 2;
const int servo1Pin = 12;
const int servo2Pin = 11;
const int servo3Pin = 10;
const int servo4Pin = 9;
const int servo5Pin = 8;
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

  
  // left/right = irRemote.key4, irRemote.key6
  // humerus up/down = irRemote.key1, irRemote.key7
  // radius up/down = irRemote.key2, irRemote.key8
  // hand up/down = irRemote.key3, irRemote.key9
  // fingers close/open = irRemote.key5, irRemote.key0

  // emote wave = ?
  // emote show range = playPause

void loop()
{ 
  if(IrReceiver.decode())
  {    
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
        servo5Pos = calcMove(moveSteps, servo5Pos, minDegreesFinger, maxDegreesFinger);
        servo5.write(servo5Pos);
        break;
      case irRemote.keyEq:
        Serial.println("EQ");
        break;
      case irRemote.keyStRept:
        Serial.println("ST/REPT");
        break;
      case irRemote.key1:
        Serial.println("1");
        servo2Pos = calcMove(moveSteps, servo2Pos, minDegreesSegment, maxDegreesSegment);
        servo2.write(servo2Pos);
        break;
      case irRemote.key2:
        Serial.println("2");
        servo3Pos = calcMove(moveSteps, servo3Pos, minDegreesSegment, maxDegreesSegment);
        servo3.write(servo3Pos);
        break;
      case irRemote.key3:
        Serial.println("3");
        servo4Pos = calcMove(moveSteps, servo4Pos, minDegreesSegment, maxDegreesSegment);
        servo4.write(servo4Pos);
        break;
      case irRemote.key4:
        Serial.println("4");
        servo1Pos = calcMove(moveSteps, servo1Pos, minDegreesSegment, maxDegreesSegment);
        servo1.write(servo1Pos);
        break;
      case irRemote.key5:
        Serial.println("5");
        servo5Pos = calcMove(-1 * moveSteps, servo5Pos, minDegreesFinger, maxDegreesFinger);
        servo5.write(servo5Pos);
        break;
      case irRemote.key6:
        Serial.println("6");
        servo1Pos = calcMove(-1 * moveSteps, servo1Pos, minDegreesSegment, maxDegreesSegment);
        servo1.write(servo1Pos);
        break;
      case irRemote.key7:
        Serial.println("7");
        servo2Pos = calcMove(-1 * moveSteps, servo2Pos, minDegreesSegment, maxDegreesSegment);
        servo2.write(servo2Pos);
        break;
      case irRemote.key8:
        Serial.println("8");
        servo3Pos = calcMove(-1 * moveSteps, servo3Pos, minDegreesSegment, maxDegreesSegment);
        servo3.write(servo3Pos);
        break;
      case irRemote.key9:
        Serial.println("9");
        servo4Pos = calcMove(-1 * moveSteps, servo4Pos, minDegreesSegment, maxDegreesSegment);
        servo4.write(servo4Pos);
        break;
      default:
        Serial.print(" - value: ");
        Serial.println(IrReceiver.decodedIRData.command);
    }
  
    IrReceiver.resume(); 
  }
}

int calcMove(int toMove, int current, int minDegrees, int maxDegrees)
{
    int steps = abs(toMove)/10;
    
    if(toMove > 0 && current < (maxDegrees - steps))
      return (current += steps); 
    else if(toMove < 0 && current > (minDegrees + steps))
      return (current -= steps); 
}
