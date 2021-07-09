
#ifndef ElegooIrRemote_h
#define ElegooIrRemote_h

#include "Arduino.h"

struct ElegooIrRemote
{
  ElegooIrRemote();
  static const int keyPower = 69;
  static const int keyVolumePlus = 70;
  static const int keyFuncStop = 71;
  static const int keyBack = 68;
  static const int keyPlayPause = 64;
  static const int keyForward = 67;
  static const int keyDown = 7;
  static const int keyVolumeMinus = 21;
  static const int keyUp = 9;
  static const int key0 = 22;
  static const int keyEq = 25;
  static const int keyStRept = 13;
  static const int key1 = 12;
  static const int key2 = 24;
  static const int key3 = 94;
  static const int key4 = 8;
  static const int key5 = 28;
  static const int key6 = 90;
  static const int key7 = 66;
  static const int key8 = 82;
  static const int key9 = 74;
};

extern ElegooIrRemote elegooIrRemote;

#endif