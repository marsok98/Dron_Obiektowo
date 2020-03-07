#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <unistd.h>
#include "Wektor3D.hh"
#include "Macierz3x3.hh"
#include "lacze_do_gnuplota.hh"
#include "FunkcjeDoMenu.hh"
#include "Prostopadloscian.hh"
#include "Graniastoslup6.hh"
#include "Dron.hh"
#include "PrzeszkodaPr.hh"
#include "ObiektSceny.hh"
#include "Scena.hh"
#include <list>
#include <memory>
using namespace std;

int main()
{
  Scena S1;
  S1.SterowanieAktualnymDronem();
}

