/*
================================================================================
 Plik: BazaTowarow.cpp
--------------------------------------------------------------------------------
 Autor:     Ola Gdowska
--------------------------------------------------------------------------------
 Zawiera: Definicje funkcji obsługi baz produktów.
 --------------------------------------------------------------------------------
================================================================================
*/

//=========================        Includes        ===========================//
#include <iostream>
#include <fstream>
#include <string>
#include "BazaTowarow.hpp"
#include "struktury.hpp"
#include <stdlib.h>
#include <conio.h>

using namespace std;

//========================= Functions  ===========================//

int Wyszukaj_Kod_Towaru(void){ //funkcja pomocnicza wyszukująca w pliku towary.txt jaki jest kod ostatniego towaru. Zwraca ilosc towarów w pliku
	structTowar Towar[200];
	int nr_linii = 1, i=0, temp;
	string linia;

	fstream plik; //zmienna plikowa
	plik.open("towary.txt", ios::in); //otwarcie pliku do odczytu

	if (plik.good() == false){
		cout << " Nie udalo sie otworzyc pliku!";
		exit(0);
	}
	while (getline(plik, linia))//(!plik.eof();
	{
		switch (nr_linii){
		case 1: {Towar[i].iKodTowaru = atoi(linia.c_str()); temp = i+1; }
		}
		if (nr_linii == 8) { nr_linii = 0; i++; } //(nt_tab==5) {nr_tab=0
		nr_linii++; //nr_tab++;

	}
	plik.close();
			return temp;
	}


bool Dodaj(struct structTowar Towar){// Funkcja dodająca produkty do pliku towary.txt. Argumentem funkcji jest struktura Towar
    fstream plik;
    plik.open("towary.txt", ios::out | ios::app);
    int KodTowaru;

    KodTowaru = Wyszukaj_Kod_Towaru();   //KodTowaru jest analogiczny z id towaru w bazie. 
										//Dodawane automatycznie dla każdego towaru, jednoczesnie mówi o ilosci towarow w pliku towary.txt
    Towar.iKodTowaru = KodTowaru + 1;

    plik << Towar.iKodTowaru << endl;
    plik << Towar.iKodKreskowy << endl;

    for (int i = 0; i < Towar.sNazwa.length(); i++) //zamiana duzych liter na male w sNazwa podczas dodawania do pliku towary.txt (ulatwienie przy pozniejszym wyszukiwaniu po nazwie)
    {
        Towar.sNazwa[i] = tolower(Towar.sNazwa[i]);
    }

    plik << Towar.sNazwa << endl;
    plik << Towar.sKategoria << endl;
    plik << Towar.fCena << endl;
    plik << Towar.iPodatek << endl;
    plik << Towar.iIlosc << endl;
    plik << endl;
    plik.close();

    return true;
}

