#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <windows.h>
using namespace std;

class Uzytkownik
{
    int id;
    string nazwa, haslo;

public:
    Uzytkownik(int = 0, string ="", string="");
    void pobierzDaneZliniiDlaUzytkownika(string liniaUzytkownika);

friend class ListaUzytkownikow;


};

class ListaUzytkownikow
{
    vector <Uzytkownik> lista;

public:
    ListaUzytkownikow();
    ~ListaUzytkownikow();
    void rejestracja();
    int logowanie();
    void zmianaHasla(int idZalogowanegoUzytkownika);
    void zapiszUzytkownikaWpliku();

};




