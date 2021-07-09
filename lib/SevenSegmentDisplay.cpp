#include "Arduino.h"
#include "SevenSegmentDisplay.h"

SevenSegmentDisplay::SevenSegmentDisplay(int NorthGPin, int NorthFPin, int NorthAPin, int NorthBPin, int SouthEPin, int SouthDPin, int SouthCPin, int SouthDPPin)
{
  currentNumber = 0;
  // All output
  _NorthGPin = NorthGPin;
  _NorthFPin = NorthFPin;
  _NorthAPin = NorthAPin;
  _NorthBPin = NorthBPin;
  _SouthEPin = SouthEPin;
  _SouthDPin = SouthDPin;
  _SouthCPin = SouthCPin;
  _SouthDPPin = SouthDPPin;
}

// Loop though all symbols
void SevenSegmentDisplay::displayAll()
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
void SevenSegmentDisplay::displayOff()
{
  digitalWrite(_NorthAPin, LOW);
  digitalWrite(_NorthBPin, LOW);
  digitalWrite(_SouthCPin, LOW);
  digitalWrite(_SouthDPin, LOW);
  digitalWrite(_SouthEPin, LOW);
  digitalWrite(_NorthFPin, LOW);
  digitalWrite(_NorthGPin, LOW);
  digitalWrite(_SouthDPPin, LOW);
}

