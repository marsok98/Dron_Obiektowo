#pragma once
#include <unistd.h>
#include "Graniastoslup6.hh"
#include "lacze_do_gnuplota.hh"
#include "FunkcjeDoMenu.hh"
#include "ObiektSceny.hh"
#include "Prostopadloscian.hh"
#define ILOSCROTOROW 4
#define PLIK_KORPUS "prostopadloscian.dat"
#define PLIK_WIRNIK1 "szesciokat1.dat"
#define PLIK_WIRNIK2 "szesciokat2.dat"
#define PLIK_WIRNIK3 "szesciokat3.dat"
#define PLIK_WIRNIK4 "szesciokat4.dat"
/*!
 * \file  Dron.hh
 *  
 *  Plik zawiera klase Dron oraz metody obslugujace te klase
 */

/*!
 * \brief Klasa modeluje pojecie Dron
 * 
 * Klasa dron sklada sie z jednego obiektu klasy Prostopadloscian odpawiadajacego za Korpus
 * oraz z tablicy  obiektow klasy Graniastoslup6  tworzace wirniki Drona
 * Klasa dziedziczy po obiekcie sceny bo bedzie wyswietlana na scenie
 */
class Dron : public ObiektSceny
{   
    Prostopadloscian Korpus;
    Graniastoslup6 Rotor[ILOSCROTOROW];
    /*!
     * \brief Pole przechowuje kat obrotu w stopniach o jaki jest obrocony Dron wzgledem OZ
     */
    double KatZ_stopnie = 0;
    double SkalaDrona = 1;
    double Wymiar_Wirnika =  SkalaDrona * 6;
    double Wymiar_Korpusu =  SkalaDrona * 15;
    double Grubosc_Wirnika = SkalaDrona * 3;
    /*!
     * \brief Pole ktore przechowuje srednice kola opisanego na dronie
     */
    double RozstawDrona;
    /*!
     * \brief Pole przechowuje Odleglosc od srodka drona do wysokosci drona
     */
    double GruboscDrona;
public:
    double PobierzKat_Z(){return KatZ_stopnie;}
    /*!
     * \brief Metoda umozliwia pobranie Wektora Przesuniecia z korpusu co jest jednoznaczne
     * punktem srodka Drona
     */
    Wektor3D PobierzWektorPrzesuniecia(){return Korpus.PobierzWektorPrzesuniecia();}
    double PobierzRozstawDrona(){return RozstawDrona;}
    double PobierzGruboscDrona(){return GruboscDrona;}

    /*!
     * \brief Metoda ktora sprawdza czy zaszla kolizja miedzy dronami
     * 
     * Metoda wirtualna dziedziczaca z klasy ObiektSceny, umozliwiajaca wykrywanie kolizji miedzy Dronami
     * Kolizja jest liczona poprzez aproksymacje korpusu do okregu poprzez wyznaczenie maksymalnego
     * promienia. Metoda porownuje po osi OZ oraz sprawdza warunek odleglosci dwoch Dronow.
     * Srodki Dronow to tak naprawde WektorPrzesuniecia ktore moga byc rowniez interpretowane jako punkty
     * \param[in] shared_ptr <Dron> Wsk - Wskaznik dzielony wskazujacy na obiektklasy Dron
     * \retval true - Gdy kolizja zajdzie
     * \retval false - w wypadku przeciwnym
     */
    virtual bool CzyZaszlaKolizja(shared_ptr <Dron> Wsk);
    
    /*!
     * \brief Metoda ktora wczytuje z cin skale drona i zapisuje do pola SkalaDrona
     */
    void WczytajSkaleDrona();
    /*!
     * \brief Metoda ktora wywoluje metody Inicjalizuj dla poszczegolnych skladowych klasy Drona
     * 
     * Przypisuje Korpusowi, rotorom odpowiednie wartosci z klasy, oraz przesuwa Rotory na miejsce 
     * gornych wierzcholkow Korpusu.
     */
    void Inicjalizuj();
    /*!
     * \brief Metoda Dodaje pliki do Lacza Gnuplota
     * 
     * Metoda nadaje nazwe plikom oraz konwertuje ID drona do stringa i dodaje taki plik do Lacza
     */

