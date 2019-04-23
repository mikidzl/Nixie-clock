#include "przyciski.h"

Przycisk::Przycisk(int pinPrzycisku)
{
  pin = pinPrzycisku;
  stan = wylaczony;
}

void Przycisk::zerujPrzycisk()
{
  stan = wylaczony;
}

void Przycisk::sprawdzPrzycisk(unsigned long &czasPrzycisk)
{
  if ((digitalRead(pin) == LOW) || stan != wylaczony)
  {
    if (stan == wylaczony && opoznieniePrzycisk <= (micros() - czasPrzycisk)) // włącza licznik czasu, zapewnia minimalny okres między kliknięciami przycisków oraz debouncing
    {
      czasPrzycisk = micros();
      stan = wcisniety;
    }
    else if ((digitalRead(pin) == HIGH) && graniczneWcisniecie <= (micros() - czasPrzycisk) && stan == wcisniety)
    {
      czasPrzycisk = micros();
      stan = dlugieWcisniecie;
    }
    else if ((digitalRead(pin) == HIGH) && stan == wcisniety)
    {
      czasPrzycisk = micros();
      stan = krotkieWcisniecie;
    }
    else if (stan == krotkieWcisniecie || stan == dlugieWcisniecie)
      stan = wylaczony;
  }
}
