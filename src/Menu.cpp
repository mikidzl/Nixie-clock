#include "Menu.h"

Menu::Menu()
{
    option = clock;
    powrot = 7500000;
}

void Menu::program(int C[], zegarRTC& Zegar, Przycisk przycisk1, Przycisk przycisk2, Przycisk przycisk3)
{
    stanPrzyciskow(przycisk1, przycisk2, przycisk3);

    changingOption(przycisk1, przycisk3);

    switch (option)
    {
    case clock:

        Zegar.clock(C);

        if (przycisk2.stan == dlugieWcisniecie)
        {
            option = settingTime;
        }
        // if (tablica_Nixie[1] - godzina_odtrucia != 0)
        // {
        //   option = odtruwanie_lampy;
        //   godzina_odtrucia = tablica_Nixie[1];
        // }

        break;

    case settingTime:

        Zegar.setTime(C, przycisk1, przycisk2, przycisk3);

        wrocDoZegara(przycisk2);
        break;

    case thermometer:

        Zegar.thermometer(C);
        wrocDoZegara(przycisk2);
        break;

    case date:

        Zegar.date(C);

        if(przycisk2.stan == dlugieWcisniecie)
            option = settingDate;

        wrocDoZegara(przycisk2);

        break;

    case settingDate:

        Zegar.setDate(C, przycisk1, przycisk2, przycisk3);

        if(przycisk2.stan == dlugieWcisniecie)
            option = date;

        wrocDoZegara(przycisk2);

        break;

    case stoper:

        Zegar.stoper(C, przycisk2);

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
        option = clock;
        break;
    }

}

void Menu::nextOption()
{
    option = static_cast<Opcje>(option + 1);
    if (option == koniec)
    {
        option = clock;
    }
}

void Menu::previousOption()
{
    if (option == clock)
    {
        option = koniec;
    }
    option = static_cast<Opcje>(option - 1);
}

void Menu::changingOption(Przycisk doPrzodu, Przycisk doTylu)
{
    if (czyZmienicOpcje())
    {
        if(doPrzodu.stan == krotkieWcisniecie)
            nextOption();

        if(doTylu.stan == krotkieWcisniecie)
            previousOption();  
    }    
}

bool Menu::czyZmienicOpcje()
{
    if(option == settingTime || option == settingDate)
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
    if ((powrot <= micros() - licznik_Menu) && option != clock)
    {
        option = clock;
    }
    else if(option == settingTime && przycisk2.stan == dlugieWcisniecie)
    {
        option = clock;
    }
    else if(option == settingDate && przycisk2.stan == dlugieWcisniecie)
    {
        option = date;
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

