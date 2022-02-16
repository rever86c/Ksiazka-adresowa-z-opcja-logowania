#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <windows.h>
#include "LogowanieUzytkownikow.h"
using namespace std;

Uzytkownik::Uzytkownik(int i, string n, string h )
{
    id =i;
    nazwa = n;
    haslo = h;
}

void Uzytkownik::pobierzDaneZliniiDlaUzytkownika(string liniaUzytkownika)
{
    vector <string> rozdzieloneElementy;
    stringstream pobierz(liniaUzytkownika);
    string elementy;

    while(getline(pobierz, elementy,'|'))
    {
        rozdzieloneElementy.push_back(elementy);
    }

    istringstream (rozdzieloneElementy[0]) >> id;
    nazwa = rozdzieloneElementy[1];
    haslo =rozdzieloneElementy[2];
}

ListaUzytkownikow::ListaUzytkownikow()
{
    fstream listaUzytkownikow;
    listaUzytkownikow.open("Uzytkownicy.txt", ios::in);
    string liniaJednegoUzytkownika;

    Uzytkownik uzytkownik1;
    if(listaUzytkownikow.good()==true)
    {
        while(getline(listaUzytkownikow,liniaJednegoUzytkownika))
        {
            uzytkownik1.pobierzDaneZliniiDlaUzytkownika(liniaJednegoUzytkownika);
            lista.push_back(uzytkownik1);
        }
        listaUzytkownikow.close();
    }
}

ListaUzytkownikow::~ListaUzytkownikow()
{
    zapiszUzytkownikaWpliku();
    cout<<"W tym momencie powinien zadzialac destruktor"<<endl;
}


void ListaUzytkownikow::rejestracja()
{
    Uzytkownik nowyUzytkownik;
    cout<<"Podaj nazwe uzytkownika: ";
    cin>>nowyUzytkownik.nazwa;
    int i = 0;
    while(i<lista.size())
    {
        if(lista[i].nazwa == nowyUzytkownik.nazwa)
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

    if(lista.size()==0)
    {
        nowyUzytkownik.id =1;
    }
    else
    {
        nowyUzytkownik.id = lista[lista.size()-1].id+1;
    }
    lista.push_back(nowyUzytkownik);
    cout<<"Konto zalozone"<<endl;
    Sleep(1000);
}

int ListaUzytkownikow::logowanie()
{
    string nazwa, haslo;
    cout<<"Podaj nazwe: ";
    cin>>nazwa;
    int i = 0;
    while(i<lista.size())
    {
        if(lista[i].nazwa == nazwa)
        {
            for(int proba =0; proba < 3; proba++)
            {
                cout <<"Podaj haslo. Pozostalo prob "<<3-proba <<": "; ;
                cin>>haslo;
                if(lista[i].haslo == haslo)
                {
                    cout<<"Zalogowales sie."<<endl;
                    Sleep(1000);
                    return lista[i].id;
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

void ListaUzytkownikow::zmianaHasla(int idZalogowanegoUzytkownika)
{
    string haslo;
    cout <<"Podaj nowe haslo: ";
    cin>>haslo;
    for(int i = 0; i < lista.size(); i++)
    {
        if(lista[i].id == idZalogowanegoUzytkownika)
        {
            lista[i].haslo = haslo;
            cout <<"Haslo zostalo zmienieone" <<endl;
            Sleep(1500);
        }
    }
}

void ListaUzytkownikow::zapiszUzytkownikaWpliku()
{
    fstream plikTekstowy;
    plikTekstowy.open("Uzytkownicy.txt", ios::out);
    if(plikTekstowy.good()==true)
    {
        for(int i =0; i<lista.size(); i++)
        {
            plikTekstowy<<lista[i].id<<"|";
            plikTekstowy<<lista[i].nazwa<<"|";
            plikTekstowy<<lista[i].haslo<<endl;
        }
        plikTekstowy.close();

    }
    else
    {
        cout<<"Nie mozna zapisac do pliku!"<<endl;
        plikTekstowy.close();
    }
}

