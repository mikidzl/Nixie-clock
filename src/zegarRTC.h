#ifndef ZEGARRTC_H
#define ZEGARRTC_H

#include "Arduino.h"

#include <Wire.h>
#include <RtcDS3231.h>

// RtcDS3231<TwoWire> RTC(); // deklarcja zegara
// RtcDateTime dt;

class zegarRTC
{
private:
  unsigned long ogranicznik_zegara = 0;
  unsigned long interwal = 800000;

public:
  void zegar(int C[]);
  void ustawianieCzasu(int C[]);
  void temperaturaUstaw(int C[]);
  void budzik(int C[]);
  int godzina_Odtrucia;

  zegarRTC();
};

#endif