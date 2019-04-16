#include "przyciski.h"

Przycisk::Przycisk(int pinPrzycisku)
{
  this->pin = pinPrzycisku;
  this->stan = wylaczony;
}

void Przycisk::sprawdzPrzycisk(Przycisk przycisk, unsigned long &czasPrzycisk)
{
  if((digitalRead(przycisk.pin) == LOW) || przycisk.stan != wylaczony)
    {
      if(przycisk.stan == wylaczony && przycisk.opoznieniePrzycisk <= (micros() - czasPrzycisk) )                       // włącza licznik czasu, zapewnia minimalny okres między kliknięciami przycisków oraz debouncing
      {
        czasPrzycisk = micros();
        przycisk.stan = wcisniety;
      }
      else if((digitalRead(przycisk.pin) == HIGH) && przycisk.graniczneWcisniecie <=(micros() - czasPrzycisk))
      {
        czasPrzycisk = micros();
        przycisk.stan = dlugieWcisniecie;
      }
      else if((digitalRead(przycisk.pin) == HIGH) && przycisk.graniczneWcisniecie <=(micros() - czasPrzycisk))
      {
        czasPrzycisk = micros();
        przycisk.stan = krotkieWcisniecie;
      }
    }
}
