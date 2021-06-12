#include <IRremote.h>
#include <Servo.h>
#include <ResponsiveAnalogRead.h>

const long keyPower = 16753245;
const long keyVolPluss = 16736925;
const long keyFunc = 16769565;
const long keyLeft = 16720605;
const long keyPlay = 16712445;
const long keyRight = 16761405;
const long keyDown = 16769055;
const long keyVolMinus = 16754775;
const long keyUp = 16748655;
const long key0 = 16738455;
const long keyEq = 16750695;
const long keySt = 16756815;
const long key1 = 16724175;
const long key2 = 16718055;
const long key3 = 16743045;
const long key4 = 16716015;
const long key5 = 16726215;
const long key6 = 16734885;
const long key7 = 16728765;
const long key8 = 16730805;
const long key9 = 16732845;

const int irPin = 2;
IRrecv ir(irPin);
decode_results results;

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

void setup()
{
  Serial.begin(9600);
  
  ir.enableIRIn();

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
  if(ir.decode())
  {
    switch(results.value)
    {
      case keyPower:
        Serial.print("Power");
        break;
      case keyVolPluss:
        Serial.print("VOL+");
        servo2Pos += 4;
        break;
      case keyFunc:
        Serial.print("FUNC/STOP");
        break;
      case keyLeft:
        Serial.print("Left");
        servo1Pos += 4;
        break;
      case keyPlay:
        Serial.print("Play/Pause");
        break;
      case keyRight:
        Serial.print("Right");
        servo1Pos -= 4;
        break;
      case keyDown:
        Serial.print("Down");
        break;
      case keyVolMinus:
        Serial.print("VOL-");
        servo2Pos -= 4;
        break;
      case keyUp:
        Serial.print("Up");
        break;
      case key0:
        Serial.print("0");
        break;
      case keyEq:
        Serial.print("EQ");
        break;
      case keySt:
        Serial.print("ST/REPT");
        break;
      case key1:
        Serial.print("1");
        break;
      case key2:
        Serial.print("2");
        break;
      case key3:
        Serial.print("3");
        break;
      case key4:
        Serial.print("4");
        break;
      case key5:
        Serial.print("5");
        break;
      case key6:
        Serial.print("6");
        break;
      case key7:
        Serial.print("7");
        break;
      case key8:
        Serial.print("8");
        break;
      case key9:
        Serial.print("9");
        break;
      default:
        Serial.print(" - value: ");
        Serial.println(results.value);
    }

      ir.resume(); 
  }

  servo1.write(servo1Pos);
  servo2.write(servo2Pos);
  servo3.write(servo3Pos);
  servo4.write(servo4Pos);

  delay(25);
}
