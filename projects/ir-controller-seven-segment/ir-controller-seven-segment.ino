#include "IRremote.h"

// Elegoo remote
#include "ElegooIrRemote.h"
ElegooIrRemote irRemote;

const int irRecPin = 2;
const int segementNorthGPin = 3;
const int segementNorthFPin = 4;
const int segementNorthAPin = 5;
const int segementNorthBPin = 6;
const int segementSouthEPin = 7;
const int segementSouthDPin = 8;
const int segementSouthCPin = 9;
const int segementSouthDPPin = 10;

#include "SevenSegmentDisplay.h"
SevenSegmentDisplay ssDisplay(segementNorthGPin, segementNorthFPin, segementNorthAPin, segementNorthBPin, segementSouthEPin, segementSouthDPin, segementSouthCPin, segementSouthDPPin);

void setup()
{
  IrReceiver.begin(irRecPin);
  Serial.begin(9600);

  ssDisplay.display0();
}

void loop()
{
  if(IrReceiver.decode())
  {    
    switch(IrReceiver.decodedIRData.command)
    {
      case irRemote.keyPower:
        Serial.println("Power");
        ssDisplay.displayOff();
        break;
      case irRemote.keyVolumePlus:
        Serial.println("VOL+");
        ssDisplay.displayDotPoint();
        break;
      case irRemote.keyFuncStop:
        Serial.println("FUNC/STOP");
        break;
      case irRemote.keyBack:
        Serial.println("Back");
        break;
      case irRemote.keyPlayPause:
        Serial.println("Play/Pause");
        ssDisplay.displayAll();
        break;
      case irRemote.keyForward:
        Serial.println("Forward");
        break;
      case irRemote.keyDown:
        Serial.println("Down");
        ssDisplay.decrement();
        break;
      case irRemote.keyVolumeMinus:
        Serial.println("VOL-");
        ssDisplay.displayMinus();
        break;
      case irRemote.keyUp:
        Serial.println("Up");
        ssDisplay.increment();
        break;
      case irRemote.key0:
        Serial.println("0");
        ssDisplay.setNumber(0);
        break;
      case irRemote.keyEq:
        Serial.println("EQ");
        break;
      case irRemote.keyStRept:
        Serial.println("ST/REPT");
        break;
      case irRemote.key1:
        Serial.println("1");
        ssDisplay.setNumber(1);
        break;
      case irRemote.key2:
        Serial.println("2");
        ssDisplay.setNumber(2);
        break;
      case irRemote.key3:
        Serial.println("3");
        ssDisplay.setNumber(3);
        break;
      case irRemote.key4:
        Serial.println("4");
        ssDisplay.setNumber(4);
        break;
      case irRemote.key5:
        Serial.println("5");
        ssDisplay.setNumber(5);
        break;
      case irRemote.key6:
        Serial.println("6");
        ssDisplay.setNumber(6);
        break;
      case irRemote.key7:
        Serial.println("7");
        ssDisplay.setNumber(7);
        break;
      case irRemote.key8:
        Serial.println("8");
        ssDisplay.setNumber(8);
        break;
      case irRemote.key9:
        Serial.println("9");
        ssDisplay.setNumber(9);
        break;
      default:
        Serial.print(" - value: ");
        Serial.println(IrReceiver.decodedIRData.command);
    }
  
    IrReceiver.resume(); 
  }
}
