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

void Menu::wrocDoZegara(Przycisk przycisk1, Przycisk przycisk2, Przycisk przycisk3)
{
    if (przycisk1.stan != wylaczony || przycisk2.stan != wylaczony || przycisk3.stan != wylaczony)
        licznik_Menu = micros();
    if (powrot <= micros() - licznik_Menu || przycisk2.stan == dlugieWcisniecie)
    {
        opcja = zegar_;
    }
}

void Menu::program(int C[], zegarRTC Zegar, Przycisk przycisk1, Przycisk przycisk2, Przycisk przycisk3)
{
    switch (opcja)
    {
    case zegar_:
        switch (przycisk1.stan)
        {
        case krotkieWcisniecie:
            opcja = termometr;
            
            break;

        case dlugieWcisniecie:
            
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

        break;

    case termometr:

        Zegar.temperaturaUstaw(C);

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
    if(opcja != zegar_)
        wrocDoZegara(przycisk1, przycisk2, przycisk3);

}

void jasnosc()
{
//   if (przycisk1.stan == krotkieWcisniecie)
//   {
//     if (nixie.jasnosc < 84)
//       nixie.jasnosc += 15;
//     przycisk1.zerujPrzycisk();
//   }
//   else if (przycisk1.stan == dlugieWcisniecie)
//   {
//       nixie.jasnosc = 5;
//     przycisk1.zerujPrzycisk();
//   }
//   if (przycisk2.stan == krotkieWcisniecie)
//   {
//     if (nixie.jasnosc > 16)
//       nixie.jasnosc += -15;
//     przycisk2.zerujPrzycisk();
//   }
//   else if (przycisk2.stan == dlugieWcisniecie)
//   {
//     if (nixie.jasnosc > 21)
//       nixie.jasnosc += -10;
//     przycisk2.zerujPrzycisk();
//   }
}

