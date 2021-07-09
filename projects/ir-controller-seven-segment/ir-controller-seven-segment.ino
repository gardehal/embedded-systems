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

int currentNumber = 0;

void setup()
{
  IrReceiver.begin(irRecPin);
  Serial.begin(9600);

  display0();
}

void loop()
{
  if(IrReceiver.decode())
  {    
    switch(IrReceiver.decodedIRData.command)
    {
      case irRemote.keyPower:
        Serial.println("Power");
        displayOff();
        break;
      case irRemote.keyVolumePlus:
        Serial.println("VOL+");
        displayDotPoint();
        break;
      case irRemote.keyFuncStop:
        Serial.println("FUNC/STOP");
        break;
      case irRemote.keyBack:
        Serial.println("Back");
        break;
      case irRemote.keyPlayPause:
        Serial.println("Play/Pause");
        displayAll();
        break;
      case irRemote.keyForward:
        Serial.println("Forward");
        break;
      case irRemote.keyDown:
        Serial.println("Down");
        decrement();
        break;
      case irRemote.keyVolumeMinus:
        Serial.println("VOL-");
        displayMinus();
        break;
      case irRemote.keyUp:
        Serial.println("Up");
        increment();
        break;
      case irRemote.key0:
        Serial.println("0");
        setNumber(0);
        break;
      case irRemote.keyEq:
        Serial.println("EQ");
        break;
      case irRemote.keyStRept:
        Serial.println("ST/REPT");
        break;
      case irRemote.key1:
        Serial.println("1");
        setNumber(1);
        break;
      case irRemote.key2:
        Serial.println("2");
        setNumber(2);
        break;
      case irRemote.key3:
        Serial.println("3");
        setNumber(3);
        break;
      case irRemote.key4:
        Serial.println("4");
        setNumber(4);
        break;
      case irRemote.key5:
        Serial.println("5");
        setNumber(5);
        break;
      case irRemote.key6:
        Serial.println("6");
        setNumber(6);
        break;
      case irRemote.key7:
        Serial.println("7");
        setNumber(7);
        break;
      case irRemote.key8:
        Serial.println("8");
        setNumber(8);
        break;
      case irRemote.key9:
        Serial.println("9");
        setNumber(9);
        break;
      default:
        Serial.print(" - value: ");
        Serial.println(IrReceiver.decodedIRData.command);
    }

      IrReceiver.resume(); 
  }
}

void setNumber(int number)
{
  if(number < 0 || number > 9)
    number = 0;
    
  switch(number)
  {
    case 0:
      display0();
      currentNumber = 0;
      break;
    case 1:
      display1();
      currentNumber = 1;
      break;
    case 2:
      display2();
      currentNumber = 2;
      break;
    case 3:
      display3();
      currentNumber = 3;
      break;
    case 4:
      display4();
      currentNumber = 4;
      break;
    case 5:
      display5();
      currentNumber = 5;
      break;
    case 6:
      display6();
      currentNumber = 6;
      break;
    case 7:
      display7();
      currentNumber = 7;
      break;
    case 8:
      display8();
      currentNumber = 8;
      break;
    case 9:
      display9();
      currentNumber = 9;
      break;
  }
}

void increment()
{
  int increment = currentNumber + 1;
  if(increment > 9)
    increment = 0;
    
  setNumber(increment);
}

void decrement()
{
  int decrement = currentNumber - 1;
  if(decrement < 0)
    decrement = 9;
    
  setNumber(decrement);
}

// Loop though all symbols
void displayAll()
{
  int delayTime = 500;

  // Initiate
  displayOff();
  delay(delayTime);

  // Numbers
  setNumber(0);
  delay(delayTime);
  setNumber(1);
  delay(delayTime);
  setNumber(2);
  delay(delayTime);
  setNumber(3);
  delay(delayTime);
  setNumber(4);
  delay(delayTime);
  setNumber(5);
  delay(delayTime);
  setNumber(6);
  delay(delayTime);
  setNumber(7);
  delay(delayTime);
  setNumber(8);
  delay(delayTime);
  setNumber(9);
  delay(delayTime);

  // Symbols
  displayDotPoint();
  delay(delayTime);
  displayMinus();
  delay(delayTime);

  // Letters
  displayA();
  delay(delayTime);
  displayB();
  delay(delayTime);
  displayC();
  delay(delayTime);
  displayE();
  delay(delayTime);
  displayF();
  delay(delayTime);
  displayG();
  delay(delayTime);
  displayH();
  delay(delayTime);
  displayI();
  delay(delayTime);
  displayJ();
  delay(delayTime);
  displayL();
  delay(delayTime);
  displayO();
  delay(delayTime);
  displayP();
  delay(delayTime);
  displayS();
  delay(delayTime);
  displayU();
  delay(delayTime);

  // Reset
  setNumber(0);
  displayOff();
}

