#include <iostream>
#include <windows.h>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Znajomy
{
    int numerID;
    string imie, nazwisko, numerTelefonu, mail, adres;
};

string konwerjsaIntNaString ( int liczba)
{
    ostringstream ss;
    ss << liczba;
    string lancuch = ss.str();
    return lancuch;
}

void zapiszNowegoZnajomego(vector <Znajomy> &znajomi)
{
    string imie, nazwisko, adres, numerTelefonu, mail;
    string liniaZDanymiZnajomego = "";
    Znajomy Osoba;

    cout << endl << "Zapisywanie nowego znajomego." << endl << endl;
    cout << "Podaj imie: ";
    cin >> imie;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    cout << "Podaj numer telefonu: ";
    cin.sync();
    getline(cin,numerTelefonu);
    cout << "Podaj mail: ";
    cin >> mail;
    cout << "Podaj adres: ";
    cin.sync();
    getline(cin,adres);

    // Do zmiennej typu Znajomy Osoba zapisuje poszczegolne dane
    if (znajomi.empty() == true)  // je¿eli ksia¿ka adresowa jest pusta
    {
        Osoba.numerID = 1;           // to nowy adresat ma id=1
    }
    else
    {
        Osoba.numerID = znajomi.back().numerID + 1; // w przeciwnym przypadku pobierz id ostatniej osoby z ksi¹¿ki adresowej i zwiêksz wartoœæ o jeden.
    }

    Osoba.imie = imie;
    Osoba.nazwisko = nazwisko;
    Osoba.numerTelefonu = numerTelefonu;
    Osoba.mail = mail;
    Osoba.adres = adres;

    znajomi.push_back(Osoba);

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out);

    if (plik.good() == true)
    {
        for (vector <Znajomy>::iterator itr = znajomi.begin(); itr != znajomi.end(); itr++)
        {
            liniaZDanymiZnajomego += konwerjsaIntNaString(itr -> numerID) + '|';
            liniaZDanymiZnajomego += itr -> imie + '|';
            liniaZDanymiZnajomego += itr -> nazwisko + '|';
            liniaZDanymiZnajomego += itr -> numerTelefonu + '|';
            liniaZDanymiZnajomego += itr -> mail + '|';
            liniaZDanymiZnajomego += itr -> adres + '|';

            plik << liniaZDanymiZnajomego << endl;
            liniaZDanymiZnajomego = "";
        }
        plik.close();
        cout << "Dane zostaly zapisne." << endl;
        system("pause");
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
}

void wczytajZnajomychZPliku(vector <Znajomy> &znajomi)
{
    string linia;
    string wyraz;
    int iloscPionowychKresek = 0;
    int ileZnakowWyjac = 0;
    int poczatek = 0 ;
    int iloscZnajomych = 0;
    fstream plik;
    Znajomy pusty;

    znajomi.clear();
    plik.open("KsiazkaAdresowa.txt",ios::in); // aby otworzyc plik do odczytu
    if (plik.good() == true)
    {
        // odczytuje linie po kolei. Linie w pliku tekstowym w przeciwienstwie do tablic sa numerowane od 1
        // funkcja getline odczytuje ze zmiennej plikowej plik i zapisuje linie jako stringa do zmiennej linia.
        // funkcja zwraca true dopoki sa linie do odczytania. Zwroci false, gdy plik sie skonczy

        while (getline(plik,linia))
        {
            znajomi.push_back(pusty);
            iloscZnajomych++;
            ileZnakowWyjac = 0;
            poczatek = 0;
            iloscPionowychKresek = 0;

            for (int i = 0; i < linia.size(); i++)
            {
                ileZnakowWyjac = i - poczatek;
                if (linia[i] == '|')
                {
                    iloscPionowychKresek++;
                    wyraz = linia.substr (poczatek,ileZnakowWyjac);
                    switch (iloscPionowychKresek)
                    {
                    case 1:
                        znajomi[iloscZnajomych - 1].numerID = atoi(wyraz.c_str());
                        break;
                    case 2:
                        znajomi[iloscZnajomych - 1].imie = wyraz;
                        break;
                    case 3:
                        znajomi[iloscZnajomych - 1].nazwisko = wyraz;
                        break;
                    case 4:
                        znajomi[iloscZnajomych - 1].numerTelefonu = wyraz;
                        break;
                    case 5:
                        znajomi[iloscZnajomych - 1].mail = wyraz;
                        break;
                    case 6:
                        znajomi[iloscZnajomych - 1].adres = wyraz;
                        break;
                    }
                    poczatek = poczatek + ileZnakowWyjac + 1;
                }
               //znajomi[iloscZnajomych - 1].numerID = iloscZnajomych;
            }
        }
        plik.close();
    }
}

