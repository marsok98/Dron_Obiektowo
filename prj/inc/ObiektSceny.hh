#pragma once
#include <iostream>
#include <cmath>
#include <iomanip>
#include <memory>
using namespace std;
class Dron;
/*!
 * \file  ObiektSceny.hh
 *  
 *  Plik zawiera klase ObiektSceny oraz metody obslugujace
 */

/*!
 * \brief Klasa modeluje pojecie Obiektu Sceny
 * 
 * Obiekty tworzone wyswietlaja sie na scenie tj oknie gnuplota
 * Klasa posiada metode wirtualna
 */
class ObiektSceny
{
   /*!
    * \brief Pole przechowuje ilosc aktualnie istniejacych obiektow klasy ObiektSceny
    */
   static int IloscObiektowSceny;
  /*!
   *\brief Pole przechowuje ilosc w sumie  stworzonych obiektow klasy ObiektSceny
   */
    static int LacznaIloscObiektowSceny;
protected:
  /*!
   * \brief Pole przechowuje numer porzadkowy drona czyli ID, zapewnia to nam identyfikacje drona
   */
    int ID;
public:


  int getID(){return ID;}
  /*!
   *\brief Konstruktor domyslny
   *
   * Konstruktor domyslny, ktory inkrementuje pola statyczne oraz przypisuje ID
   */
  
  ObiektSceny() 
  {
    ++IloscObiektowSceny;
    ID = IloscObiektowSceny;
    ++LacznaIloscObiektowSceny;
  }
  
  /*!
   * \brief Konstruktor kopiujacy
   *
   * Konstruktor kopiujacy, ktory inkrementuje pola statyczne
   * oraz przypisuje obiekt kopiowany do siebie
   */
  ObiektSceny(const  ObiektSceny &Obj) 
  {
    ++IloscObiektowSceny;
    ++LacznaIloscObiektowSceny;
    *this = Obj;
  }
  
  /*!
   *\brief Destruktor
   *
   * Dekrementuje pole statyczne IloscObiektowSceny
   */
   ~ObiektSceny(){--IloscObiektowSceny;}
  /*!
   *\brief Metoda zwraca ilosc aktualnie istniejacych IloscObiektowSceny
   */
  static int ZwrocIloscObiektowSceny() { return IloscObiektowSceny; }
  /*!
   * \brief Metoda zwraca ilosc LacznaIloscObiektowScenow
   */
  static int ZwrocLacznaIloscObiektowSceny() { return LacznaIloscObiektowSceny; }
  /*!
   * \brief Metoda wirtualna ktora jest uszczegolowiana w klasach pochodnych
   */
  virtual bool CzyZaszlaKolizja(shared_ptr <Dron> Wsk) = 0;
  
};

 