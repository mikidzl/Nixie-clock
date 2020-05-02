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
  unsigned long clock_limiter;
  unsigned long interwal = 300000;

  void changeSecond(bool add);
  void changeMinute(bool add);
  void changeHour(bool add);
  void checkTimeOverFlow();
  void changeTime(Przycisk przycisk1, Przycisk przycisk3);

  void changeDate(Przycisk foward, Przycisk backward);
  void checkDateOverFlow();
  void changeDay(bool add);
  void changeMonth(bool add);
  void changeYear(bool add);

  void changeNumberPair(Przycisk przycisk2);
  bool option_turn_on;
  int Temp[6];

  void blinkPair(int C[]);
  unsigned long okres_migania = 200000;
  bool blink;
  bool show_result;
  unsigned long stoper_time;

  void copyArray(int A[], int B[]);
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
  int godzina_Odtrucia;

  zegarRTC();
};

#endif