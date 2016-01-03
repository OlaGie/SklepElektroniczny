/*
Autor xxx

*/
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "Kasa.hpp"
#include "BazaTowarow.hpp"
#include "serwis.hpp"


using namespace std;


int menu_s1(){

cout<<"----------------------------------------------"<<endl;
cout<<"|\t witaj w serwisie                   |"<<endl;
cout<<"|                                           |"<<endl;
cout<<"|\t Co chcesz zrobic                   |"<<endl;
cout<<"|\t 1 - Dodaj nowe zlecenie            |"<<endl;
cout<<"|\t 2 - Wyszukaj istniejace            |"<<endl;
cout<<"|\t 3 - Wyswietl wszystkie             |"<<endl;
cout<<"|\t 0 - wyjscie do poprzedniego menu   |"<<endl;
cout<<"----------------------------------------------"<<endl;
int x;
cout<<"Twoj wybor:"; cin>> x; cout<<endl<<endl;

switch(x) {
case 1: {
system( "cls" );
Dodajzam();

break;
}
case 2: {

    fflush(stdin);
        system( "cls" );

 Wyswietl_zam();

menu_s1();
break;
}

case 3: {

    fflush(stdin);
Wyswietl_wszystkie();

menu_s1();
break;
}

case 0: {
    system( "cls" );
 main();
break;
}
default:
    system( "cls" );
   menu_s1();
}
return(0);
}


struct zamowienie{
int nr_uslugi;
std::string nazwa;
std::string opis;
string data;
float cena;

};


int liczba_uslug = 0;
zamowienie Lista_2[2000];



int Dodajzam(){
struct zamowienie Lista_2;

int nr;
nr = Wyszukaj_Nr_Uslugi();
Lista_2.nr_uslugi = nr + 1;

cout<<"\t  Dodajesz nowa usluge:"<<endl<<endl;
cout<<"\t  Podaj nazwe:"<<endl;
cin.sync();
getline(cin, Lista_2.nazwa);

cout<<endl;

cout<<"\t  Dodaj opis usterki"<<endl;
cin.sync();
getline(cin,Lista_2.opis);
cout<<endl;

cout<<"\t  Dodaj date zlozenia zamowienia"<<endl;
cin>>Lista_2.data;
cout<<endl;

cout<<"\t  Wpisz Cene"<<endl;
cin>>Lista_2.cena;
cout<<endl;

cout << "\t Numer uslugi: " << Lista_2.nr_uslugi << endl;


liczba_uslug++;
DodajD(Lista_2);
menu_s1();
return 0;
}


int Pokazzamowienie(){  // wyswietla aktualnie wprowadzone uslugi

    system( "cls" );

      cout<<"Zamowienia serwisowe"<<endl<<endl;
      for (int dlugosc=0;dlugosc<liczba_uslug;dlugosc++)
      {
          cout<<dlugosc+1<<"  |  ";
          cout<<Lista_2[dlugosc].nr_uslugi<<"  |  ";
          cout<<Lista_2[dlugosc].nazwa<<"  |  ";
          cout<<Lista_2[dlugosc].opis<<"  |  ";
          cout<<Lista_2[dlugosc].data<<"  |  ";
          cout<<Lista_2[dlugosc].cena<<endl<<endl;

      }
return(0);
  }



int Wyszukaj_Nr_Uslugi(){ //funkcja przeszukuje plik serwis.txt
	zamowienie Lista_2[2000];
	int nr_linii = 1, i=0, temp;
	string linia;

	fstream plik;
	plik.open("serwis.txt", ios::in);

	if (plik.good() == false){
		cout << "Nie udalo sie otworzyc pliku!";
		exit(0);
	}
	while (getline(plik, linia))
	{
		switch (nr_linii){
		case 1: {Lista_2[i].nr_uslugi = atoi(linia.c_str()); temp = i+1; }
		}
		if (nr_linii == 6) { nr_linii = 0; i++; }
		nr_linii++;

	}
	plik.close();
			return temp;
	}


