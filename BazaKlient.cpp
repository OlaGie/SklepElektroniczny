/*
================================================================================
 Plik: BazaKlient.cpp
--------------------------------------------------------------------------------
 Autorzy:       xxx
 Projekt:       Sklep elektroniczny
 Kompilator:    GNU GCC (Code::Blocks v13.12)
 Hardware:      PC
 Utworzony:     11.05.2014
--------------------------------------------------------------------------------
 Zawiera: Definicje funkcji obsługi bazy danych klientów.
--------------------------------------------------------------------------------
 Komentarze:
    Ważne - wszystkie niedociągnięcia, potrzeby poprawek, itp. są oznaczone "ToDo"
--------------------------------------------------------------------------------
 Change log:

================================================================================
*/

//=========================        Includes        ===========================//
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "Struktury.hpp"
#include "BazaKlient.hpp"

using namespace std;

//========================= Constants definitions  ===========================//
#define LIMITER_WYNIKOW 100

//======================= Error Message Definitions ==========================//
//=========================         Macros         ===========================//
//========================= Variables definitions  ===========================//
//========================= Functions definitions  ===========================//

/*
    Funkcja dodaje rekord nowego klienta w pliku Klienci.txt
    Funkcja jako argument przyjmuje wskaźnik do struktury danych klienta.
        iKodKlienta ze struktury jest ignorowany! Można zostawić domyślne 0.
        Funkcja nadaje iKodKlienta = (max(plik->iKodKlienta) + 1).
    Funkcja zwraca wartość iKodKlienta po poprawnym dodaniu klienta do bazy.
    W przypadku niepowodzenia zwraca "0".
*/
bool bDodajKlienta(struct structKlient *DaneKlienta) //ToDo - poprawić na int iDodajKlienta
{
    //Sprawdzamy czy klient już istnieje: Czy NIP jest zajęty?
    int* iTemp;
    iTemp = piSzukajKlienta("sNIP", DaneKlienta->sNIP);
    if(0 != iTemp[0])
    {
        cout << "Klient o podanym numerze NIP juz istnieje w bazie.\n";
        cout << "Numer klienta w bazie: " << iTemp[1] << endl;
        return true;
    }

    /*ToDo:
        kursor na koniec pliku, kursor linijkę wyżej, pobierz pierwszy element z wiersza.
        iKodKlienta = max(plik->iKodKlienta); -ToDo
    */
    //Aktualnie zrobimy prostszą ale mniej efektywną metodą.
    int iKodKlientaMax = iOstatniKlient();

    fstream plik;
	plik.open("Klienci.txt", ios::out | ios::app);
	if(0 == plik.is_open())
    {
        cout << "Nie mozna otworzyc pliku Klienci.txt\n";
        return true;
    }

    plik << (iKodKlientaMax + 1) << "\t";
    plik << DaneKlienta->sImie << "\t";
    plik << DaneKlienta->sNazwisko << "\t";
    plik << DaneKlienta->sFirma << "\t";
    plik << DaneKlienta->sNIP << "\t";
    plik << DaneKlienta->liRegon << "\t";
    plik << DaneKlienta->sNumerTelefonu << "\t";
    plik << DaneKlienta->iRabat << endl;
    plik.close();
    return false;
}

/*
    Funkcja nadpisuje w pliku dane klienta nowym zestawem danych (nie dotyczy iKodKlienta).
    Funkcja przyjmuje wskaźnik do struktury DaneKlienta.
    Funkcja zwraca wartość logiczną 'true' w przypadku wystąpienia błędu.
    Pozytywne zakończenie funkcji zwraca 'false'.
*/
bool bEdytujKlienta(struct structKlient *DaneKlienta)
{
    //otwórz plik Klienci.txt do odczytu
    ifstream plik_we;
    fstream plik_wy;
    string sBufor;
    int iTmp;
    int iFlag = 0;
	plik_we.open("Klienci.txt", ios::in);
	plik_wy.open("temp.txt", ios::out);
	if(0 == plik_we.is_open())
    {
        cout << "Nie mozna otworzyc pliku Klienci.txt\n";
        return true;
    }
    if(0 == plik_wy.is_open())
    {
        cout << "Nie można otworzyc pliku temp.txt\n";
        return true;
    }

    //szukamy wiersz zawierający dane wybranego klienta:
    while(!plik_we.eof())
    {
        getline(plik_we, sBufor);
        istringstream issTmp(sBufor);
        issTmp >> iTmp;
        if(iTmp == DaneKlienta->iKodKlienta)
        {
            //znaleźliśmy klienta
            //tu wrzucamy nowe dane do drugiego pliku
            plik_wy << DaneKlienta->iKodKlienta << "\t";
            plik_wy << DaneKlienta->sImie << "\t";
            plik_wy << DaneKlienta->sNazwisko << "\t";
            plik_wy << DaneKlienta->sFirma << "\t";
            plik_wy << DaneKlienta->sNIP << "\t";
            plik_wy << DaneKlienta->liRegon << "\t";
            plik_wy << DaneKlienta->sNumerTelefonu << "\t";
            plik_wy << DaneKlienta->iRabat << endl;
            iFlag = 1;
        }
        else
        {
            //a tu przerzucamy całą resztę
            plik_wy << sBufor << endl;
        }
    }
    plik_we.close();
    plik_wy.close();
    remove("Klienci.txt");
    rename("temp.txt", "Klienci.txt");
}

