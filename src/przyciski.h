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
  void sprawdzPrzycisk(unsigned long &czasPrzycisk);

private:
  unsigned long opoznieniePrzycisk = 30000;
  unsigned long graniczneWcisniecie = 500000;
  void zerujPrzycisk();
};

#endif