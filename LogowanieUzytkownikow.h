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

struct Uzytkownik
{
    int id;
    string nazwa, haslo;
};

vector <Uzytkownik> rejestracja(vector <Uzytkownik> uzytkownicy);
int logowanie(vector <Uzytkownik> uzytkownicy);
vector <Uzytkownik> zmianaHasla(vector <Uzytkownik> uzytkownicy, int idZalogowanegoUzytkownika);
void zapiszUzytkownikaWpliku(vector <Uzytkownik> uzytkownicy);
Uzytkownik pobierzDaneZliniiDlaUzytkownika(string liniaUzytkownika);
vector <Uzytkownik> wczytajUzytkownikowZpliku();
