#include "Dron.hh"
bool Dron::CzyZaszlaKolizja(shared_ptr <Dron> Wsk)
{
    double OdlegloscXY;
    double OdlegloscZ;
    Wektor3D PolozenieArg = Wsk->PobierzWektorPrzesuniecia();
    Wektor3D Polozenie = this->PobierzWektorPrzesuniecia();

    OdlegloscXY = sqrt(pow((PolozenieArg[0] - Polozenie[0]),2)+ pow((PolozenieArg[1]-Polozenie[1]),2));
    OdlegloscZ  = fabs(PolozenieArg[2]-Polozenie[2]);

    if(OdlegloscXY <= RozstawDrona and OdlegloscZ <= GruboscDrona)
    {
        cout<<"Kolizja z innym dronem"<<endl;
        cout<<"Ruch zostal przerwany"<<endl;
        return true;
    }
    return false;
}

void Dron::WczytajSkaleDrona()
{
    cout<<"\n Podaj skale do drona: ";
    cin>>SkalaDrona;
    cout<<"\n Podana przez Ciebie skala wynosi:  "<<SkalaDrona;
    cout<<endl;
}


void Dron::Inicjalizuj()
{ 
    Korpus.Inicjalizuj(SkalaDrona * Wymiar_Korpusu);
    Rotor[0].Inicjalizuj(SkalaDrona * Wymiar_Wirnika, SkalaDrona * Grubosc_Wirnika);
    Rotor[1].Inicjalizuj(SkalaDrona * Wymiar_Wirnika, SkalaDrona * Grubosc_Wirnika);
    Rotor[2].Inicjalizuj(SkalaDrona * Wymiar_Wirnika, SkalaDrona * Grubosc_Wirnika);
    Rotor[3].Inicjalizuj(SkalaDrona * Wymiar_Wirnika, SkalaDrona * Grubosc_Wirnika);

    Wektor3D Wek0 (-SkalaDrona * Wymiar_Korpusu,     SkalaDrona * Wymiar_Korpusu,     SkalaDrona * Wymiar_Korpusu + SkalaDrona * Grubosc_Wirnika);
    Wektor3D Wek1 (-SkalaDrona * Wymiar_Korpusu,     -SkalaDrona * Wymiar_Korpusu,    SkalaDrona * Wymiar_Korpusu + SkalaDrona * Grubosc_Wirnika);
    Wektor3D Wek2 (SkalaDrona * Wymiar_Korpusu,      SkalaDrona * Wymiar_Korpusu,     SkalaDrona * Wymiar_Korpusu + SkalaDrona * Grubosc_Wirnika);
    Wektor3D Wek3 (SkalaDrona * Wymiar_Korpusu,      -SkalaDrona * Wymiar_Korpusu,    SkalaDrona * Wymiar_Korpusu + SkalaDrona * Grubosc_Wirnika);

    Rotor[0].Ustaw_Offset_DodajDo_Offsetu_(Wek0);
    Rotor[1].Ustaw_Offset_DodajDo_Offsetu_(Wek1);
    Rotor[2].Ustaw_Offset_DodajDo_Offsetu_(Wek2);
    Rotor[3].Ustaw_Offset_DodajDo_Offsetu_(Wek3);
    
    RozstawDrona = 2 * sqrt(2) * Wymiar_Korpusu + 2  * Wymiar_Wirnika;
    GruboscDrona = 2 * Grubosc_Wirnika + Wymiar_Korpusu;

}

void Dron::DodajPlikiDronowi(PzG::LaczeDoGNUPlota &Lacze)
{
  Lacze.DodajNazwePliku("korpus_drona"+to_string(ID),PzG::SR_Ciagly);
  Lacze.DodajNazwePliku("wirnik1_drona"+to_string(ID),PzG::SR_Ciagly);
  Lacze.DodajNazwePliku("wirnik2_drona"+to_string(ID),PzG::SR_Ciagly);
  Lacze.DodajNazwePliku("wirnik3_drona"+to_string(ID),PzG::SR_Ciagly);
  Lacze.DodajNazwePliku("wirnik4_drona"+to_string(ID),PzG::SR_Ciagly);
}

