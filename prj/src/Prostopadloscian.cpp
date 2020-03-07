#include "Prostopadloscian.hh"
        

void Prostopadloscian::Inicjalizuj(double Wymiar)
{
  Poczatkowy_Wierzcholek.push_back(Wektor3D(Wymiar, Wymiar, Wymiar));
  Poczatkowy_Wierzcholek.push_back(Wektor3D(Wymiar, -Wymiar, Wymiar));
  Poczatkowy_Wierzcholek.push_back(Wektor3D(-Wymiar, Wymiar, Wymiar));
  Poczatkowy_Wierzcholek.push_back(Wektor3D(-Wymiar, -Wymiar, Wymiar));

  Poczatkowy_Wierzcholek.push_back(Wektor3D(-Wymiar, Wymiar, -Wymiar));
  Poczatkowy_Wierzcholek.push_back(Wektor3D(-Wymiar, -Wymiar, -Wymiar));
  Poczatkowy_Wierzcholek.push_back(Wektor3D(Wymiar, Wymiar, -Wymiar));
  Poczatkowy_Wierzcholek.push_back(Wektor3D(Wymiar, -Wymiar, -Wymiar));

  Aktualny_Wierzcholek = Poczatkowy_Wierzcholek;
}