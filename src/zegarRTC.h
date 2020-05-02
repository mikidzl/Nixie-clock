#ifndef ZEGARRTC_H
#define ZEGARRTC_H

#include <Wire.h>
#include <DS3231.h>

#include "Arduino.h"
#include "przyciski.h"

enum CzasPara
{
  Third,
  Second,
  First,

  Last
};

class zegarRTC
{
private:
  unsigned long ogranicznik_zegara;
  unsigned long interwal = 300000;

  void changeSecond(int C[], bool add);
  void changeMinute(int C[], bool add);
  void changeHour(int C[], bool add);
  void checkTimeOverFlow(int C[]);
  void checkDateOverFlow(int C[]);
  void changeTime(int C[], Przycisk przycisk1, Przycisk przycisk3);

  void changeDate(int C[], Przycisk foward, Przycisk backward);
  void changeDay(int C[], bool add);
  void changeMonth(int C[], bool add);
  void changeYear(int C[], bool add);

  void changeNumberPair(Przycisk przycisk2);

  void migajZegarem(int C[]);
  unsigned long okres_migania = 200000;
  bool miganie = true;
  bool show_result;
  unsigned long stoper_time;

  bool add;
  CzasPara pairPointer;

public:
  DS3231 RTC;
  RTCDateTime dt;
  void clock(int C[]);
  void date(int C[]);
  void stoper(int C[], Przycisk button);
  void setTime(int C[], Przycisk przycisk1, Przycisk przycisk2, Przycisk przycisk3);
  void setDate(int C[], Przycisk przycisk1, Przycisk przycisk2, Przycisk przycisk3);
  void thermometer(int C[]);
  // void budzik(int C[], enum wartoscPrzycisku);
  bool opcja_wlaczona;
  int godzina_Odtrucia;

  zegarRTC();
};

#endif