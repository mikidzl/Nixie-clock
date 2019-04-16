#ifndef ZEGARRTC_H
#define ZEGARRTC_H

#include "Arduino.h"

#include <Wire.h>
#include <RtcDS3231.h>

RtcDateTime dt;
RtcDS3231<TwoWire> clock(Wire); // deklarcja zegara

class zegarRTC
{
  private:
    unsigned int ogranicznik_zegara = 0;
    unsigned int interwal = 800000;

  public:
    zegarRTC(/* args */);
    void zegar(int C[]);
    void ustawianieCzasu(int C[]);
    void temperaturaUstaw(int C[]);
    int godzina_Odtrucia;
};

#endif