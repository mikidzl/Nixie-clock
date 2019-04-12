#include "kontrola_Nixie.h"



void nixieWrite(uint8_t value)
{
  //D is most significant bit
  //A is least significant bit
  digitalWrite(12, (value & 0x08) >> 3);
  digitalWrite(11, (value & 0x04) >> 2);
  digitalWrite(10, (value & 0x02) >> 1);
  digitalWrite(9, value & 0x01);
}

void wyswietlPWM(int C[], unsigned long okres, unsigned long &licznik_czasu, int &licznik_jasnosci, int &lampa, int &jasnosc)
{
  wylaczLampe(C,okres,licznik_czasu,licznik_jasnosci,lampa,jasnosc);
  wlaczLampe(C,okres,licznik_czasu,licznik_jasnosci,lampa,jasnosc);
}

void wlaczLampe(int C[], unsigned long okres, unsigned long &licznik_czasu, int &licznik_jasnosci, int &lampa, int &jasnosc)
{
  if(okres <= (micros()-licznik_czasu) )        //kiedy zapalić lampe
        {
          licznik_czasu = micros();
          digitalWrite(latchPin, LOW);

          byte zero=0;
          
          bitWrite(zero, lampa , HIGH);
          shiftOut(dataPin, clockPin, MSBFIRST, zero);
          digitalWrite(latchPin, HIGH);

          //nixieWrite(C[lampa -1])

          if(lampa  == 6) 
            lampa =1;
          else lampa ++;

          
          if(licznik_jasnosci==10)                                        //pobieranie wartości do jasności
            {
              jasnosc = map(analogRead(A1),0,1023,10,99); 
              licznik_jasnosci=0;
            }
          licznik_jasnosci++;
        }
}

void wylaczLampe(int C[], unsigned long okres, unsigned long &licznik_czasu, int &licznik_jasnosci, int &lampa, int &jasnosc)
{
  if(((okres*jasnosc)/100) <= (micros()-licznik_czasu))       //kiedy zgasić lampe PWM (jasność)
    {
      byte zero=0;
      digitalWrite(latchPin, LOW);
      bitWrite(zero, lampa , LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, zero);
      digitalWrite(latchPin, HIGH);
    }
}