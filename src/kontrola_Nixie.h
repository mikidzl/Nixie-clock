#ifndef kontrola_Nixie_H
#define kontrola_Nixie_H

#include "Arduino.h"

//Pin connected to latch pin (ST_CP) of 74HC595
const int latchPin = 3;
//Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 4;
////Pin connected to Data in (DS) of 74HC595
const int dataPin = 2;

void nixieWrite(uint8_t value);
void wyswietlPWM(int C[], unsigned long okres, unsigned long &licznik, int &licznik_jasnosci, int &lampa, int &jasnosc);

#endif