#include "Graniastoslup6.hh"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <math.h>


using namespace std;


void Graniastoslup6::Inicjalizuj(double Wymiar_Wirnika,double Grubosc_Wirnika) {
  Poczatkowy_Wierzcholek.push_back(Wektor3D(Wymiar_Wirnika,     Wymiar_Wirnika*sqrt(3),   Grubosc_Wirnika));
  Poczatkowy_Wierzcholek.push_back(Wektor3D(-Wymiar_Wirnika,    Wymiar_Wirnika*sqrt(3),   Grubosc_Wirnika));
  Poczatkowy_Wierzcholek.push_back(Wektor3D(Wymiar_Wirnika*2,   0,                        Grubosc_Wirnika));
  Poczatkowy_Wierzcholek.push_back(Wektor3D(-Wymiar_Wirnika*2,  0,                        Grubosc_Wirnika));
  Poczatkowy_Wierzcholek.push_back(Wektor3D(Wymiar_Wirnika,     -Wymiar_Wirnika*sqrt(3),  Grubosc_Wirnika));
  Poczatkowy_Wierzcholek.push_back(Wektor3D(-Wymiar_Wirnika,    -Wymiar_Wirnika*sqrt(3),  Grubosc_Wirnika));

  Poczatkowy_Wierzcholek.push_back(Wektor3D(Wymiar_Wirnika,     -Wymiar_Wirnika*sqrt(3), -Grubosc_Wirnika));
  Poczatkowy_Wierzcholek.push_back(Wektor3D(-Wymiar_Wirnika,    -Wymiar_Wirnika*sqrt(3), -Grubosc_Wirnika));
  Poczatkowy_Wierzcholek.push_back(Wektor3D(Wymiar_Wirnika*2,   0,                       -Grubosc_Wirnika));
  Poczatkowy_Wierzcholek.push_back(Wektor3D(-Wymiar_Wirnika*2,  0, -Grubosc_Wirnika));
  Poczatkowy_Wierzcholek.push_back(Wektor3D(Wymiar_Wirnika,     Wymiar_Wirnika*sqrt(3),  -Grubosc_Wirnika));
  Poczatkowy_Wierzcholek.push_back(Wektor3D(-Wymiar_Wirnika,    Wymiar_Wirnika*sqrt(3),  -Grubosc_Wirnika));

  Aktualny_Wierzcholek = Poczatkowy_Wierzcholek;
}

