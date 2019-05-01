#ifndef ZEGARRTC_H
#define ZEGARRTC_H

#include <Wire.h>
#include <DS3231.h>

#include "Arduino.h"
#include "przyciski.h"

enum CzasPara
{
  Sekunda,
  Minuta,
  Godzina,

  ostatni_element
};

class zegarRTC
{
private:
  unsigned long ogranicznik_zegara = 0;
  unsigned long interwal = 800000;

public:
  DS3231 RTC;
  RTCDateTime dt;
  void zegar(int C[]);
  void ustawianieCzasu(int C[], Przycisk przycisk1, Przycisk przycisk2, Przycisk przycisk3);
  void temperaturaUstaw(int C[]);
  void budzik(int C[]);
  bool opcja_wlaczona;

  void zmienCzas(int C[], Przycisk przycisk1, Przycisk przycisk3);
  void zmienSekunde(int C[], bool dodac);
  void zmienMinute(int C[], bool dodac);
  void zmienGodzine(int C[], bool dodac);
  void sprawdzOverflow(int C[]);
  bool dodac;
  CzasPara opcjaZmienCzas;

  int godzina_Odtrucia;

  zegarRTC();
};

#endif