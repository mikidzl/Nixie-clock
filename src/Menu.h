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
  /* data */
public:
  Opcje opcja;
  unsigned long licznik_Menu;
  unsigned long powrot;
  void wrocDoZegara(Przycisk przycisk1, Przycisk przycisk2, Przycisk przycisk3);

  void nastepnaOpcja();
  Menu(/* args */);
  void menu(int C[], zegarRTC, Przycisk przycisk1, Przycisk przycisk2, Przycisk przycisk3);
};

#endif