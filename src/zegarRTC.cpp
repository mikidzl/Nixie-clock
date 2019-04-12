#include "zegarRTC.h"

RtcDS3231<TwoWire> clock(Wire);           // deklarcja zegara

RtcDateTime dt; 

unsigned int ogranicznik_zegara = 0;
unsigned int interwal = 800000;

void zegar(int C[])      //pobiera czas z modułu RTC oraz rozbija na cyfry
{ 
  if(micros() - ogranicznik_zegara >= interwal)
  {
    dt = clock.GetDateTime();

    C[5]= dt.Second() %10;
    C[4]= dt.Second() /10;

    C[3]= dt.Minute() %10;
    C[2]= dt.Minute() /10;

    C[1]= dt.Hour() %10;
    C[0]= dt.Hour() /10;

    ogranicznik_zegara = micros();
  }
  
}

void ustawianieCzasu(int C[])
{
  
}

void temperaturaUstaw(int C[])
{
  int temperatura = int(100*clock.GetTemperature().AsFloatDegC());

  C[0] = 10;
  C[1] = 10;
  C[2] = temperatura / 1000;
  C[3] = (temperatura / 100) % 10;
  C[4] = (temperatura / 10) % 10;
  C[5] = temperatura % 10;
}

int wlaczZegar()
{
    clock.Begin();
  return clock.GetDateTime().Hour() % 10;
}