#include <LiquidCrystal.h>

const int d4LcdPin = 2;
const int d5LcdPin = 3;
const int d6LcdPin = 4;
const int d7LcdPin = 5;
const int eLcdPin = 11;
const int rsLcdPin = 12;

const int rockPin = 12;
const int paperPin = 12;
const int scissorPin = 12;

const char *rps[] = {"Rock", "Paper", "Scissor"};
const String WELCOME = "Rock, Paper, Scissors! Please press a button... ";
const String SCORE = "Score";
const String BOT = "Bot";
const String USER = "User";
const String WON = "won!";
const String LOST = "lost!";
const int msDelay = 500;

int botScore = 0;
int userScore = 0;

LiquidCrystal lcd(rsLcdPin, eLcdPin, d7LcdPin, d6LcdPin, d5LcdPin, d4LcdPin);

void setup() 
{
  lcd.begin(16, 2);
}

void loop() 
{
  //TODO buttons, code, diagram, video
  
  // write some stuff to lcd
  // wait for user input
  // pick random index of rps
  // compare user pick and bot pick
  // update score on the right
  
  // ex.:
  // Rock, Paper, Scissors! Please press a button... // scroll
  // Score B: 0, U: 0
  // .. 
  // Bot: Rock      0
  // User: Scissor  0
  // ...
  // Bot won!       1
  // User lost!     0
  // ...
  // Rock, Paper, Scissors! Please press a button... // scroll
  // Score B: 1, U: 0

  scrollMessage(0, WELCOME, msDelay);
}

int botPickRandom()
{
  return random(0, sizeof(rps) - 1);
}

void scrollMessage(int line, String message, int msDelay)
{
  for(int i = 0; i < message.length(); i++)
  {
    String displaySegment = "";
    for(int j = i; j < i + 16; j++)
    {
      if(j >= message.length())
        displaySegment.concat(message[j - message.length()]);  
      else
        displaySegment.concat(message[j]);
    }

    lcd.clear();
    
    lcd.setCursor(0, 1);
    String s = SCORE;
    s.concat(" ");
    s.concat("B: ");
    s.concat(botScore);
    s.concat(", U: ");
    s.concat(userScore);
    lcd.print(s);
  
    lcd.setCursor(0, 0);
    lcd.print(displaySegment);
    delay(msDelay);
  }
}
