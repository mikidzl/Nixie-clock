#include "Menu.h"

Menu::Menu()
{
    opcja = zegar_;
    powrot = 7500000;
}

void Menu::nastepnaOpcja()
{
    opcja = static_cast<Opcje>(opcja + 1);
    if (opcja == koniec)
    {
        opcja = zegar_;
    }
}

void Menu::poprzedniaOpcja()
{
    if (opcja == zegar_)
    {
        opcja = koniec;
    }
    opcja = static_cast<Opcje>(opcja - 1);
}

void Menu::zmianaOpcji(Przycisk doPrzodu, Przycisk doTylu)
{
    if (czyZmienicOpcje())
    {
        if(doPrzodu.stan == krotkieWcisniecie)
            nastepnaOpcja();

        if(doTylu.stan == krotkieWcisniecie)
            poprzedniaOpcja();  
    }    
}

bool Menu::czyZmienicOpcje()
{
    if(opcja == ustawianie_czasu)
        return false;
    else
        return true;      
}

void Menu::stanPrzyciskow(Przycisk przycisk1, Przycisk przycisk2, Przycisk przycisk3)
{
    if (przycisk1.stan != wylaczony || przycisk2.stan != wylaczony || przycisk3.stan != wylaczony)
        licznik_Menu = micros();
}

void Menu::wrocDoZegara(Przycisk przycisk2)
{  
    if ((powrot <= micros() - licznik_Menu || przycisk2.stan == dlugieWcisniecie) && opcja != zegar_)
    {
        opcja = zegar_;
    }
}

void Menu::program(int C[], zegarRTC Zegar, Przycisk przycisk1, Przycisk przycisk2, Przycisk przycisk3)
{
    stanPrzyciskow(przycisk1, przycisk2, przycisk3);

    zmianaOpcji(przycisk1, przycisk3);

    switch (opcja)
    {
    case zegar_:

        if(przycisk2.stan == dlugieWcisniecie)
        {
            opcja = ustawianie_czasu;
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

    case data:

        Zegar.data(C);
        wrocDoZegara(przycisk2);

        break;


    case budzik_:
        //switch(p1)
        //Zegar.budzik(tablica_Nixie);

        break;

    case odtruwanie_lampy:

        //odtruwanieLamp(tablica_Nixie);
        wrocDoZegara(przycisk2);

        break;

    default:
        opcja = zegar_;
        break;
    }

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