// Turn all segments off
void displayOff()
{
  digitalWrite(segementNorthAPin, LOW);
  digitalWrite(segementNorthBPin, LOW);
  digitalWrite(segementSouthCPin, LOW);
  digitalWrite(segementSouthDPin, LOW);
  digitalWrite(segementSouthEPin, LOW);
  digitalWrite(segementNorthFPin, LOW);
  digitalWrite(segementNorthGPin, LOW);
  digitalWrite(segementSouthDPPin, LOW);
}

// Turn all off, turn A, B, C, D, E, F on
void display0()
{
  digitalWrite(segementNorthGPin, LOW);
  digitalWrite(segementSouthDPPin, LOW);
  
  digitalWrite(segementNorthAPin, HIGH);
  digitalWrite(segementNorthBPin, HIGH);
  digitalWrite(segementSouthCPin, HIGH); 
  digitalWrite(segementSouthDPin, HIGH);
  digitalWrite(segementSouthEPin, HIGH);
  digitalWrite(segementNorthFPin, HIGH);
}

// Turn all off, turn B, C on
void display1()
{
  digitalWrite(segementNorthAPin, LOW);
  digitalWrite(segementSouthDPin, LOW);
  digitalWrite(segementSouthEPin, LOW);
  digitalWrite(segementNorthFPin, LOW);
  digitalWrite(segementNorthGPin, LOW);
  digitalWrite(segementSouthDPPin, LOW);
  
  digitalWrite(segementNorthBPin, HIGH);
  digitalWrite(segementSouthCPin, HIGH);
}

// Turn all off, turn A, B, D, E, G on
void display2()
{
  digitalWrite(segementSouthCPin, LOW);
  digitalWrite(segementNorthFPin, LOW);
  digitalWrite(segementSouthDPPin, LOW);
  
  digitalWrite(segementNorthAPin, HIGH);
  digitalWrite(segementNorthBPin, HIGH);
  digitalWrite(segementSouthDPin, HIGH);
  digitalWrite(segementSouthEPin, HIGH);
  digitalWrite(segementNorthGPin, HIGH);
}

// Turn all off, turn A, B, C, D, G on
void display3()
{
  digitalWrite(segementSouthEPin, LOW);
  digitalWrite(segementNorthFPin, LOW);
  digitalWrite(segementSouthDPPin, LOW);
  
  digitalWrite(segementNorthAPin, HIGH);
  digitalWrite(segementNorthBPin, HIGH);
  digitalWrite(segementSouthCPin, HIGH);
  digitalWrite(segementSouthDPin, HIGH);
  digitalWrite(segementNorthGPin, HIGH);
}

// Turn all off, turn B, C, F, G, on
void display4()
{
  digitalWrite(segementNorthAPin, LOW);
  digitalWrite(segementSouthDPin, LOW);
  digitalWrite(segementSouthEPin, LOW);
  digitalWrite(segementSouthDPPin, LOW);

  digitalWrite(segementNorthBPin, HIGH);
  digitalWrite(segementSouthCPin, HIGH); 
  digitalWrite(segementNorthFPin, HIGH);
  digitalWrite(segementNorthGPin, HIGH);
}

// Turn all off, turn A, C, D, F, G on
void display5()
{
  digitalWrite(segementNorthBPin, LOW);
  digitalWrite(segementSouthEPin, LOW);
  digitalWrite(segementSouthDPPin, LOW);

  digitalWrite(segementNorthAPin, HIGH);
  digitalWrite(segementSouthCPin, HIGH); 
  digitalWrite(segementSouthDPin, HIGH);
  digitalWrite(segementNorthFPin, HIGH);
  digitalWrite(segementNorthGPin, HIGH);
}

// Turn all off, turn A, C, D, E, F, G on
void display6()
{
  digitalWrite(segementNorthBPin, LOW);
  digitalWrite(segementSouthDPPin, LOW);

  digitalWrite(segementNorthAPin, HIGH);
  digitalWrite(segementSouthCPin, HIGH); 
  digitalWrite(segementSouthDPin, HIGH);
  digitalWrite(segementSouthEPin, HIGH);
  digitalWrite(segementNorthFPin, HIGH);
  digitalWrite(segementNorthGPin, HIGH);
}

// Turn all off, turn A, D, E on
void display7()
{
  digitalWrite(segementSouthDPin, LOW);
  digitalWrite(segementSouthEPin, LOW);
  digitalWrite(segementNorthFPin, LOW);
  digitalWrite(segementNorthGPin, LOW);
  digitalWrite(segementSouthDPPin, LOW);

  digitalWrite(segementNorthAPin, HIGH);
  digitalWrite(segementNorthBPin, HIGH);
  digitalWrite(segementSouthCPin, HIGH);
}

