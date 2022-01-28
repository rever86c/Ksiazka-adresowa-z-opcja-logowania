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

struct Uzytkownik
{
    int id;
    string nazwa, haslo;
};

void wyswietlWszystkieKontakty(vector <Kontakt> ksiazkaAdresowa)
{
    for(int i = 0; i <ksiazkaAdresowa.size(); i++ )
    {
        cout<< ksiazkaAdresowa[i].kontaktID <<". "<< ksiazkaAdresowa[i].imie <<", "<< ksiazkaAdresowa[i].nazwisko <<", ";
        cout<< ksiazkaAdresowa[i].nrTelefonu <<", "<< ksiazkaAdresowa[i].eMail <<", "<< ksiazkaAdresowa[i].adresZamieszkania <<endl;

    }
}

Kontakt pobierzDaneZlinii(string liniaKontaktu)
{
    Kontakt daneKontaktu;
    vector <string> rozdzieloneElementy;
    stringstream pobierz(liniaKontaktu);
    string elementy;
    while(getline(pobierz, elementy,'|'))
    {
        rozdzieloneElementy.push_back(elementy);
    }
    istringstream (rozdzieloneElementy[0]) >> daneKontaktu.kontaktID;
    istringstream(rozdzieloneElementy[1]) >> daneKontaktu.idUzytkownika;
    daneKontaktu.imie = rozdzieloneElementy[2];
    daneKontaktu.nazwisko =rozdzieloneElementy[3];
    daneKontaktu.nrTelefonu = rozdzieloneElementy[4];
    daneKontaktu.eMail = rozdzieloneElementy[5];
    daneKontaktu.adresZamieszkania = rozdzieloneElementy[6];
    return daneKontaktu;
}

bool czyKsiazkaAdresowaIstnieje()
{
    bool ksiazkaAdresowaIstnieje = false;
    ifstream czyPlikIstnieje("ksiazkaAdresowa.txt");
    if(czyPlikIstnieje) {ksiazkaAdresowaIstnieje = true;}
    else    {ksiazkaAdresowaIstnieje = false;}
    czyPlikIstnieje.close();
    return ksiazkaAdresowaIstnieje;
}

bool czyKsiazkaAdresowaMaZawartosc()
{
    bool ksiazkaAdresowaJestPoprawna = false;
    string liniaJednegoKontaktu;
    fstream ksiazka;
    ksiazka.open("ksiazkaAdresowa.txt", ios::in);
    getline(ksiazka,liniaJednegoKontaktu);
    if(liniaJednegoKontaktu.size()>0)   {ksiazkaAdresowaJestPoprawna = true;}
    else    {ksiazkaAdresowaJestPoprawna = false;}
    ksiazka.close();
    return ksiazkaAdresowaJestPoprawna;
}

Kontakt wprowadzDaneNowegoKontaktu()
{
    Kontakt nowyKontakt;
    cout<< "Podaj Imie nowego kontaktu: ";
    getline(cin,nowyKontakt.imie);
    cout<< "Podaj Nazwisko nowego kontaktu: ";
    getline(cin,nowyKontakt.nazwisko);
    cout<< "Podaj numer telefonu nowego kontaktu: ";
    getline(cin,nowyKontakt.nrTelefonu);
    cout<< "Podaj eMail nowego kontaktu: ";
    getline(cin,nowyKontakt.eMail);
    cout<< "Podaj adres zamieszkania nowego kontaktu: ";
    getline(cin,nowyKontakt.adresZamieszkania);
    return nowyKontakt;
}

void stworzPlikIZapiszNowyKontakt(Kontakt nowyKontakt)
{
    fstream plikTekstowy;
    plikTekstowy.open("ksiazkaAdresowa.txt", ios::out);
    plikTekstowy<<nowyKontakt.kontaktID<<"|"<<nowyKontakt.idUzytkownika<<"|"<<nowyKontakt.imie<<"|"<<nowyKontakt.nazwisko<<"|";
    plikTekstowy<<nowyKontakt.nrTelefonu<<"|"<<nowyKontakt.eMail<<"|"<<nowyKontakt.adresZamieszkania<<endl;
    plikTekstowy.close();
}

