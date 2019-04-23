#include "kontrola_Nixie.h"

NIXIE::NIXIE()
{
  latchPin = 4;
  clockPin = 3;
  dataPin = 2;

  okres = 1000000;   //czas między zapalaniem się kolejnych lamp
  licznik_czasu = 0; //zmienna do określania czasu
  jasnosc = 50;      //procentowa wartość jasności
  lampa = 1;         //sprawdzanie która lampa jest aktywna
  licznik_jasnosci = 0;
}

void NIXIE::nixieNapisz(uint8_t value)
{
  //D cyfra
  //A cyfra jednosci
  digitalWrite(12, (value & 0x08) >> 3);
  digitalWrite(11, (value & 0x04) >> 2);
  digitalWrite(10, (value & 0x02) >> 1);
  digitalWrite(9, value & 0x01);
}

void NIXIE::migajZegar(int C[], CzasPara para)
{
  switch (para)
  {
  case Sekunda:
    C[4] = 10;
    C[5] = 10;
    break;

  case Minuta:
    C[2] = 10;
    C[3] = 10;
    break;

  case Godzina:
    C[0] = 10;
    C[1] = 10;
    break;

  default:
    para = Sekunda;
    break;
  }
}

void NIXIE::wyswietlPWM(int C[])
{
  wylaczLampe();
  wlaczLampe(C);
}

void NIXIE::wlaczLampe(int C[])
{
  if (okres <= (micros() - licznik_czasu)) //kiedy zapalić lampe
  {
    licznik_czasu = micros();
    digitalWrite(latchPin, LOW);

    byte zero = 0;

    bitWrite(zero, lampa, HIGH);
    shiftOut(dataPin, clockPin, MSBFIRST, zero);
    digitalWrite(latchPin, HIGH);

    //nixieNapisz(C[lampa -1]);

    if (lampa == 6)
      lampa = 1;
    else
      lampa++;

    // if (licznik_jasnosci == 10) //pobieranie wartości do jasności
    // {
    //   jasnosc = map(analogRead(A1), 0, 1023, 10, 99);
    //   licznik_jasnosci = 0;
    // }
    // licznik_jasnosci++;
  }
}

void NIXIE::wylaczLampe()
{
  if (((okres * jasnosc) / 100) <= (micros() - licznik_czasu)) //kiedy zgasić lampe PWM (jasność)
  {
    byte zero = 0;
    digitalWrite(latchPin, LOW);
    bitWrite(zero, lampa, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, zero);
    digitalWrite(latchPin, HIGH);
  }
}