void SevenSegmentDisplay::setNumber(int number)
{
  if(number < 0 || number > 9)
    number = 0;
    
  switch(number)
  {
    case 0:
      SevenSegmentDisplay::display0();
      currentNumber = 0;
      break;
    case 1:
      SevenSegmentDisplay::display1();
      currentNumber = 1;
      break;
    case 2:
      SevenSegmentDisplay::display2();
      currentNumber = 2;
      break;
    case 3:
      SevenSegmentDisplay::display3();
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

void SevenSegmentDisplay::increment()
{
  int increment = currentNumber + 1;
  if(increment > 9)
    increment = 0;
    
  setNumber(increment);
}

void SevenSegmentDisplay::decrement()
{
  int decrement = currentNumber - 1;
  if(decrement < 0)
    decrement = 9;
    
  setNumber(decrement);
}

// Turn all off, turn A, B, C, D, E, F on
void SevenSegmentDisplay::display0()
{
  digitalWrite(_NorthGPin, LOW);
  digitalWrite(_SouthDPPin, LOW);
  
  digitalWrite(_NorthAPin, HIGH);
  digitalWrite(_NorthBPin, HIGH);
  digitalWrite(_SouthCPin, HIGH); 
  digitalWrite(_SouthDPin, HIGH);
  digitalWrite(_SouthEPin, HIGH);
  digitalWrite(_NorthFPin, HIGH);
}

// Turn all off, turn B, C on
void SevenSegmentDisplay::display1()
{
  digitalWrite(_NorthAPin, LOW);
  digitalWrite(_SouthDPin, LOW);
  digitalWrite(_SouthEPin, LOW);
  digitalWrite(_NorthFPin, LOW);
  digitalWrite(_NorthGPin, LOW);
  digitalWrite(_SouthDPPin, LOW);
  
  digitalWrite(_NorthBPin, HIGH);
  digitalWrite(_SouthCPin, HIGH);
}

// Turn all off, turn A, B, D, E, G on
void SevenSegmentDisplay::display2()
{
  digitalWrite(_SouthCPin, LOW);
  digitalWrite(_NorthFPin, LOW);
  digitalWrite(_SouthDPPin, LOW);
  
  digitalWrite(_NorthAPin, HIGH);
  digitalWrite(_NorthBPin, HIGH);
  digitalWrite(_SouthDPin, HIGH);
  digitalWrite(_SouthEPin, HIGH);
  digitalWrite(_NorthGPin, HIGH);
}

// Turn all off, turn A, B, C, D, G on
void SevenSegmentDisplay::display3()
{
  digitalWrite(_SouthEPin, LOW);
  digitalWrite(_NorthFPin, LOW);
  digitalWrite(_SouthDPPin, LOW);
  
  digitalWrite(_NorthAPin, HIGH);
  digitalWrite(_NorthBPin, HIGH);
  digitalWrite(_SouthCPin, HIGH);
  digitalWrite(_SouthDPin, HIGH);
  digitalWrite(_NorthGPin, HIGH);
}

// Turn all off, turn B, C, F, G, on
void SevenSegmentDisplay::display4()
{
  digitalWrite(_NorthAPin, LOW);
  digitalWrite(_SouthDPin, LOW);
  digitalWrite(_SouthEPin, LOW);
  digitalWrite(_SouthDPPin, LOW);

  digitalWrite(_NorthBPin, HIGH);
  digitalWrite(_SouthCPin, HIGH); 
  digitalWrite(_NorthFPin, HIGH);
  digitalWrite(_NorthGPin, HIGH);
}

// Turn all off, turn A, C, D, F, G on
void SevenSegmentDisplay::display5()
{
  digitalWrite(_NorthBPin, LOW);
  digitalWrite(_SouthEPin, LOW);
  digitalWrite(_SouthDPPin, LOW);

  digitalWrite(_NorthAPin, HIGH);
  digitalWrite(_SouthCPin, HIGH); 
  digitalWrite(_SouthDPin, HIGH);
  digitalWrite(_NorthFPin, HIGH);
  digitalWrite(_NorthGPin, HIGH);
}

// Turn all off, turn A, C, D, E, F, G on
void SevenSegmentDisplay::display6()
{
  digitalWrite(_NorthBPin, LOW);
  digitalWrite(_SouthDPPin, LOW);

  digitalWrite(_NorthAPin, HIGH);
  digitalWrite(_SouthCPin, HIGH); 
  digitalWrite(_SouthDPin, HIGH);
  digitalWrite(_SouthEPin, HIGH);
  digitalWrite(_NorthFPin, HIGH);
  digitalWrite(_NorthGPin, HIGH);
}

// Turn all off, turn A, D, E on
void SevenSegmentDisplay::display7()
{
  digitalWrite(_SouthDPin, LOW);
  digitalWrite(_SouthEPin, LOW);
  digitalWrite(_NorthFPin, LOW);
  digitalWrite(_NorthGPin, LOW);
  digitalWrite(_SouthDPPin, LOW);

  digitalWrite(_NorthAPin, HIGH);
  digitalWrite(_NorthBPin, HIGH);
  digitalWrite(_SouthCPin, HIGH);
}

// Turn all off, turn A, B, C, D, E, F, G on
void SevenSegmentDisplay::display8()
{
  digitalWrite(_SouthDPPin, LOW);
  
  digitalWrite(_NorthAPin, HIGH);
  digitalWrite(_NorthBPin, HIGH);
  digitalWrite(_SouthCPin, HIGH);
  digitalWrite(_SouthDPin, HIGH);
  digitalWrite(_SouthEPin, HIGH);
  digitalWrite(_NorthFPin, HIGH);
  digitalWrite(_NorthGPin, HIGH);
}

// Turn all off, turn A, B, C, D, F, G on
void SevenSegmentDisplay::display9()
{
  digitalWrite(_SouthEPin, LOW);
  digitalWrite(_SouthDPPin, LOW);
  
  digitalWrite(_NorthAPin, HIGH);
  digitalWrite(_NorthBPin, HIGH);
  digitalWrite(_SouthCPin, HIGH);
  digitalWrite(_SouthDPin, HIGH);
  digitalWrite(_NorthFPin, HIGH);
  digitalWrite(_NorthGPin, HIGH);
}

// Turn all off, turn DP on
void SevenSegmentDisplay::displayDotPoint()
{
  digitalWrite(_NorthAPin, LOW);
  digitalWrite(_NorthBPin, LOW);
  digitalWrite(_SouthCPin, LOW);
  digitalWrite(_SouthDPin, LOW);
  digitalWrite(_SouthEPin, LOW);
  digitalWrite(_NorthFPin, LOW);
  digitalWrite(_NorthGPin, LOW);
  
  digitalWrite(_SouthDPPin, HIGH);
}

// Turn all off, turn G on
void SevenSegmentDisplay::displayMinus()
{
  digitalWrite(_NorthAPin, LOW);
  digitalWrite(_NorthBPin, LOW);
  digitalWrite(_SouthCPin, LOW);
  digitalWrite(_SouthDPin, LOW);
  digitalWrite(_SouthEPin, LOW);
  digitalWrite(_NorthFPin, LOW);
  digitalWrite(_SouthDPPin, LOW);
  
  digitalWrite(_NorthGPin, HIGH);
}

// Turn all off, turn A, B, C, E, F, G on
void SevenSegmentDisplay::displayA()
{
  digitalWrite(_SouthDPPin, LOW);
  digitalWrite(_SouthDPin, LOW);
  
  digitalWrite(_NorthAPin, HIGH);
  digitalWrite(_NorthBPin, HIGH);
  digitalWrite(_SouthCPin, HIGH);
  digitalWrite(_SouthEPin, HIGH);
  digitalWrite(_NorthFPin, HIGH);
  digitalWrite(_NorthGPin, HIGH);
}

// Turn all off, turn A, B, C, D, E, F, G on
void SevenSegmentDisplay::displayB()
{
  digitalWrite(_SouthDPPin, LOW);
  
  digitalWrite(_NorthAPin, HIGH);
  digitalWrite(_NorthBPin, HIGH);
  digitalWrite(_SouthCPin, HIGH);
  digitalWrite(_SouthDPin, HIGH);
  digitalWrite(_SouthEPin, HIGH);
  digitalWrite(_NorthFPin, HIGH);
  digitalWrite(_NorthGPin, HIGH);
}

// Turn all off, turn A, D, E, F on
void SevenSegmentDisplay::displayC()
{
  digitalWrite(_NorthBPin, LOW);
  digitalWrite(_SouthCPin, LOW);
  digitalWrite(_NorthGPin, LOW);
  digitalWrite(_SouthDPPin, LOW);

  digitalWrite(_NorthAPin, HIGH);
  digitalWrite(_SouthDPin, HIGH);
  digitalWrite(_SouthEPin, HIGH);
  digitalWrite(_NorthFPin, HIGH);
}

// Turn all off, turn A, D, E, F, G on
void SevenSegmentDisplay::displayE()
{
  digitalWrite(_NorthBPin, LOW);
  digitalWrite(_SouthCPin, LOW);
  digitalWrite(_SouthDPPin, LOW);

  digitalWrite(_NorthAPin, HIGH);
  digitalWrite(_SouthDPin, HIGH);
  digitalWrite(_SouthEPin, HIGH);
  digitalWrite(_NorthFPin, HIGH);
  digitalWrite(_NorthGPin, HIGH);
}

// Turn all off, turn A, E, F, G on
void SevenSegmentDisplay::displayF()
{
  digitalWrite(_NorthBPin, LOW);
  digitalWrite(_SouthCPin, LOW);
  digitalWrite(_SouthDPin, LOW);
  digitalWrite(_SouthDPPin, LOW);

  digitalWrite(_NorthAPin, HIGH);
  digitalWrite(_SouthEPin, HIGH);
  digitalWrite(_NorthFPin, HIGH);
  digitalWrite(_NorthGPin, HIGH);
}

// Turn all off, turn A, C, D, E, F, G on
void SevenSegmentDisplay::displayG()
{
  digitalWrite(_NorthBPin, LOW);
  digitalWrite(_SouthDPPin, LOW);

  digitalWrite(_NorthAPin, HIGH);
  digitalWrite(_SouthCPin, HIGH); 
  digitalWrite(_SouthDPin, HIGH);
  digitalWrite(_SouthEPin, HIGH);
  digitalWrite(_NorthFPin, HIGH);
  digitalWrite(_NorthGPin, HIGH);
}

// Turn all off, turn B, C, E, F, G on
void SevenSegmentDisplay::displayH()
{
  digitalWrite(_NorthAPin, LOW);
  digitalWrite(_SouthDPin, LOW);
  digitalWrite(_SouthDPPin, LOW);
  
  digitalWrite(_NorthBPin, HIGH);
  digitalWrite(_SouthCPin, HIGH);
  digitalWrite(_SouthEPin, HIGH);
  digitalWrite(_NorthFPin, HIGH);
  digitalWrite(_NorthGPin, HIGH);
}

// Turn all off, turn B, C on
void SevenSegmentDisplay::displayI()
{
  digitalWrite(_NorthAPin, LOW);
  digitalWrite(_SouthDPin, LOW);
  digitalWrite(_SouthEPin, LOW);
  digitalWrite(_NorthFPin, LOW);
  digitalWrite(_NorthGPin, LOW);
  digitalWrite(_SouthDPPin, LOW);
  
  digitalWrite(_NorthBPin, HIGH);
  digitalWrite(_SouthCPin, HIGH);
}

// Turn all off, turn B, C, D on
void SevenSegmentDisplay::displayJ()
{
  digitalWrite(_NorthAPin, LOW);
  digitalWrite(_SouthEPin, LOW);
  digitalWrite(_NorthFPin, LOW);
  digitalWrite(_NorthGPin, LOW);
  digitalWrite(_SouthDPPin, LOW);
  
  digitalWrite(_NorthBPin, HIGH);
  digitalWrite(_SouthCPin, HIGH);
  digitalWrite(_SouthDPin, HIGH);
}

// Turn all off, turn D, E, F on
void SevenSegmentDisplay::displayL()
{
  digitalWrite(_NorthAPin, LOW);
  digitalWrite(_NorthBPin, LOW);
  digitalWrite(_SouthCPin, LOW);
  digitalWrite(_NorthGPin, LOW);
  digitalWrite(_SouthDPPin, LOW);
  
  digitalWrite(_SouthDPin, HIGH);
  digitalWrite(_SouthEPin, HIGH);
  digitalWrite(_NorthFPin, HIGH);
}

// Turn all off, turn A, B, C, D, E, F on
void SevenSegmentDisplay::displayO()
{
  digitalWrite(_NorthGPin, LOW);
  digitalWrite(_SouthDPPin, LOW);
  
  digitalWrite(_NorthAPin, HIGH);
  digitalWrite(_NorthBPin, HIGH);
  digitalWrite(_SouthCPin, HIGH); 
  digitalWrite(_SouthDPin, HIGH);
  digitalWrite(_SouthEPin, HIGH);
  digitalWrite(_NorthFPin, HIGH);
}

// Turn all off, turn A, B, E, F, G on
void SevenSegmentDisplay::displayP()
{
  digitalWrite(_SouthCPin, LOW);
  digitalWrite(_SouthDPin, LOW);
  digitalWrite(_SouthDPPin, LOW);
  
  digitalWrite(_NorthAPin, HIGH);
  digitalWrite(_NorthBPin, HIGH);
  digitalWrite(_SouthEPin, HIGH);
  digitalWrite(_NorthFPin, HIGH);
  digitalWrite(_NorthGPin, HIGH);
}

// Turn all off, turn A, C, D, F, G on
void SevenSegmentDisplay::displayS()
{
  digitalWrite(_NorthBPin, LOW);
  digitalWrite(_SouthEPin, LOW);
  digitalWrite(_SouthDPPin, LOW);

  digitalWrite(_NorthAPin, HIGH);
  digitalWrite(_SouthCPin, HIGH); 
  digitalWrite(_SouthDPin, HIGH);
  digitalWrite(_NorthFPin, HIGH);
  digitalWrite(_NorthGPin, HIGH);
}

// Turn all off, turn B, C, D, E, F on
void SevenSegmentDisplay::displayU()
{
  digitalWrite(_NorthAPin, LOW);
  digitalWrite(_NorthGPin, LOW);
  digitalWrite(_SouthDPPin, LOW);
  
  digitalWrite(_NorthBPin, HIGH);
  digitalWrite(_SouthCPin, HIGH);
  digitalWrite(_SouthDPin, HIGH);
  digitalWrite(_SouthEPin, HIGH);
  digitalWrite(_NorthFPin, HIGH);
}