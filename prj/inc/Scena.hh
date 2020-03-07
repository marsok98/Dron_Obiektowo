#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include "lacze_do_gnuplota.hh"
#include "FunkcjeDoMenu.hh"
#include "FabrykaObiektow.hh"
#include <list>
#include <memory>
using namespace std;

/*!
 * \file  Scena.hh
 *  
 *  Plik zawiera klase Scena oraz metody obslugujace te klase
 */

/*!
 * \brief Klasa modeluje pojecie Sceny
 * 
 * Klasa ta obsluguje pojecie Sceny, Przechowuje Fabryke Dronow 
 * Drony, przeszkody, oraz odpowiada za kolizje
 */
class Scena
{
  /*!
   * \brief Pole przechowujace FabrykeObiektow
   */
  FabrykaObiektow Fab;
  /*!
   * \brief Pole przechowujace Lacze do Gnuplota
   */
  PzG::LaczeDoGNUPlota  Lacze;
  /*!
   * \brief Lista wskaznikow dzielonych typu Dron do przechowania wskaznikow na Drony
   */
  list< shared_ptr <Dron> > ListaDronow;
  /*!
   * \brief Lista wskaznikow dzielonych typu ObiektSceny do przechowania wskaznikow na ObiektySceny
   */
  list< shared_ptr <ObiektSceny> > ListaObiektowSceny;
  /*!
   * \brief Pole przechowujace pozycje AktualnegoDrona na liscie
   */
  list< shared_ptr <Dron> >::iterator AktualnyDron;
public:
  /*!
   * \brief Konstruktor domyslny klasy Scena
   * 
   * Konstruktor Tworzy Drony i PrzeszkodyPr oraz umieszcza wskazniki do tych Obiektow
   * Na listach ListaDronow oraz ListaObiektowSceny
   * Inicjalizuje Lacze, ustawia zakresy
   * Rysuje Poczatkowe Polozenie Figur
   * Inicjalizuje pole AktualnyDron
   */
  Scena();
  /*!
   * \brief Metoda ktora zajmuje sie poprawnym zainicjowaniem drona na scenie
   * 
   * Metoda Inicjalizuje, Dodaje pliki dronowi, Przesuwa o Wektor3D W, zapisuje do plikow
   * Wrzuca wskaznik do tego drona na dwie listy tj. ListaDronow oraz ListaObiektowSceny
   * \param[in] shared_ptr <Dron> Wsk - Wskaznik na Drona ktorego chcemy poddac tym operacjom
   * \param[in] const Wektor3D &W - Wektor o ktory chcemy przesunac poczatkowo Drona
   */
  void UsunDronazSceny();
  void UstawDronaNaScenieWrzucNaListy(shared_ptr <Dron> Wsk,const Wektor3D &W);
  /*!
   * \brief Metoda ktora zajmuje sie poprawnym zainicjowaniem PrzeszkodyPr na scenie
   * 
   * Metoda Inicjalizuje zadanymi wartosciami , dodaje pliki przeszkodzie,
   * Przesuwa o Wektor3D &W, zapisuje do pliku oraz wrzuca na liste ListaObiektowSceny
   * \param[in] shared_ptr <Dron> Wsk - Wskaznik na PrzeszkodePr ktora chcemy poddac tym operacjom
   * \param[in] const Wektor3D &W - Wektor o ktory chcemy przesunac poczatkowo PrzeszkodePr
   */
  void UstawPrzeszkodeWrzucNaListe(shared_ptr<PrzeszkodaPr> Wsk,
  double WymiarX, double WymiarY, double WymiarZ, const Wektor3D &W );
  /*!
   * \brief Metoda umozliwiajaca sterowanie aktualnym dronem
   * 
   * Metoda umozliwia zadawanie uzytkownikowi  przesuniec, obrotow, 
   * WyswietlanieMenu, Selekcje Drona.
   * Lot drona jest kontrolowany przez wykrywacz przeszkod
   */
  void SterowanieAktualnymDronem();
  /*!
   * \brief Metoda umozliwia SelekcjeDrona
   * 
   * W zaleznosci od parametru Numer odpowiedni iterator listy zostanie przypisany
   * do Pola AktualnyDron w klasie
   */
  void SelekcjaDrona(int Numer);
  /*!
   * \brief Metoda umozliwiajaca wczytanie drogi i katu lotu oraz zwrocenie WektoraCzastkowego
   */
  Wektor3D WczytajDrogeZwrocWektorCzastkowy();
};