#ifndef przyciski_h
#define przyciski_h

#include "Arduino.h"

enum wartoscPrzycisku
{
    wylaczony,
    wcisniety,
    krotkieWcisniecie,
    dlugieWcisniecie
};

class Przycisk
{
  public:
    wartoscPrzycisku stan;
    int pin;
    Przycisk(int pinPrzycisku);
    void sprawdzPrzycisk(Przycisk przyscisk, unsigned long &czasPrzycisk);

  private:
    unsigned long opoznieniePrzycisk = 50000;
    unsigned long graniczneWcisniecie = 200000;
};

#endif