#include "zegarRTC.h"

zegarRTC::zegarRTC()
{
  RTC.begin();
  godzina_Odtrucia = RTC.getDateTime().hour %10;
}

void zegarRTC::zegar(int C[]) //pobiera czas z modułu RTC oraz rozbija na cyfry
{
  if (micros() - ogranicznik_zegara >= interwal)
  {
    dt = RTC.getDateTime();

    C[5] = dt.second % 10;
    C[4] = dt.second / 10;

    C[3] = dt.minute % 10;
    C[2] = dt.minute / 10;

    C[1] = dt.hour % 10;
    C[0] = dt.hour / 10;

    ogranicznik_zegara = micros();
  }
}

void zegarRTC::ustawianieCzasu(int C[])
{
}

void zegarRTC::temperaturaUstaw(int C[])
{
  int temperatura = int(100);

  C[0] = 10;
  C[1] = 10;
  C[2] = temperatura / 1000;
  C[3] = (temperatura / 100) % 10;
  C[4] = (temperatura / 10) % 10;
  C[5] = temperatura % 10;
}

// void zegarRTC::budzik(int C[], wartoscPrzycisku)
// {
//   if(wartoscPrzycisku == wylaczony)
//   {
    
//   }
// }