Kontakt dodajKontaktDoIstniejacychWPliku(Kontakt nowyKontakt, int idZalogowanegoUzytkownika)
{
    fstream ksiazka;
    ksiazka.open("ksiazkaAdresowa.txt", ios::in);
    string liniaJednegoKontaktu;
    vector <Kontakt> odczytaneKontakty;
    Kontakt odczytanaLinia;
    fstream plikTekstowy;
    plikTekstowy.open("ksiazkaAdresowaTymczasowa.txt", ios::out);
    int nowyKontaktID = 0;

    while(getline(ksiazka,liniaJednegoKontaktu))
    {
        odczytanaLinia = pobierzDaneZlinii(liniaJednegoKontaktu);
        plikTekstowy<<odczytanaLinia.kontaktID<<"|"<<odczytanaLinia.idUzytkownika<<"|"<<odczytanaLinia.imie<<"|"<<odczytanaLinia.nazwisko<<"|";
        plikTekstowy<<odczytanaLinia.nrTelefonu<<"|"; plikTekstowy<<odczytanaLinia.eMail<<"|"<<odczytanaLinia.adresZamieszkania<<endl;
        nowyKontaktID = odczytanaLinia.kontaktID;
    }
    nowyKontakt.idUzytkownika = idZalogowanegoUzytkownika;
    nowyKontakt.kontaktID = nowyKontaktID+1;
    plikTekstowy<<nowyKontakt.kontaktID<<"|"<<nowyKontakt.idUzytkownika<<"|"<<nowyKontakt.imie<<"|"<<nowyKontakt.nazwisko<<"|";
    plikTekstowy<<nowyKontakt.nrTelefonu<<"|"<<nowyKontakt.eMail<<"|"<<nowyKontakt.adresZamieszkania<<endl;
    ksiazka.close();
    plikTekstowy.close();
    remove( "ksiazkaAdresowa.txt" );
    rename( "ksiazkaAdresowaTymczasowa.txt", "ksiazkaAdresowa.txt");
    return nowyKontakt;
}

vector <Kontakt> dodajNowyKontaktWPliku(vector <Kontakt> ksiazkaAdresowa, int idZalogowanegoUzytkownika)
{
    Kontakt nowyKontakt;
    nowyKontakt = wprowadzDaneNowegoKontaktu();
    if(czyKsiazkaAdresowaIstnieje() && czyKsiazkaAdresowaMaZawartosc())
    {
            nowyKontakt=dodajKontaktDoIstniejacychWPliku(nowyKontakt, idZalogowanegoUzytkownika);
    }
    else
    {
        nowyKontakt.kontaktID = 1;
        nowyKontakt.idUzytkownika = idZalogowanegoUzytkownika;
        stworzPlikIZapiszNowyKontakt(nowyKontakt);
    }
    ksiazkaAdresowa.push_back(nowyKontakt);
    return ksiazkaAdresowa;
}

bool sprawdzCzyImieWystepuje(vector<Kontakt> ksiazkaAdresowa, string imie)
{
    int liczbaKontaktowZtymImieniem=0;
    bool imieWystepuje = false;
    for(int i =0; i<ksiazkaAdresowa.size(); i++)
    {
        if(ksiazkaAdresowa[i].imie == imie)
        {
            liczbaKontaktowZtymImieniem++;
        }
    }

    if(liczbaKontaktowZtymImieniem>0)
    {
        imieWystepuje=true;
    }

    return imieWystepuje;
}

void wyszukajPoImieniu(vector <Kontakt> ksiazkaAdresowa)
{
    cout<<"Wprowadz wyszukiwane imie: ";
    string wyszukiwaneImie;
    getline(cin, wyszukiwaneImie);

    if(sprawdzCzyImieWystepuje(ksiazkaAdresowa,wyszukiwaneImie))
    {
        for(int i =0; i<ksiazkaAdresowa.size(); i++)
        {
            if(ksiazkaAdresowa[i].imie == wyszukiwaneImie)
            {
                cout<< ksiazkaAdresowa[i].kontaktID <<". "<< ksiazkaAdresowa[i].imie <<", "<< ksiazkaAdresowa[i].nazwisko <<", ";
                cout<< ksiazkaAdresowa[i].nrTelefonu <<", "<< ksiazkaAdresowa[i].eMail <<", "<< ksiazkaAdresowa[i].adresZamieszkania <<endl;
            }
        }
    }
    else
    {
        cout<<"Brak kontaktow o takim imieniu"<<endl;
    }
}

bool sprawdzCzyNazwiskoWystepuje(vector <Kontakt> ksiazkaAdresowa, string nazwisko)
{
    int liczbaKontaktowZtymNazwiskiem=0;
    bool nazwiskoWystepuje = false;
    for(int i =0; i<ksiazkaAdresowa.size(); i++)
    {
        if(ksiazkaAdresowa[i].nazwisko == nazwisko)
        {
            liczbaKontaktowZtymNazwiskiem++;
        }
    }

    if(liczbaKontaktowZtymNazwiskiem>0)
    {
        nazwiskoWystepuje=true;
    }

    return nazwiskoWystepuje;
}

