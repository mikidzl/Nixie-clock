#include "przyciski.h"

unsigned long opoznieniePrzycisk = 50000;
unsigned long dlugieWcisniecie = 200000;

void przycisk(bool &stan, const int przycisk, int &p, unsigned long &czasPrzycisk)
{
  if((digitalRead(przycisk) == LOW) || stan)
  {
    if(~stan && opoznieniePrzycisk <= (micros() - czasPrzycisk) )                       // włącza licznik czasu, zapewnia minimalny okres między kliknięciami przycisków oraz debouncing
    {
      czasPrzycisk = micros();
      stan = true;
    }
    else if((digitalRead(przycisk) == HIGH) && dlugieWcisniecie <=(micros() - czasPrzycisk))
    {
      p = 2;
      czasPrzycisk = micros();
      stan = false;
    }
    else if((digitalRead(przycisk) == HIGH) && opoznieniePrzycisk <=(micros() - czasPrzycisk))
    {
      p = 1;
      czasPrzycisk = micros();
      stan = false;
    }
  }
}