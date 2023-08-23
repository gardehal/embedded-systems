#ifndef SevenSegmentDisplay_h
#define SevenSegmentDisplay_h

#include "Arduino.h"

/**
 * @brief The SevenSegmentDisplay struct controls a 7-segment display.
 *
 * This struct provides methods for controlling the display to show digits,
 * letters, symbols, and more.
 */
struct SevenSegmentDisplay
{
    public:
        /**
        * @brief Constructor for the SevenSegmentDisplay struct.
        * @param NorthGPin The pin connected to the North segment G.
        * @param NorthFPin The pin connected to the North segment F.
        * @param NorthAPin The pin connected to the North segment A.
        * @param NorthBPin The pin connected to the North segment B.
        * @param SouthEPin The pin connected to the South segment E.
        * @param SouthDPin The pin connected to the South segment D.
        * @param SouthCPin The pin connected to the South segment C.
        * @param SouthDPPin The pin connected to the South segment DP.
        */
        SevenSegmentDisplay(int NorthGPin, int NorthFPin, int NorthAPin, int NorthBPin, int SouthEPin, int SouthDPin, int SouthCPin, int SouthDPPin);  
        void displayAll();                                // @brief Display everything that could be displayed with a delay (500ms)
        void displayOff();                                // @brief Turn all segments off
        void setNumber(int number);                       // @brief Display a number in 7 segments @param number Number that will be displayed on 7 segment (int)
        void increment();                                 // @brief Increment the current number on display by one
        void decrement();                                 // @brief Decrement the current number on display by one
        void display0();                                  // @brief Display 0 on 7 segments
        void display1();                                  // @brief Display 1 on 7 segments
        void display2();                                  // @brief Display 2 on 7 segments
        void display3();                                  // @brief Display 3 on 7 segments
        void display4();                                  // @brief Display 4 on 7 segments
        void display5();                                  // @brief Display 5 on 7 segments
        void display6();                                  // @brief Display 6 on 7 segments
        void display7();                                  // @brief Display 7 on 7 segments
        void display8();                                  // @brief Display 8 on 7 segments   
        void display9();                                  // @brief Display 9 on 7 segments
        void displayDotPoint();                           // @brief Clears the display and opens dot
        void displayMinus();                              // @brief Display minus (Straight line) on display
        void displayA();                                  // @brief Display letter 'A' on 7 segments
        void displayB();                                  // @brief Display letter 'B' on 7 segments
        void displayC();                                  // @brief Display letter 'C' on 7 segments
        void displayE();                                  // @brief Display letter 'E' on 7 segments 
        void displayF();                                  // @brief Display letter 'F' on 7 segments
        void displayG();                                  // @brief Display letter 'G' on 7 segments
        void displayH();                                  // @brief Display letter 'H' on 7 segments
        void displayI();                                  // @brief Display letter 'I' on 7 segments
        void displayJ();                                  // @brief Display letter 'J' on 7 segments
        void displayL();                                  // @brief Display letter 'L' on 7 segments
        void displayO();                                  // @brief Display letter 'O' on 7 segments
        void displayP();                                  // @brief Display letter 'P' on 7 segments
        void displayS();                                  // @brief Display letter 'S' on 7 segments
        void displayU();                                  // @brief Display letter 'U' on 7 segments
    private:
        int currentNumber;                                // Number that is being displayed on display

        //Pins
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