void wyswietlWszystkichZnajomych(vector <Znajomy> &znajomi)
{
    for (vector <Znajomy>::iterator itr = znajomi.begin(); itr != znajomi.end(); itr++)
    {
        cout << endl;
        cout << "Numer ID: " << itr -> numerID << endl;
        cout << itr -> imie << " " << itr -> nazwisko << endl;
        cout << "Numer telefonu: " << itr -> numerTelefonu << endl;
        cout << "Mail: " << itr -> mail << endl;
        cout << "Adres: " << itr -> adres << endl;
        cout << endl;
    }
    system("pause");
}

void szukajImie(vector <Znajomy> &znajomi)
{
    string poszukiwaneImie;
    bool znalezionyZnajomy = 0;
    cout << endl << "Podaj imie znajomego, ktorego mamy wyszukac: ";
    cin >> poszukiwaneImie;

    for (vector <Znajomy>::iterator itr = znajomi.begin(); itr != znajomi.end(); itr++)
    {
        if (itr -> imie == poszukiwaneImie)
        {
            znalezionyZnajomy = 1;
            cout << endl;
            cout << "Numer ID: " << itr -> numerID << endl;
            cout << itr -> imie << " " << itr -> nazwisko << endl;
            cout << "Numer telefonu: " << itr -> numerTelefonu << endl;
            cout << "Mail: " << itr -> mail << endl;
            cout << "Adres: " << itr -> adres << endl;
            cout << endl;
        }
    }

    if(!znalezionyZnajomy)   //jesli zmienna Znaleziony_znajomy==0
    {
        cout << endl << "Nie znaleziono osoby o tym imieniu." << endl << endl;
    }
    system("pause");
}

void szukajNazwisko(vector <Znajomy> &znajomi)
{
    string poszukiwaneNazwisko;
    bool znalezionyZnajomy = 0;
    cout << endl << "Podaj nazwisko znajomego, ktorego mamy wyszukac: ";
    cin >> poszukiwaneNazwisko;

    for (vector <Znajomy>::iterator itr = znajomi.begin(); itr != znajomi.end(); itr++)
    {
        if (itr -> nazwisko == poszukiwaneNazwisko)
        {
            znalezionyZnajomy = 1;
            cout << endl;
            cout << "Numer ID: " << itr -> numerID << endl;
            cout << itr -> imie << " " << itr -> nazwisko << endl;
            cout << "Numer telefonu: " << itr -> numerTelefonu << endl;
            cout << "Mail: " << itr -> mail << endl;
            cout << "Adres: " << itr -> adres << endl;
            cout << endl;
        }
    }

    if(!znalezionyZnajomy)   //jesli zmienna Znaleziony_znajomy==0
    {
        cout << endl << "Nie znaleziono osoby o tym nazwisku." << endl << endl;
    }
    system("pause");
}

void edytujKontakt (vector <Znajomy> &znajomi)
{
    string numerTelefonu, mail, adres;
    char wybranaPozycjaMenu;

    int poszukiwanyNumerID;
    bool znalezionyZnajomy = 0;
    int pozycjaZnalezionejOsoby = 0;


    cout << "Wyszukanie znajomego. Podaj numer ID znajomego: ";
    cin >> poszukiwanyNumerID;

    for (vector <Znajomy>::iterator itr = znajomi.begin(); itr != znajomi.end(); itr++)
    {
        if (itr -> numerID == poszukiwanyNumerID)
        {
            znalezionyZnajomy = 1;
            system("cls");
            cout << "Edycja kontaktu." << endl;
            cout << itr -> imie << " " << itr -> nazwisko << endl;
            cout << "Numer telefonu: " << itr -> numerTelefonu << endl;
            cout << "Mail: " << itr -> mail << endl;
            cout << "Adres: " << itr -> adres << endl;
            cout << endl;
            cout << "1.Edytuj numer telefonu." << endl;
            cout << "2.Edytuj adres mailowy." << endl;
            cout << "3.Edytuj adres kontaktowy." << endl;
            cout << "4.Edytuj wszystkie informacje." << endl;
            cout << "9.Zakoncz edycje." << endl<<endl;
            cin>> wybranaPozycjaMenu;

            switch(wybranaPozycjaMenu)
            {
            case '1':
                cout << "Podaj nowy numer telefonu: ";
                cin.sync();
                getline(cin,numerTelefonu);
                znajomi[pozycjaZnalezionejOsoby].numerTelefonu = numerTelefonu;
                break;
            case '2':
                cout << "Podaj nowy adres mailowy: ";
                cin >>  mail;
                znajomi[pozycjaZnalezionejOsoby].mail = mail;
                break;
            case '3':
                cout << "Podaj nowy adres kontaktowy: ";
                cin.sync();
                getline(cin,adres);
                znajomi[pozycjaZnalezionejOsoby].adres = adres;
                break;
            case '4':
                cout << "Podaj nowy numer telefonu: ";
                cin.sync();
                getline(cin,numerTelefonu);
                cout << "Podaj nowy adres mailowy: ";
                cin >>  mail;
                cout << "Podaj nowy adres kontaktowy: ";
                cin.sync();
                getline(cin,adres);

                znajomi[pozycjaZnalezionejOsoby].numerTelefonu = numerTelefonu;
                znajomi[pozycjaZnalezionejOsoby].mail = mail;
                znajomi[pozycjaZnalezionejOsoby].adres = adres;
                break;
            case '9':
                system("pause");
                break;
            }
            cout << "Edycja kontaktu przebiegla pomyslnie." << endl << endl;

        }
        pozycjaZnalezionejOsoby++;
    }

    if(!znalezionyZnajomy)   //jesli zmienna Znaleziony_znajomy==0
    {
        cout << endl << "Nie znaleziono osoby o podanym: imieniu i nazwisku." << endl << endl;
        system("pause");
    }
}

