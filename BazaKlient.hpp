/*
================================================================================
 Plik: BazaKlient.hpp
--------------------------------------------------------------------------------
 Autorzy:       xxx
 Projekt:       Sklep elektroniczny
 Kompilator:    GNU GCC (Code::Blocks v13.12)
 Hardware:      PC
 Utworzony:     11.05.2014
--------------------------------------------------------------------------------
 Zawiera: Deklaracje funkcji obsługi bazy danych klientów.
--------------------------------------------------------------------------------
 Komentarze:
    Ważne - wszystkie niedociągnięcia, potrzeby poprawek, itp. są oznaczone "ToDo"
--------------------------------------------------------------------------------
 Change log:

================================================================================
*/

#ifndef BAZAKLIENT_HPP_INCLUDED
#define BAZAKLIENT_HPP_INCLUDED

//=========================        Includes        ===========================//
#include "Struktury.hpp"
using namespace std;

//========================= Functions declarations ===========================//
//bool bDodajKlienta(int iKodKlienta, string sImie, string sNazwisko, string sFirma, int iNIP, int iRegon, string sNumerTelefonu, int iRabat);
bool bDodajKlienta(struct structKlient *DaneKlienta);
bool bEdytujKlienta(struct structKlient *DaneKlienta);
bool bUsunKlienta(int iKodKlienta);
structKlient* PobierzKlienta(int iKodKlienta);
int* piSzukajKlienta(string sNazwaZmiennej, long long int iWartoscZmiennej);
int* piSzukajKlienta(string sNazwaZmiennej, string sWartoscZmiennej);
int iOstatniKlient(void);
void vMenuKlient(void);
int iWyswietlListeKlientow(void);
int iPobierzInt(void);
string sWyswietlZmienne(void);
int iNumerZmiennej(string sNazwaZmiennej);
void vWyswietlWyniki(int *piWyniki);

#endif // BAZAKLIENT_HPP_INCLUDED
