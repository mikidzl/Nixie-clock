#include "zegarRTC.h"

zegarRTC::zegarRTC()
{
  // RTC.begin();
  // while (!RTC.isReady());
  
  //First_Odtrucia = RTC.getDateTime().hour %10;
  ogranicznik_zegara = interwal;          //wartość początkowa, aby zegar od zadziałał od razu przy pierwszym włączeniu
  opcja_wlaczona = false;
  pairPointer = Third;
  show_result = false;
}

void zegarRTC::clock(int C[]) //pobiera czas z modułu RTC oraz rozbija na cyfry
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

void zegarRTC::date(int C[]) //pobiera czas z modułu RTC oraz rozbija na cyfry
{
  if (micros() - ogranicznik_zegara >= interwal)
  {
    dt = RTC.getDateTime();

    C[5] = (dt.year - 2000) % 10;
    C[4] = (dt.year - 2000) / 10;

    C[3] = dt.month % 10;
    C[2] = dt.month / 10;

    C[1] = dt.day % 10;
    C[0] = dt.day / 10;

    ogranicznik_zegara = micros();
  }
}

void zegarRTC::stoper(int C[], Przycisk button)
{
  if(opcja_wlaczona && !show_result)
  {
    unsigned long time = millis()/10 - stoper_time;

    C[5] = time % 10;
    C[4] = (time / 10) % 10;

    C[3] = (time / 100) % 10;
    C[2] = (time / 1000) % 6;

    C[1] = (time / 6000) % 10;
    C[0] = (time / 60000) % 10;

    if(C[0] == 9 && C[1] == 9)
    {
      opcja_wlaczona = false;
      show_result = false;
    }
  }

  if(opcja_wlaczona && button.stan == krotkieWcisniecie)
  {
    if(show_result == true)
    {
      opcja_wlaczona = false;
      show_result = false;
    }
    else
      show_result = true;
  }
  else if(!opcja_wlaczona && !show_result)
  {
    for(int i=0; i <= 5; i++)
      C[i] = 0;

    if(button.stan == krotkieWcisniecie)
    {
      opcja_wlaczona = true;
      stoper_time = millis()/10;
    }
  }
}

void zegarRTC::setTime(int C[], Przycisk przycisk1, Przycisk przycisk2, Przycisk przycisk3)
{
  changeNumberPair(przycisk2);

  changeTime(C, przycisk1, przycisk3);
  
  if (przycisk2.stan == dlugieWcisniecie)
  {
    dt = RTC.getDateTime();
    uint8_t First = C[0] * 10 + C[1];
    uint8_t Second = C[2] * 10 + C[3];
    uint8_t Third = C[4] * 10 + C[5];

    RTC.setDateTime(dt.year, dt.month, dt.day, First, Second, Third);
  }

}

void zegarRTC::changeTime(int C[], Przycisk przycisk1, Przycisk przycisk3) //pozwala na zmiane wskazywanego czasu podręczenego i jego kontrolę przy pomocy przycisków
{
  if (przycisk1.stan == krotkieWcisniecie || przycisk3.stan == krotkieWcisniecie)
  {
    if (przycisk1.stan == krotkieWcisniecie)
    {
      add = true;
    }
    else
    {
      add = false;
    }

    switch (pairPointer)
    {
    case Third:
      changeSecond(C, add);
      break;

    case Second:
      changeMinute(C, add);
      break;

    case First:
      changeHour(C, add);
      break;

    default:
      break;
    }
    checkTimeOverFlow(C);
  }
}

void zegarRTC::setDate(int C[], Przycisk przycisk1, Przycisk przycisk2, Przycisk przycisk3)
{
  changeNumberPair(przycisk2);
  
  changeDate(C, przycisk1, przycisk3);

  if (przycisk2.stan == dlugieWcisniecie)
  {
    dt = RTC.getDateTime();
    uint8_t day = C[0] * 10 + C[1];
    uint8_t month = C[2] * 10 + C[3];
    uint8_t year = C[4] * 10 + C[5];

    RTC.setDateTime(2000 + year, month, day, dt.hour, dt.minute, dt.second);
  }
}

void zegarRTC::changeDate(int C[], Przycisk foward, Przycisk backward)
{
  if (foward.stan == krotkieWcisniecie || backward.stan == krotkieWcisniecie)
  {
    if (foward.stan == krotkieWcisniecie)
    {
      add = true;
    }
    else
    {
      add = false;
    }

    switch (pairPointer)
    {
    case Third:
      changeYear(C, add);
      break;

    case Second:
      changeMonth(C, add);
      break;

    case First:
      changeDay(C, add);
      break;

    default:
      break;
    }


    checkDateOverFlow(C);
  }
}

void zegarRTC::changeNumberPair(Przycisk przycisk2)
{
  if (przycisk2.stan == krotkieWcisniecie)
  {
    pairPointer = static_cast<CzasPara>(pairPointer + 1);
    if (pairPointer == Last)
    {
      pairPointer = Third;
    }
  }
}

void zegarRTC::checkTimeOverFlow(int C[])
{
  for (int i = 5; i >= 1; i--) 
  {
    if ((C[i] == 6 && i % 2 == 0) || C[i] == 10) // przekroczenie górnego limitu cyfry
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
  
  if (C[0] < 0)           //overflow godzin
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

void zegarRTC::checkDateOverFlow(int C[])
{
  for(int i=5; i>=0; i = i - 2)     //overflow of upper decimal place
  {
    if(C[i] >= 10)
    {
      C[i] = 0;
      C[i-1]++;
    }

    if(C[i] <= -1)
    {
      C[i] = 9;
      C[i-1]--;
    }
  }

  
}

void zegarRTC::changeDay(int C[], bool add)
{
  if(add)
  {
    C[1]++;
  }
  else
  {
    C[1]--;
  }
  
}

void zegarRTC::changeMonth(int C[], bool add)
{
  if(add)
  {
    C[3]++;
  }
  else
  {
    C[3]--;
  }
  
}

void zegarRTC::changeYear(int C[], bool add)
{
  if(add)
  {
    C[5]++;
  }
  else
  {
    C[5]--;
  }
  
}

void zegarRTC::changeSecond(int C[], bool add)
{
  if (add)
  {
    C[5]++;
  }
  else
  {
    C[5]--;
  }
}

void zegarRTC::changeMinute(int C[], bool add)
{
  if (add)
  {
    C[3]++;
  }
  else
  {
    C[3]--;
  }
}

void zegarRTC::changeHour(int C[], bool add)
{
  if (add)
  {
    C[1]++;
  }
  else
  {
    C[1]--;
  }
}

void zegarRTC::thermometer(int C[])
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
  switch (pairPointer)
  {
  case Third:
    C[5] = 10;
    C[4] = 10;
    break;

  case Second:
    C[3] = 10;
    C[2] = 10;
    break;

  case First:
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