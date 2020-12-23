#include "kontrola_Nixie.h"

NIXIE::NIXIE()
{
  latchPin = 4;
  clockPin = 3;
  dataPin = 2;

  pinMode(latchPin,OUTPUT);  //pins for steering shift register 74hc595n
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);

  pinMode(A,OUTPUT);        //pins for steering 74141 nixie driver
  pinMode(B,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(D,OUTPUT);


  okres = 3000;   //czas między zapalaniem się kolejnych lamp
  licznik_czasu = 0; //zmienna do określania czasu
  jasnosc = 50;      //procentowa wartość jasności
  lampa = 1;         //sprawdzanie która lampa jest aktywna
  licznik_jasnosci = 0;
}

void NIXIE::nixieNapisz(uint8_t value)
{
  //D cyfra
  //A cyfra jednosci
  digitalWrite(D, (value & 0x08) >> 3);
  digitalWrite(C, (value & 0x04) >> 2);
  digitalWrite(B, (value & 0x02) >> 1);
  digitalWrite(A, value & 0x01);
}

void NIXIE::wyswietlPWM(int C[])
{
  wylaczLampe();
  wlaczLampe(C);
}

void NIXIE::wlaczLampe(int C[])
{
  if (okres <= (micros() - licznik_czasu))      //when to light the lamp
  {
    licznik_czasu = micros();

    if(C[lampa -1] <= 9 && C[lampa -1] >= 0  )    //ensuring that value for lamp is a digit
    {
      nixieNapisz(C[lampa -1]);
      lamp_status = HIGH;
    }
    else                    //if not don't show anything
    {
      nixieNapisz(10);      //value 10-15 turns high impedence state on 74141 output
      lamp_status = LOW;
    }
    

    digitalWrite(latchPin, LOW);

    byte zero = 0;

    bitWrite(zero, lampa, lamp_status);
    shiftOut(dataPin, clockPin, MSBFIRST, zero);
    digitalWrite(latchPin, HIGH);


    if (lampa == 6)
      lampa = 1;
    else
      lampa++;

    if (licznik_jasnosci >= 25) //pobieranie wartości do jasności
    {
      jasnosc = map(analogRead(brightnessPin), 0, 1023, 12, 96);
      licznik_jasnosci = 0;
    }
    licznik_jasnosci++;
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
    nixieNapisz(10);
  }
}