void wyszukajPoNazwisku(vector <Kontakt> ksiazkaAdresowa)
{
    cout<<"Wprowadz wyszukiwane nazwisko: ";
    string wyszukiwaneNazwisko;
    getline(cin, wyszukiwaneNazwisko);

    if(sprawdzCzyNazwiskoWystepuje(ksiazkaAdresowa,wyszukiwaneNazwisko))
    {
        for(int i =0; i<ksiazkaAdresowa.size(); i++)
        {
            if(ksiazkaAdresowa[i].nazwisko == wyszukiwaneNazwisko)
            {
                cout<< ksiazkaAdresowa[i].kontaktID <<". "<< ksiazkaAdresowa[i].imie <<", "<< ksiazkaAdresowa[i].nazwisko <<", ";
                cout<< ksiazkaAdresowa[i].nrTelefonu <<", "<< ksiazkaAdresowa[i].eMail <<", "<< ksiazkaAdresowa[i].adresZamieszkania <<endl;
            }
        }
    }
    else
    {
        cout<<"Brak kontaktow o takim nazwisku"<<endl;
    }
}

bool zapytajCzyUsunacKontakt()
{
    system("cls");
    bool czyUsunac = false;
    cout<<"Aby potwierdzic usuniecie kontaktu nacisnij t "<<endl;
    char wyborOpcji = getch();
    if(wyborOpcji=='t')
    {
        czyUsunac=true;
        cout<<"Kontakt zostal usuniety!"<<endl;
    }
    return czyUsunac;
}

void usunKontaktZpliku(int idKontaktuDoUsuniecia)
{
    fstream ksiazka;
    ksiazka.open("ksiazkaAdresowa.txt", ios::in);
    string liniaJednegoKontaktu;
    vector <Kontakt> odczytaneKontakty;
    Kontakt odczytanaLinia;
    fstream plikTekstowy;
    plikTekstowy.open("ksiazkaAdresowaTymczasowa.txt", ios::out);
    while(getline(ksiazka,liniaJednegoKontaktu))
    {
        odczytanaLinia = pobierzDaneZlinii(liniaJednegoKontaktu);
        if(odczytanaLinia.kontaktID != idKontaktuDoUsuniecia)
        {
            plikTekstowy<<odczytanaLinia.kontaktID<<"|"<<odczytanaLinia.idUzytkownika<<"|"<<odczytanaLinia.imie<<"|";
            plikTekstowy<<odczytanaLinia.nazwisko<<"|"<<odczytanaLinia.nrTelefonu<<"|"<<odczytanaLinia.eMail<<"|";
            plikTekstowy<<odczytanaLinia.adresZamieszkania<<endl;
        }
    }
    ksiazka.close();
    plikTekstowy.close();
    remove( "ksiazkaAdresowa.txt" );
    rename( "ksiazkaAdresowaTymczasowa.txt", "ksiazkaAdresowa.txt");
}

vector <Kontakt> usunKontakt(vector <Kontakt> ksiazkaAdresowa)
{
    int idKontaktuDoUsuniecia;
    cout<<"Wprowadz numer ID kontakt ktory chcesz usunac: ";
    cin>> idKontaktuDoUsuniecia;
    cin.ignore( std::numeric_limits < std::streamsize >::max(), '\n' );
    int pozycjaKontaktuDoUsuniecia;
    bool kontaktDoUsunieciaZnaleziony = false;
    for(int i =0; i <ksiazkaAdresowa.size(); i++)
    {
        if(ksiazkaAdresowa[i].kontaktID == idKontaktuDoUsuniecia)
        {
            pozycjaKontaktuDoUsuniecia = i;
            kontaktDoUsunieciaZnaleziony = true;
            break;
        }
    }
    if(kontaktDoUsunieciaZnaleziony)
    {
        if(zapytajCzyUsunacKontakt())
        {
            vector <Kontakt> ::iterator wskaznikDoElementuDoUsuniecia = ksiazkaAdresowa.begin() + pozycjaKontaktuDoUsuniecia;
            ksiazkaAdresowa.erase(wskaznikDoElementuDoUsuniecia);
        }
        usunKontaktZpliku(idKontaktuDoUsuniecia);
    }
    else
    {
        cout<<"Nie ma takiego ID kontaktu!"<<endl;
        Sleep(1000);
    }
    return ksiazkaAdresowa;
}

