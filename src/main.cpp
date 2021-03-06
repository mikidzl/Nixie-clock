#include <Arduino.h>

#include "kontrola_Nixie.h"
#include "przyciski.h"
#include "zegarRTC.h"
#include "Menu.h"

Przycisk przycisk1(9); // deklaracje przycisków, liczba oznacza pin podłączenia przycisku
Przycisk przycisk2(10);
Przycisk przycisk3(11);

NIXIE nixie;          // klasa konwertująca BCD oraz obsługująca lampy
//int tablica_Nixie[6]; //tablica cyfr do wyświetlenia na lampach

int tablica_Nixie[6] = {10,10,10,10,10,10};

int dupa = 0;

zegarRTC Zegar; //klasa obsługująca zegar RTC

Menu menu;

//const int szum_przemiatnie = 14; // pin do pobierania szumu inicjującego rand

unsigned long czasPrzycisk = 0;

bool opcjaStan = true;

int godzina_odtrucia;
int licznik_przemiecen = 0;
bool czy_odtruwamy = false;
unsigned long przemiatanie;
unsigned long czas_Przemiecenia = 10000000;

unsigned long fejktajm = 0;

//____________________________________________________________________

void odtruwanieLamp(int C[]);
void fejkDispej(int C[]);

//___________________________________________________________________________

void setup()
{
  Serial.begin(115200);
  Serial.println("Połączono");

  Zegar.RTC.begin(); 
  while (!Zegar.RTC.isReady());

  przemiatanie = micros();
}

void loop()
{
  menu.program(tablica_Nixie, Zegar, przycisk1, przycisk2, przycisk3);
  nixie.wyswietlPWM(tablica_Nixie);


  // if(micros() - przemiatanie > 100000)
  // {
  //   dupa++;
  //   if(dupa == 100) dupa = 0;

  //   tablica_Nixie[5] = dupa%10;
  //   tablica_Nixie[4] = dupa/10;
  //   przemiatanie = micros();
  // }

  fejkDispej(tablica_Nixie);


  przycisk1.sprawdzPrzycisk(czasPrzycisk); // obsługa stanu przycisków
  przycisk2.sprawdzPrzycisk(czasPrzycisk);
  przycisk3.sprawdzPrzycisk(czasPrzycisk);

}



void fejkDispej(int C[])
{ 
  if(micros() - fejktajm >= 99000)
  {
    Serial.print(C[0]);
    Serial.print(C[1]);
    Serial.print(":");
    Serial.print(C[2]);
    Serial.print(C[3]);
    Serial.print(":");
    Serial.print(C[4]);
    Serial.println(C[5]);
    fejktajm = micros();
  }

}

void odtruwanieLamp(int C[])
{
//   if (!czy_odtruwamy)
//   {
//     przemiatanie = micros();
//     czy_odtruwamy = true;
//   }

//   randomSeed(analogRead(szum_przemiatnie));
//   Zegar.zegarek(C);

//   if (czas_Przemiecenia + licznik_przemiecen * (czas_Przemiecenia / 10) <= micros() - przemiatanie)
//   {
//     licznik_przemiecen++;
//     if (licznik_przemiecen >= 6)
//     {
//       opcja = zegar_;
//       czy_odtruwamy = false;
//       return;
//     }
//   }

//   if ((6 - nixie.lampa) - licznik_przemiecen >= 0)
//     C[nixie.lampa - 1] = random(10);
}