void usunKontakt (vector <Znajomy> &znajomi)
{
    int poszukiwanyNumerID;
    //int licznik = 0;

    cout << "Wyszukanie znajomego. Podaj numer ID znajomego: ";
    cin >> poszukiwanyNumerID;

    for (vector <Znajomy>::iterator itr = znajomi.begin(); itr != znajomi.end(); itr++)
    {
        if (itr -> numerID == poszukiwanyNumerID)
        {
            itr = znajomi.erase(itr);
            cout << "Kontakt zostal usuniety." << endl << endl;
            system("pause");
            break;
        }
        //licznik++;
    }
}

void zapisDanychDoPliku (vector <Znajomy> &znajomi)
{
    fstream plik;
    string liniaZDanymiZnajomego = "";
    plik.open("KsiazkaAdresowa.txt", ios::out);

    if (plik.good() == true)
    {
        for (vector <Znajomy>::iterator itr = znajomi.begin(); itr != znajomi.end(); itr++)
        {
            liniaZDanymiZnajomego += konwerjsaIntNaString(itr -> numerID) + '|';
            liniaZDanymiZnajomego += itr -> imie + '|';
            liniaZDanymiZnajomego += itr -> nazwisko + '|';
            liniaZDanymiZnajomego += itr -> numerTelefonu + '|';
            liniaZDanymiZnajomego += itr -> mail + '|';
            liniaZDanymiZnajomego += itr -> adres + '|';

            plik << liniaZDanymiZnajomego << endl;
            liniaZDanymiZnajomego = "";
        }
        plik.close();
        cout << "Dane zostaly zapisne." << endl;
        system("pause");
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
}

int main()
{
    vector <Znajomy> znajomi;
    char wybranaPozycjaMenu;

    wczytajZnajomychZPliku(znajomi);
    while(1)
    {
        wczytajZnajomychZPliku(znajomi);
        system("cls");
        cout<< "Ksiazka adresowa."<<endl<<endl;
        cout << "1.Zapisz nowego znajomego." << endl;
        cout << "2.Wyszukaj znajomego." << endl;
        cout << "3.Wyswietl liste znajomych." << endl;
        cout << "4.Edytuj kontakt." << endl;
        cout << "5.Usun kontakt." << endl;
        cout << "9.Zakoncz program." << endl<<endl;
        cin>> wybranaPozycjaMenu;


        switch(wybranaPozycjaMenu)
        {
        case '1':
            zapiszNowegoZnajomego(znajomi);
            break;
        case '2':

            system("cls");
            cout<< "Wyszukiwanie znajomego." <<endl<< endl;
            cout<<"1.Wyszukiwanie wg imienia." <<endl;
            cout<<"2.Wyszukiwanie wg nazwiska." <<endl;
            cout<<"9.Zakoncz wyszukiwanie."<< endl;
            cin>> wybranaPozycjaMenu;

            switch(wybranaPozycjaMenu)
            {
            case '1':
                szukajImie(znajomi);
                break;
            case '2':
                szukajNazwisko(znajomi);
                break;
            case '9':
                system("pause");
            }
            break;
        case '3':
            wyswietlWszystkichZnajomych(znajomi);
            break;
        case '4':
            edytujKontakt(znajomi);
            zapisDanychDoPliku(znajomi);
            break;
        case '5':
            usunKontakt(znajomi);
            zapisDanychDoPliku(znajomi);
            break;
        case '9':
            exit(0);
            break;
        }

    }
    return 0;
}
