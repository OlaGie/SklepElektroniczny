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
#include "struktury.hpp"


using namespace std;

struct zamowienie{   ///potrzebne zeby zaladowac do paragonu usluge serwisowa
int nr_uslugi;
std::string nazwa;
std::string opis;
string data;
float cena;

};


/// MENU MAIN KASY - Podstawowe
int menu_k1(){
    int wybor_menu_k1;
    cout<<"\t |--------------------------------------------|  \n";
    cout<<"\t |                                            |  \n";
    cout<<"\t |	1. Obsluga paragonu	              |  \n";
 	cout<<"\t |	2. Sprawdzanie towaru                 |  \n";
    cout<<"\t |	0. Wyjscie do poprzedniego menu       |  \n";
    cout<<"\t |                                            |  \n";
    cout<<"\t |--------------------------------------------|  \n";
    cout<<"\t |                                            |  \n";
	cout<<"\t | Co chcesz robic ??                         |  \n";
    cout<<"\t |                                            |  \n";
    cout<<"\t |--------------------------------------------|  \n";

    cin>>wybor_menu_k1;

    switch(wybor_menu_k1)
	{
		case 1:
		{
		    system( "cls" );
		    paragon();
			break;
		}
		case 2:
		{
            system( "cls" );
                sprawdzenie();
                menu_k1();
			break;
		}
		case 0:
		{ system( "cls" );
            main();
			break;
		}
        default:
      {
           menu_k1();
      }
}
return (0);
}



int paragon(){     ///tworzy paragon
int wybor_menu_k2;

    PokazListe();
cout<<"|--------------------------------------------|\n";
    cout<<"|	1. Dodaj towar do paragonu           |\n";
 	cout<<"|	2. Dodaj usluge serwisowa            |\n";
 	cout<<"|	3. Zakoncz i drukuj paragon          |\n";
    cout<<"|	4. Usun pozycje z paragonu           |\n";
    cout<<"|	5. Wycofaj paragon                   |\n";
    cout<<"|	0. Wyjscie do poprzedniego menu      |\n";
cout<<"|--------------------------------------------|\n\n";
	cout<<"Co chcesz robic ??\n\n";

    cin>>wybor_menu_k2;

    switch(wybor_menu_k2)
	{
		case 1:
		{
    system( "cls" );


       dodaj_do_paragonu();
        paragon();




			break;
		}
		case 2:
		{
           	     system( "cls" );
		   dodajuslugedop();
		    paragon(); ///funkcje wczytywania z pliku serwisowego

			break;
		}

		case 3: ///zakoncz i drukuj paragon
		{
           	     system( "cls" );
           	     drukowanie_paragonu();
           	      paragon();

			break;
		}

				case 4:/// usun wybrana pozycje z paragonu
		{
		     system( "cls" );
		    cout<<"Wybierz pozycje którą usunąć";
           	    usun_pozycje();
           	    paragon();

			break;

			case 5:/// usun paragon i nie zapisuj
		{
		    system( "cls" );
		    usun_paragon();


			break;
		}
		case 0:
		{ system( "cls" );
            menu_k1();
			break;
		}
        default:
      {
           paragon();
      }
}

return (0);
}

}



///struktura listy dwukierunkowej do tworzenia paragonu

  struct produkt{
    int KodT; ///produktu
	int Kod; ///kreskowy
	string Nazwa;
	string Kategoria;
	float Cena;
	int Podatek;
	int Ilosc;
	struct produkt *poprzedni,*nastepny;
	 };

   int ile=0;
     produkt Lista[99]; ///tworzy tablice struktur o wielkosci 99



void PokazListe(){  /// wyswietla aktualny paragon
    system( "cls" );

      cout<<"               Lista produktow"<<endl<<endl;
      for (int dlugosc=0;dlugosc<ile;dlugosc++)
      {
          cout<<dlugosc+1<<"  |  ";
          cout<<Lista[dlugosc].Kod<<"  |  ";
          cout<<Lista[dlugosc].Nazwa<<"  |  ";
          cout<<Lista[dlugosc].Cena<<"  |  ";
          cout<<Lista[dlugosc].Ilosc<<endl<<endl;
      }
sumowanie();
  }


int dodaj_do_paragonu() ///dodawanie po kodzie do paragonu
{
      int Kod;
      cout<<endl<< "Podaj kod kreskowy"<<endl<<endl;
      cin>>Kod;

    structTowar * Towar;
	Towar = Zapamietaj();

		        	int ilosc, i;
                    ilosc = Wyszukaj_Kod_Towaru();

	for (i = 0; i < ilosc; i++) ///przepisuje z tablicy magazynu do listy dwukierunkowej
	{
		if (Towar[i].iKodKreskowy == Kod)


            {
                int ile_na_magazynie,wpisana_ilosc;
                cout<<endl<<Towar[i].iKodKreskowy<<"   "<<Towar[i].sNazwa<<"   "<<Towar[i].fCena<<"   "<<Towar[i].iIlosc<<endl<<endl;
                cout<<"podaj ilosc nie wiecej niz: "<<"   "<<Towar[i].iIlosc<<endl<<endl;
                cin>>wpisana_ilosc;
                if (wpisana_ilosc>Towar[i].iIlosc){

                }
			  Lista[ile].Kod = Towar[i].iKodKreskowy;
			Lista[ile].Nazwa = Towar[i].sNazwa;
			 Lista[ile].Cena = Towar[i].fCena;
			 ile_na_magazynie=Towar[i].iIlosc;
			Lista[ile].Ilosc = wpisana_ilosc;

            ile++;
            }
    }
    return (0);
}



