#include <Arduino.h>

#include "kontrola_Nixie.h"
#include "przyciski.h"
#include "zegarRTC.h"
#include "Menu.h"

Przycisk przycisk1(6); // deklaracje przycisków
Przycisk przycisk2(7);
NIXIE nixie;          // klasa konwertująca BCD oraz obsługująca lampy
int tablica_Nixie[6]; //tablica cyfr do wyświetlenia na lampach

zegarRTC Zegar; //klasa obsługująca zegar RTC

const int szum_przemiatnie = 14; // pin do pobierania szumu inicjującego rand

unsigned long czasPrzycisk = 0;

Opcje opcja = zegar_;
bool opcjaStan = true;
unsigned long licznik_Menu;
unsigned long powrot = 10000000;

int temperatura;
int godzina_odtrucia;
int licznik_przemiecen = 0;
bool czy_odtruwamy = false;
unsigned long przemiatanie;
unsigned long czas_Przemiecenia = 10000000;

//____________________________________________________________________

//void menu(); //wybieranie opcji do wyświetlenia
void ustawianieCzasu(int C[]);
void temperaturaUstaw(int C[]);
void odtruwanieLamp(int C[]);
void budzik(int C[]);
void startOpcja();
void wrocDoZegara();

void fejkDispej(int C[]);

//___________________________________________________________________________

void setup()
{

  pinMode(nixie.latchPin, OUTPUT); //piny do sterowania rejestrem przesuwnym
  pinMode(nixie.dataPin, OUTPUT);
  pinMode(nixie.clockPin, OUTPUT);

  pinMode(przycisk1.pin, INPUT_PULLUP);
  pinMode(przycisk2.pin, INPUT_PULLUP);

  Serial.begin(115200);
  Serial.print("Połączono");
}

void loop()
{
  //menu();
  //nixie.wyswietlPWM(tablica_Nixie);
  Zegar.zegar(tablica_Nixie);

  fejkDispej(tablica_Nixie);
  delay(500);
  //przycisk1.sprawdzPrzycisk(czasPrzycisk); // obsługa stanu przycisków
  //przycisk2.sprawdzPrzycisk(czasPrzycisk);

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

// void menu()
// {
//   switch (opcja)
//   {
//   case zegar_:
//     switch (przycisk1.stan)
//     {
//     case krotkieWcisniecie:
//       opcja = termometr;
//       przycisk1.stan = wylaczony;
//       break;

//     case dlugieWcisniecie:
//       opcja = ustawianie_czasu;
//       przycisk1.stan = wylaczony;
//       break;
//     }

//     Zegar.zegar(tablica_Nixie);

//     if (tablica_Nixie[1] - godzina_odtrucia != 0)
//     {
//       opcja = odtruwanie_lampy;
//       godzina_odtrucia = tablica_Nixie[1];
//     }

//     break;

//   case ustawianie_czasu:
//     startOpcja();
//     Zegar.ustawianieCzasu(tablica_Nixie);
//     wrocDoZegara();

//     break;

//   case termometr:
//     startOpcja();
//     Zegar.temperaturaUstaw(tablica_Nixie);
//     wrocDoZegara();

//     break;

//   case budzik_:
//     //switch(p1)
//     Zegar.budzik(tablica_Nixie);

//     break;

//   case odtruwanie_lampy:

//     odtruwanieLamp(tablica_Nixie);

//     break;

//   default:
//     opcja = zegar_;
//     break;
//   }
// }

void startOpcja()
{
  licznik_Menu = micros();
}
void wrocDoZegara()
{
  if (powrot <= micros() - licznik_Menu)
  {
    opcja = zegar_;
  }
}

void odtruwanieLamp(int C[])
{
  if (!czy_odtruwamy)
  {
    przemiatanie = micros();
    czy_odtruwamy = true;
  }

  randomSeed(analogRead(szum_przemiatnie));
  Zegar.zegar(C);

  if (czas_Przemiecenia + licznik_przemiecen * (czas_Przemiecenia / 10) <= micros() - przemiatanie)
  {
    licznik_przemiecen++;
    if (licznik_przemiecen >= 6)
    {
      opcja = zegar_;
      czy_odtruwamy = false;
      return;
    }
  }

  if ((6 - nixie.lampa) - licznik_przemiecen >= 0)
    C[nixie.lampa - 1] = random(10);
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