/*
    !!! Uważam, że tej funkcji nie powinno być ze względu na spójność danych (np. faktur)!
    Funkcja usuwa z bazy klientów rekord z danymi klienta.
    Funkcja jak argument przyjmuje numer klienta iKodKlienta.
    Funkcja zwraca wartość logiczną "false" w przyparku powodzenia.
    Błąd sygnalizowany jest przez zwrócenie "true".
*/
/*bool bUsunKlienta(int iKodKlienta) //ToDo
{
    if(0 == iKodKlienta)
    {
        return true;
    }
    return false;
}*/

/*
    Funkcja zwraca strukturę klienta o kodzie iKodKlienta.
    Jeżeli klient o takim kodzie nie istnieje to funkcja zwraca NULL.
*/
structKlient* PobierzKlienta(int iKodKlienta)//ToDo : lepiej będzie zrobić przez wskaźnik. Ale skąd wtedy wziąć strukturę? Może jako obiekt globalny?
{
    struct structKlient* DaneKlienta;//wskaźnik na strukturę do przechowywania danych
    DaneKlienta = new (struct structKlient);

    //otwórz plik Klienci.txt do odczytu
    ifstream plik;
	plik.open("Klienci.txt", ios::in);
    //szukamy wiersz zawierający dane wybranego klienta:
    int iFlag = 0;
    int iTmp; string sTmp;
    string sBufor;
    while(!plik.eof())
    {
        getline(plik, sBufor);
        istringstream issTmp(sBufor);
        issTmp >> iTmp;
        if(iTmp == iKodKlienta)
        {
            iFlag = 1;
            DaneKlienta->iKodKlienta = iKodKlienta;
            issTmp >> sTmp;
            DaneKlienta->sImie = sTmp;
            issTmp >> sTmp;
            DaneKlienta->sNazwisko = sTmp;
            issTmp >> sTmp;
            DaneKlienta->sFirma = sTmp;
            issTmp >> sTmp;
            DaneKlienta->sNIP = sTmp;
            issTmp >> iTmp;
            DaneKlienta->liRegon = iTmp;
            issTmp >> sTmp;
            DaneKlienta->sNumerTelefonu = sTmp;
            issTmp >> iTmp;
            DaneKlienta->iRabat = iTmp;
            plik.close();
            break;
        }
    }
    plik.close();
    if(0 == iFlag)
    {
        cout << "W bazie nie znaleziono wskazanego numeru klienta." << endl;
        return NULL;
    }
    return DaneKlienta;
}

