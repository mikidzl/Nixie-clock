#include <Arduino.h>

#include "kontrola_Nixie.h"
#include "przyciski.h"
#include "zegarRTC.h"
#include "Menu.h"

Przycisk przycisk1(8); // deklaracje przycisków
Przycisk przycisk2(9);
Przycisk przycisk3(10);

NIXIE nixie;          // klasa konwertująca BCD oraz obsługująca lampy
int tablica_Nixie[6]; //tablica cyfr do wyświetlenia na lampach

zegarRTC Zegar; //klasa obsługująca zegar RTC

Menu menu;

const int szum_przemiatnie = 14; // pin do pobierania szumu inicjującego rand

unsigned long czasPrzycisk = 0;

Opcje opcja = zegar_;
bool opcjaStan = true;

int temperatura;
int godzina_odtrucia;
int licznik_przemiecen = 0;
bool czy_odtruwamy = false;
unsigned long przemiatanie;
unsigned long czas_Przemiecenia = 10000000;

//____________________________________________________________________

void odtruwanieLamp(int C[]);
void jasnosc();
void fejkDispej(int C[]);

//___________________________________________________________________________

void setup()
{

  pinMode(nixie.latchPin, OUTPUT); //piny do sterowania rejestrem przesuwnym
  pinMode(nixie.dataPin, OUTPUT);
  pinMode(nixie.clockPin, OUTPUT);

  Serial.begin(115200);
  Serial.println("Połączono");

  Zegar.RTC.begin(); 
  while (!Zegar.RTC.isReady());
}

void loop()
{
  menu.menu(tablica_Nixie, Zegar, przycisk1, przycisk2, przycisk3);
  nixie.wyswietlPWM(tablica_Nixie);

  fejkDispej(tablica_Nixie);

  przycisk1.sprawdzPrzycisk(czasPrzycisk); // obsługa stanu przycisków
  przycisk2.sprawdzPrzycisk(czasPrzycisk);
  przycisk3.sprawdzPrzycisk(czasPrzycisk);
}

void jasnosc()
{
  // if (przycisk1.stan == krotkieWcisniecie)
  // {
  //   if (nixie.jasnosc < 84)
  //     nixie.jasnosc += 15;
  //   przycisk1.zerujPrzycisk();
  // }
  // else if (przycisk1.stan == dlugieWcisniecie)
  // {
  //     nixie.jasnosc = 5;
  //   przycisk1.zerujPrzycisk();
  // }
  // if (przycisk2.stan == krotkieWcisniecie)
  // {
  //   if (nixie.jasnosc > 16)
  //     nixie.jasnosc += -15;
  //   przycisk2.zerujPrzycisk();
  // }
  // else if (przycisk2.stan == dlugieWcisniecie)
  // {
  //   if (nixie.jasnosc > 21)
  //     nixie.jasnosc += -10;
  //   przycisk2.zerujPrzycisk();
  // }
}

void odtruwanieLamp(int C[])
{
//   if (!czy_odtruwamy)
//   {
//     przemiatanie = micros();
//     czy_odtruwamy = true;
//   }

//   randomSeed(analogRead(szum_przemiatnie));
//   Zegar.zegar(C);

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

void fejkDispej(int C[])
{
  Serial.print(C[0]);
  Serial.print(C[1]);
  Serial.print(":");
  Serial.print(C[2]);
  Serial.print(C[3]);
  Serial.print(":");
  Serial.print(C[4]);
  Serial.println(C[5]);
}