#ifndef ZEGARRTC_H
#define ZEGARRTC_H

#include "Arduino.h"

#include <Wire.h>
#include <RtcDS3231.h>



void zegar(int C[]);
void ustawianieCzasu(int C[]);
void temperaturaUstaw(int C[]);
int wlaczZegar();



#endif