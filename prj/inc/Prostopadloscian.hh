#pragma once

#include "FiguraGeometryczna.hh"

/*!
 * \file  Prostopadloscian.hh
 *  
 *  Plik zawiera klase FiguraGeometryczna oraz metody obslugujace te klase
 */

/*!
 *\brief Klasa modeluje pojecie Prostopadloscianu, dziedziczaca z FiguryGeometryczny
 */
class Prostopadloscian: public FiguraGeometryczna
{
    public:
  /*!
   *\brief Metoda inicjalizuje wierzcholki prostopadloscianu do zadanych
   * wartosci
   * 
   * Ustawia Poczatkowy_Wierzcholek oraz synchronizuje z Aktualnym Wierzcholkiem
   * Pobiera jeden argument typu double Wymiar, tworzac szescian
   */
    void Inicjalizuj(double Wymiar);
};