void Dron::ZapiszDronaDoPlikow()
{
    Korpus.ZapisFiguryDoPliku("korpus_drona"+to_string(ID));
    Rotor[0].ZapisFiguryDoPliku("wirnik1_drona"+to_string(ID));
    Rotor[1].ZapisFiguryDoPliku("wirnik2_drona"+to_string(ID));
    Rotor[2].ZapisFiguryDoPliku("wirnik3_drona"+to_string(ID));
    Rotor[3].ZapisFiguryDoPliku("wirnik4_drona"+to_string(ID));
}

void Dron::PrzesunDronaDodajDoWektoraPrzesuniecia(const Wektor3D &Wek)
{
    Korpus.PrzesunDodajDoWektoraPrzesuniecia(Wek);
    int i;
    for(i=0;i<ILOSCROTOROW;i++)
    {
        Rotor[i].PrzesunDodajDoWektoraPrzesuniecia(Wek);
    }
}

void Dron::AnimowanyRuchNaWprost(PzG::LaczeDoGNUPlota &Lacze,const Wektor3D &WektorCzastkowy)
{
    AnimowanyObrotSmigiel(Lacze);
    PrzesunDronaDodajDoWektoraPrzesuniecia(WektorCzastkowy);
    ZapiszDronaDoPlikow();
    usleep(5000);
    Lacze.Rysuj();
}

void Dron::PrzesunDronaNaSrodekUkladuWspolrzednych()
{
    Korpus.PrzesunNaSrodekUkladuWspolrzednych();
    int i;
    for(i=0;i<ILOSCROTOROW;i++)
    {
        Rotor[i].PrzesunNaSrodekUkladuWspolrzednych();
    }
}


void Dron::WrocNaPozycjeDronemPoLekkimObrocie()
{
    Korpus.WrocNaPozycjePoLekkimObrocie();
    int i;
    for(i=0;i<ILOSCROTOROW;i++)
    {
        Rotor[i].WrocNaPozycjePoLekkimObrocie();
    }
}


void Dron::ObrocDrona(Macierz3x3 &MacierzObrotu)
{
    Korpus.ObrocFigure(MacierzObrotu);
    int i;
    for(i=0;i<ILOSCROTOROW;i++)
    {
        Rotor[i].ObrocFigure(MacierzObrotu);
    }
}

void Dron::AnimowanyObrotSmigiel(PzG::LaczeDoGNUPlota &Lacze)
{
    int i,j;
    Macierz3x3 MacierzObrotu;
    double kat =360;
    double kat_czastkowy = kat * 1/5.0;
    double suma_kata=0;

    for(j=0;j<5;j++)
    {
        suma_kata += kat_czastkowy;
        MacierzObrotu = UtworzMacierzZ(suma_kata);
        for(i=0;i<ILOSCROTOROW;i++)
        {
            Rotor[i].Cofnij_Offset_();
            Rotor[i].PrzesunNaSrodekUkladuWspolrzednych();
            Rotor[i].ObrocFigure(MacierzObrotu);
            Rotor[i].Ustaw_Offset_();
            Rotor[i].WrocNaPozycjePoLekkimObrocie();
        }
        ZapiszDronaDoPlikow();
        usleep(10000);
        Lacze.Rysuj();
    }
}

void Dron::AnimowanyObrotDrona(PzG::LaczeDoGNUPlota &Lacze)
{
  double kat;
  cout<<"Podaj kat do obrocenia Drona: "<<endl;
  cin>>kat;
  Macierz3x3 MacierzObrotu;
  double Czastkowy_kat = kat * (1/40.0);
  
  int i;
  for(i=0;i<40;i++)
  {
    AnimowanyObrotSmigiel(Lacze);
    PrzesunDronaNaSrodekUkladuWspolrzednych();
    KatZ_stopnie += Czastkowy_kat;
    MacierzObrotu=UtworzMacierzZ(KatZ_stopnie);
    ObrocDrona(MacierzObrotu);
    WrocNaPozycjeDronemPoLekkimObrocie();
    ZapiszDronaDoPlikow();
    usleep(5000);
    Lacze.Rysuj();
   }
}