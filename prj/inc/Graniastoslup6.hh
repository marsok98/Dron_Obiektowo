#pragma once
 
#include "Prostopadloscian.hh"
/*!
 * \file  Graniastoslup6.hh
 *  
 *  Plik zawiera klase Graniastoslup6 oraz metody obslugujace te klase
 */

/*!
 * \brief Klasa modeluje pojecie Graniastoslupa szesciokatnego foremnego,
 * dziedziczaca z FiguryGeometrycznej ktora jest
 */
class Graniastoslup6: public FiguraGeometryczna
{
    public:
  /*!
   * \brief Metoda inicjalizuje wierzcholki Graniastoslupa szesciokatnego foremnego
   * 
   * Inicjalizuje Graniastoslup szesciokatny foremny
   * Ustawia Poczatkowy_Wierzcholek oraz synchronizuje z Aktualnym Wierzcholkiem
   * \param[in] Wymiar_Wirnika
   * \param[in] Grubosc_Wirnika
   */
    void Inicjalizuj(double Wymiar_Wirnika,double Grubosc_Wirnika);
};