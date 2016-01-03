/*
================================================================================
Plik: main_magazyn.cpp
--------------------------------------------------------------------------------
Autorzy:     Ola Gdowska
--------------------------------------------------------------------------------
Zawiera: Menu oraz poruszanie sie po magazynie
--------------------------------------------------------------------------------

================================================================================
*/
//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include "BazaTowarow.hpp"
#include <cstdlib>
#include <stdlib.h>
#include <istream>
#include <string>
#include <fstream>
#include <locale.h>
#include <Windows.h>
#include "Struktury.hpp"

using namespace std;

void menu_magazyn(void)
{
	cout << "   ---------------------------" << endl;
	cout << "   MENU MAGAZYN" << endl << endl;
	cout << "   1: Dodawanie produktow" << endl;
	cout << "   2: Przyjmowanie towaru" << endl;
	cout << "   3: Modyfikacja produktow" << endl;
	cout << "   4: Wyswietlanie produktow" << endl;
	cout << "   5: Niskie stany magazynowe" << endl;
	cout << "   0: Powrot do menu glownego" << endl;
	cout << "   ---------------------------" << endl;
}
void main_magazyn(void)
{
	menu_magazyn();
	int wybor_m;
	cin >> wybor_m;
	char cenac[9];
	int KodKreskowy, Ilosc, Wybor, i;
	struct structTowar Towar;
	while (wybor_m != 0){
		switch (wybor_m)
		{
		case 1:{
				   cout << "  DODAWANIE PRODUKTOW" << endl;
				   cout << "  -------------------" << endl;
				    KodKreskowy= Sprawdzenie_Kod();
					if (!Sprawdz_Kod(KodKreskowy)){ break; }
					Towar.iKodKreskowy = KodKreskowy;
				   cout << " Podaj nazwe towaru: ";
				   cin.sync(); //Czyszczenie zawartoœci strumienia wejœciowego
				   getline(cin, Towar.sNazwa);
				   cout << " Wybierz kategorie towaru: " << endl;
				   cout << " 1: Komputer" << endl;
				   cout << " 2: Aparat" << endl;
				   cout << " 3: Kamera" << endl;

				   Wybor = Sprawdzenie_Dana();
					   switch (Wybor){
					   case 1: {Towar.sKategoria = "komputer"; break;  }
					   case 2: {Towar.sKategoria = "aparat"; break; }
					   case 3: {Towar.sKategoria = "kamera"; break; }
					   default:{cout << " Wybierz poprawny numer kategorii!" << endl<<" Sprobuj jeszcze raz"; break; }
					   }
					   if (Wybor>3) { break; }
				   cout  << " Podaj cene towaru: " ;
				   cin >> cenac;
				   if (!Sprawdzenie_Cena(cenac)) { break; }
				   Towar.fCena=atof(cenac);

				   cout << " Podaj podatek od towaru: ";
				   Towar.iPodatek = Sprawdzenie_Dana();
				   if (Towar.iPodatek > 100){
					   while (Towar.iPodatek > 100){
						   cout << " Podaj poprawna wartosc podatku" << endl;
						   Towar.iPodatek = Sprawdzenie_Dana();
					   }
				   }
				   cout << " Podaj ilosc jaka chcesz dodac: ";
				   Towar.iIlosc = Sprawdzenie_Dana();
				   cout << endl;
				   Dodaj(Towar);
				   system("pause");
				   break;
		}
		case 2:{//przyjmowanie towaru
				   cout << "  PRZYJMOWANIE TOWAROW" << endl;
				   cout << "  --------------------" << endl;
				   KodKreskowy = Sprawdzenie_Kod();
				   cout << " Podaj ilosc jaka chcesz dodac: ";
				   Ilosc = Sprawdzenie_Dana();
				   Edycja_Ilosc(KodKreskowy, Ilosc);
				   system("pause");
				   break;
		}
		case 3:{ //modyfikacja nazwy,ceny,ilosci
				   cout << "  MODYFIKACJA TOWAROW" << endl;
				   cout << "  -------------------" << endl;
				   string sNazwa;
				   cout << " Wybierz co zmienic" << endl;
				   cout << " 1. Nazwa" << endl;
				   cout << " 2. Cena" << endl;
				   cout << " 3. Ilosc" << endl;
				   int wybor_k;
				   cin >> wybor_k;
				   switch (wybor_k){
				   case 1:{
							  cout << "  MODYFIKACJA NAZWY TOWARU" << endl;
							  cout << "  ------------------------" << endl;
							  fflush(stdin);
							  KodKreskowy = Sprawdzenie_Kod();
							  fflush(stdin);
							  cout << " Podaj nowa nazwe towaru ";
							  getline(cin, sNazwa);
							  cout << endl;
							  Edycja_Nazwa(KodKreskowy, sNazwa);
							  system("pause");
							  break;
				   }

				   case 2:{
							  cout << "  MODYFIKACJA CENY TOWARU" << endl;
							  cout << "  -----------------------" << endl;
							  float cena;
							  fflush(stdin);
							  KodKreskowy = Sprawdzenie_Kod();
							  fflush(stdin);
							  cout << " Podaj nowa cene towaru ";
							  cin >> cenac;
							  if (!Sprawdzenie_Cena(cenac)) { break; }
							  cena = atof(cenac);
							  cout << endl;
							  Edycja_Cena(KodKreskowy, cena);
							  fflush(stdin);
							  system("pause");
							  break;
				   }
				   case 3:{
							  cout << "  MODYFIKACJA ILOSCI TOWARU" << endl;
							  cout << "  -------------------------" << endl;
							  int ile;
							  KodKreskowy = Sprawdzenie_Kod();
							  fflush(stdin);
							  cout << " Podaj rzeczywista ilosc towaru w magazynie ";
							  Ilosc = Sprawdzenie_Dana();
							  Edycja_Ilosc2(KodKreskowy, Ilosc);
							  system("pause");
							  break;
				   }
				   default: cout << " Wybierz wlasciwy numer" << endl;
					   break;
				   }
				   break;
		}

		case 4:{//wyswietlanie produktow
				   cout << "  WYSWIETLANIE TOWAROW" << endl;
				   cout << "  --------------------" << endl;
				   string sNazwa;
				   cout << " Wybierz kryterium, zeby wyswietlic produkty" << endl;
				   cout << " 1. Kod" << endl;
				   cout << " 2. Nazwa" << endl;
				   cout << " 3. Cena" << endl;
				   Wybor = Sprawdzenie_Dana();
				   switch (Wybor){
				   case 1:{
							  cout << "  WYSWIETLANIE TOWAROW PO KODZIE KRESKOWYM" << endl;
							  cout << "  ----------------------------------------" << endl;
							  fflush(stdin);
							  KodKreskowy = Sprawdzenie_Kod();
							  fflush(stdin);
							  Wyswietl_Kod(KodKreskowy);
							  break;
				   }
				   case 2:{
							  cout << "  WYSWIETLANIE TOWAROW PO NAZWIE" << endl;
							  cout << "  ------------------------------" << endl;
							  cout << "Podaj nazwe produktu zaczynajac od marki " << endl;
							  cin.sync(); //Czyszczenie zawartoœci strumienia wejœciowego
							  getline(cin, sNazwa);
							  Wyswietl_nazwe(sNazwa);
							  break;
				   }
				   case 3:{
							  cout << "  WYSWIETLANIE TOWAROW PO ZAKRESIE CENOWYM" << endl;
							  cout << "  ----------------------------------------" << endl;
							  float cena1, cena2;
							  cout << " Podaj zakres cenowy " << endl;
							  cout << " Cena od ";
							  cin >> cenac;
							  if (!Sprawdzenie_Cena(cenac)) { break; }
							  cena1 = atof(cenac);
							  cout << " do ";
							  cin >> cenac;
							  if (!Sprawdzenie_Cena(cenac)) { break; }
							  cena2 = atof(cenac);
							  cout << " Kategoria: " << endl;
							  cout << " 1: Komputer" << endl;
							  cout << " 2: Kamera" << endl;
							  cout << " 3: Aparat" << endl;
							  Wybor=Sprawdzenie_Dana();
							  Wyswietl_cene(cena1, cena2, Wybor);
							  break;
				   }
				   default: cout << " Wybierz wlasciwy numer" << endl;
					   break;
				   }
				   break;
		}
		case 5:{  //niskie stany magazynowe
				   cout << "  WYSWIETLANIE NISKICH STANOW MAGAZYNOWYCH TOWAROW" << endl;
				   cout << "  ------------------------------------------------" << endl;
				   cout << " Dla jakiej ilosci minimalnej pokazac produkty?" << endl;
				   Ilosc = Sprawdzenie_Dana();
				   Stan_Minimalny(Ilosc);
				   break;
		} 
		case 0:{ //menu glowne
				   return;
		}

		}
		cout << endl;
		menu_magazyn();

		fflush(stdin);
		fflush(stdout);
		cin >> wybor_m;
	}

	return;
}