void DodajD(struct zamowienie Lista_2){// Funkcja dodaj¹ca zlecenia serwisowe
	fstream plik;
	plik.open("serwis.txt", ios::out | ios::app);
int nr_zam;
	nr_zam = Wyszukaj_Nr_Uslugi();

	plik << Lista_2.nr_uslugi << endl;
	plik << Lista_2.nazwa << endl;
	plik << Lista_2.opis << endl;
	plik << Lista_2.data << endl;
	plik << Lista_2.cena << endl;

	plik << endl;
	plik.close();

	return;
}

zamowienie* pamiec(){ //Funkcja wczytująca wzystkie rekordy z pliku serwis.txt Zwraca wskaznik do struktur.


	zamowienie *Lista_2;
	Lista_2 = new zamowienie[Wyszukaj_Nr_Uslugi()];
	zamowienie Temp;

	string linia; int i = 0, nr_linii = 1;
	int k = 1;

	fstream plik;
	plik.open("serwis.txt", ios::in);

	if (plik.good() == false){
		cout << "Nie udalo sie otworzyc pliku!"; exit(0);
	}
	while (!plik.eof()){
		getline(plik, linia);

		switch (nr_linii)
		{
		case 1: Lista_2[i].nr_uslugi=atoi(linia.c_str()); break;
		case 2: Lista_2[i].nazwa=linia; break;
		case 3: Lista_2[i].opis=linia; break;
		case 4: Lista_2[i].data=linia; break;
		case 5: Lista_2[i].cena = atoi(linia.c_str()); break;

		case 6: break;
		}
		if (nr_linii == 6) {
			nr_linii = 0;
			i++;
		}
		nr_linii++;
	}
	plik.close();
	return Lista_2;
}


bool Wyswietl_zam(){ //Funkcja wyszukujaca zlecenia serwisowe po podaniu nr zlecenia
	zamowienie * Lista_2;
	Lista_2 = pamiec();
int nr;
cout << "\t |--------------------------|" <<endl;
cout << "\t |                          |" <<endl;
cout << "\t | podaj numer zamowienia:  |" <<endl;
cout << "\t |--------------------------|" <<endl<<endl;
cin>>nr;
	int ilosc, ilosc2, i, licznik = 0;
	ilosc = Wyszukaj_Nr_Uslugi();

	for (i = 0; i < ilosc; i++){
		if (Lista_2[i].nr_uslugi == nr){
            cout << "\t |>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" <<endl;
            cout << "\t |                                                 " <<endl;
			cout << "\t | Numer zamowienia         " << Lista_2[i].nr_uslugi << "                " << endl;
			cout << "\t | Nazwa uslugi             " << Lista_2[i].nazwa         << "                " << endl;
			cout << "\t | Opis                     " << Lista_2[i].opis                  << "                " << endl;
			cout << "\t | Data przyjecia           " << Lista_2[i].data        << "                " << endl;
			cout << "\t | Cena                     " << Lista_2[i].cena                  << "                " << endl;
            cout << "\t |                                                 " <<endl;
            cout << "\t |>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" <<endl;
            cout << "\t                                                  " <<endl;
			return true;
		}

	}
    cout << "\t |-------------------------------------------------|" <<endl<<endl;
	cout << "\t | Nie znaleziono uslugi o podanym numerze         |"<< endl;
    cout << "\t |-------------------------------------------------|" <<endl<<endl;
	return true;
}


bool Wyswietl_wszystkie(){ //Funkcja wyszukujaca zlecenia serwisowe w kolejności
	zamowienie * Lista_2;
	Lista_2 = pamiec();

    system( "cls" );

	int ilosc, ilosc2, i, licznik = 0;
	ilosc = Wyszukaj_Nr_Uslugi();

	for (i = 0; i < ilosc; i++){

            cout << "|----------------------------------------------------------------------|" << endl;
			cout << "|Nr: " << Lista_2[i].nr_uslugi << "   ";
			cout << "Nazwa uslugi: " << Lista_2[i].nazwa << "   ";
			cout << "Data przyjecia: " << Lista_2[i].data << "   ";
			cout << "Cena: " << Lista_2[i].cena << "    "<< endl;
            cout << "|Opis: " << Lista_2[i].opis << "|    "<< endl;

		}


	return true;
}















