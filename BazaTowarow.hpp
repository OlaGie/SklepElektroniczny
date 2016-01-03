/*
================================================================================
 Plik: BazaTowarow.hpp
--------------------------------------------------------------------------------
 Autor:     Ola Gdowska
--------------------------------------------------------------------------------
 Zawiera: Deklaracje funkcji obsługi bazy produktów.
 --------------------------------------------------------------------------------
================================================================================
*/

#ifndef BAZADANYCH_HPP_
#define BAZADANYCH_HPP_

//=========================        Includes        ===========================//
#include "struktury.hpp"
using namespace std;

//========================= Functions declarations ===========================//

structTowar* Zapamietaj();
int Wyszukaj_Kod_Towaru();
bool Dodaj(struct structTowar); 
bool Wyswietl_Kod(int iKodTowaru); 
int Wyswietl_Kod2(int kod);
bool Wyswietl_nazwe(string sNazwa); 
bool Wyswietl_cene(float cena1, float cena2, int kategoria);
int Stan_Minimalny(int ilosc);
bool Edycja_Ilosc(int kodkreskowy, int ilosc);
bool Edycja_Ilosc2(int kodkreskowy, int ile);
bool Kopia(struct structTowar Towar[], int licznik);
bool Edycja_Nazwa(int kodkreskowy, string NowaNazwa);
bool Edycja_Cena(int kodkreskowy, float NowaCena);
int Sprawdzenie_Kod(void);
int Sprawdzenie_Dana(void);
int Sprawdzenie_Cena(char tab[]);
int Sprawdz_Kod(int kod);

#endif // BAZADANYCH_HPP_