/*
    Funkcja wyszukuje struktury klientów spełniające zadany warunek.
    Funkcja zwraca tablicę kodów klientów spełniających warunek. Tablica[0] zawiera liczbę wyników.
    Tablica[1...n] zawiera wyniki.
*/
int* piSzukajKlienta(string sNazwaZmiennej, long long int iWartoscZmiennej)
{
    //Otwieramy plik:
    ifstream plik;
	plik.open("Klienci.txt", ios::in);
	if(0 == plik.is_open())
    {
        cout << "Nie mozna otworzyc pliku Klienci.txt\n";
        return NULL;
    }

    //Szukamy w pliku:
    string sBufor;
    int iFlagaTab = 0;
    int iZmienna = 0;
    int iTemp = 0;
    int* iTablicaWynikow;
    int iKodKlienta = 1;
    iTablicaWynikow = new int [LIMITER_WYNIKOW*sizeof(int)];
    *iTablicaWynikow = 0; //ustawiamy liczbę wyników na 0
    int iLimiter = 1; //modyfikator wskaźnika na tablicę wyników


    if("iKodKlienta" == sNazwaZmiennej)
    {
        iZmienna = 1;
    }
    else if("liRegon" == sNazwaZmiennej)
    {
        iZmienna = 6;
    }
    else if("iRabat" == sNazwaZmiennej)
    {
        iZmienna = 8;
    }
    else
    {
        iZmienna = 0;
    }

    while(!plik.eof())
    {
        getline(plik,sBufor); //Wczytujemy wiersz z pliku
        istringstream issTemp(sBufor);
        iFlagaTab = 1;
        do
        {
            string sub;
            issTemp >> sub;
            istringstream iss(sub);
            if(1 == iFlagaTab)//zapamiętujemy aktualnie czytanego klienta
            {
                iss >> iTemp;
                iKodKlienta = iTemp;
            }
            if(iFlagaTab == iZmienna)
            {
                //konwersja na long long integer (bo lliNIP) i zapis do iTablicaWynikow
                long long int lliTmp;
                iss >> lliTmp;
                if(lliTmp == iWartoscZmiennej)
                {
                    iTablicaWynikow[iLimiter] = iKodKlienta;
                    iLimiter++;
                    if(LIMITER_WYNIKOW == iLimiter)//sprawdzamy czy osiągnięto koniec tablicy wqyników
                    {
                        break;
                    }
                }
            }
            iFlagaTab++;
        }while(issTemp);
    }
    iTablicaWynikow[0] = iLimiter - 1;//zapisujemy liczbę wyników
    plik.close();
    return iTablicaWynikow;
}

/* Przeciążenie funkcji w celu obsługi typu string*/
int* piSzukajKlienta(string sNazwaZmiennej, string sWartoscZmiennej)
{
    //Otwieramy plik:
    ifstream plik;
	plik.open("Klienci.txt", ios::in);
	if(0 == plik.is_open())
    {
        cout << "Nie mozna otworzyc pliku Klienci.txt\n";
        return NULL;
    }

    //Szukamy w pliku:
    string sBufor;      //bufor do wczytywania pliku
    int iFlagaTab = 0;  //licznik tabulatora/kolumny
    int iZmienna = 0;   //niezbędne do switch'a
    //int iTemp = 0;
    int* iTablicaWynikow;
    int iKodKlienta = 1;
    iTablicaWynikow = new int [LIMITER_WYNIKOW*sizeof(int)];
    *iTablicaWynikow = 0;
    int iLimiter = 1; //modyfikator wskaźnika na tablicę wyników


    if("sImie" == sNazwaZmiennej)
    {
        iZmienna = 2;
    }
    else if("sNazwisko" == sNazwaZmiennej)
    {
        iZmienna = 3;
    }
    else if("sFirma" == sNazwaZmiennej)
    {
        iZmienna = 4;
    }
    else if("sNIP" == sNazwaZmiennej)
    {
        iZmienna = 5;
    }
    else if("sNumerTelefonu" == sNazwaZmiennej)
    {
        iZmienna = 7;
    }
    else
    {
        iZmienna = 0;
    }

    while(!plik.eof())
    {
        getline(plik,sBufor); //Wczytujemy wiersz z pliku
        istringstream issTemp(sBufor);
        iFlagaTab = 1;
        do
        {
            string sub;
            issTemp >> sub;
            if(1 == iFlagaTab)//zapamiętujemy aktualnie czytanego klienta
            {
                istringstream iss(sub);
                iss >> iKodKlienta;
            }
            if(iFlagaTab == iZmienna)
            {
                //konwersja na integer i zapis do iTablicaWynikow
                if(sub == sWartoscZmiennej)
                {
                    iTablicaWynikow[iLimiter] = iKodKlienta;
                    iLimiter++;
                    if(LIMITER_WYNIKOW == iLimiter)//sprawdzamy czy osiągnięto koniec tablicy wyników
                    {
                        break;
                    }
                }
            }
            iFlagaTab++;
        }while(issTemp);
    }
    iTablicaWynikow[0] = iLimiter - 1;//zapisujemy liczbę wyników
    plik.close();
    return iTablicaWynikow;
}

/*
    Funkcja zwraca max(iKodKlienta) z pliku Klienci.txt
*/
int iOstatniKlient(void)
{
    ifstream plik;
    string sBufor, sPoprzedniaLinia;
    int iKodKlientaMax;

	plik.open("Klienci.txt", ios::in);
	if(0 == plik.is_open())
    {
        cout << "Nie mozna otworzyc pliku Klienci.txt\n";
        return 0;
    }
    while(!plik.eof())
    {
        sPoprzedniaLinia = sBufor;
        getline(plik,sBufor);
    }
    plik.close();
    istringstream issTemp(sPoprzedniaLinia);
    issTemp >> iKodKlientaMax;
    return iKodKlientaMax;
}

