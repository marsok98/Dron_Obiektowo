#ifndef FUNKCJEDOMENU_HH
#define FUNKCJEDOMENU_HH
#include <fstream>
#include <iostream>
#include <iomanip>
#include <Wektor3D.hh>
#include <ObiektSceny.hh>
using namespace std;

/*!
 * \file  FunkcjeDoMenu.hh
 *  
 *  Plik zawiera naglowki funkcji ktore sluza wczytywaniu danych oraz zapisu 
 */


/*!
 * \brief Funkcja pozwalajaca na wyswietlenie menu na cout 
*/
void WyswietlMenu();



/*!
 * \brief Funkcja pozwalajaca na wczytanie sprawdzenie zapisanie liczby ze strumienia Strm 
 *
 * Dane zapisuje do zmiennej typu double
 * Funkcja posiada zabezpieczenie przed wpisaniem czegos innego niz liczba typu int
 * \param[in] Strm - Strumien wejsciowy
 * \param[in] liczba - zmienna do ktorej zapisuje poprawnie wczytana liczbe
 * \retval true - gdy operacja wczytania powiodła się,
 * \retval false - w przypadku przeciwnym.
 */

bool wczytaj_sprawdz_zapisz_liczbe(istream &Strm, double &liczba);


/*!
 * \brief Funkcja pozwalajaca na wczytanie sprawdzenie zapisanie liczby ze strumienia Strm 
 *
 * Dane zapisuje do zmiennej typu int
 * Funkcja posiada zabezpieczenie przed wpisaniem czegos innego niz liczba typu int
 * \param[in] Strm - Strumien wejsciowy
 * \param[in] liczba - zmienna do ktorej zapisuje poprawnie wczytana liczbe
 * \retval true - gdy operacja wczytania powiodła się,
 * \retval false - w przypadku przeciwnym.
 */

bool wczytaj_sprawdz_zapisz_liczbe(istream &Strm, int &liczba);



/*!
 * \brief Funkcja pozwalajaca na wczytanie sprawdzenie zapisanie znaku ze strumienia Strm
 *
 * Dane zapisuje do zmiennej typu char
 * Funkcja posiada zabezpieczenie przez wpisaniem czegos innego niz znak
 * \param[in] Strm - Strumien wejsciowy
 * \param[in] znak - zmienna do ktorej zapisuje poprawnie wczytany znak
 * \retval true - gdy operacja wczytania powiodła się,
 * \retval false - w przypadku przeciwnym.
 */

bool wczytaj_sprawdz_zapisz_znak(istream &Strm, char &znak);




























#endif