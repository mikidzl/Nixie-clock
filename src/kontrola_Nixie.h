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

  public:
    int latchPin;
    int clockPin;
    int dataPin;
    
    int jasnosc;
    int Nixie;
    int lampa;

    NIXIE();
    void wyswietlPWM(int C[]);
    void migajZegar(int C[]);

};

#endif