#ifndef kontrola_Nixie_H
#define kontrola_Nixie_H

#include "Arduino.h"

class NIXIE
{
  private:
    unsigned long licznik_czasu;
    unsigned long okres;
    int licznik_jasnosci;
    void wlaczLampe(int C[]);
    void wylaczLampe();
    void nixieNapisz(uint8_t value);

    bool lamp_status;

    int A = 5;
    int B = 6;
    int C = 7;
    int D = 8;

  public:
    int latchPin;
    int clockPin;
    int dataPin;
    int brightnessPin = A1;
    
    int jasnosc;
    int Nixie;
    int lampa;

    NIXIE();
    void wyswietlPWM(int C[]);
    void migajZegar(int C[]);

};

#endif