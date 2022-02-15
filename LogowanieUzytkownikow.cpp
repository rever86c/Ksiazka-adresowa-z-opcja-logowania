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
using namespace std;

vector <Uzytkownik> rejestracja(vector <Uzytkownik> uzytkownicy)
{
    Uzytkownik nowyUzytkownik;
    cout<<"Podaj nazwe uzytkownika: ";
    cin>>nowyUzytkownik.nazwa;
    int i = 0;
    while(i<uzytkownicy.size())
    {
        if(uzytkownicy[i].nazwa == nowyUzytkownik.nazwa)
        {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika";
            cin >> nowyUzytkownik.nazwa;
            i =0;
        }
        else
        {
            i++;
        }

    }
    cout << "Podaj haslo: ";
    cin >> nowyUzytkownik.haslo;

    if(uzytkownicy.size()==0)
    {
        nowyUzytkownik.id =1;
    }
    else
    {
        nowyUzytkownik.id = uzytkownicy[uzytkownicy.size()-1].id+1;
    }
    uzytkownicy.push_back(nowyUzytkownik);
    cout<<"Konto zalozone"<<endl;
    Sleep(1000);
    return uzytkownicy;

}

int logowanie(vector <Uzytkownik> uzytkownicy)
{
    string nazwa, haslo;
    cout<<"Podaj nazwe: ";
    cin>>nazwa;
    int i = 0;
    while(i<uzytkownicy.size())
    {
        if(uzytkownicy[i].nazwa == nazwa)
        {
            for(int proba =0; proba < 3; proba++)
            {
                cout <<"Podaj haslo. Pozostalo prob "<<3-proba <<": "; ;
                cin>>haslo;
                if(uzytkownicy[i].haslo == haslo)
                {
                    cout<<"Zalogowales sie."<<endl;
                    Sleep(1000);
                    return uzytkownicy[i].id;

                }
            }
            cout<<"Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba"<<endl;
            Sleep(3000);
            return 0;
        }
        i++;

    }
    cout<<"Nie ma uzytkownika z takim logiem" <<endl;
    Sleep(2000);
    return 0;
}

vector <Uzytkownik> zmianaHasla(vector <Uzytkownik> uzytkownicy, int idZalogowanegoUzytkownika)
{
    string haslo;
    cout <<"Podaj nowe haslo: ";
    cin>>haslo;
    for(int i = 0; i < uzytkownicy.size(); i++)
    {
        if(uzytkownicy[i].id == idZalogowanegoUzytkownika)
        {
            uzytkownicy[i].haslo = haslo;
            cout <<"Haslo zostalo zmienieone" <<endl;
            Sleep(1500);
        }
    }
    return uzytkownicy;
}

void zapiszUzytkownikaWpliku(vector <Uzytkownik> uzytkownicy)
{
    fstream plikTekstowy;
    plikTekstowy.open("Uzytkownicy.txt", ios::out);
    if(plikTekstowy.good()==true)
    {
        for(int i =0; i<uzytkownicy.size(); i++)
        {
            plikTekstowy<<uzytkownicy[i].id<<"|";
            plikTekstowy<<uzytkownicy[i].nazwa<<"|";
            plikTekstowy<<uzytkownicy[i].haslo<<endl;
        }
        plikTekstowy.close();

    }
    else
    {
        cout<<"Nie mozna zapisac do pliku!"<<endl;
        plikTekstowy.close();
    }
}

Uzytkownik pobierzDaneZliniiDlaUzytkownika(string liniaUzytkownika)
{
    Uzytkownik daneUzytkownika;
    vector <string> rozdzieloneElementy;
    stringstream pobierz(liniaUzytkownika);
    string elementy;

    while(getline(pobierz, elementy,'|'))
    {
        rozdzieloneElementy.push_back(elementy);
    }

    istringstream (rozdzieloneElementy[0]) >> daneUzytkownika.id;
    daneUzytkownika.nazwa = rozdzieloneElementy[1];
    daneUzytkownika.haslo =rozdzieloneElementy[2];
    return daneUzytkownika;
}

vector <Uzytkownik> wczytajUzytkownikowZpliku()
{
    fstream listaUzytkownikow;
    listaUzytkownikow.open("Uzytkownicy.txt", ios::in);
    string liniaJednegoUzytkownika;
    vector <Uzytkownik> odczytaniUzytkownicy;
    if(listaUzytkownikow.good()==true)
    {
        while(getline(listaUzytkownikow,liniaJednegoUzytkownika))
        {
            odczytaniUzytkownicy.push_back(pobierzDaneZliniiDlaUzytkownika(liniaJednegoUzytkownika));
        }
        listaUzytkownikow.close();
    }
    return odczytaniUzytkownicy;
}
