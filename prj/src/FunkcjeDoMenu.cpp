#include "FunkcjeDoMenu.hh"


void WyswietlMenu()
{
  cout<<"j - lot na wprost"<< endl;
  cout<<"o - obrot drona"<<endl;
  cout<<"w - wyswietl menu"<<endl;
  cout<<"D - dodaj drona"<<endl;
  cout<<"U - usun drona"<<endl;
  cout<<"P - Dodaj przeszkode"<<endl;
  cout<<"k - koniec dzialania programu"<< endl;
  cout<<"\nInformacje o Wektorach3D: \n";
  cout << "Ilosc lacznie stworzonych obiektow klasy Wektor3D: ";
  cout << Wektor3D::ZwrocLacznaIloscWektorow()<<endl;
  cout << "Ilosc istniejacych obiektow klasy Wektor3D: ";
  cout << Wektor3D::ZwrocIloscWektorow()<<endl;
  cout <<"\nInformacje o Obiektach Sceny\n";
  cout << "Ilosc lacznie stworzonych obiektow klasy ObiektSceny: ";
  cout << ObiektSceny::ZwrocLacznaIloscObiektowSceny()<<endl;
  cout << "Ilosc istniejacych obiektow klasy ObiektSceny: ";
  cout << ObiektSceny::ZwrocIloscObiektowSceny()<<endl;
}


bool wczytaj_sprawdz_zapisz_znak(istream &Strm, char &znak)
{
	char temp;
	Strm >> temp;
	if(Strm.fail())
	{
		cout<<"Nie podales znaku, Blad\n";
		Strm.clear();
		Strm.ignore(1000, '\n');         										
		return false;
	}
	else
	{
		znak = temp;
		return true;
	}

}

bool wczytaj_sprawdz_zapisz_liczbe(istream &Strm, double &liczba)
{
	double temp;
	Strm >> temp;
	if(Strm.fail())
  {
		cout<<"Nie podales liczby, Blad\n";
		Strm.clear();
		Strm.ignore(1000, '\n');         										
		return false;
	}
	else
	{
		liczba = temp;			//jesli wszystko ok to przypisz do liczby wartosc wczytana
		return true;
	}
}


bool wczytaj_sprawdz_zapisz_liczbe(istream &Strm, int &liczba)
{
	int temp;
	Strm >> temp;
	if(Strm.fail())
	{
		cout<<"Nie podales liczby, Blad\n";   
		Strm.clear();
		Strm.ignore(1000, '\n');        				//jesli zostalo wczytanego cos nieprawidlowego to zwroc strumien
		return false;
	}
	else
	{
		liczba = temp;												//jesli wszystko ok to przypisz do liczby wartosc wczytana
		return true;
	}
}







