#include "zegarRTC.h"

zegarRTC::zegarRTC()
{
  // RTC.begin();
  // while (!RTC.isReady());

  //First_Odtrucia = RTC.getDateTime().hour %10;
  RTC_limiter = -interwal; //wartość początkowa, aby zegar od zadziałał od razu przy pierwszym włączeniu
  clock_limiter = -1000;

  option_turn_on = false;
  pairPointer = Third;
  show_result = false;
  blink = false;
}

void zegarRTC::clock(int C[]) //main function, gets time from RTC module and assign numbers for each place of an array
{

  if (millis() - RTC_limiter >= interwal) //keeps from asking RTC module about time ever cycle, because it's time consuming
  {
    if (!option_turn_on)
    {
      option_turn_on = true;
      for (int i = 0; i <= 5; i++) // turns off all the digits of the display
        C[i] = 10;
    }
    else
    {
      dt = RTC.getDateTime();

      Time[5] = dt.second % 10;
      Time[4] = dt.second / 10;

      Time[3] = dt.minute % 10;
      Time[2] = dt.minute / 10;

      Time[1] = dt.hour % 10;
      Time[0] = dt.hour / 10;

      RTC_limiter = millis(); //resets clock limiter
      option_turn_on = false;
    }
  }
  if (millis() - clock_limiter >= 1000)
  {
    Time[5] += (millis() - clock_limiter)/1000;
    clock_limiter = millis();

    checkTimeOverFlow(Time);
    copyArray(Time, C);
  }
}

void zegarRTC::date(int C[]) //pobiera czas z modułu RTC oraz rozbija na cyfry
{
  if (micros() - RTC_limiter >= interwal)
  {
    dt = RTC.getDateTime();

    C[5] = (dt.year - 2000) % 10;
    C[4] = (dt.year - 2000) / 10;

    C[3] = dt.month % 10;
    C[2] = dt.month / 10;

    C[1] = dt.day % 10;
    C[0] = dt.day / 10;

    clock_limiter = micros();
  }
}

void zegarRTC::stoper(int C[], Przycisk button) //used as stop timer
{
  if (option_turn_on && !show_result) //while counting and showing the time
  {
    unsigned long time = millis() / 10 - stoper_time;

    C[5] = time % 10;
    C[4] = (time / 10) % 10; // hundreths of a second

    C[3] = (time / 100) % 10;
    C[2] = (time / 1000) % 6; //  seconds

    C[1] = (time / 6000) % 10;
    C[0] = (time / 60000) % 10; // minutes

    if (C[0] == 9 && C[1] == 9) //ends stoper if reached 99 minutes
    {
      option_turn_on = false;
      show_result = false;
    }
  }

  if (option_turn_on && button.stan == krotkieWcisniecie || button.stan == dlugieWcisniecie) // showing result
  {
    if (show_result == true) // resets stoper to initial state
    {
      option_turn_on = false;
      show_result = false;
    }
    else // so it shows the result and takes two times to enter this if to reset
      show_result = true;
  }
  else if (!option_turn_on && !show_result) //initial state waiting to actvie counting time by pressing the button
  {
    for (int i = 0; i <= 5; i++) // zeros all the digits of the display
      C[i] = 0;

    if (button.stan == krotkieWcisniecie) //intializes counting
    {
      option_turn_on = true;
      stoper_time = millis() / 10;
    }
  }
}

void zegarRTC::setTime(int C[], Przycisk przycisk1, Przycisk przycisk2, Przycisk przycisk3)
{
  if (!option_turn_on) //so it enters this condition only when once when initialized
  {
    copyArray(C, Temp); //copies time to temporary array for changing values
    option_turn_on = true;
  }

  changeNumberPair(przycisk2);

  changeTime(przycisk1, przycisk3);

  copyArray(Temp, C);

  blinkPair(C);

  if (przycisk2.stan == dlugieWcisniecie)
  {
    dt = RTC.getDateTime();
    uint8_t First = C[0] * 10 + C[1];
    uint8_t Second = C[2] * 10 + C[3];
    uint8_t Third = C[4] * 10 + C[5];

    RTC.setDateTime(dt.year, dt.month, dt.day, First, Second, Third);
    option_turn_on = false;
  }
}

void zegarRTC::changeTime(Przycisk przycisk1, Przycisk przycisk3) //pozwala na zmiane wskazywanego czasu podręczenego i jego kontrolę przy pomocy przycisków
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
      changeSecond(add);
      break;

    case Second:
      changeMinute(add);
      break;

    case First:
      changeHour(add);
      break;

    default:
      break;
    }
    checkTimeOverFlow(Temp);
  }
}

void zegarRTC::setDate(int C[], Przycisk przycisk1, Przycisk przycisk2, Przycisk przycisk3)
{
  changeNumberPair(przycisk2);

  changeDate(przycisk1, przycisk3);

  if (przycisk2.stan == dlugieWcisniecie)
  {
    dt = RTC.getDateTime();
    uint8_t day = C[0] * 10 + C[1];
    uint8_t month = C[2] * 10 + C[3];
    uint8_t year = C[4] * 10 + C[5];

    RTC.setDateTime(2000 + year, month, day, dt.hour, dt.minute, dt.second);
  }
}

