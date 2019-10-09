#include "zegarRTC.h"

zegarRTC::zegarRTC()
{
  //RTC.begin();
  //godzina_Odtrucia = RTC.getDateTime().hour %10;
  ogranicznik_zegara = 0;          //wartość początkowa, aby zegar od zadziałał od razu przy pierwszym włączeniu
  opcja_wlaczona = false;
  opcjaZmienCzas = Sekunda;
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

void zegarRTC::ustawianieCzasu(int C[], Przycisk przycisk1, Przycisk przycisk2, Przycisk przycisk3)
{

  zmienPara(przycisk2);

  zmienCzas(C, przycisk1, przycisk3);

  if (przycisk2.stan == dlugieWcisniecie)
  {
    dt = RTC.getDateTime();
    uint8_t godzina = C[0] * 10 + C[1];
    uint8_t minuta = C[2] * 10 + C[3];
    uint8_t sekunda = C[4] * 10 + C[5];

    RTC.setDateTime(dt.year, dt.month, dt.day, godzina, minuta, sekunda);
  }
}

void zegarRTC::zmienCzas(int C[], Przycisk przycisk1, Przycisk przycisk3) //pozwala na zmiane wskazywanego czasu podręczenego i jego kontrolę przy pomocy przycisków
{
  if (przycisk1.stan == krotkieWcisniecie || przycisk3.stan == krotkieWcisniecie)
  {
    if (przycisk1.stan == krotkieWcisniecie)
    {
      dodac = true;
    }
    else
    {
      dodac = false;
    }

    switch (opcjaZmienCzas)
    {
    case Sekunda:
      zmienSekunde(C, dodac);
      break;

    case Minuta:
      zmienMinute(C, dodac);
      break;

    case Godzina:
      zmienGodzine(C, dodac);
      break;

    default:
      break;
    }
    sprawdzOverflow(C);
  }
}

void zegarRTC::zmienPara(Przycisk przycisk2)
{
  if (przycisk2.stan == krotkieWcisniecie)
  {
    // switch (opcjaZmienCzas)
    // {
    // case Sekunda:
    //   opcjaZmienCzas = Minuta;
    //   break;

    // case Minuta:
    //   opcjaZmienCzas = Godzina;
    //   break;

    // case Godzina:
    //   opcjaZmienCzas = Sekunda;
    //   break;

    // default:
    //   break;
    // }

    opcjaZmienCzas = static_cast<CzasPara>(opcjaZmienCzas + 1);
    if (opcjaZmienCzas == ostatni_element)
    {
      opcjaZmienCzas = Sekunda;
    }
  }
}

void zegarRTC::sprawdzOverflow(int C[])
{
  for (int i = 5; i >= 1; i--) // przekroczenie górnego limitu cyfry
  {
    if ((C[i] == 6 && i % 2 == 0) || C[i] == 10)
    {
      C[i] = 0;
      C[i - 1]++;
    }

    if (C[i] == -1) //przekroczenie dolnego limitu cyfry
    {
      if (i % 2 == 0)
      {
        C[i] = 5;
        C[i - 1]--;
      }
      else
      {
        C[i] = 9;
        C[i - 1]--;
      }
    }
  }
  
  if (C[0] < 0)
  {
    C[0] = 2;
    C[1] = 3;
  }
  else if (C[1] == 4 && C[0] == 2)
  {
    for (int i = 0; i < 6; i++)
      C[i] = 0;
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
  if (micros() - ogranicznik_zegara >= interwal)
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

void zegarRTC::migajZegarem(int C[])
{
  if (micros() - ogranicznik_zegara > okres_migania)
    ;
  switch (opcjaZmienCzas)
  {
  case Sekunda:
    C[5] = 10;
    C[4] = 10;
    break;

  case Minuta:
    C[3] = 10;
    C[2] = 10;
    break;

  case Godzina:
    C[1] = 10;
    C[0] = 10;
    break;

  default:
    break;
  }
}

// void zegarRTC::budzik(int C[], wartoscPrzycisku)
// {
//   if (wartoscPrzycisku == wylaczony)
//   {
//   }
// }