vector <Kontakt> edytujImie(vector <Kontakt> ksiazkaAdresowa, int idKontaktuDoEdycji)
{
    cout<<"Wprowadz nowe imie: ";
    string noweImie;
    getline(cin, noweImie);

    for(int i =0; i <ksiazkaAdresowa.size(); i++)
    {
        if(ksiazkaAdresowa[i].kontaktID == idKontaktuDoEdycji)
        {
            ksiazkaAdresowa[i].imie = noweImie;
            break;
        }
    }
    return ksiazkaAdresowa;
}

vector <Kontakt> edytujNazwisko(vector <Kontakt> ksiazkaAdresowa, int idKontaktuDoEdycji)
{
    cout<<"Wprowadz nowe nazwisko: ";
    string noweNazwisko;
    getline(cin, noweNazwisko);

    for(int i =0; i <ksiazkaAdresowa.size(); i++)
    {
        if(ksiazkaAdresowa[i].kontaktID == idKontaktuDoEdycji)
        {
            ksiazkaAdresowa[i].nazwisko = noweNazwisko;
            break;
        }
    }
    return ksiazkaAdresowa;
}

vector <Kontakt> edytujTelefon(vector <Kontakt> ksiazkaAdresowa, int idKontaktuDoEdycji)
{
    cout<<"Wprowadz nowy numer telefonu: ";
    string nowyTelefon;
    getline(cin, nowyTelefon);

    for(int i =0; i <ksiazkaAdresowa.size(); i++)
    {
        if(ksiazkaAdresowa[i].kontaktID == idKontaktuDoEdycji)
        {
            ksiazkaAdresowa[i].nrTelefonu = nowyTelefon;
            break;
        }
    }
    return ksiazkaAdresowa;
}

vector <Kontakt> edytujMaila(vector <Kontakt> ksiazkaAdresowa, int idKontaktuDoEdycji)
{
    cout<<"Wprowadz nowy adres Email: ";
    string nowyMail;
    getline(cin, nowyMail);

    for(int i =0; i <ksiazkaAdresowa.size(); i++)
    {
        if(ksiazkaAdresowa[i].kontaktID == idKontaktuDoEdycji)
        {
            ksiazkaAdresowa[i].eMail = nowyMail;
            break;
        }
    }
    return ksiazkaAdresowa;
}

vector <Kontakt> edytujAdres(vector <Kontakt> ksiazkaAdresowa, int idKontaktuDoEdycji)
{
    cout<<"Wprowadz nowy adres: ";
    string nowyAdres;
    getline(cin, nowyAdres);

    for(int i =0; i <ksiazkaAdresowa.size(); i++)
    {
        if(ksiazkaAdresowa[i].kontaktID == idKontaktuDoEdycji)
        {
            ksiazkaAdresowa[i].adresZamieszkania = nowyAdres;
            break;
        }
    }
    return ksiazkaAdresowa;
}

int pozycjaElementuWwektorze(int idKontakt, vector <Kontakt> ksiazkaAdresowa)
{
    int i = 0;
    while(idKontakt != ksiazkaAdresowa[i].kontaktID)
    {
        i++;
    }
    return i;
}

void edytujKontaktwPliku(int idKontaktuDoEdycji, vector <Kontakt> ksiazkaAdresowa)
{
    fstream ksiazka;
    ksiazka.open("ksiazkaAdresowa.txt", ios::in);
    string liniaJednegoKontaktu;
    vector <Kontakt> odczytaneKontakty;
    Kontakt odczytanaLinia;
    fstream plikTekstowy;
    plikTekstowy.open("ksiazkaAdresowaTymczasowa.txt", ios::out);
    int pozycjaWwektorze =pozycjaElementuWwektorze(idKontaktuDoEdycji, ksiazkaAdresowa);

    while(getline(ksiazka,liniaJednegoKontaktu))
    {
        odczytanaLinia = pobierzDaneZlinii(liniaJednegoKontaktu);

        if(odczytanaLinia.kontaktID != idKontaktuDoEdycji)
        {
            plikTekstowy<<odczytanaLinia.kontaktID<<"|"<<odczytanaLinia.idUzytkownika<<"|"<<odczytanaLinia.imie<<"|";
            plikTekstowy<<odczytanaLinia.nazwisko<<"|"<<odczytanaLinia.nrTelefonu<<"|"<<odczytanaLinia.eMail<<"|";
            plikTekstowy<<odczytanaLinia.adresZamieszkania<<endl;

        }
        else
        {
            plikTekstowy<<ksiazkaAdresowa[pozycjaWwektorze].kontaktID<<"|"<<ksiazkaAdresowa[pozycjaWwektorze].idUzytkownika<<"|";
            plikTekstowy<<ksiazkaAdresowa[pozycjaWwektorze].imie<<"|"<<ksiazkaAdresowa[pozycjaWwektorze].nazwisko<<"|";
            plikTekstowy<<ksiazkaAdresowa[pozycjaWwektorze].nrTelefonu<<"|"<<ksiazkaAdresowa[pozycjaWwektorze].eMail<<"|";
            plikTekstowy<<ksiazkaAdresowa[pozycjaWwektorze].adresZamieszkania<<endl;
        }
    }
    ksiazka.close();
    plikTekstowy.close();

    remove( "ksiazkaAdresowa.txt" );
    rename( "ksiazkaAdresowaTymczasowa.txt", "ksiazkaAdresowa.txt");
}