void zegarRTC::changeDate(Przycisk foward, Przycisk backward)
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
      changeYear(add);
      break;

    case Second:
      changeMonth(add);
      break;

    case First:
      changeDay(add);
      break;

    default:
      break;
    }

    checkDateOverFlow();
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

void zegarRTC::checkTimeOverFlow(int Temp[])
{
  for (int i = 5; i >= 1; i--)
  {
    if (Temp[i] >= 10 && i % 2 == 1) //overflowing upper limit of odd digits
    {
      Temp[i - 1] += Temp[i] / 10;
      Temp[i] = Temp[i] % 10;
    }

    if (Temp[i] >= 6 && (i == 4 || i == 2)) //overflowing upper limit for tens of seconds and tens of minutes
    {
      Temp[i - 1] += Temp[i] / 6;
      Temp[i] = Temp[i] % 6;
    }

    if (Temp[i] <= -1) //checking for violation of lower limit
    {
      if (i % 2 == 0)
      {
        Temp[i] = 5;
        Temp[i - 1]--;
      }
      else
      {
        Temp[i] = 9;
        Temp[i - 1]--;
      }
    }
  }

  if (Temp[0] < 0) //overflow of hours
  {
    Temp[0] = 2;
    Temp[1] = 3;
  }
  else if (Temp[1] >= 4 && Temp[0] == 2)    //  if next day
  {
    Temp[1] = Temp[0]*10 + Temp[1] - 24;    //  thus synchronization interval with clock shouldn't be more than 6 hours
  }
}

void zegarRTC::checkDateOverFlow()
{
  for (int i = 5; i >= 0; i = i - 2) //overflow of upper decimal place
  {
    if (Temp[i] >= 10)
    {
      Temp[i] = 0;
      Temp[i - 1]++;
    }

    if (Temp[i] <= -1)
    {
      Temp[i] = 9;
      Temp[i - 1]--;
    }
  }
}

void zegarRTC::changeDay(bool add)
{
  if (add)
  {
    Temp[1]++;
  }
  else
  {
    Temp[1]--;
  }
}

void zegarRTC::changeMonth(bool add)
{
  if (add)
  {
    Temp[3]++;
  }
  else
  {
    Temp[3]--;
  }
}

void zegarRTC::changeYear(bool add)
{
  if (add)
  {
    Temp[5]++;
  }
  else
  {
    Temp[5]--;
  }
}

void zegarRTC::changeSecond(bool add)
{
  if (add)
  {
    Temp[5]++;
  }
  else
  {
    Temp[5]--;
  }
}

void zegarRTC::changeMinute(bool add)
{
  if (add)
  {
    Temp[3]++;
  }
  else
  {
    Temp[3]--;
  }
}

void zegarRTC::changeHour(bool add)
{
  if (add)
  {
    Temp[1]++;
  }
  else
  {
    Temp[1]--;
  }
}

void zegarRTC::thermometer(int C[])
{
  // if (button.stan == krotkieWcisniecie)
  //   RTC.forceConversion();
  if (millis() - RTC_limiter >= interwal)
  {
    RTC.forceConversion();
    int temperatura = int(100 * RTC.readTemperature());

    C[0] = 0;
    C[1] = 0;
    C[2] = temperatura / 1000;
    C[3] = (temperatura / 100) % 10;
    C[4] = (temperatura / 10) % 10;
    C[5] = temperatura % 10;

    RTC_limiter = millis();
  }
}

void zegarRTC::blinkPair(int C[])
{
  if (micros() - clock_limiter >= okres_migania)
  {
    switch (blink)
    {
    case false:
      blink = true;
      break;

    case true:
      blink = false;
      break;

    default:
      break;
    }
    clock_limiter = micros();
  }
  if (blink)
  {
    switch (pairPointer)
    {
    case Third:
      C[5] = 0;
      C[4] = 0;
      break;

    case Second:
      C[3] = 0;
      C[2] = 0;
      break;

    case First:
      C[1] = 0;
      C[0] = 0;
      break;

    default:
      break;
    }
  }
}

void zegarRTC::slotMachine(int C[])
{
  if (slotCounter < 6 && micros() - slotTime >= slotChange)
  {
    if (slotCounter == 0)
    {
      for (int i = 0; i < 6; i++)
        C[i] = 0;
    }
    for (int i = 5; 5 - slotCounter <= i; i--)
    {
      C[i] = slotCounter + i - 5;
    }
    slotCounter++;
    slotTime = micros();
  }
  else if (slotCounter >= 6 && micros() - slotTime >= slotChange)
  {
    slotTime = micros();
    for (int i = 0; i < 6; i++)
      C[i] = (C[i] + 1) % 10;
  }
}

void zegarRTC::copyArray(int A[], int B[])
{
  for (int i = 0; i < 6; i++)
    B[i] = A[i];
}

// void zegarRTC::budzik(int C[], wartoscPrzycisku)
// {
//   if (wartoscPrzycisku == wylaczony)
//   {
//   }
// }