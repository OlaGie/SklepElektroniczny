/*
================================================================================
 Plik: main.c
--------------------------------------------------------------------------------
 Autorzy:       xxx
 Projekt:       Sklep elektroniczny
 Kompilator:    GNU GCC (Code::Blocks v13.12)
 Hardware:      PC
 Utworzony:     05.06.2014
--------------------------------------------------------------------------------
 Zawiera: Plik g³ówny
--------------------------------------------------------------------------------
 Komentarze:

================================================================================
*/


//=========================        Includes        ===========================//
//#include "struktury.hpp"
//#include "BazaKlient.hpp"
//#include "BazaTowarow.hpp"
#include "menu.hpp"
#include <locale.h>
#include <windows.h>

using namespace std;

//========================= Constants definitions  ===========================//
//=========================         Macros         ===========================//
//========================= Variables definitions  ===========================//
//========================= Functions definitions  ===========================//
//=================================== Main ===================================//

int main(void)
{
    //system("chcp 65001");
    //SetConsoleOutputCP(65001);
    //setlocale(LC_ALL, "polish");
    main_menu();
}