/*
    Funkcja wyświetla wiersze z pliku "Klienci.txt" w grupach po 20 wierszy.
    Funkcja w przypadku niepowodzenia/błędu zwraca '0'.
*/
int iWyswietlListeKlientow(void)
{
    ifstream plik;
    string sBufor;
    int iLimitWyswietlania = 20; //Maz 20 wierszy wyswietlonych.
    int iLicznik = 1;

	plik.open("Klienci.txt", ios::in);
	if(0 == plik.is_open())
    {
        cout << "Nie mozna otworzyc pliku Klienci.txt\n";
        return 0;
    }
    while(!plik.eof())
    {
        getline(plik, sBufor);
        cout << sBufor << endl;
        if(iLicznik == iLimitWyswietlania)//limitujemy liczbę klientów wyświetlonych w jednej grupie
        {
            iLicznik = 1;//reset licznika
            system("pause");
        }
        else
        {
            iLicznik++;
        }
    }
    return 1;
}

/*
    Funkcja pobiera dane ze strumienia wejściowego i sprawdza czy jest to dana liczbowa.
    Funkcja zwraca dane w postaci int.
    Jeżeli strumień zawiera jakiekolwiek znaki nie będące cyframi funkcja przerywa działanie i zwraca -1
*/
int iPobierzInt(void)
{
    int iWynik, iTmp, i;
    i = 0;
    string sBufor;
    cin.clear();
    cin.sync();
    cin >> sBufor;
    while(1)
    {
        if(NULL == sBufor[i])
        {
            break;
        }
        iTmp = sBufor[i];
        if((iTmp > 47)&&(iTmp < 58))
        {
            //OK
            i++;
        }
        else
        {
            cout << "Wprowadzony ciag nie jest wlasciwa liczba!" << endl;
            return -1;
        }
    }
    istringstream issTmp(sBufor);
    issTmp >> iWynik;
    return iWynik;
}

string sPobierzString(void)
{
    string sWynik;
    cin.clear();
    cin.sync();
    cin >> sWynik;
    return sWynik;
}

/*
    Funkcja wyświetla menu bazy klientów i obsługuje wybory użytkownika.
*/
void vMenuKlient(void)
{
    int iWybor = 1;
    int iWartosc;
    int *piWyniki;
    long long int lliWartosc;
    string sTemp, sWartosc;
    struct structKlient* skKlient;
    skKlient = new structKlient;

    while(0 != iWybor)
    {
        system("cls");
        cout << "=========================================================" << endl;
        cout << "\t == Baza klientow ==" << endl;
        cout << "\t 1. Dodaj nowego klienta." << endl;
        cout << "\t 2. Edytuj dane klienta." << endl;
        cout << "\t 3. Wyszukaj klienta." << endl;
        cout << "\t 4. Wyswietl liste wszystkich klientow." << endl;
        cout << "\t 0. Wyjscie z menu obslugi bazy klientow." << endl;
        cout << "=========================================================" << endl;

        iWybor = iPobierzInt();

        switch(iWybor)
        {
            case 1://1. Dodaj nowego klienta.
                cout << "Podaj imie klienta:" << endl;
                    skKlient->sImie = sPobierzString();
                cout << "Podaj nazwisko klienta:" << endl;
                    skKlient->sNazwisko = sPobierzString();
                cout << "Podaj firme, ktora klient reprezentuje (lub wpisz \"brak\" dla klientow indywidualnych):" << endl;
                    skKlient->sFirma = sPobierzString();
                cout << "Podaj NIP klienta:" << endl;
                    skKlient->sNIP = sPobierzString();
                cout << "Podaj regon klienta (lub '0')" << endl;
                    skKlient->liRegon = iPobierzInt();
                cout << "Podaj numer telefonu klienta w formacie +48xxxxxxxxx :" << endl;
                    skKlient->sNumerTelefonu = sPobierzString();
                cout << "Podaj wartosc rabatu przyznanego klientowi [%]:" << endl;
                    skKlient->iRabat = iPobierzInt();
                bDodajKlienta(skKlient);
                break;
            case 2://2. Edytuj dane klienta.
                cout << "Podaj numer klienta" << endl;
                cin.clear();
                cin.sync();
                iWybor = iPobierzInt();
                skKlient = PobierzKlienta(iWybor);
                cout << "Który parametr chcesz edytowac?" << endl;
                iWybor = iNumerZmiennej(sWyswietlZmienne());
                if(1 == iWybor)
                {
                    cout << "Nie można zmieniać numeru klienta." << endl;
                }
                else if((0 > iWybor)||(8 < iWybor))
                {
                    cout << "Nieprawidlowy wybor."<< endl;
                }
                else
                {
                    cout << "Podaj nowa wartosc" << endl;
                    cin.clear();
                    cin.sync();
                    switch(iWybor)
                    {
                        case 2:
                            cin >> skKlient->sImie;
                            break;
                        case 3:
                            cin >> skKlient->sNazwisko;
                            break;
                        case 4:
                            cin >> skKlient->sFirma;
                            break;
                        case 5:
                            cin >> skKlient->sNIP;
                            break;
                        case 6:
                            cin >> skKlient->liRegon;
                            break;
                        case 7:
                            cin >> skKlient->sNumerTelefonu;
                            break;
                        case 8:
                            cin >> skKlient->iRabat;
                            break;
                    }
                }
                break;
            case 3://3. Wyszukaj klienta.
                cout << "Wedlug ktorego parametru chcesz wyszukiwac?" << endl;
                sTemp = sWyswietlZmienne();
                iWartosc = iNumerZmiennej(sTemp);
                if(0 == iWartosc)
                {
                    break;
                }
                cout << "Podaj wartosc parametru " << sTemp << ", ktora chcesz wyszukac:" << endl;
                cin.clear();
                cin.sync();
                piWyniki = new int[100];
                if((iWartosc == 1)||(iWartosc == 5)||(iWartosc == 6)||(iWartosc == 8))
                {
                    cin >> lliWartosc;
                    piWyniki = piSzukajKlienta(sTemp, lliWartosc);
                    vWyswietlWyniki(piWyniki);
                }
                else
                {
                    cin >> sWartosc;
                    piWyniki = piSzukajKlienta(sTemp, sWartosc);
                    vWyswietlWyniki(piWyniki);
                }
                delete piWyniki;
                break;
            case 4://4. Wyswietl liste wszystkich klientow.
                iWyswietlListeKlientow();
                break;
            case 0://0. Wyjscie z menu obslugi bazy klientow.
            default:
                delete skKlient;
                return;
        }
        delete skKlient;
        system("pause");
    }
    return;
}

