#pragma once
#include "FiguraGeometryczna.hh"
#include "ObiektSceny.hh"
#include "Dron.hh"
#include <string>
#include <cmath>
/*!
 * \file  PrzeszkodaPr.hh
 *  
 *  Plik zawiera klase PrzeszkodaPr  oraz metody obslugujace te klase
 */

/*!
 * \brief Klasa modeluje pojecie Przeszkody Prostopadlosciennej
 * 
 * Klasa ta dziedziczy z Figury Geometrycznej oraz z Obiektu Sceny
 */

class PrzeszkodaPr : public FiguraGeometryczna, public ObiektSceny
{   
    double Dlugosc;
    double Szerokosc;
    double Wysokosc;
public:
    /*!
     * \brief Metoda Dodaje pliki do Lacza Gnuplota
     * 
     * Metoda nadaje nazwe plikom oraz konwertuje ID ObiektuSceny do stringa i dodaje taki plik do Lacza
     */
    void DodajPlikPrzeszkodzie(PzG::LaczeDoGNUPlota &Lacze);
    /*!
     * \brief Metoda ktora sprawdza czy zaszla kolizja miedzy dronem a przeszkoda
     * 
     * Metoda wirtualna dziedziczaca z klasy ObiektSceny, umozliwiajaca wykrywanie kolizji miedzy Dronem
     * a przeszkoda
     * Kolizja jest liczona poprzez aproksymacje Drona do okregu poprzez wyznaczenie maksymalnego
     * promienia. Metoda porownuje po osi OZ oraz sprawdza warunek odleglosci Drona i PrzeszkodyPr
     * Srodki tych obiektowGraficznych to tak naprawde WektorPrzesuniecia
     * ktore moga byc rowniez interpretowane jako punkty
     * \param[in] shared_ptr <Dron> Wsk - Wskaznik dzielony wskazujacy na obiektklasy Dron
     * \retval true - Gdy kolizja zajdzie
     * \retval false - w wypadku przeciwnym
     */
    virtual bool CzyZaszlaKolizja(shared_ptr <Dron> Wsk);
    /*!
     * \brief Metoda Inicjalizuja przeszkode prostopadloscienna
     * \param[in] Dlugosc
     * \param[in] Szerokosc
     * \param[in] Wysokosc
     */
    void Inicjalizuj(double Dlugosc, double Szerokosc, double Wysokosc);
    /*!
     * \brief Metoda ktora zapisuje Przeszkode Prostopadloscienna do pliku
     */
    void ZapiszPrzeszkodeDoPliku();
};