bool Kopia(struct structTowar Towar[], int licznik){// funkcja pomocnicza do przepisywania zawartości z pliku towary.txt do pliku kopia.txt
													//Funkcja użyta przy funkcjach do edytowania zawartości towarów w pliku
	fstream plik;
	plik.open("kopia.txt", ios::in | ios::out);
	int i;
	for (i = 0; i < licznik; i++){
		plik << Towar[i].iKodTowaru << endl;
		plik << Towar[i].iKodKreskowy << endl;
		plik << Towar[i].sNazwa << endl;
		plik << Towar[i].sKategoria << endl;
		plik << Towar[i].fCena << endl;
		plik << Towar[i].iPodatek << endl;
		plik << Towar[i].iIlosc << endl;
		plik << endl;
	}
	plik.close();

	return true;
}
structTowar* Zapamietaj(){ //Funkcja pomocnicza wykorzystywana do pobierania wszystkich towarów z pliku. Zwraca wskaznik do struktur.
	//Funkcja wykorzystywana do funkcji wyszukujących

	structTowar *Towar;
	Towar = new structTowar[Wyszukaj_Kod_Towaru()];
	structTowar Temp;

	string linia; int i = 0, nr_linii = 1;
	int k = 1;

	fstream plik; //zmienna plikowa
	plik.open("towary.txt", ios::in); //otwarcie pliku do odczytu

	if (plik.good() == false){
		cout << " Nie udalo sie otworzyc pliku!"; exit(0);
	}
	while (!plik.eof()){ //dopoki nie nastapi koniec pliku, pobieranie kolejnych lini z pliku towary.txt
						//Kazdemu towarowi odpowiada 8 kolejnych lini w pliku, kazda linia jest przyporzadkowana do odpowiedniego elementu struktury
		getline(plik, linia);

		switch (nr_linii)
		{
		case 1: Towar[i].iKodTowaru = atoi(linia.c_str()); break;
		case 2: Towar[i].iKodKreskowy = atoi(linia.c_str()); break;
		case 3: Towar[i].sNazwa = linia; break;
		case 4: Towar[i].sKategoria = linia; break;
		case 5: Towar[i].fCena = atof(linia.c_str()); break;
		case 6: Towar[i].iPodatek = atoi(linia.c_str()); break;
		case 7: Towar[i].iIlosc = atoi(linia.c_str()); break;
		case 8: break;
		}
		if (nr_linii == 8) {
			nr_linii = 0;
			i++;
		}
		nr_linii++;
	}
	plik.close();
	return Towar;
}

bool Wyswietl_nazwe(string sNazwa){//Funkcja wyszukująca towar po podaniu nazwy. Argumentem jest nazwa towaru
									//Żeby funkcja wyszukała towar wystarczy podac pierwszy czlon nazwy (zazwyczaj jest to marka towaru np lenovo)

    structTowar * Towar;
    Towar = Zapamietaj(); 

    int ilosc, i,licznik=0;
    ilosc = Wyszukaj_Kod_Towaru();
    for (int i = 0; i < sNazwa.length(); i++)
    {
        sNazwa[i] = tolower(sNazwa[i]);
    }

    for (i = 0; i < ilosc; i++){

        if (!Towar[i].sNazwa.find(sNazwa)){ 
            cout << " Kod kreskowy " << Towar[i].iKodKreskowy << endl;
            cout << " Nazwa towaru " << Towar[i].sNazwa << endl;
            cout << " Cena towaru " << Towar[i].fCena << endl;
            cout << " Ilosc: " << Towar[i].iIlosc << endl << endl;
            licznik++;
        }
    }
    if (licznik == 0){
        cout << " Brak produktu o podanej nazwie" << endl;
    }
    return true;
}


bool Wyswietl_Kod(int kod){ //Funkcja wyszukujaca towary po podaniu kodu kreskowego towaru
	structTowar * Towar;
	Towar = Zapamietaj();

	int ilosc, ilosc2, i, licznik = 0;
	ilosc = Wyszukaj_Kod_Towaru();

	for (i = 0; i < ilosc; i++){
		if (Towar[i].iKodKreskowy == kod){
			cout << " Kod kreskowy " << Towar[i].iKodKreskowy << endl;
			cout << " Nazwa towaru " << Towar[i].sNazwa << endl;
			cout << " Cena towaru " << Towar[i].fCena << endl;
			cout << " Ilosc: " << Towar[i].iIlosc << endl << endl;
			return true;
		}

	}
	cout << " Nie znaleziono produktu o podanym kodzie" << endl;
	return true;
}

