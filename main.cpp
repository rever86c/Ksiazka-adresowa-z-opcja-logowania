#include <iostream>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <bits/stdc++.h>
#include <sstream>
#include <stdio.h>
#include "LogowanieUzytkownikow.h"
#include "KsiazkaAdresowa.h"
using namespace std;

int main()
{
    char wyborOpcji, wybor;
    int idZalogowanegoUzytkownika = 0;
    vector <Kontakt> kontaktyWksiazce;
    vector <Uzytkownik> uzytkownicy = wczytajUzytkownikowZpliku();
    while(1)
    {
        if(idZalogowanegoUzytkownika == 0)
        {
            system("cls");
            cout<<"1. Logowanie"<<endl;
            cout<<"2. Rejestracja"<<endl;
            cout<<"9. Zamknij program"<<endl;
            wybor=getch();

            switch(wybor)
            {
            case '1':
                idZalogowanegoUzytkownika = logowanie(uzytkownicy);
                kontaktyWksiazce = wczytajKontaktyZplikuZalogowanego(idZalogowanegoUzytkownika);
                break;
            case '2':
                uzytkownicy = rejestracja(uzytkownicy);
                zapiszUzytkownikaWpliku(uzytkownicy);
                oczekiwanieNaEnter();
                break;
            case '9':
                exit(0);
            }
        }
        else
        {
            system("cls");
            cout<<"1. Dodaj adresata."<<endl;
            cout<<"2. Wyszukaj po imieniu."<<endl;
            cout<<"3. Wyszukaj po nazwisku."<<endl;
            cout<<"4. Wyswietl wszystkich adresatow."<<endl;
            cout<<"5. Usun adresata."<<endl;
            cout<<"6. Edytuj adresata."<<endl;
            cout<<"7. Zmien haslo."<<endl;
            cout<<"9. Wyloguj sie."<<endl;
            wyborOpcji = getch();

            switch(wyborOpcji)
            {
            case '1':
                system("cls");
                kontaktyWksiazce=dodajNowyKontaktWPliku(kontaktyWksiazce, idZalogowanegoUzytkownika);
                oczekiwanieNaEnter();
                break;
            case '2':
                system("cls");
                wyszukajPoImieniu(kontaktyWksiazce);
                oczekiwanieNaEnter();
                break;
            case '3':
                system("cls");
                wyszukajPoNazwisku(kontaktyWksiazce);
                oczekiwanieNaEnter();
                break;
            case '4':
                system("cls");
                wyswietlWszystkieKontakty(kontaktyWksiazce);
                oczekiwanieNaEnter();
                break;
            case '5':
                system("cls");
                kontaktyWksiazce= usunKontakt(kontaktyWksiazce);
                oczekiwanieNaEnter();
                break;
            case '6':
                system("cls");
                kontaktyWksiazce= edytujKontakt(kontaktyWksiazce);
                oczekiwanieNaEnter();
                break;
            case '7':
                system("cls");
                uzytkownicy = zmianaHasla(uzytkownicy, idZalogowanegoUzytkownika);
                zapiszUzytkownikaWpliku(uzytkownicy);
                oczekiwanieNaEnter();
                break;
            case '9':
                idZalogowanegoUzytkownika =0;
                system("cls");
                break;
            }
        }
    }
    return 0;
}
