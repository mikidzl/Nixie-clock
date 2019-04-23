#ifndef ZEGARRTC_H
#define ZEGARRTC_H

#include <Wire.h>
#include <DS3231.h>

#include "Arduino.h"
#include "przyciski.h"

class zegarRTC
{
private:
  unsigned long ogranicznik_zegara = 0;
  unsigned long interwal = 800000;

public:
  DS3231 RTC;
  RTCDateTime dt;
  void zegar(int C[]);
  void ustawianieCzasu(int C[]);
  void temperaturaUstaw(int C[]);
  void budzik(int C[]);
  bool opcja_wlaczona;

  void zmienSekunde(int C[], bool dodac);
  void zmienMinute(int C[], bool dodac);
  void zmienGodzine(int C[], bool dodac);
  void sprawdzOverflow(int C[]);


  int godzina_Odtrucia;


  zegarRTC();
};

// class budzik
// {
// private:
//   /* data */
// public:
//   budzik(/* args */);
//   ~budzik();
// };

// budzik::budzik(/* args */)
// {
// }

// budzik::~budzik()
// {
// }


#endif