#ifndef MACIERZ3X3_HH
#define MACIERZ3X3_HH


#include <iostream>

#include "Macierz.hh"




/*!
 * \file  Macierz3x3.hh
 *  
 *  Plik zawiera instancje szablonu Macierz - Klasa Macierz3x3
 *  oraz funkcje obslugujace te klase
 */







/*!
 * \brief Klasa Macierz3x3 jest instancją szablonu Macierz
 *
 *  Klasa Macierz inicjuje  Macierz3x3 bedącą szablonem wywolana z wartoscia 3
 */
typedef Macierz<3>  Macierz3x3;



/*!
 * \brief Przeciazenie operatora mnozenia dla dwoch obiektow klasy Macierz3x3
 *
 * Funkcja przeciaza operator mnozenia, realizuje mnozenie oraz zwraca Macierz wynikowa
 * \param[in] MacierzA - Macierz z lewej strony znaku mnozenia
 * \param[in] MacierzB - Macierz z prawej strony znaku mnozenia
 * \return Macierz3x3 wyniku
 */
Macierz3x3 operator * (const Macierz3x3 &MacierzA ,const Macierz3x3 &MacierzB);

/*!
 *\brief Funkcja tworzy macierz obrotu przez os OX
 *\param kat - kat o ktory ma byc obrocona bryla, podany w stopniach
 *\return Funkcja zwraca macierz rotacji Macierz3x3
 */
Macierz3x3 UtworzMacierzX(double kat);
/*!
 *\brief Funkcja tworzy macierz obrotu przez os OY
 *\param kat - kat o ktory ma byc obrocona bryla, podany w stopniach
 *\return Funkcja zwraca macierz rotacji Macierz3x3
 */
Macierz3x3 UtworzMacierzY(double kat);
/*!
 *\brief Funkcja tworzy macierz obrotu przez os OZ
 *\param kat - kat o ktory ma byc obrocona bryla, podany w stopniach
 *\return Funkcja zwraca macierz rotacji Macierz3x3
 */
Macierz3x3 UtworzMacierzZ(double kat);
#endif
