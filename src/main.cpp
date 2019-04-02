#include <Arduino.h>

#include <Wire.h>
#include <RtcDS3231.h>

#include "kontrola_Nixie.h"
#include "przyciski.h"


RtcDS3231<TwoWire> clock(Wire);           // deklarcja zegara

RtcDateTime dt;                           // zmienna przechowująca date oraz czas



const int przycisk1 = 5;          // zmiennne potrzebne obsługi przycisków
bool t1 = false;
int p1 = 0;

const int przycisk2 = 6;
bool t2 = false;
int p2 = 0;

const int przycisk3 = 7;              
bool t3 = false;
int p3 = 0;

const int szum_przemiatnie = 14;          // pin do pobieania szumu inicjującego rand

unsigned long czasPrzycisk = 0;

int opcja= 0;
bool opcjaStan = true;
unsigned long licznik_Menu;
unsigned long powrot = 10000000;

int temperatura;
int godzina_odtrucia;
int licznik_przemiecen = 0;
bool czy_odtruwamy = false;
unsigned long przemiatanie;
unsigned long czas_Przemiecenia = 10000000;

unsigned long okres = 2000;         //czas między zapalaniem się kolejnych lamp
unsigned long licznik_czasu = 0;    //zmienna do określania czasu
int jasnosc = 50;                    //procentowa wartość jasności
int lampa = 1;                      //licznik_czasu lampy
int licznik_jasnosci = 0;                                    
int Nixie[6];                       //tablica cyfr do wyświetlenia na lampach


//____________________________________________________________________


void menu();                                                  //wybieranie opcji do wyświetlenia
void zegar(int C[]);
void ustawianieCzasu(int C[]);
void temperaturaUstaw(int C[]);
void odtruwanieLamp(int C[]);
void budzik(int C[]);
void startOpcja();
void wrocDoZegara();

void setup() {

  pinMode(latchPin, OUTPUT);      //piny do sterowania rejestrem przesuwnym
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);

  pinMode(przycisk1,INPUT_PULLUP);
  pinMode(przycisk2,INPUT_PULLUP);
  pinMode(przycisk3,INPUT_PULLUP);

  clock.Begin();
  godzina_odtrucia = clock.GetDateTime().Hour() % 10;
}

void loop() {
  
  //menu();
  wyswietlPWM(Nixie,okres,licznik_czasu,licznik_jasnosci,lampa,jasnosc);
  opcja = 0;


  // przycisk(t1,przycisk1,p1,czasPrzycisk);         // obsługa stanu przycisków
  // przycisk(t2,przycisk2,p2,czasPrzycisk);
  // przycisk(t3,przycisk3,p3,czasPrzycisk);

}


void menu() 
{
  switch(opcja)
  {
    case 0:
      // switch(p1)
      // {
      //   case 1:
      //     opcja = 2;//
      //     p1 = 0;
      //   break;

      //   case 2:
      //     opcja = 1;
      //     p1 = 0;
      //   break;
      // }
      
      zegar(Nixie);
      
      // if(Nixie[1] - godzina_odtrucia != 0)
      // {
      //   opcja = 6;
      //   godzina_odtrucia = Nixie[1];
      // }
        
    break;

    case 1:
      startOpcja();
      ustawianieCzasu(Nixie);
      wrocDoZegara();
      
    break;

    case 2:

      temperaturaUstaw(Nixie);

    break;

    case 3:
      switch(p1)
      budzik(Nixie);

    break;

    case 6:

      odtruwanieLamp(Nixie);
      
    break;
    
    default:
      opcja = 0;
    break;
  }
}


void zegar(int C[])      //pobiera czas z modułu RTC oraz rozbija na cyfry
{ 
  dt = clock.GetDateTime();

  C[5]= dt.Second() %10;
  C[4]= dt.Second() /10;

  C[3]= dt.Minute() %10;
  C[2]= dt.Minute() /10;

  C[1]= dt.Hour() %10;
  C[0]= dt.Hour() /10;
  
}

void ustawianieCzasu(int C[])
{
  
}

void startOpcja()
{
  licznik_Menu = micros();
}
void wrocDoZegara()
{
  if (powrot <= micros() - licznik_Menu ) {
    opcja = 0;
  }
  
}

void temperaturaUstaw(int C[])
{
  temperatura = int(100*clock.GetTemperature().AsFloatDegC());

  C[0] = 10;
  C[1] = 10;
  C[2] = temperatura / 1000;
  C[3] = (temperatura / 100) % 10;
  C[4] = (temperatura / 10) % 10;
  C[5] = temperatura % 10;
}


void odtruwanieLamp(int C[])
{
  if(!czy_odtruwamy)
  {
    przemiatanie = micros();
    czy_odtruwamy = true;
  }

  randomSeed(analogRead(szum_przemiatnie));
  zegar(C);

  if (czas_Przemiecenia + licznik_przemiecen*(czas_Przemiecenia/10) <= micros() - przemiatanie)
  {
    licznik_przemiecen++;
    if(licznik_przemiecen >= 6)
    {
      opcja = 0;
      czy_odtruwamy = false;
      return;
    }
  }
  
  if( (6 - lampa ) - licznik_przemiecen >= 0)
    C[lampa -1] = random(10);
  
}