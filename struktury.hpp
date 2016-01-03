/*
================================================================================
 Plik: struktury.hpp
--------------------------------------------------------------------------------
 Autorzy:           xxx
 Projekt:           Sklep elektroniczny
 Kompilator:        GNU GCC (Code::Blocks v13.12)
 Hardware:          PC
 Utworzony:         24.04.2014
--------------------------------------------------------------------------------
 Zawiera: Struktury do przechowywania danych klientów i towarów.
--------------------------------------------------------------------------------
 Komentarze:

================================================================================
*/

#ifndef STRUKTURY_HPP_INCLUDED
#define STRUKTURY_HPP_INCLUDED

//=========================        Includes        ===========================//
#include <iostream>
using namespace std;

//========================= Structures definitions ===========================//
//Struktura danych klienta z wartościami domyślnymi.
struct structKlient
{
    //Numer identyfikacyjny klienta w bazie klientów.
    int iKodKlienta;// = 0;
    //Imię / imiona klienta. W przypadku firmy zawiera dane przedstawiciela.
    string sImie;// = "Brak danych";
    //Nazwisko (również wieloczłonowe). W przypadku firmy zawiera dane przedstawiciela.
    string sNazwisko;// = "Brak danych";
    //Nazwa firmy. W przypadku klientów indywidualnych wartość ustawiona na "Brak".
    string sFirma;// = "Brak";
    //NIP - miało być long long int ale, z jakiegoś powodu, kompilator i tak robi int
    string sNIP;// = 0;
    //Regon 9cyfr
    long int liRegon;// = 0;
    //Numer telefonu kontaktowego do klienta. [+48 123456789]
    string sNumerTelefonu;// = 0;
    //Rabat dla klienta uwzględniany przy obliczaniu ceny sumarycznej. [%]
    int iRabat;// = 0;
};

//Struktura danych towaru z wartościami domyślnymi.
struct structTowar
{
	int iKodTowaru = 2;
	int iKodKreskowy=0;
	string sNazwa = "Brak danychhhh";
	string sKategoria;
	float fCena = 2;
	int iPodatek = 2;
	int iIlosc = 2;
};

#endif // STRUKTURY_HPP_INCLUDED
