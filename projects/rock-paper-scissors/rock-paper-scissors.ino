#include <LiquidCrystal.h>
#include "PinChangeInt.h"

const int d4LcdPin = 5;
const int d5LcdPin = 6;
const int d6LcdPin = 7;
const int d7LcdPin = 8;
const int eLcdPin = 9;
const int rsLcdPin = 10;

const int rockPin = 2;
const int paperPin = 3;
const int scissorPin = 4;

const char *rps[] = {"Rock", "Paper", "Scissor"};
const String WELCOME = "Rock, Paper, Scissors! Please press a button... ";
const String SCORE = "Score";
const String BOT = "Bot";
const String USER = "User";
const String WON = "won!";
const String LOST = "lost!";
const String DRAW = "Game draw!";
const int msDelay = 2000;

int buttonState = 0; 
int botScore = 0;
int userScore = 0;
boolean botWon = false;
boolean interrupt = false;
int userPick = 0;

LiquidCrystal lcd(rsLcdPin, eLcdPin, d7LcdPin, d6LcdPin, d5LcdPin, d4LcdPin);

void setup() 
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  
  pinMode(rockPin, INPUT_PULLUP);
  pinMode(paperPin, INPUT_PULLUP);
  pinMode(scissorPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(rockPin), userPickRock, CHANGE);
  attachInterrupt(digitalPinToInterrupt(paperPin), userPickPaper, CHANGE);
  attachPinChangeInterrupt(scissorPin, userPickScissor, CHANGE);
}

void loop() 
{
  buttonState = digitalRead(rockPin);
  scrollMessage(0, WELCOME, msDelay);
  if(interrupt)
  {
    startGame(userPick);
    interrupt = false;
  }
}

void doInterrupt()
{
  interrupt = true;
}

void userPickRock()
{
  userPick = 0;
  doInterrupt();
}

void userPickPaper()
{
  userPick = 1;
  doInterrupt();
}

void userPickScissor()
{
  userPick = 2;
  doInterrupt();
}

int botPickRandom()
{
  return random(0, sizeof(rps) / sizeof(rps[0]));
}

int startGame(int userPick)
{
  int botPick = botPickRandom();
  
  String botPickString = BOT;
  botPickString.concat(": ");
  botPickString.concat(rps[botPick]);
  String userPickString = USER;
  userPickString.concat(": ");
  userPickString.concat(rps[userPick]);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(botPickString);
  lcd.setCursor(0, 1);
  lcd.print(userPickString);

  delay(msDelay);
  
  calculateWinner(userPick, botPick);
}

void calculateWinner(int userPick, int botPick)
{
  if(userPick == botPick) // Draw
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(DRAW);
  }
  else
  {
    if((userPick == 0 && botPick == 1) // U: Rock, B: Paper
       || (userPick == 1 && botPick == 2) // U: Papere, B: Scissor
       || (userPick == 2 && botPick == 0)) // U: Scissor, B: Rock
    {
      botWon = true;
      botScore++;
    }
    else
    {
      botWon = false;
      userScore++;
    }

    if(userScore > 9)
    {
      userScore = 0;
      botScore = 0;
      
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("User won");
      lcd.setCursor(4 , 1);
      lcd.print("the game!");
      delay(msDelay * 2);
      return;
    }
    else if(botScore > 9)
    {
      userScore = 0;
      botScore = 0;
      
      lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("Bot won");
      lcd.setCursor(4 , 1);
      lcd.print("the game!");
      delay(msDelay * 2);
      return;
    }

    String botResult = LOST;
    if(botWon)
      botResult = WON;
    String userResult = WON;
    if(botWon)
      userResult = LOST;
    
    String botResultString = BOT;
    botResultString.concat(" ");
    botResultString.concat(botResult);
    String userResultString = USER;
    userResultString.concat(" ");
    userResultString.concat(userResult);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(botResultString);
    lcd.setCursor(15, 0);
    lcd.print(botScore);
    lcd.setCursor(0, 1);
    lcd.print(userResultString);
    lcd.setCursor(15, 1);
    lcd.print(userScore);
    
    delay(msDelay);
  }
}

void scrollMessage(int line, String message, int msDelay)
{
  for(int i = 0; i < message.length(); i++)
  {
    if(interrupt)
      return;
    
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
    delay(msDelay / 2);
  }
}