int Wyswietl_Kod2(int kod){ //Funkcja wyszukujaca towary po podaniu kodu kreskowego towaru
	structTowar * Towar;
	Towar = Zapamietaj();

	int ilosc, i, licznik = 0;
	ilosc = Wyszukaj_Kod_Towaru();

	for (i = 0; i < ilosc; i++){
		if (Towar[i].iKodKreskowy == kod){
			licznik++;
		}
	}
	if (licznik == 0){
		cout << " Nie znaleziono produktu o podanym kodzie" << endl;
		return 1;
	}
	else
		return 0;
}
int Sprawdz_Kod(int kod){ //funkcja sprawdzajaca, czy kod kreskowy towaru istnieje w bazie.
							//funkcja wykorzystywana przy dodawaniu produktow do bazy
	structTowar * Towar;
	Towar = Zapamietaj();

	int ilosc, i, licznik = 0;
	ilosc = Wyszukaj_Kod_Towaru();

	for (i = 0; i < ilosc; i++){
		if (Towar[i].iKodKreskowy == kod){
			cout << " Kod, ktory chcesz wprowadzic juz istnieje w bazie." << endl;
			cout << " Modyfikuj istniejacy towar, lub wprowadz produkt o innym kodzie" << endl;
			return 0;
		}
	}
	return 1;
}
bool Wyswietl_cene(float cena1, float cena2, int kategoria){//Funkcja wyszukująca towary z przedzialu cenowego (cena1-cena2), z uwzględnieniem kategorii towaru

	structTowar * Towar;
	Towar = Zapamietaj();

	int ilosc, ilosc2, i, licznik = 0;
	string sKategoria;
	ilosc = Wyszukaj_Kod_Towaru();

	switch (kategoria){
	case 1:  sKategoria = "komputer"; break;
	case 2:  sKategoria = "kamera"; break;
	case 3:  sKategoria = "aparat"; break;
	default: cout << " Nie udalo sie otworzyc pliku!"; exit(0);
	}

	for (i = 0; i < ilosc; i++){
			if (Towar[i].fCena >= cena1 && Towar[i].fCena <= cena2 && Towar[i].sKategoria==sKategoria){
				cout << " Nazwa towaru " << Towar[i].sNazwa << endl;
				cout << " Kod kreskowy " << Towar[i].iKodKreskowy << endl;
				cout << " Cena towaru " << Towar[i].fCena << endl;
				cout << " Ilosc: " << Towar[i].iIlosc << endl << endl;
				licznik++;
			}
		}

	if (licznik == 0){
		cout << " Brak produktu spelniajacego kryteria cenowe" << endl;
}
	return true;
}


