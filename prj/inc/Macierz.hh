#ifndef MACIERZ_HH
#define MACIERZ_HH


#include <iostream>
using namespace std;
#include "Wektor3D.hh"
#define PI 3.14159265

/*!
 * \file  Macierz.hh
 *  
 *  Plik zawiera definicję szablonu klasy realizującej macierz 
 */




/*!
 * \brief  Klasa modeluje pojecie macierzy
 *
 *  Szablon Macierz to szablon przedstawiający macierz, bedącą tablica obiektu Wektor
 * W klasie Macierz przechowywane są funkcje przeciążające operatory oraz metody klasy 
 */
template<int Wymiar>
class Macierz {

    Wektor <Wymiar> macierz[Wymiar];
    
public:
  
    /*!
     * \brief Przeciazenie operatora [] 
     *
     * Funkcja przeciążająca operator [], zwraca tablice wektorow,
     * wywolana z argumentem typu int. Nie mozna zmieniac wartosci
     */
    Wektor <Wymiar> operator [] (int i) const {return macierz[i];}
    
    /*!
     * \brief Przeciazenie operatora [] (modyfikacja wartosci)
     *
     * Funkcja przeciążająca operator [], zwraca tablice wektorow,
     * wywolana z argumentem typu int. Mozna zmieniac wartosci
     */
    Wektor<Wymiar> &operator [] (int i) {return macierz[i];}

    /*! 
     * \brief Przeciazenie operatora mnozenia
     *
     * Funkcja przeciążająca operator mnożenia, odpowiada za mnożenie przez siebie wektora i macierzy,
     * wywoływana z jednym argumentem klasy Wektor , zwraca także wartość wektora,będącego
     * wynikiem mnożenia oraz należacym do klasy Wektor 
     */
    Wektor <Wymiar> operator * (const Wektor <Wymiar> &Wek);


    /*!
     * \brief Konstruktor ktory zapewnia ze stworzona Macierz bedzie odrazu jednostkowa
     *
     * Funkcja Inicjalizuje Macierz jednostkowa
     * Korzystamy z faktu ze dowolna macierz przemnozona przez macierz jednostkowa 
     * nadal pozostaje ta sama Macierza
     */
    Macierz();
};   










template<int Wymiar>
Wektor <Wymiar> Macierz<Wymiar>::operator * (const Wektor <Wymiar> &Wek)
{
  Wektor<Wymiar> Wynik = {}; //zainicjowanie tablicy zerami
  int i,j;
  for(i=0;i<Wymiar;i++)
  {
    for(j=0;j<Wymiar;j++)
    {
      Wynik[i]+=macierz[i][j] * Wek[j];
    } 
  }
  return Wynik;
}

template<int Wymiar>
Macierz<Wymiar>::Macierz()
{
    int i,k;
    for(i=0;i<Wymiar;i++)
    {
      for(k=0;k<Wymiar;k++)
      {
        if(i==k)
        {
          macierz[i][k] = 1;
        }
        else
        {
          macierz[i][k] = 0;
        }
      }
    }
}


#endif
