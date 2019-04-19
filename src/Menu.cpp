#include "Menu.h"

Menu::Menu()
{
    opcja = zegar_;
}

void Menu::nastepnaOpcja()
{
    opcja = static_cast<Opcje>(opcja + 1);
    if (opcja == liczba_elementow)
    {
        opcja = zegar_;
    }
}
