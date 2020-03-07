#include "PrzeszkodaPr.hh"

bool PrzeszkodaPr::CzyZaszlaKolizja(shared_ptr <Dron> Wsk)
{
    double OdlegloscXY;
    double OdlegloscZ;
    Wektor3D PolozenieArg = Wsk->PobierzWektorPrzesuniecia();
    Wektor3D Polozenie = this->PobierzWektorPrzesuniecia();

    double PrzekatnaPrzeszkody = sqrt(pow(Dlugosc,2)+pow(Szerokosc,2));

    double RozstawDrona = Wsk ->PobierzRozstawDrona();
    double GruboscDrona= Wsk ->PobierzGruboscDrona();

    OdlegloscXY = sqrt(pow((PolozenieArg[0] - Polozenie[0]),2)+ pow((PolozenieArg[1]-Polozenie[1]),2));
    OdlegloscZ  = fabs(PolozenieArg[2]-Polozenie[2]);

    double Minimalna_OdlegloscXY = RozstawDrona/2.0 + PrzekatnaPrzeszkody/2.0;
    double Minimalna_OdlegloscZ = GruboscDrona + Wysokosc/2.0;

    if(OdlegloscXY <= Minimalna_OdlegloscXY   and 
    OdlegloscZ <= Minimalna_OdlegloscZ)
    {
        cout<<"Kolizja z inna przeszkoda"<<endl;
        cout<<"Ruch zostal przerwany"<<endl;
        return true;
    }
    return false;
}



void PrzeszkodaPr::Inicjalizuj(double Dlugosc, double Szerokosc, double Wysokosc)
{
  this->Dlugosc =2 * Dlugosc;
  this->Szerokosc =2 * Szerokosc;
  this->Wysokosc =2 * Wysokosc;

  Poczatkowy_Wierzcholek.push_back(Wektor3D(Dlugosc, Szerokosc, Wysokosc));
  Poczatkowy_Wierzcholek.push_back(Wektor3D(Dlugosc, -Szerokosc, Wysokosc));
  Poczatkowy_Wierzcholek.push_back(Wektor3D(-Dlugosc, Szerokosc, Wysokosc));
  Poczatkowy_Wierzcholek.push_back(Wektor3D(-Dlugosc, -Szerokosc, Wysokosc));

  Poczatkowy_Wierzcholek.push_back(Wektor3D(-Dlugosc, Szerokosc, -Wysokosc));
  Poczatkowy_Wierzcholek.push_back(Wektor3D(-Dlugosc, -Szerokosc, -Wysokosc));
  Poczatkowy_Wierzcholek.push_back(Wektor3D(Dlugosc, Szerokosc, -Wysokosc));
  Poczatkowy_Wierzcholek.push_back(Wektor3D(Dlugosc, -Szerokosc, -Wysokosc));

  Aktualny_Wierzcholek = Poczatkowy_Wierzcholek;
}

void PrzeszkodaPr::DodajPlikPrzeszkodzie(PzG::LaczeDoGNUPlota &Lacze)
{
  Lacze.DodajNazwePliku("Przeszkoda"+to_string(ID),PzG::SR_Ciagly);
}

void PrzeszkodaPr::ZapiszPrzeszkodeDoPliku()
{
  ZapisFiguryDoPliku("Przeszkoda"+to_string(ID));
}