int sprawdzenie() ///sprawdzanie nazwy i ceny towaru po kodzie
{
      int Kod;
      cout<< "Podaj kod kreskowy"<<endl;
      cin>>Kod;

    structTowar * Towar;
	Towar = Zapamietaj();

		        	int ilosc, i;
                    ilosc = Wyszukaj_Kod_Towaru();

	for (i = 0; i < ilosc; i++)
	{
		if (Towar[i].iKodKreskowy == Kod)
            {
			cout<<Towar[i].iKodKreskowy<<"  |  ";
			cout<<Towar[i].sNazwa<<"  |  ";
			cout<<Towar[i].fCena<<"  |  ";
			cout<<Towar[i].iIlosc<<endl<<endl;
            }
    }
    return (0);
}

int usun_pozycje()  ///usuwa wybrana pozycje z paragonu
{
    if (ile<1){
            paragon();
    }
    else {
  int dlugosc;
  PokazListe();
    cout<<"wybierz pozycje do usuniecia:"<<endl<<endl;
cin>>dlugosc;
dlugosc--;
          cout<<endl<<"Czy usunac towar z paragonu ?"<<endl<<endl;
              cout<<"1. - USUN"<<endl<<endl;
              cout<<"0. - NIE USUWAJ"<<endl<<endl;

          cout<<dlugosc+1<<"  |  ";
          cout<<Lista[dlugosc].Kod<<"  |  ";
          cout<<Lista[dlugosc].Nazwa<<"  |  ";
          cout<<Lista[dlugosc].Cena<<"  |  ";
          cout<<Lista[dlugosc].Ilosc<<endl<<endl;

          int potwierdz;
          cin>>potwierdz;
          cout<<endl<<endl;
          if (potwierdz=1){

for (int dousuniecia=dlugosc; Lista[dousuniecia].Kod>0; dousuniecia++)
      {
            Lista[dlugosc].Kod = Lista[dlugosc+1].Kod;
			Lista[dlugosc].Nazwa = Lista[dlugosc+1].Nazwa;
			Lista[dlugosc].Cena = Lista[dlugosc+1].Cena;
			Lista[dlugosc].Ilosc = Lista[dlugosc+1].Ilosc;
      }
ile--;
            paragon();
                        }
        else {
            paragon();
        }

return (0);
}

}


int usun_paragon(){   /// kasowanie obecnego paragonu

cout<<endl<<"Czy usunac paragon"<<endl<<endl;
              cout<<"1. - USUN"<<endl<<endl;
              cout<<"0. - NIE USUWAJ"<<endl<<endl;
              int wybor;
              cin>>wybor;

              if (wybor=1){
                    ile=0;
            paragon();}
            else {
                    paragon();
            }

return (0);

}


int sumowanie(){    /// wyswietlanie sumy rachunku - trzeba zmienic na float albo double !!

float suma_razem=0;

      for (int dlugosc=0;dlugosc<ile;dlugosc++)
      {
          suma_razem=suma_razem+(Lista[dlugosc].Cena*Lista[dlugosc].Ilosc);


      }
cout<<"----------------------------------------------"<<endl;
cout<<"| RAZEM:   ";
cout<<suma_razem<<"                                 |"<<endl;
cout<<"----------------------------------------------"<<endl<<endl;
return (0);
}


int drukowanie_paragonu() /// wyswietla paragon usuwa z magazynu tyle towarow co na paragonie, kasuje obecny paragon,
{
         for (int dlugosc=0;dlugosc<ile;dlugosc++)
      {
Edycja_Ilosc(Lista[dlugosc].Kod,-Lista[dlugosc].Ilosc);

      }

system( "cls" );
  cout<<" DRUKOWANIE PARAGONU "<<endl<<endl;
   PokazListe();

ile=0;
cout<<"----------------------------"<<endl<<endl;
cout<<"PARAGON WYDRUKOWANY"<<endl<<endl;
cout<<"----------------------------"<<endl<<endl;
system("pause");
paragon();

return (0);
}

bool dodajuslugedop(){ /// Funkcja wyszukujaca zlecenia serwisowe po podaniu nr zlecenia
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

            Lista[ile].Kod = Lista_2[i].nr_uslugi;
			Lista[ile].Nazwa = Lista_2[i].nazwa;
			Lista[ile].Cena = Lista_2[i].cena;
			Lista[ile].Ilosc = 1;

             ile++;
			return true;
		}
	}
	system( "cls" );
    cout << "\t |-------------------------------------------------|" <<endl<<endl;
	cout << "\t | Nie znaleziono uslugi o podanym numerze         |"<< endl;
    cout << "\t |-------------------------------------------------|" <<endl<<endl;
    system("pause");
	return true;
}







