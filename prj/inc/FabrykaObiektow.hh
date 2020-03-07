#pragma once

#include "Dron.hh"
#include "ObiektSceny.hh"
#include "PrzeszkodaPr.hh"
#include <memory>

/*!
 * \file  FabrykaObiektow.hh
 *  
 *  Plik zawiera klase FabrykaObiektow oraz metody obslugujace te klasy
 */

/*!
 * \brief Typ wyliczeniowy okreslajacy wybor Robot czy Przeszkoda
 */
enum TypObiektu{Robot,Przeszkoda};
/*
 * \brief Klasa modelujaca pojecie  FabrykeObiektow ktora bedzie odpowiedzialna za Tworzenie Obiektow Sceny
 * 
 * Klasa zapewnia nam mozliwosc tworzenia obiektow 
 */
class FabrykaObiektow
{
    public:
    /*
     * \brief Metoda umozliwiajaca stworzenie Obiektu Sceny
     * 
     * Metoda zwraca wskaznik do nowo utworzonego obiektu Sceny
     * \param[in] Typ - Typ wyliczeniowy mogacy przyjmowac wartosci Robot i Przeszkoda
     * \return shared_ptr<ObiektSceny> Wskaznik na nowo powstaly obiektsceny, moze to byc 
     * Dron albo Przeszkoda Pr
     */
    shared_ptr<ObiektSceny> StworzObiekt(TypObiektu Typ);
};