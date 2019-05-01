#include "Menu.h"

Menu::Menu()
{
    opcja = zegar_;
    powrot = 7500000;
}

void Menu::nastepnaOpcja()
{
    opcja = static_cast<Opcje>(opcja + 1);
    if (opcja == liczba_elementow)
    {
        opcja = zegar_;
    }
}

void Menu::startOpcja(Przycisk przycisk1, Przycisk przycisk2, Przycisk przycisk3)
{
    if (przycisk1.stan != wylaczony || przycisk2.stan != wylaczony || przycisk3.stan != wylaczony)
        licznik_Menu = micros();
}
void Menu::wrocDoZegara(Przycisk przycisk2)
{
    if (powrot <= micros() - licznik_Menu || przycisk2.stan == dlugieWcisniecie)
    {
        opcja = zegar_;
    }
}

void Menu::menu(int C[], zegarRTC Zegar, Przycisk przycisk1, Przycisk przycisk2, Przycisk przycisk3)
{
    switch (opcja)
    {
    case zegar_:
        switch (przycisk1.stan)
        {
        case krotkieWcisniecie:
            opcja = termometr;
            startOpcja(przycisk1, przycisk2, przycisk3);
            break;

        case dlugieWcisniecie:
            startOpcja(przycisk1, przycisk2, przycisk3);
            opcja = ustawianie_czasu;
            break;
        }

        Zegar.zegar(C);

        // if (tablica_Nixie[1] - godzina_odtrucia != 0)
        // {
        //   opcja = odtruwanie_lampy;
        //   godzina_odtrucia = tablica_Nixie[1];
        // }

        break;

    case ustawianie_czasu:

        Zegar.ustawianieCzasu(C, przycisk1, przycisk2, przycisk3);
        wrocDoZegara(przycisk2);

        break;

    case termometr:

        Zegar.temperaturaUstaw(C);
        wrocDoZegara(przycisk2);

        break;

    case budzik_:
        //switch(p1)
        //Zegar.budzik(tablica_Nixie);

        break;

    case odtruwanie_lampy:

        //odtruwanieLamp(tablica_Nixie);

        break;

    default:
        opcja = zegar_;
        break;
    }
}