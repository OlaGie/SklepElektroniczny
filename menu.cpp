/*
================================================================================
 Plik: menu.cpp
--------------------------------------------------------------------------------
 Autorzy:     xxx
 Projekt:     Sklep elektroniczny
 Kompilator:  Dev-C ++
 Hardware:    PC
 Utworzony:   05.06.2014
--------------------------------------------------------------------------------
 Zawiera: Menu programu oraz połączenie wszytkich elementow
 --------------------------------------------------------------------------------
*/
//#include<stdio.h>
#include<stdlib.h>
//#include<stdbool.h>
#include<iostream>
#include <windows.h>
#include <cstdlib>
#include "struktury.hpp"
//#include "BazaTowarow.hpp"
#include "main_magazyn.hpp"
#include "BazaKlient.hpp"
#include "Kasa.hpp"
#include "serwis.hpp"
#include "menu.hpp"

using namespace std;


void  menu()
{
    char choice;
        system("cls");

        	char a=201,b=205,c=187,d=186,e=204,f=185,g=200,h=188;
        	cout <<a;
           for (int i=0; i<71; i++)
                cout <<b;
        	cout <<c;

        	cout << "\n"<<d <<"\t\t\t Sklep elektroniczny - SZCZUREK \t\t"<< d <<"\n";

        	cout << e;
            for (int i=0; i<71; i++)
                cout <<b;
        	cout << f <<"\n";
        	cout << d;

        	cout << "\t Wersja programu 1.0.0 | Wszytkie prawa zastrzezone\t\t"<< d<<"\n";
        	cout << e;
            for (int i=0; i<71; i++)
                cout <<b;
        	cout << f <<"\n";
        	cout <<d <<"Menu:\t\t\t\t\t\t\t\t\t";
        	cout <<d<< "\n"<<d<<"\t\t\t 1. Kasa\t\t\t\t\t"<<d;
        	cout << "\n"<<d<<"\t\t\t 2. Magazyn\t\t\t\t\t"<<d;
        	cout << "\n"<<d<<"\t\t\t 3. Baza klentow\t\t\t\t"<<d;
        	cout << "\n"<<d<<"\t\t\t 4. Serwis\t\t\t\t\t"<<d;
        	cout << "\n"<<d<<"\t\t\t 5. Autorzy programu\t\t\t\t"<<d;
        	cout << "\n"<<d << "\t\t\t\t\t\t\t\t\t"<<d<<"\n"<<d<<"\t\t\t 0. Zamknij program\t\t\t\t"<<d;
        	cout << "\n"<<d<<"\t\t\t\t\t\t\t\t\t"<<d<<"\n"<<e;
            for (int i=0; i<71; i++)
                cout <<b;
        	cout <<f;
        	cout <<"\n"<<d<<"\t\t\t Wybierz i nacisnij Enter :=> \t\t\t"<<d<<"\n";
        	cout << g;
            for (int i=0; i<71; i++)
                cout <<b;
        	cout <<h<<"\n";

        cin >> choice;
        if (choice == '1') {
            cout << "\n\n Kasa";
            cout << "\n\n";

            // Tutaj wkleic odwolanie do pliku z kasa
            system("cls");
            menu_k1();

            menu();
        }
        else if (choice == '2') {
            cout << "\n\n Magazyn";
            cout << "\n\n";

            // Tutaj wkleic odwolanie do pliku z magazynem
            main_magazyn();
            //system("pause");
            menu();
        }
    	else if (choice == '3') {
            cout << "\n\n Baza klientow";
            cout << "\n\n";
            // Tutaj wkleic odwolanie do pliku z baza klientow
            vMenuKlient();
            //system("pause");
            menu();
        }
        else if (choice == '4') {
            cout << "\n\n Serwis";
            cout << "\n\n";

            // Tutaj wkleic odwolanie do pliku z serwisem
            system("cls");
            menu_s1();

            menu();
        }
        else if (choice == '5') {
                system("cls");
            cout << "\n\nAutorzy programu:\n";
            cout <<a;
            for (int i=0; i<23; i++)
                cout <<b;
        	cout <<c;
            cout << "\n"<<d<<"1.Aleksandra Gdowska\t"<<d<<"\n"<<d<<"2.Krzysztof Kowalski\t"<<d<<"\n"<<d<<"3.Krzysztof Lazowski\t"<<d<<"\n"<<d<<"4.Pawel Ciaranek\t"<<d<<"\n"<<d<<"5.Dawid Kozdras\t"<<d<<"\n";
           	cout << g;
            for (int i=0; i<23; i++)
                cout <<b;
       		cout <<h<<"\n";
		    system("pause");
            menu();
        }
        else if (choice == '0') {
            cout << "\n\n\tDziekujemy za skorzystanie z naszego programu.\n";
            exit( 0 );
        }
}

void main_menu()
{
 char choice = 0;
    do {
    menu();
    } while (choice != '5');
}
