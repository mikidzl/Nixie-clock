#include "zegarRTC.h"

zegarRTC::zegarRTC()
{
  //RTC.begin();
  //godzina_Odtrucia = RTC.getDateTime().hour %10;
  opcja_wlaczona = false;
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
  dt = RTC.getDateTime();
  uint8_t godzina = C[0] * 10 + C[1];
  uint8_t minuta = C[2] * 10 + C[3];
  uint8_t sekunda = C[4] * 10 + C[5];

  RTC.setDateTime(dt.year, dt.month, dt.day, godzina, minuta, sekunda);
}

void zegarRTC::sprawdzOverflow(int C[])
{
  for (int i = 5; i >= 1; i--)
  {
    if (C[i] == 6 && i % 2 == 0)
    {
      C[i] = 0;
      C[i - 1]++;
    }
    else if (C[i] == 10)
    {
      C[i] = 0;
      C[i - 1]++;
    }
    else if (C[1] == 4 && C[0] == 2)
    {
      for (int i = 0; i < 6; i++)
        C[i] = 0;
    }
  }
  for (int i = 4; i >= 0; i--)
  {
    if (C[i] == -1 && i % 2 == 0)
    {
      C[i] == 0;
      C[i - 1]--;
    }
    else if (C[i] == -1)
    {
      C[i] = 0;
      C[i - 1]++;
    }
    else if (C[1] == 4 && C[0] == 2)
    {
      for (int i = 0; i < 6; i++)
        C[i] == 0;
    }
  }
}
void zegarRTC::zmienSekunde(int C[], bool dodac)
{
  if (dodac)
  {
    C[5]++;
  }
  else
  {
    C[5]--;
  }
}

void zegarRTC::zmienMinute(int C[], bool dodac)
{
  if (dodac)
  {
    C[3]++;
  }
  else
  {
    C[3]--;
  }
}

void zegarRTC::zmienGodzine(int C[], bool dodac)
{
  if (dodac)
  {
    C[1]++;
  }
  else
  {
    C[1]--;
  }
}

void zegarRTC::temperaturaUstaw(int C[])
{
  if (micros() - ogranicznik_zegara >= interwal())
  {
    RTC.forceConversion();
    int temperatura = int(100 * RTC.readTemperature());

    C[0] = 0;
    C[1] = 0;
    C[2] = temperatura / 1000;
    C[3] = (temperatura / 100) % 10;
    C[4] = (temperatura / 10) % 10;
    C[5] = temperatura % 10;
  }
}

// void zegarRTC::budzik(int C[], wartoscPrzycisku)
// {
//   if (wartoscPrzycisku == wylaczony)
//   {
//   }
// }