int Stan_Minimalny(int ile){ //Funkcja zwracajaca towary, o ilosci <= zadanemu argumentowi 'ile'

	cout << " Stan ponizszych produktow jest w ilosci mniejszej niz "<<ile<< endl;
	structTowar * Towar;
	Towar = Zapamietaj();

	int ilosc, ilosc2, i, licznik = 0;
	ilosc = Wyszukaj_Kod_Towaru();

	for (i = 0; i < ilosc; i++){
		if (Towar[i].iIlosc <= ile){
			cout << " Kod kreskowy " << Towar[i].iKodKreskowy << endl;
			cout << " Nazwa towaru " << Towar[i].sNazwa << endl;
				cout << " Ilosc: " << Towar[i].iIlosc << endl << endl;
			}
	}
	cout << " Uzupelnij stany magazynowe!" << endl;
	return 1;
}
bool Edycja_Ilosc(int kodkreskowy, int Oile){ //funkcja modyfikujaca ilosc towarow. Dodaje 'Oile' towarow do aktualnej ilosci w pliku towary.txt
											//Wykorzystywana przy "Przyjmowaniu towarow"

	if (Wyswietl_Kod2(kodkreskowy) != 0){
		cout << " Sprobuj jeszcze raz podajac kod kreskowy produktu z bazy" << endl;
		return true;
	}
	else{
		cout << endl << " Edytujesz towar o nastepujacych danych" << endl << endl;
		Wyswietl_Kod(kodkreskowy);
		fstream plik_kopia;
		plik_kopia.open("kopia.txt", ios::out | ios::app); //otwarcie pliku do odczytu i zapisu

		if (plik_kopia.good() == false){
			cout << " Nie udalo sie otworzyc pliku!"; exit(0);
		}

		structTowar * Towar;
		Towar = Zapamietaj();

		int ilosc, i;
		ilosc = Wyszukaj_Kod_Towaru();

		for (i = 0; i < ilosc; i++){
			if (Towar[i].iKodKreskowy == kodkreskowy){
				Towar[i].iIlosc = Towar[i].iIlosc + Oile;
				cout << " Nowa ilosc towaru " << Towar[i].iIlosc << endl;
			}
		}
		Kopia(Towar, ilosc);
		plik_kopia.close();

		if (remove("towary.txt") != 0)
			perror(" Blad usuwania pliku");

		int wynik;
		char oldname[] = "kopia.txt";
		char newname[] = "towary.txt";
		wynik = rename(oldname, newname);
		if (wynik == 0)
			cout << " Poprawnie dodano towar" << endl;
		else	perror("Blad zmiany nazwy pliku");

		return true;
	}

}
bool Edycja_Ilosc2(int kodkreskowy, int ile){ //funkcja modyfikujaca ilosc towarow. Zamienia ilosc w pliku towary.txt na wartosc 'ile'
											//Wykorzystywana przy "Modyfikacji ilosci towarow"
	if (Wyswietl_Kod2(kodkreskowy) != 0){
		cout << " Sprobuj jeszcze raz podajac kod kreskowy produktu z bazy" << endl;
		return true;
	}
	else{
		cout << endl << " Edytujesz towar o nastepujacych danych" << endl << endl;
		Wyswietl_Kod(kodkreskowy);
		fstream plik_kopia;
		plik_kopia.open("kopia.txt", ios::out | ios::app); //otwarcie pliku do odczytu i zapisu

		if (plik_kopia.good() == false){
			cout << " Nie udalo sie otworzyc pliku!"; exit(0);
		}

		structTowar * Towar;
		Towar = Zapamietaj();

		int ilosc, i;
		ilosc = Wyszukaj_Kod_Towaru();

		for (i = 0; i < ilosc; i++){
			if (Towar[i].iKodKreskowy == kodkreskowy){
				Towar[i].iIlosc = ile;
				cout << " Aktualna ilosc towarow w magazynie " << Towar[i].iIlosc << endl;
			}
		}
		Kopia(Towar, ilosc);
		plik_kopia.close();

		if (remove("towary.txt") != 0)
			perror(" Blad usuwania pliku");

		int wynik;
		char oldname[] = "kopia.txt";
		char newname[] = "towary.txt";
		wynik = rename(oldname, newname);
		if (wynik == 0)
			cout << " Poprawnie zmieniono ilosc towarow w magazynie" << endl;
		else	perror("Blad zmiany nazwy pliku");

		return true;
	}
}

bool Edycja_Nazwa(int kodkreskowy, string NowaNazwa){ //Funkcja edytująca nazwę towaru
	if (Wyswietl_Kod2(kodkreskowy) != 0){
		cout << " Sprobuj jeszcze raz podajac kod kreskowy produktu z bazy" << endl;
		return true;
	}
	else{
		cout << endl << " Edytujesz towar o nastepujacych danych" << endl << endl;
		Wyswietl_Kod(kodkreskowy);

		fstream plik_kopia;
		plik_kopia.open("kopia.txt", ios::out | ios::app); //otwarcie pliku do odczytu i zapisu

		if (plik_kopia.good() == false){
			cout << " Nie udalo sie otworzyc pliku!"; exit(0);
		}

		structTowar * Towar;
		Towar = Zapamietaj();

		int ilosc, i;
		ilosc = Wyszukaj_Kod_Towaru();

		for (i = 0; i < ilosc; i++){
			if (Towar[i].iKodKreskowy == kodkreskowy){
				Towar[i].sNazwa = NowaNazwa;
				cout << " Nowa nazwa towaru " << Towar[i].sNazwa << endl;
			}
		}
		Kopia(Towar, ilosc);
		plik_kopia.close();

		if (remove("towary.txt") != 0)
			perror(" Blad usuwania pliku");

		int wynik;
		char oldname[] = "kopia.txt";
		char newname[] = "towary.txt";
		wynik = rename(oldname, newname);
		if (wynik == 0)
			cout << " Poprawnie zmieniono nazwe towaru" << endl;
		else	perror(" Blad zmiany nazwy pliku");

		return true;
	}
}