    void DodajPlikiDronowi(PzG::LaczeDoGNUPlota &Lacze);
    /*!
     * \brief Metoda ktora zapisuje Drona do 5 plikow.
     * 
     * Kazdy Rotor czy tez Korpus ma swoj plik do zapisu
     */
    void ZapiszDronaDoPlikow();
    /*!
     * \brief Metoda ktora przesuwa poszczegolne skladowe klasy Dron oraz dodaje do 
     * WektoraPrzesuniecia poszczegolnych skladowych klasy
     * 
     * Przyjmuje jeden argument wejsciowy klasy Wektor3D
     */
    void PrzesunDronaDodajDoWektoraPrzesuniecia(const Wektor3D &Wek);
    /*!
     * \brief Metoda odpowiada za Animowany Ruch na wprost
     * 
     * Metoda pobiera ze standardowego strumienia droge oraz katwznoszenia
     * Te dane sa konwertowane na Wektor a potem dzielony na 40 czesci
     * Nastepnie zostanie to przekazane do petli ktora zapisuje co iteracje do pliku
     * co powoduje ruch.
     * Przy okazji wywolana zostaje metoda AnimacjaObrotSmigiel ktora odpowiada za krecenie sie
     * wokol wlasnej osi Rotorow
     */
    void AnimowanyRuchNaWprost(PzG::LaczeDoGNUPlota &Lacze,const Wektor3D &WektorCzastkowy);
    /*!
     * \brief Metoda przesuwa poszczegolne skladowe klasy na srodek ukladu wspolrzednych
     * 
     * Metoda do aktualnego wierzcholka przypisuje poczatkowe wierzcholki co jest rownoznaczne
     * z przesunieciem Drona do pozycji poczatkowej
     * \param[in] Lacze Lacze do gnuplota dzieki ktoremu mozemy rysowac figury
     */
    void PrzesunDronaNaSrodekUkladuWspolrzednych();
    /*!
     * \brief Metoda ktora jest wykorzystywana po przesunieciu drona o maly kat zeby powrocic
     * do pozycji przed przesunieciem na srodek ukladu
     * 
     * Metoda wywoluje metody na poszczegolnych obiektach skladowych klasy dron
     * Dzieki temu mozliwy jest ruch drona
     */
    void WrocNaPozycjeDronemPoLekkimObrocie();
    /*!
     * \brief Metoda umozliwiajaca obrocenie drona za pomoca MacierzObrotu
     * 
     * Metoda jest zlozeniem wywolan metod dla obiektu FiguraGeometryczna
     * Dzieki temu zlozeniu caly dron jest obracany
     * \param[in] MacierzObrotu
     */
    void ObrocDrona(Macierz3x3 &MacierzObrotu);
    /*!
     * \brief Metoda umozliwia animowany obrot drona wokol wlasnej osi
     * 
     * Metoda wczytuje kat obrotu ze standardowego strumienia
     * Obraca Drona wokol wlasnej osi oraz zapisuje kat do pola KatZ w klasie Dron
     * Kat zostaje dzielony na male czesci a nastepnie Dron zostaje obracany o maly 
     * kat i w kazdym obiegu petli zostaje zapisany do plikow co powoduje animacje
     * obrotu
     * Rowniez dla tej metody stale dziala AnimowanyObrotSmigiel ktora odpowiada za obrot
     * rotorow wokol wlasnej osi
     * \param[in] Lacze Lacze do gnuplota dzieki ktoremu mozemy rysowac figury
     */
    void AnimowanyObrotDrona(PzG::LaczeDoGNUPlota &Lacze);
    /*!
     * \brief Metoda umozliwia animowany obrot smigiel
     * 
     * AnimowanyObrotSmigiel polega na powrocie kazdego z wirnika do poczatkowego punktu i obrocie
     * o maly kat a nastepnie powrot na polozenie zadane. Operacja powtarzana wiele razy spowoduje 
     * animowany obrot wirnika wokol wlasnej osi
     * \param[in] Lacze Lacze do gnuplota dzieki ktoremu mozemy rysowac figury
     */
    void AnimowanyObrotSmigiel(PzG::LaczeDoGNUPlota &Lacze);
};