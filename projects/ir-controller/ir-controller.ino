#include <IRremote.h>

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

const int irRecPin = 2;
const int segementNorthGPin = 3;
const int segementNorthFPin = 4;
const int segementNorthAPin = 5;
const int segementNorthBPin = 6;
const int segementSouthEPin = 7;
const int segementSouthDPin = 8;
const int segementSouthCPin = 9;
const int segementSouthDPPin = 10;

IRrecv irrecv(irRecPin);
decode_results results;

int currentNumber = 0;

void setup()
{
  irrecv.enableIRIn();
  irrecv.blink13(true);
  Serial.begin(9600);

  display0();
}

void loop()
{
    
  if(irrecv.decode(&results))
  {
    switch(results.value)
    {
      case keyPower:
        Serial.print("Power");
        displayOff();
        break;
      case keyVolPluss:
        Serial.print("VOL+");
        displayDotPoint();
        break;
      case keyFunc:
        Serial.print("FUNC/STOP");
        break;
      case keyLeft:
        Serial.print("Left");
        break;
      case keyPlay:
        Serial.print("Play/Pause");
        displayAll();
        break;
      case keyRight:
        Serial.print("Right");
        break;
      case keyDown:
        Serial.print("Down");
        decrement();
        break;
      case keyVolMinus:
        Serial.print("VOL-");
        displayMinus();
        break;
      case keyUp:
        Serial.print("Up");
        increment();
        break;
      case key0:
        Serial.print("0");
        setNumber(0);
        break;
      case keyEq:
        Serial.print("EQ");
        break;
      case keySt:
        Serial.print("ST/REPT");
        break;
      case key1:
        Serial.print("1");
        setNumber(1);
        break;
      case key2:
        Serial.print("2");
        setNumber(2);
        break;
      case key3:
        Serial.print("3");
        setNumber(3);
        break;
      case key4:
        Serial.print("4");
        setNumber(4);
        break;
      case key5:
        Serial.print("5");
        setNumber(5);
        break;
      case key6:
        Serial.print("6");
        setNumber(6);
        break;
      case key7:
        Serial.print("7");
        setNumber(7);
        break;
      case key8:
        Serial.print("8");
        setNumber(8);
        break;
      case key9:
        Serial.print("9");
        setNumber(9);
        break;
      default:
        Serial.print(" - value: ");
        Serial.println(results.value);
    }

      irrecv.resume(); 
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