vector <Kontakt> edytujKontakt(vector <Kontakt> ksiazkaAdresowa)
{
    int idKontaktuDoEdycji;
    cout<<"Wprowadz ID kontaktu ktory chcesz edytowac: ";
    cin>>idKontaktuDoEdycji;
    cin.ignore( std::numeric_limits < std::streamsize >::max(), '\n' );

    bool kontaktDoEdycjiZnaleziony = false;
    for(int i =0; i <ksiazkaAdresowa.size(); i++)
    {
        if(ksiazkaAdresowa[i].kontaktID == idKontaktuDoEdycji)
        {
            kontaktDoEdycjiZnaleziony = true;
            break;
        }
    }

    if(kontaktDoEdycjiZnaleziony)
    {
        system("cls");
        cout<<"Ktore pole chcesz edytowac?"<<endl;
        cout<<"1. Imie."<<endl;
        cout<<"2. Nazwisko."<<endl;
        cout<<"3. Numer telefonu."<<endl;
        cout<<"4. Email."<<endl;
        cout<<"5. Adres."<<endl;
        cout<<"6. Powrot do menu glownego."<<endl;

        char wyborOpcji = getch();

        switch(wyborOpcji)
        {
        case '1':
            system("cls");
            ksiazkaAdresowa=edytujImie(ksiazkaAdresowa, idKontaktuDoEdycji);
            break;
        case '2':
            system("cls");
            ksiazkaAdresowa=edytujNazwisko(ksiazkaAdresowa, idKontaktuDoEdycji);
            break;
        case '3':
            system("cls");
            ksiazkaAdresowa=edytujTelefon(ksiazkaAdresowa, idKontaktuDoEdycji);
            break;
        case '4':
            system("cls");
            ksiazkaAdresowa=edytujMaila(ksiazkaAdresowa, idKontaktuDoEdycji);
            break;
        case '5':
            system("cls");
            ksiazkaAdresowa=edytujAdres(ksiazkaAdresowa, idKontaktuDoEdycji);
            break;
        case '6':
            break;
        }

        edytujKontaktwPliku(idKontaktuDoEdycji, ksiazkaAdresowa);
    }
    else
    {
        cout<<"Nie ma takiego ID kontaktu!"<<endl;
        Sleep(1000);
    }

    return ksiazkaAdresowa;
}

void oczekiwanieNaEnter()
{
    cout<<endl<<"Nacisnij enter aby wrocic do menu glownego."<<endl;
    cin.get();
}

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

vector <Kontakt> wczytajKontaktyZplikuZalogowanego(int idZalogowanegoUzytkownika)
{
    fstream ksiazka;
    ksiazka.open("ksiazkaAdresowa.txt", ios::in);
    string liniaJednegoKontaktu;
    vector <Kontakt> odczytaneKontakty;
    Kontakt odczytanaLinia;
    if(czyKsiazkaAdresowaIstnieje() && czyKsiazkaAdresowaMaZawartosc() )
    {
        while(getline(ksiazka,liniaJednegoKontaktu))
        {
            odczytanaLinia = pobierzDaneZlinii(liniaJednegoKontaktu);
            if(odczytanaLinia.idUzytkownika == idZalogowanegoUzytkownika)
            {
                odczytaneKontakty.push_back(odczytanaLinia);
            }
        }
    }
    ksiazka.close();
    return odczytaneKontakty;
}

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