// Turn all off, turn A, B, C, D, E, F, G on
void display8()
{
  digitalWrite(segementSouthDPPin, LOW);
  
  digitalWrite(segementNorthAPin, HIGH);
  digitalWrite(segementNorthBPin, HIGH);
  digitalWrite(segementSouthCPin, HIGH);
  digitalWrite(segementSouthDPin, HIGH);
  digitalWrite(segementSouthEPin, HIGH);
  digitalWrite(segementNorthFPin, HIGH);
  digitalWrite(segementNorthGPin, HIGH);
}

// Turn all off, turn A, B, C, D, F, G on
void display9()
{
  digitalWrite(segementSouthEPin, LOW);
  digitalWrite(segementSouthDPPin, LOW);
  
  digitalWrite(segementNorthAPin, HIGH);
  digitalWrite(segementNorthBPin, HIGH);
  digitalWrite(segementSouthCPin, HIGH);
  digitalWrite(segementSouthDPin, HIGH);
  digitalWrite(segementNorthFPin, HIGH);
  digitalWrite(segementNorthGPin, HIGH);
}

// Turn all off, turn DP on
void displayDotPoint()
{
  digitalWrite(segementNorthAPin, LOW);
  digitalWrite(segementNorthBPin, LOW);
  digitalWrite(segementSouthCPin, LOW);
  digitalWrite(segementSouthDPin, LOW);
  digitalWrite(segementSouthEPin, LOW);
  digitalWrite(segementNorthFPin, LOW);
  digitalWrite(segementNorthGPin, LOW);
  
  digitalWrite(segementSouthDPPin, HIGH);
}

// Turn all off, turn G on
void displayMinus()
{
  digitalWrite(segementNorthAPin, LOW);
  digitalWrite(segementNorthBPin, LOW);
  digitalWrite(segementSouthCPin, LOW);
  digitalWrite(segementSouthDPin, LOW);
  digitalWrite(segementSouthEPin, LOW);
  digitalWrite(segementNorthFPin, LOW);
  digitalWrite(segementSouthDPPin, LOW);
  
  digitalWrite(segementNorthGPin, HIGH);
}

// Turn all off, turn A, B, C, E, F, G on
void displayA()
{
  digitalWrite(segementSouthDPPin, LOW);
  digitalWrite(segementSouthDPin, LOW);
  
  digitalWrite(segementNorthAPin, HIGH);
  digitalWrite(segementNorthBPin, HIGH);
  digitalWrite(segementSouthCPin, HIGH);
  digitalWrite(segementSouthEPin, HIGH);
  digitalWrite(segementNorthFPin, HIGH);
  digitalWrite(segementNorthGPin, HIGH);
}

// Turn all off, turn A, B, C, D, E, F, G on
void displayB()
{
  digitalWrite(segementSouthDPPin, LOW);
  
  digitalWrite(segementNorthAPin, HIGH);
  digitalWrite(segementNorthBPin, HIGH);
  digitalWrite(segementSouthCPin, HIGH);
  digitalWrite(segementSouthDPin, HIGH);
  digitalWrite(segementSouthEPin, HIGH);
  digitalWrite(segementNorthFPin, HIGH);
  digitalWrite(segementNorthGPin, HIGH);
}

// Turn all off, turn A, D, E, F on
void displayC()
{
  digitalWrite(segementNorthBPin, LOW);
  digitalWrite(segementSouthCPin, LOW);
  digitalWrite(segementNorthGPin, LOW);
  digitalWrite(segementSouthDPPin, LOW);

  digitalWrite(segementNorthAPin, HIGH);
  digitalWrite(segementSouthDPin, HIGH);
  digitalWrite(segementSouthEPin, HIGH);
  digitalWrite(segementNorthFPin, HIGH);
}

// Turn all off, turn A, D, E, F, G on
void displayE()
{
  digitalWrite(segementNorthBPin, LOW);
  digitalWrite(segementSouthCPin, LOW);
  digitalWrite(segementSouthDPPin, LOW);

  digitalWrite(segementNorthAPin, HIGH);
  digitalWrite(segementSouthDPin, HIGH);
  digitalWrite(segementSouthEPin, HIGH);
  digitalWrite(segementNorthFPin, HIGH);
  digitalWrite(segementNorthGPin, HIGH);
}

// Turn all off, turn A, E, F, G on
void displayF()
{
  digitalWrite(segementNorthBPin, LOW);
  digitalWrite(segementSouthCPin, LOW);
  digitalWrite(segementSouthDPin, LOW);
  digitalWrite(segementSouthDPPin, LOW);

  digitalWrite(segementNorthAPin, HIGH);
  digitalWrite(segementSouthEPin, HIGH);
  digitalWrite(segementNorthFPin, HIGH);
  digitalWrite(segementNorthGPin, HIGH);
}

