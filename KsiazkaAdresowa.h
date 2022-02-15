#include <iostream>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <bits/stdc++.h>
#include <sstream>
#include <stdio.h>

using namespace std;

struct Kontakt
{
    int kontaktID;
    int idUzytkownika;
    string imie;
    string nazwisko;
    string nrTelefonu;
    string eMail;
    string adresZamieszkania;
};

void wyswietlWszystkieKontakty(vector <Kontakt> ksiazkaAdresowa);
Kontakt pobierzDaneZlinii(string liniaKontaktu);
bool czyKsiazkaAdresowaIstnieje();
bool czyKsiazkaAdresowaMaZawartosc();
Kontakt wprowadzDaneNowegoKontaktu();
void stworzPlikIZapiszNowyKontakt(Kontakt nowyKontakt);
Kontakt dodajKontaktDoIstniejacychWPliku(Kontakt nowyKontakt, int idZalogowanegoUzytkownika);
vector <Kontakt> dodajNowyKontaktWPliku(vector <Kontakt> ksiazkaAdresowa, int idZalogowanegoUzytkownika);
bool sprawdzCzyImieWystepuje(vector<Kontakt> ksiazkaAdresowa, string imie);
void wyszukajPoImieniu(vector <Kontakt> ksiazkaAdresowa);
bool sprawdzCzyNazwiskoWystepuje(vector <Kontakt> ksiazkaAdresowa, string nazwisko);
void wyszukajPoNazwisku(vector <Kontakt> ksiazkaAdresowa);
bool zapytajCzyUsunacKontakt();
void usunKontaktZpliku(int idKontaktuDoUsuniecia);
vector <Kontakt> usunKontakt(vector <Kontakt> ksiazkaAdresowa);
vector <Kontakt> edytujImie(vector <Kontakt> ksiazkaAdresowa, int idKontaktuDoEdycji);
vector <Kontakt> edytujNazwisko(vector <Kontakt> ksiazkaAdresowa, int idKontaktuDoEdycji);
vector <Kontakt> edytujTelefon(vector <Kontakt> ksiazkaAdresowa, int idKontaktuDoEdycji);
vector <Kontakt> edytujMaila(vector <Kontakt> ksiazkaAdresowa, int idKontaktuDoEdycji);
vector <Kontakt> edytujAdres(vector <Kontakt> ksiazkaAdresowa, int idKontaktuDoEdycji);
int pozycjaElementuWwektorze(int idKontakt, vector <Kontakt> ksiazkaAdresowa);
void edytujKontaktwPliku(int idKontaktuDoEdycji, vector <Kontakt> ksiazkaAdresowa);
vector <Kontakt> edytujKontakt(vector <Kontakt> ksiazkaAdresowa);
void oczekiwanieNaEnter();
vector <Kontakt> wczytajKontaktyZplikuZalogowanego(int idZalogowanegoUzytkownika);
