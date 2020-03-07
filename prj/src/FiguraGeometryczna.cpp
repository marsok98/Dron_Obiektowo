#include "FiguraGeometryczna.hh"




void FiguraGeometryczna::PrzesunDodajDoWektoraPrzesuniecia(const Wektor3D &Wek)
{
    WektorPrzesuniecia = WektorPrzesuniecia + Wek;
    unsigned int i;
    for(i=0; i<Aktualny_Wierzcholek.size();i++)
    {
        Aktualny_Wierzcholek[i] = Poczatkowy_Wierzcholek[i] + WektorPrzesuniecia;
    }
}

void FiguraGeometryczna::Ustaw_Offset_DodajDo_Offsetu_(const Wektor3D &Wek)
{
  Wektor_Offsetu_ = Wektor_Offsetu_ + Wek;
  unsigned int i;
  for(i=0; i<Poczatkowy_Wierzcholek.size();i++)
  {
    Poczatkowy_Wierzcholek[i] = Poczatkowy_Wierzcholek[i] + Wektor_Offsetu_;
  }
  Aktualny_Wierzcholek = Poczatkowy_Wierzcholek;
}

void FiguraGeometryczna::Cofnij_Offset_()
{
  unsigned int i;
  for(i=0;i<Poczatkowy_Wierzcholek.size();i++)
  {
    Poczatkowy_Wierzcholek[i] = Poczatkowy_Wierzcholek[i] - Wektor_Offsetu_;
    Aktualny_Wierzcholek[i] = Aktualny_Wierzcholek[i] - Wektor_Offsetu_;
  }
}

void FiguraGeometryczna::Ustaw_Offset_()
{
  unsigned int i;
  for(i=0;i<Poczatkowy_Wierzcholek.size();i++)
  {
    Poczatkowy_Wierzcholek[i] = Poczatkowy_Wierzcholek[i] + Wektor_Offsetu_;
    Aktualny_Wierzcholek[i] = Aktualny_Wierzcholek[i] + Wektor_Offsetu_;
  }
}

void FiguraGeometryczna::PrzesunNaSrodekUkladuWspolrzednych()
{
  Aktualny_Wierzcholek = Poczatkowy_Wierzcholek;
}

void FiguraGeometryczna::WrocNaPozycjePoLekkimObrocie()
{
  unsigned int i;
  for(i=0;i<Aktualny_Wierzcholek.size();i++)
  {
    Aktualny_Wierzcholek[i] = Aktualny_Wierzcholek[i] + WektorPrzesuniecia;
  }
  
}

void FiguraGeometryczna::ObrocFigure(Macierz3x3 &MacierzObrotu)
{
  unsigned int i;
  for(i=0;i<Aktualny_Wierzcholek.size();i++)
  {
	  Aktualny_Wierzcholek[i] = MacierzObrotu * Poczatkowy_Wierzcholek[i];
  }
}

bool FiguraGeometryczna::ZapisFiguryDoPliku(string NazwaPliku)
{
  ofstream  StrmPlikowy;

  StrmPlikowy.open(NazwaPliku);
  if (!StrmPlikowy.is_open())  {
    cerr << ":(  Operacja otwarcia do zapisu \"" << NazwaPliku << "\"" << endl
	 << ":(  nie powiodla sie." << endl;
    return false;
  }

  unsigned int i;
	for(i=0;i<Aktualny_Wierzcholek.size();)
	{
		StrmPlikowy<<Aktualny_Wierzcholek[i];
		StrmPlikowy<<"\n"<<defaultfloat;
    i++;
		if(i%2 == 0) StrmPlikowy<<endl;
	}

  StrmPlikowy<<fixed << setprecision(20)<<Aktualny_Wierzcholek[0]<<endl;
  StrmPlikowy<<Aktualny_Wierzcholek[1]<<defaultfloat<<endl;
  StrmPlikowy.close();
  return !StrmPlikowy.fail();
}