bool Edycja_Cena(int kodkreskowy, float NowaCena){ //Funkcja edytująca cenę towaru
	if (Wyswietl_Kod2(kodkreskowy) != 0){
		cout << " Sprobuj jeszcze raz podajac kod kreskowy produktu z bazy" << endl;
		return true;
	}
	else{
		cout << endl << " Edytujesz towar o nastepujacych danych" << endl << endl;
		Wyswietl_Kod(kodkreskowy);
		fstream plik_kopia;
		plik_kopia.open("kopia.txt", ios::out | ios::app); //otwarcie pliku do odczytu i zapisu

		if (plik_kopia.good() == false){
			cout << " Nie udalo sie otworzyc pliku!"; exit(0);
		}

		structTowar * Towar;
		Towar = Zapamietaj();

		int ilosc, i;
		ilosc = Wyszukaj_Kod_Towaru();

		for (i = 0; i < ilosc; i++){
			if (Towar[i].iKodKreskowy == kodkreskowy){
				Towar[i].fCena = NowaCena;
				cout << " Nowa cena towaru " << Towar[i].fCena << endl;
			}
		}
		Kopia(Towar, ilosc);
		plik_kopia.close();

		if (remove("towary.txt") != 0)
			perror(" Blad usuwania pliku");

		int wynik;
		char oldname[] = "kopia.txt";
		char newname[] = "towary.txt";
		wynik = rename(oldname, newname);
		if (wynik == 0)
			cout << " Poprawnie zmieniono cene towaru" << endl;
		else	perror(" Blad zmiany nazwy pliku");

		return true;
	}
}
int Sprawdzenie_Kod(void){ //funkcja sprawdzajaca, czy kod kreskowy podawany przez uzytkowanika jest w poprawnym formacie. 
							//w razie wczytania znakow innych niz cyfry, program wyswietli komunikat o blednym formacie danych
	int zmienna;
	cout << " Podaj kod kreskowy produktu ";
	if (cin >> zmienna)
		return zmienna;
	else {
		while (!(cin >> zmienna)) //dopóki strumień jest w stanie błędu -> dopóki podawane są błędne dane
		{
			cin.clear(); //kasowanie flagi błędu strumienia
			cin.sync(); //kasowanie zbędnych znaków z bufora
			cout << " Podaj poprawny format kodu kreskowego!" << endl;
		}
		cout << " Wczytano: " << zmienna << endl;
	}

	return zmienna;
}
int Sprawdzenie_Dana(void){
	int zmienna;
	if (cin >> zmienna)
		return zmienna;
	else {
		while (!(cin >> zmienna)) //dopóki strumień jest w stanie błędu -> dopóki podawane są błędne dane
		{
			cin.clear(); //kasowanie flagi błędu strumienia
			cin.sync(); //kasowanie zbędnych znaków z bufora
			cout << " Podaj poprawna wartosc" << endl;
		}
		cout << " Wczytano: " << zmienna << endl;
	}
	return zmienna;
}

int Sprawdzenie_Cena(char tab[]){ //funkcja zamieniajaca przecinek na kropke przy podawaniu ceny w formacie zmiennoprzecinkowym
									//funkcja sprawdza rowniez format wprowadzanych danych
	int i;
	for (i = 0; i < 9; i++){
		if (tab[i] == ',') tab[i] = '.';
	}
	if (!atof(tab)){
		cout << " Niepoprawny format ceny!" << endl;
		return 0;
	}
	return 1;
}
