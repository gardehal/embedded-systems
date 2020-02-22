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

void setup()
{
  irrecv.enableIRIn();
  irrecv.blink13(true);
  Serial.begin(9600);
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
        break;
      case keyFunc:
        Serial.print("FUNC/STOP");
        break;
      case keyLeft:
        Serial.print("Left");
        break;
      case keyPlay:
        Serial.print("Play/Pause");
        break;
      case keyRight:
        Serial.print("Right");
        break;
      case keyDown:
        Serial.print("Down");
        break;
      case keyVolMinus:
        Serial.print("VOL-");
        break;
      case keyUp:
        Serial.print("Up");
        break;
      case key0:
        Serial.print("0");
        display0();
        break;
      case keyEq:
        Serial.print("EQ");
        break;
      case keySt:
        Serial.print("ST/REPT");
        break;
      case key1:
        Serial.print("1");
        display1();
        break;
      case key2:
        Serial.print("2");
        display2();
        break;
      case key3:
        Serial.print("3");
        display3();
        break;
      case key4:
        Serial.print("4");
        display4();
        break;
      case key5:
        Serial.print("5");
        display5();
        break;
      case key6:
        Serial.print("6");
        display6();
        break;
      case key7:
        Serial.print("7");
        display7();
        break;
      case key8:
        Serial.print("8");
        display8();
        break;
      case key9:
        Serial.print("9");
        display9();
        break;
      default:
        Serial.print(" - value: ");
        Serial.println(results.value);
    }

      irrecv.resume(); 
  }
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
