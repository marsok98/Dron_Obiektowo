#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include "Wektor3D.hh"
#include "Macierz3x3.hh"
#include "lacze_do_gnuplota.hh"
#include <unistd.h>

using namespace std;

/*!
 * \file  FiguraGeometryczna.hh
 *  
 *  Plik zawiera klase FiguraGeometryczna oraz metody obslugujace te klase
 */

/*!
 * \brief Klasa modeluje pojecie Figury Geometrycznej
 * 
 *  Ta klasa  daje mozliwosc stworzenia na jej podstawie innych Figur
 */
class FiguraGeometryczna{
protected:
    /*!
     * \brief Pole przechowuje oryginalne punkty poszczegolnych wierzcholkow
     */
    vector<Wektor3D> Poczatkowy_Wierzcholek;
    /*!
    * \brief Pole przechowuje zmodyfikowane operacje na PoczatkowymWierzcholku
    */
    vector<Wektor3D> Aktualny_Wierzcholek;
    /*!
     * \brief Pole przechowuje Wektor o ktory przesuniety jest Aktualny_Wierzcholek wzgledem
     * Poczatkowy_Wierzcholek
     */
    Wektor3D WektorPrzesuniecia;
    /*!
     * \brief Pole przechowuje Wektor o ktory przesuniety jest Poczatkowy_Wierzcholek
     * Przydaje sie gdy chcemy na stale przypisac pozycje jakiejs figurze
     */
    Wektor3D Wektor_Offsetu_;
public:
    /*!
     * \brief Przeciazenie operatora indeksowania(tylko odczyt)
     *
     * Zwraca Aktualny_Wierzcholek Figury geometrycznej
     */
    Wektor3D operator [] (int i)const {return Aktualny_Wierzcholek[i];}
    /*!
     * \brief Przeciazenie operatora indeksowania(mozna modyfikowac wartosc)
     * 
     * Zwraca Aktualny_Wierzcholek Figury geometrycznej oraz mozna modyfikowac
     */
    Wektor3D &operator [] (int i)      {return Aktualny_Wierzcholek[i];}

    /*!
     * \brief Metoda umozliwiajaca przesuniecie FiguryGeometrycznej o Wektor3D 
     * oraz dodanie do WektoraPrzesuniecia
     * 
     * Metoda dodaje Wek do WektorPrzesuniecia oraz przesuwa o WektorPrzesuniecia
     * Poczatkowy_Wierzcholek i zapisuje do Aktualny_Wierzcholek
     */
    void PrzesunDodajDoWektoraPrzesuniecia(const Wektor3D &Wek);
    /*!
     * \brief Metoda umozliwia  dodanie Wektora3D do WektoraOffsetu
     * 
     * Metoda Dodaje Wektor3D Wek do WektoraOffsetu a nastepnie ustawia nowy Poczatkowy_Wierzcholek
     * Metoda moze byc uzywana tylko przy inicjalizacji bo przypisuje do AktualnegoWierzcholka
     * PoczatkowyWierzcholek
     */
    void Ustaw_Offset_DodajDo_Offsetu_(const Wektor3D &Wek);
    /*!
     * \brief Metoda odejmuje WektorOffsetu 
     * 
     * Metoda odejmuje od Aktualnego oraz Poczatkowego Wierzcholka WektorOffsetu
     */
    void Cofnij_Offset_();
    /*!
     * \brief Metoda dodaje WektorOffsetu
     * 
     * Ustawia offset to znaczy Przesuwa Aktualny_Wierzcholek i Poczatkowy_Wierzcholek 
     * o WektorOffsetu
     */
    void Ustaw_Offset_();
    /*!
     * \brief Metoda umozliwia powrot AktualnegoWierzcholka do polozenia poczatkowego
     * tzn AktualnyWierzcholek = PoczatkowyWierzcholek
     * 
     */
    void PrzesunNaSrodekUkladuWspolrzednych();
    /*!
     * \brief Metoda dodaje do AktualnegoWierzcholka WektorPrzesuniecia
     * 
     * Metoda moze byc tylko uzywana jesli AktualnyWierzcholek jest przesuniety
     * o jakis kat to mozemy nim wrocic na swoje polozenie
     * Jesli bedziemy robic tak wiele razy powstanie animacja 
     */
    void WrocNaPozycjePoLekkimObrocie();
    /*!
     * \brief Metoda obraca figure czyli przemnaza Wierzcholki Figury
     *
     * Metoda Mnozy MacierzObrotu przez PoczatkoweWierzcholki co powoduje obrot figury
     * Zapisuje do AktualnegoWierzcholka
     */
    void ObrocFigure(Macierz3x3 &MacierzObrotu);

    /*!
     * \brief Metoda Zapisuje Figure do pliku z odpowiednia notacja
     * 
     * Metoda zapisuje figure do pliku w taki sposob aby gnuplot mogl odczytac i narysowac
     * \param[in] NazwaPliku
     * \retval true Jesli operacja zapisu sie powiedzie 
     * \retval false w wypadku przeciwnym
     */
    bool ZapisFiguryDoPliku(string NazwaPliku);
    /*!
     * \brief Metoda umozliwia pobranie Wektora Przesuniecia  co jest jednoznaczne
     * punktem srodka tej figury
     */
    Wektor3D PobierzWektorPrzesuniecia(){return WektorPrzesuniecia;}
};


