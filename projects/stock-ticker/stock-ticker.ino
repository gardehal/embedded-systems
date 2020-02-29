#include <LiquidCrystal.h>

const int d4LcdPin = 2;
const int d5LcdPin = 3;
const int d6LcdPin = 4;
const int d7LcdPin = 5;
const int eLcdPin = 11;
const int rsLcdPin = 12;

LiquidCrystal lcd(rsLcdPin, eLcdPin, d7LcdPin, d6LcdPin, d5LcdPin, d4LcdPin);

void setup() 
{
  lcd.begin(16, 2);
}

void loop() 
{
  //lcd.setCursor(0, 1);

  String masterString = getTeslaStock();
  masterString.concat(" ");
  masterString.concat(getBitcoinValue());
  masterString.concat(" ");
  masterString.concat(getAlphabetStock());
  masterString.concat(" ");

  for(int i = 0; i < masterString.length(); i++)
  {
    String displaySegment = "";
    for(int j = i; j < i + 16; j++)
    {
      if(j >= masterString.length())
        displaySegment.concat(masterString[j - masterString.length()]);  
      else
        displaySegment.concat(masterString[j]);
        
      lcd.print(displaySegment);
    }

    lcd.clear();
    lcd.print(displaySegment);
    delay(500);
  }
}

float getPercentChange(float current, float previous)
{
  return ((current / previous) - 1) * 100;
}

String assembleString(String displayName, String currencySymbol, float currentValue, float previousValue)
{
  float percentChange = getPercentChange(currentValue, previousValue);
  String changeSymbol;
  if(percentChange == 0)
     changeSymbol = "=";
  if(percentChange > 0)
     changeSymbol = "^";
  if(percentChange < 0)
     changeSymbol = "v";
     
  String s = changeSymbol;
  s.concat(displayName);
  s.concat(" ");
  s.concat(currencySymbol);
  s.concat(currentValue);
  s.concat(" ");
  s.concat(percentChange);
  s.concat("%");
  return s;
}

String getTeslaStock()
{
  // No WIFI module, mock current stock value (29-02-2020)
  String displayName = "TSLA";
  String currencySymbol = "$";
  float previousValue = 645.72;
  float currentValue = 674.98;
  
  return assembleString(displayName, currencySymbol, currentValue, previousValue);
}

String getBitcoinValue()
{
  // No WIFI module, mock current stock value (29-02-2020)
  String displayName = "BTC";
  String currencySymbol = "$";
  float previousValue = 8624.81;
  float currentValue = 8547.03;
  
  return assembleString(displayName, currencySymbol, currentValue, previousValue);
}

String getAlphabetStock()
{
  // No WIFI module, mock current stock value (29-02-2020)
  String displayName = "GOOG";
  String currencySymbol = "$";
  float previousValue = 1339.33;
  float currentValue = 1301.11;
  
  return assembleString(displayName, currencySymbol, currentValue, previousValue);
}
