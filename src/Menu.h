#ifndef MENU_H
#define MENU_H

#include "Arduino.h"
#include "Menu.h"
#include "przyciski.h"
#include "Opcje.h"

#include "zegarRTC.h"


class Menu
{
private:
  void stanPrzyciskow(Przycisk przycisk1, Przycisk przycisk2, Przycisk przycisk3);
  unsigned long licznik_Menu;
  unsigned long powrot;
  void wrocDoZegara(Przycisk przycisk2);
  void nastepnaOpcja();
  void poprzedniaOpcja();
  void zmianaOpcji(Przycisk doPrzodu, Przycisk doTylu);
  bool czyZmienicOpcje();

public:
  Opcje opcja;
  Menu();
  void program(int C[], zegarRTC Zegar, Przycisk przycisk1, Przycisk przycisk2, Przycisk przycisk3);
};

#endif