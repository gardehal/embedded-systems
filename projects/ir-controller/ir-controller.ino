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

const int ledPin1 = 2;
const int ledPin2 = 3;
const int RECV_PIN = 4;
IRrecv irrecv(RECV_PIN);
decode_results results;

boolean led1On = false;
boolean led2On = false;

void setup()
{
  irrecv.enableIRIn();
  irrecv.blink13(true);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
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

      irrecv.resume(); 
  }
}

void comments()
{
  
    switch(results.value)
    {
      case key1: //Keypad button "5"
        if(led1On)
        {
          digitalWrite(ledPin1, LOW);
          led1On = false;
        }
        else
        {
          digitalWrite(ledPin1, HIGH);
          led1On = true;
        }
        break;
      case 0xFF18E7: //Keypad button "2"
        if(led2On)
        {
          digitalWrite(ledPin2, LOW);
          led2On = false;
        }
        else
        {
          digitalWrite(ledPin2, HIGH);
          led2On = true;
        }
        break;
    }
}