// Turn all off, turn A, C, D, E, F, G on
void displayG()
{
  digitalWrite(segementNorthBPin, LOW);
  digitalWrite(segementSouthDPPin, LOW);

  digitalWrite(segementNorthAPin, HIGH);
  digitalWrite(segementSouthCPin, HIGH); 
  digitalWrite(segementSouthDPin, HIGH);
  digitalWrite(segementSouthEPin, HIGH);
  digitalWrite(segementNorthFPin, HIGH);
  digitalWrite(segementNorthGPin, HIGH);
}

// Turn all off, turn B, C, E, F, G on
void displayH()
{
  digitalWrite(segementNorthAPin, LOW);
  digitalWrite(segementSouthDPin, LOW);
  digitalWrite(segementSouthDPPin, LOW);
  
  digitalWrite(segementNorthBPin, HIGH);
  digitalWrite(segementSouthCPin, HIGH);
  digitalWrite(segementSouthEPin, HIGH);
  digitalWrite(segementNorthFPin, HIGH);
  digitalWrite(segementNorthGPin, HIGH);
}

// Turn all off, turn B, C on
void displayI()
{
  digitalWrite(segementNorthAPin, LOW);
  digitalWrite(segementSouthDPin, LOW);
  digitalWrite(segementSouthEPin, LOW);
  digitalWrite(segementNorthFPin, LOW);
  digitalWrite(segementNorthGPin, LOW);
  digitalWrite(segementSouthDPPin, LOW);
  
  digitalWrite(segementNorthBPin, HIGH);
  digitalWrite(segementSouthCPin, HIGH);
}

// Turn all off, turn B, C, D on
void displayJ()
{
  digitalWrite(segementNorthAPin, LOW);
  digitalWrite(segementSouthEPin, LOW);
  digitalWrite(segementNorthFPin, LOW);
  digitalWrite(segementNorthGPin, LOW);
  digitalWrite(segementSouthDPPin, LOW);
  
  digitalWrite(segementNorthBPin, HIGH);
  digitalWrite(segementSouthCPin, HIGH);
  digitalWrite(segementSouthDPin, HIGH);
}

// Turn all off, turn D, E, F on
void displayL()
{
  digitalWrite(segementNorthAPin, LOW);
  digitalWrite(segementNorthBPin, LOW);
  digitalWrite(segementSouthCPin, LOW);
  digitalWrite(segementNorthGPin, LOW);
  digitalWrite(segementSouthDPPin, LOW);
  
  digitalWrite(segementSouthDPin, HIGH);
  digitalWrite(segementSouthEPin, HIGH);
  digitalWrite(segementNorthFPin, HIGH);
}

// Turn all off, turn A, B, C, D, E, F on
void displayO()
{
  digitalWrite(segementNorthGPin, LOW);
  digitalWrite(segementSouthDPPin, LOW);
  
  digitalWrite(segementNorthAPin, HIGH);
  digitalWrite(segementNorthBPin, HIGH);
  digitalWrite(segementSouthCPin, HIGH); 
  digitalWrite(segementSouthDPin, HIGH);
  digitalWrite(segementSouthEPin, HIGH);
  digitalWrite(segementNorthFPin, HIGH);
}

// Turn all off, turn A, B, E, F, G on
void displayP()
{
  digitalWrite(segementSouthCPin, LOW);
  digitalWrite(segementSouthDPin, LOW);
  digitalWrite(segementSouthDPPin, LOW);
  
  digitalWrite(segementNorthAPin, HIGH);
  digitalWrite(segementNorthBPin, HIGH);
  digitalWrite(segementSouthEPin, HIGH);
  digitalWrite(segementNorthFPin, HIGH);
  digitalWrite(segementNorthGPin, HIGH);
}

// Turn all off, turn A, C, D, F, G on
void displayS()
{
  digitalWrite(segementNorthBPin, LOW);
  digitalWrite(segementSouthEPin, LOW);
  digitalWrite(segementSouthDPPin, LOW);

  digitalWrite(segementNorthAPin, HIGH);
  digitalWrite(segementSouthCPin, HIGH); 
  digitalWrite(segementSouthDPin, HIGH);
  digitalWrite(segementNorthFPin, HIGH);
  digitalWrite(segementNorthGPin, HIGH);
}

// Turn all off, turn B, C, D, E, F on
void displayU()
{
  digitalWrite(segementNorthAPin, LOW);
  digitalWrite(segementNorthGPin, LOW);
  digitalWrite(segementSouthDPPin, LOW);
  
  digitalWrite(segementNorthBPin, HIGH);
  digitalWrite(segementSouthCPin, HIGH);
  digitalWrite(segementSouthDPin, HIGH);
  digitalWrite(segementSouthEPin, HIGH);
  digitalWrite(segementNorthFPin, HIGH);
}