string sWyswietlZmienne(void)
{
    cout << "1. Kod klienta." << endl;
    cout << "2. Imie." << endl;
    cout << "3. Nazwisko." << endl;
    cout << "4. Firma." << endl;
    cout << "5. NIP." << endl;
    cout << "6. Regon." << endl;
    cout << "7. Numer Telefonu." << endl;
    cout << "8. Rabat." << endl;
    cout << "0. Powrot." << endl;

    int iTemp = 0;
    cin.clear();
    cin.sync();
    cin >> iTemp;

    switch(iTemp)
    {
        case 1:
            return "iKodKlienta";
        case 2:
            return "sImie";
        case 3:
            return "sNazwisko";
        case 4:
            return "sFirma";
        case 5:
            return "sNIP";
        case 6:
            return "liRegon";
        case 7:
            return "sNumerTelefonu";
        case 8:
            return "iRabat";
        case 0:
            return "";
        default:
            cout << "Nieprawidłowy wybor.";
            return "";
    }
}

int iNumerZmiennej(string sNazwaZmiennej)
{
    int iZmienna;

    if("iKodKlienta" == sNazwaZmiennej)
    {
        iZmienna = 1;
    }
    else if("liRegon" == sNazwaZmiennej)
    {
        iZmienna = 6;
    }
    else if("iRabat" == sNazwaZmiennej)
    {
        iZmienna = 8;
    }
    else if("sImie" == sNazwaZmiennej)
    {
        iZmienna = 2;
    }
    else if("sNazwisko" == sNazwaZmiennej)
    {
        iZmienna = 3;
    }
    else if("sFirma" == sNazwaZmiennej)
    {
        iZmienna = 4;
    }
    else if("sNIP" == sNazwaZmiennej)
    {
        iZmienna = 5;
    }
    else if("sNumerTelefonu" == sNazwaZmiennej)
    {
        iZmienna = 7;
    }
    else
    {
        iZmienna = 0;
    }

    return iZmienna;
}

void vWyswietlWyniki(int *piWyniki)
{
    if(0 == *piWyniki)
    {
        cout << "Brak wynikow spelniajacych zadane kryteria." << endl;
        return;
    }
    else
    {
        cout << "Nastepujacy klienci spelniaja zadane kryteria:" << endl;
        cout << "Kod klienta:" << endl;
        for(int i = 1; i <= piWyniki[0]; i++)
        {
            cout << piWyniki[i] << endl;
        }
    }
}


