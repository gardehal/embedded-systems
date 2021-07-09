
#ifndef SevenSegmentDisplay_h
#define SevenSegmentDisplay_h

#include "Arduino.h"

struct SevenSegmentDisplay
{
    public:
        SevenSegmentDisplay(int NorthGPin, int NorthFPin, int NorthAPin, int NorthBPin, int SouthEPin, int SouthDPin, int SouthCPin, int SouthDPPin);
        void displayAll();
        void displayOff();
        void setNumber(int number);
        void increment();
        void decrement();
        void display0();
        void display1();
        void display2();
        void display3();
        void display4();
        void display5();
        void display6();
        void display7();
        void display8();
        void display9();
        void displayDotPoint();
        void displayMinus();
        void displayA();
        void displayB();
        void displayC();
        void displayE();
        void displayF();
        void displayG();
        void displayH();
        void displayI();
        void displayJ();
        void displayL();
        void displayO();
        void displayP();
        void displayS();
        void displayU();
    private:
        int currentNumber;
        int _NorthGPin;
        int _NorthFPin;
        int _NorthAPin;
        int _NorthBPin;
        int _SouthEPin;
        int _SouthDPin;
        int _SouthCPin;
        int _SouthDPPin;
};

#endif