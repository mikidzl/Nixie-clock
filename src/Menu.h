#ifndef MENU_H
#define MENU_H

#include "Arduino.h"

enum Opcje
{
    zegar_,
    ustawianie_czasu,
    budzik_,
    termometr,
    odtruwanie_lampy,
    
    liczba_elementow
};

class Menu
{
  private:
    /* data */
  public:
    Opcje opcja;
    void nastepnaOpcja();
    Menu(/* args */);
    ~Menu();
};


#endif