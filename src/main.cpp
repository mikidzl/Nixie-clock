#include <Arduino.h>

#include "kontrola_Nixie.h"
#include "przyciski.h"
#include "zegarRTC.h"

Przycisk przycisk1(5);
Przycisk przycisk2(6);
NIXIE nixie;
int tablica_Nixie[6]; //tablica cyfr do wyświetlenia na lampach

const int szum_przemiatnie = 14; // pin do pobieania szumu inicjującego rand

unsigned long czasPrzycisk = 0;

enum Opcje
{
  zegar_,
  ustawianie_czasu,
  budzik_,
  termometr,
  odtruwanie_lampy
};
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

void menu(); //wybieranie opcji do wyświetlenia
void zegar(int C[]);
void ustawianieCzasu(int C[]);
void temperaturaUstaw(int C[]);
void odtruwanieLamp(int C[]);
void budzik(int C[]);
void startOpcja();
void wrocDoZegara();
int wlaczZegar();

//___________________________________________________________________________

void setup()
{

  pinMode(nixie.latchPin, OUTPUT); //piny do sterowania rejestrem przesuwnym
  pinMode(nixie.dataPin, OUTPUT);
  pinMode(nixie.clockPin, OUTPUT);

  pinMode(przycisk1.pin, INPUT_PULLUP);
  pinMode(przycisk2.pin, INPUT_PULLUP);

  godzina_odtrucia = wlaczZegar();
}

void loop()
{

  //menu();
  nixie.wyswietlPWM(tablica_Nixie);

  zegar(tablica_Nixie);
  // przycisk(przycisk1, czasPrzycisk);         // obsługa stanu przycisków
  // przycisk(przycisk2, czasPrzycisk);
}

void menu()
{
  switch (opcja)
  {
  case zegar_:
    switch (przycisk1.stan)
    {
    case krotkieWcisniecie:
      opcja = termometr; //
      przycisk1.stan = wylaczony;
      break;

    case dlugieWcisniecie:
      opcja = ustawianie_czasu;
      przycisk1.stan = wylaczony;
      break;
    }

    zegar(tablica_Nixie);

    if (tablica_Nixie[1] - godzina_odtrucia != 0)
    {
      opcja = odtruwanie_lampy;
      godzina_odtrucia = tablica_Nixie[1];
    }

    break;

  case ustawianie_czasu:
    startOpcja();
    ustawianieCzasu(tablica_Nixie);
    wrocDoZegara();

    break;

  case termometr:
    startOpcja();
    temperaturaUstaw(tablica_Nixie);
    wrocDoZegara();

    break;

  case budzik_:
    //switch(p1)
    //budzik(Nixie);

    break;

  case odtruwanie_lampy:

    odtruwanieLamp(tablica_Nixie);

    break;

  default:
    opcja = zegar_;
    break;
  }
}

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
  zegar(C);

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