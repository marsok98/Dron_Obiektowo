#ifndef LACZE_DO_GNUPLOTA_HH
#define LACZE_DO_GNUPLOTA_HH
#include <string>
#include <list>
#include <vector>
#include<cstring>

#ifdef __GNUG__
#pragma interface
#endif

/*!
 * \file  lacze_do_gnuplota.hh
 *  
 *  Plik zawiera definicję klasy realizującej interfejs
 *  komunikacyjny do programu gnuplot.
 */


/*!
 * \brief Moduł narzędzi umożliwiających połącznie z GNUPlotem
 *
 * Niniejsza przestrzeń nazw stanowi moduł logiczny zawierający
 * narzędzia umożliwiające realizację połączenia z programem \p gnuplot.
 */
namespace PzG {

  /*!
   * \brief Określa tryb rysowania realizowanego przez program \p gnuplot
   *
   *  Typ wyliczeniowy określające dopuszczalne tryby rysowania
   *  realizowanego przez program \p gnuplot. Wybór trybu wiąże się
   *  ze zmianą sposobu interpretacji danych zawartych pliku. Jeśli 
   *  np. wybrany zostanie tryb 2D, to zakłada się, że w każdej linii
   *  pliku z danymi znajdują się wartości współrzędnych \e x, \e y.
   */
  enum TypTrybuRysowania { 
            /*!
	     * - rysowanie w trybie 2D, co sprowadza się do 
             * rysowania wykresów funkcji jednej zmiennej.
	     */
            TR_2D,  
            /*!
	     * - rysowanie w trybie 3D. Oznacza to możliwość
             * rysowania wykresów funkcji dwóch zmiennych.
             */
            TR_3D 
        };
  /*!
   * \brief Sposób rysowania linii lub punktów
   *
   *  Sposób rysowania linii lub punktów. 
   */
  enum TypSposobuRysowania { 
      /*!
       * - rysowana jest linia łaman łącząca kolejne punkty.
       * Współrzędne punktów \e x i \e y zadawane są w pliku tekstowym.
       * Zapiswane one muszą być w osobnych liniach.
         \verbatim
       20    30
       41.5  62
\endverbatim
       */
       SR_Ciagly, 
      /*!
       * - rysowane są jednakowe punkty.
       * Współrzędne punktów \e x i \e y zadawane są w pliku tekstowym.
       * Zapiswane one muszą być w osobnych liniach, np.
         \verbatim
       20    30
       41.5  62
\endverbatim
       */
       SR_Punktowy,
      /*!
       * - rysowane są punkty o różnych rozmiarach.
       * Współrzędne punktów \e x i \e y oraz ich rozmiary 
       * zadawane są w pliku tekstowym.
       * Wartość rozmiaru musi być liczbą całkowitą większą od 0.
       * Współrzędne i rozmiar muszą być w osobnych liniach, np.
         \verbatim
       20    30   5
       41.5  62   2
\endverbatim
       */
       SR_PunktowyNiejednorodny 
   };
  /*!
   * \brief Typ dostępu do plik z danymi
   * 
   * Typ dostepu do plik z danymi, tzn. czy jest on lokalny tylko 
   * z poziomu pojedynczego łącza czy też z pozmiomu wszystkich łącz
   */
  enum TypDostepuDoZasobu { 
      /*!
       * - dostęp tylko z poziomu pojedynczego łącza. 
       * Dane z pliku będą wizualizowane tylko w jednym okienku graficznym
       * odpowiadające danym łączu.
       */
      DZ_Lokalny, 
      /*!
       * - dostęp ze poziomu wszystkich łączy. 
       * Dane z pliku będą wizualizowane we okienkach graficznych
       * odpowiadającym utworzonym łączom.
       */
      DZ_Globalny 
   };

  /*!
   * \brief Zestaw informacji dotyczący pliku i sposobu rysowania
   *
   * Klasa modeluje zestaw informacji dotyczący pliku i sposobu
   * w jaki mają być wizualizowane zawarte w nim dane.
   */
  class InfoPlikuDoRysowania {
    public:
     /*!
      * \brief Inicjalizuje obiekt
      */
     InfoPlikuDoRysowania( const char*      NazwaPliku, 
                           TypSposobuRysowania  SposobRys, 
                           int              Szerokosc = 1,
                           int              Kolor = 1,
                           int              Styl  = 7
                         );
     /*!
      * \brief Udostępia nazwę pliku do rysowania
      *
      * Udostępnia nazwę pliku z danymi do rysowania.
      */
     const std::string WezNazwePliku() const { return _NazwaPliku; }
     /*!
      * \brief Zmienia nazwę pliku do rysowania
      *
      * Zmienia nazwę pliku z danymi do rysowania.
      */
     void ZmienNazwePliku(const std::string& NazwaPliku) 
                                       { _NazwaPliku = NazwaPliku; }
     /*!
      * \brief Udostępnia sposób rysowanej linii
      *
      * Udostępnia informację o sposóbie rysowania linii.
      */
     TypSposobuRysowania WezSposobRys() const { return _SposobRys; }
     /*!
      * \brief Zmienia sposób rysowania
      *
      * Zmienia sposób rysowania linii lub płaszczyzny. Rodzaj obiektu
      * zależy od typu przekazywanych danych w pliku skojarzonym z
      * z danym obiektem graficznym.
      * \param SposobRys - nowy sposób rysowania, który będzie przyporządkowany
      *               danemu obiektowi graficznemu.
      */
      InfoPlikuDoRysowania& ZmienSposobRys(TypSposobuRysowania  SposobRys) 
                                 { _SposobRys = SposobRys;  return *this; }
     /*!
      * \brief  Udostępnia informację o szerokości linii.
      *
      *  Udostępnia informację o szerokości rysowanej linii.
      */
     int WezSzerokosc() const { return _Szerokosc; }
     /*!
      * \brief Zmienia szerokość rysowania elementów graficznych.
      *
      * Zmienia szerokość rysowania elementów graficznych.
      *
      * \param Szerokosc - nowa wartość szerokości rysowanej linii.
      * \pre Parametr \e Szerokosc musi mieć warość większą od 0.
      */
     InfoPlikuDoRysowania& ZmienSzerokosc(int Szerokosc)
                                { _Szerokosc = Szerokosc;  return *this; }
     /*!
      * \brief Udostępnia numer koloru
      *
      * Udostępnia numer koloru jakim ma być rysowany dany
      * element.
      */
     int WezKolor() const { return _Kolor; }
     /*!
      * \brief Zmienia kolor rysowania elementów graficznych.
      *
      * Zmienia kolor rysowania elementów graficznych.
      *
      * Informację o kolorach rysowanych obiektów odpowiadających poszczególnym 
      * wartościom
      * można uzyskać poprzez wywołanie programu \e gnuplot, a następnie
      * wykonania polecenia \e test na poziomie interakcji z programem
      * \e gnuplot. Kolory rysowanych obiektów odpowiadające poszczególnym 
      * numerom są widoczne
      * po prawej stronie wyświetlonego okienka.
      * \param Kolor - numer nowego koloru rysowania.
      */
     InfoPlikuDoRysowania& ZmienKolor(int Kolor)
                                { _Kolor = Kolor;  return *this; }

     /*!
      * \brief Udostępia oznaczenie liczbowe stylu rysowania
      *
      * Udostępia oznaczenie liczbowe stylu rysowania danego
      * obiektu graficznego.
      *
      * Informację o stylach rysowanych obiektów odpowiadających poszczególnym 
      * wartościom
      * można uzyskać poprzez wywołanie programu \e gnuplot, a następnie
      * wykonania polecenia \e test na poziomie interakcji z programem
      * \e gnuplot. Style rysowanych obiektów odpowiadające poszczególnym 
      * numerom są widoczne
      * po prawej stronie wyświetlonego okienka.
      */
     int WezStyl() const { return _Styl; }
     /*!
      * \brief Zmienia styl rysowania
      *
      * Zmienia styl rysowania obiektu graficznego (linii lub punktów).
      * 
      * Informację o stylach rysowanych obiektów odpowiadających poszczególnym 
      * wartościom
      * można uzyskać poprzez wywołanie programu \e gnuplot, a następnie
      * wykonania polecenia \e test na poziomie interakcji z programem
      * \e gnuplot. Style rysowanych obiektów odpowiadające poszczególnym 
      * numerom są widoczne
      * po prawej stronie wyświetlonego okienka.
      * \param Styl - numer nowego stylu rysowania.
      */
     InfoPlikuDoRysowania& ZmienStyl(int Styl)
                                { _Styl = Styl;  return *this; }
     /*!
      * \brief Udostępnia etykietę punktów
      *
      *  Udostępnia etykietę, która może być użyta do 
      *  oznaczania punktów.
      */
     const std::string& WezEtykiete() const { return _Etykieta; }
     /*!
      * \brief Zmienia etykietę 
      *
      * Zmienia etykietę, która ma się pojawić przy rysowanym 
      * elemencie.
      * \param Etykieta - zawartość nowej etykiety.
      */
     InfoPlikuDoRysowania& ZmienEtykiete(const char* Etykieta)
                                { _Etykieta = Etykieta;  return *this; }

    private:
     /*!
      * \brief Nazwa pliku z danymi do rysowania
      *
      * Nazwa pliku z danymi do rysowania.
      */
     std::string  _NazwaPliku;
     /*!
      * \brief Etykieta, która może być umieszczana przy punktach
      *
      * Etykieta, którą mogą być oznaczane wyświetlane punkty.
      * Jeśli jest ich więcej niż 1, to do każdej etykiety
      * dopisywany jest kolejny numer.
      */
     std::string  _Etykieta;
     /*!
      * \brief Szerokość użytego piórka
      *
      * Określa szerokość piórka, jakie ma być użyte
      * do rysowania obiektów graficznych. W przypadku rysowania
      * obiektów punktowych określa rozmiar tego obiektu.
      */
     int  _Szerokosc;
     /*!
      * \brief Styl rysowanego elementu
      *
      *  Przechowuje informację o typie rysowanego punktu.
      *  Jeśli rysowana jest linia, to wartość ta określa typ rysowanej
      *  linii (ciągła, kreskowana, kropkowana itd.). Jeśli rysowane
      *  są obiekty punktowe, to określa ona typ rysowanego puntku (krzyżyk,
      *  kropka, kólko itd.).
      *
      * Informację o stylach rysowanych obiektów odpowiadających poszczególnym 
      * wartościom
      * można uzyskać poprzez wywołanie programu \e gnuplot, a następnie
      * wykonania polecenia \e test na poziomie interakcji z programem
      * \e gnuplot. Style rysowanych obiektów odpowiadające poszczególnym 
      * numerom są widoczne
      * po prawej stronie wyświetlonego okienka.
      */     
     int  _Styl;
     /*!
      * \brief Numer koloru rysowanego elementu
      *
      * Przechowuje numer koloru jaki ma być użyty do rysowania wykresów 
      * lub punktów (w zależności od wyboru trybu rysowania patrz 
      * \link PzG::InfoPlikuDoRysowania::_SposobRys _SposobRys\endlink).
      *
      * Informację o kolorach odpowiadających poszczególnym wartościom
      * można uzyskać poprzez wywołanie programu \e gnuplot, a następnie
      * wykonania polecenia \e test na poziomie interakcji z programem
      * \e gnuplot. Kolory odpowiadające poszczególnym numerom są widoczne
      * po prawej stronie wyświetlonego okienka.
      */
     int  _Kolor;

     /*!
      * \brief Sposób rysowania danej linii
      *
      * Przechowuje informacje o sposobie rysowania linii.
      */
     TypSposobuRysowania  _SposobRys;
  };


/*!
 * \brief  Klasa realizuje interfejs do programu GNUPlot.
 *
 * Klasa realizuje interfejs do programu GNUPlot. Pozwala ona na wskazanie
 * zbioru punktów płaszczyzn umieszczonych w pliku lub plikach.
 * Każdy taki zbiór może być następnie wizualizowany przez program 
 * gnuplot w postaci oddzielnych płaszczyzn z wycinaniem części zasłanianych.
 */
class LaczeDoGNUPlota {
 protected:
  /*!
   * \brief Lista nazw plików z danymi dla \e gnuplota.
   *
   * Pole jest zarządcą listy nazw plików, z których są wczytywane
   * dane dotyczące rysowania obrysu brył przez program \e gnuplot.
   * Operacja ta wykonywana jest po wywołaniu polecenia. Pole to jest
   * wspólne dla wszystkich łączy.
   * \link LaczeDoGNUPlota::Rysuj Rysuj\endlink.
   */
  static std::list<InfoPlikuDoRysowania>  _InfoPlikow_Glb;
  /*!
   * \brief Lista nazw plików z danymi dla \e gnuplota.
   *
   * Pole jest zarządcą listy nazw plików, z których są wczytywane
   * dane dotyczące rysowania obrysu brył przez program \e gnuplot.
   * Operacja ta wykonywana jest po wywołaniu polecenia. Pole to jest
   * indywidulane dla danego łącza.
   * \link LaczeDoGNUPlota::Rysuj Rysuj\endlink.
   */
  std::list<InfoPlikuDoRysowania>  _InfoPlikow_Lok;

   /*!
    * \brief Deskryptor wejścia standardowego procesu gnuplota
    *
    *  Pole przechowuje deskryptor wejścia standardowego związanego
    *  z procesem uruchomionego programu gnuplot.
    */
  int           _Wejscie_GNUPlota;
   /*!
    * \brief Deskryptor wejścia standardowego procesu gnuplota
    *
    *  Pole przechowuje deskryptor do wyjścia standardowego związanego
    *  z procesem uruchomionego programu gnuplot.
    */
  int           _Wyjscie_GNUPlota;
   /*!
    *  \brief Decyduje czy mają być wyświetlane komunikaty o błędach
    *
    *  Wartość tego pola decyduje o tym czy komunikaty o błędach będą 
    *  wyświetlane na wyjście standardowe błędów (\b cerr), czy też nie.
    *   \li \p true - komunikaty będę wyświetlane,
    *   \li \p false -  komunikaty nie będę wyświetlane.
    */
  bool          _WyswietlajKomunikatyOBledach;

  /*!
   * \brief Określa aktualny tryb rysowania
   *
   * Zawartość pola determinuje sposób rysowania, jaki zostanie 
   * wymuszony na programie \p gnuplot poprzez wysłanie do niego
   * odpowiednich poleceń. Wspomniane wymuszenie jest realizowane
   * poprzez wywołanie polecenia 
   * \link LaczeDoGNUPlota::Rysuj Rysuj()\endlink
   */
  TypTrybuRysowania  _TrybRys;
   /*!
    *  \brief Dolny zakres wyświetlanej skali skali dla osi \e OX.
    *
    *  Określa dolny zakres wyświetlanej skali dla osi \e OX.
    */
  float  _Xmin;
   /*!
    *  \brief Górny zakres wyświetlanej skali skali dla osi \e OX.
    *
    *  Określa górny zakres wyświetlanej skali dla osi \e OX.
    */
  float  _Xmax;
   /*!
    *  \brief Dolny zakres wyświetlanej skali skali dla osi \e OY.
    *
    *  Określa dolny zakres wyświetlanej skali dla osi \e OY.
    */
  float  _Ymin;
   /*!
    *  \brief Górny zakres wyświetlanej skali skali dla osi \e OY.
    *
    *  Określa górny zakres wyświetlanej skali dla osi \e OY.
    */
  float  _Ymax;
   /*!
    *  \brief Dolny zakres wyświetlanej skali skali dla osi \e OZ.
    *
    *  Określa dolny zakres wyświetlanej skali dla osi \e OZ.
    */
  float  _Zmin;
   /*!
    *  \brief Górny zakres wyświetlanej skali skali dla osi \e OZ.
    *
    *  Określa górny zakres wyświetlanej skali dla osi \e OZ.
    */
  float  _Zmax;
   /*!
    * \brief Skala rysunku wzdłuż osi \e OX
    *
    *  Wartość tego pola definiuje skalowanie rysunku wzdłuż osi 
    *  \e OX (oś horyzontalna ekranu).
    */
  float  _Xskala;
   /*!
    * \brief Skala rysunku wzdłuż osi \e OZ
    *
    *  Wartość tego pola definiuje skalowanie rysunku wzdłuż osi 
    *  \e OZ (oś wertykalna ekranu).
    */
  float  _Zskala;
   /*!
    * \brief Rotacja rysunku względem osi \e OX
    *
    *  Wartość tego pola definiuje rotację rysunku (zmiane punktu patrzenia)
    *  względem osi \e OX.
    */
  float  _Xrotacja;
   /*!
    * \brief Rotacja rysunku względem osi \e OZ
    *
    *  Wartość tego pola definiuje rotację rysunku (zmiane punktu patrzenia)
    *  względem osi \e OZ.
    */
  float  _Zrotacja;

  /*!
   * \brief Czy oś OX ma być widoczna
   *
   * Przechowuje informację decydującą o tym czy oś OX będzie
   * widoczna na rysunku (\p true), czy też nie (\p false).
   */
  bool _PokazOs_OX;

  /*!
   * \brief Czy oś OY ma być widoczna
   *
   * Przechowuje informację decydującą o tym czy oś OY będzie
   * widoczna na rysunku (\p true), czy też nie (\p false).
   */
  bool _PokazOs_OY;



  /*!
   * \brief Tworzy listę parametrów umożliwiających rysowanie dodatkowych elementów
   *
   * Metoda ta przewidziana jest jako element rozszerzenia pozwalającego
   * w klasach pochodnych powiększyć listę rysowanych elementów.
   * \pre Parametr \e Polecenie powinien zawierać polecenie \e plot lub \e splot,
   *      do którego będzie możliwe dopisanie dalszego ciągu.
   * \param Polecenie - polecenie rysowania, do którego mają być dopisane 
   *                    nazwy plików i odpowiednie parametry dla polecenia plot.
   * \param Sep - zawiera znak separatora między poszczególnymi
   *              parametrami. Jeżeli parametry listy przeszkód
   *              są generowane jako pierwsze, to zmienna ta musi 
   *              być wskaźnikiem do wskaźnika na łańcuch: " ".
   */
  virtual bool DopiszPlikiDoPoleceniaRysowania( std::string   &Polecenie, 
                                                char const   **Sep 
                                              );

  /*!
   *  \brief Tworzy polecenie ustawiające zakres dla danej współrzędnej.
   *
   *  Tworzy polecenie dla programu \e gnuplot ustawiające zakres 
   *  współrzędnych wybranej współrzędnej \e x, \e y lub \e z, 
   *  dla której ma być tworzony dany rysunek.
   *  \param Os - zawiera znak określający współrzędną, dla której
   *             ma zostać wygenerowane polecenie ustawienia zakresu.
   *  \return łańcuch znaków polecenia ustawiającego żądany zakres
   *          dla wybranej współrzędnej.
   */
  std::string ZapiszUstawienieZakresu(char Os) const;
  /*!
   *  \brief Tworzy polecenie ustawiające punkt obserwacji.
   *
   *  Tworzy polecenie dla programu \e gnuplot ustawiajające punkt obserwacji
   *  poprzez zadanie rotacji i skali dla poszczególnych osi.
   */
  std::string ZapiszUstawienieRotacjiISkali() const;
   /*!
    * \brief Przesyła polecenie do gnuplota
    *
    * Przesyła na wejście programu \e gnuplot zadany ciąg znaków.
    *  \param Polecenie - komunikat przeznaczony do przeslania.
    *
    * \pre  Musi być zainicjowane połączenie z programem gnuplot.
    *
    * \retval true  - jesli przeslanie polecenia zakończyło się powodzeniem,
    * \retval false - w przypadku przeciwnym.
    *
    */
  bool PrzeslijDoGNUPlota(const char *Polecenie);
  /*!
   * \brief  Udostępnia informację czy mają być wyświetlane informacje o błędach.
   *
   *  Udostępnia wartość pola
   *  \link LaczeDoGNUPlota::_WyswietlajKomunikatyOBledach
   *            _WyswietlajKomunikatyOBledach\endlink.
   *  Określa ono, czy mają być wyświetlane komunikaty o błędach na wyjście
   *  standardowe, czy też nie.
   */
  bool CzyWyswietlacKomunikaty() const { return _WyswietlajKomunikatyOBledach;}
  /*!
   * \brief Uruchamia program \e gnuplot jako proces potomny.
   *
   * Uruchamia program \e gnuplot jako proces potomny.
   * \retval true - jeśli operacja powiodła się.
   * \retval false - w przypadku przeciwnym.
   */
  bool UtworzProcesPotomny();
  /*!
   * \brief Wyświetla komunika błędu
   *
   * Wyświetla na wyjście "standard error" komunikat (przekazany jako
   * parametr), o ile pole 
   *   \link LaczeDoGNUPlota::_WyswietlajKomunikatyOBledach
   *          _WyswietlajKomunikatyOBledach\endlink  ma wartość
   * \p true. W przypadku przeciwnym komunikat nie jest wyświetlany.
   */
  void KomunikatBledu(const char *Komunikat) const;

  /*!
   * \brief Tworzy preambułę poprzedzającą polecenie rysowania
   *
   *  Tworzy zbiór poleceń, które ustawiają właściwy tryb rysowania
   *  oraz zakresy współrzędnych, jak też wszystkie inne parametry
   *  wynikające z przyjętego trybu rysowania.
   */
  void BudujPreambulePoleceniaRysowania(std::string &Preambula) const;

  /*!
   * \brief Tworzy preambułę poprzedzającą polecenie rysowania w trybie 2D
   *
   *  Tworzy zbiór poleceń, które ustawiają właściwy tryb rysowania
   *  oraz zakresy współrzędnych, jak też wszystkie inne parametry
   *  wynikające z trybu rysowania 2D.
   */
  void BudujPreambule_2D(std::string &Preambula) const;


  /*!
   * \brief Tworzy preambułę poprzedzającą polecenie rysowania w trybie 3D
   *
   *  Tworzy zbiór poleceń, które ustawiają właściwy tryb rysowania
   *  oraz zakresy współrzędnych, jak też wszystkie inne parametry
   *  wynikające z trybu rysowania 3D.
   */
  void BudujPreambule_3D(std::string &Preambula) const;


 public:

  /*!
   * \brief Umożliwia lub zabrania rysowania osi OX
   *
   * Umożliwia lub zabrania rysowania osi \e OX na rysunku wykresu.
   * \param Pokaz - decyduje o tym czy oś \e OX będzie rysowana (\p true),
   *                czy też nie (\p false).
   */
  void PokazOs_OX(bool Pokaz) { _PokazOs_OX = Pokaz; }

  /*!
   * \brief Czy oś OX ma być rysowana
   *
   * Udostępnia informację czy oś \e OX ma być rysowana,
   * czy też nie.
   * \retval true - gdy oś \e OX ma być rysowana,
   * \retval false - w przypadku przeciwnym.
   */
  bool PokazOs_OX() const { return _PokazOs_OX; }


  /*!
   * \brief Umożliwia lub zabrania rysowania osi OY
   *
   * Umożliwia lub zabrania rysowania osi \e OY na rysunku wykresu.
   * \param Pokaz - decyduje o tym czy oś \e OY będzie rysowana (\p true),
   *                czy też nie (\p false).
   */
  void PokazOs_OY(bool Pokaz) { _PokazOs_OY = Pokaz; }

  /*!
   * \brief Czy oś OY ma być rysowana
   *
   * Udostępnia informację czy oś \e OY ma być rysowana,
   * czy też nie.
   * \retval true - gdy oś \e OY ma być rysowana,
   * \retval false - w przypadku przeciwnym.
   */
  bool PokazOs_OY() const { return _PokazOs_OY; }


  /*!
   * \brief Dolna wartość zakresu dla osi \e OX
   *
   *  Udostępnia dolną wartość zakresu skali wzdłuż osi \e OX.
   */
  float Xmin() const { return _Xmin; }
  /*!
   * \brief Górną wartość zakresu dla osi \e OX
   *
   *  Udostępnia górną wartość zakresu skali wzdłuż osi \e OX.
   */
  float Xmax() const { return _Xmax; }
  /*!
   * \brief Dolną wartość zakresu dla osi \e OY
   *
   *  Udostępnia dolną wartość zakresu skali wzdłuż osi \e OY.
   */
  float Ymin() const { return _Ymin; }
  /*!
   * \brief Górną wartość zakresu dla osi \e OY
   *
   *  Udostępnia górną wartość zakresu skali wzdłuż osi \e OY.
   */
  float Ymax() const { return _Ymax; }
  /*!
   * \brief Dolną wartość zakresu dla osi \e OZ
   *
   *  Udostępnia dolną wartość zakresu skali wzdłuż osi \e OZ.
   */
  float Zmin() const { return _Zmin; }
  /*!
   * \brief Górną wartość zakresu dla osi \e OZ
   *
   *  Udostępnia górną wartość zakresu skali wzdłuż osi \e OZ.
   */
  float Zmax() const { return _Zmax; }

  /*!
   * \brief Zmienia tryb rysowania
   *
   * Zmienia tryb rysowania jaki zostanie wymuszony na programie
   * \p gnuplot.
   * \param Tryb - wartość parametru określa nowy tryb rysowania.
   */
  void ZmienTrybRys(TypTrybuRysowania  Tryb) { _TrybRys = Tryb; }

  /*!
   * \brief Udostępnia aktualny tryb rysowania
   *
   * Udostępnia informację o aktualnym trybie rysowania.
   */
  TypTrybuRysowania WezTrybRys() const { return _TrybRys; }

  /*!
   *  \brief Ustawia zakres osi \e OX
   *
   * Ustawia zakres osi \e OX. Ogranicza to obszar, który będzie
   * zwizualizowany przez programa \e gnuplot.
   * \param Xo - dolna granica obszaru rysowania dla osi \e OX.
   * \param Xn - górna granica obszaru rysowania dla osi \e OX.
   */
  void UstawZakresX(float Xo, float Xn) { _Xmin = Xo;  _Xmax = Xn; }
  /*!
   *  \brief Ustawia zakres osi \e OY
   *
   * Ustawia zakres osi \e OY. Ogranicza to obszar, który będzie
   * zwizualizowany przez programa \e gnuplot.
   * \param Yo - dolna granica obszaru rysowania dla osi \e OY.
   * \param Yn - górna granica obszaru rysowania dla osi \e OY.
   */
  void UstawZakresY(float Yo, float Yn) { _Ymin = Yo;  _Ymax = Yn; }
  /*!
   *  \brief Ustawia zakres osi \e OZ. 
   *
   * Ustawia zakres osi \e OZ. Ogranicza to obszar, który będzie
   * zwizualizowany przez programa \e gnuplot.
   * \param Zo - dolna granica obszaru rysowania dla osi \e OZ.
   * \param Zn - górna granica obszaru rysowania dla osi \e OZ.
   */
  void UstawZakresZ(float Zo, float Zn) { _Zmin = Zo;  _Zmax = Zn; }


  /*!
   *  \brief Udostępnia skalę dla osi \e OX.
   *
   *  Udostępnia skalę dla osi \e OX dla tworzonego rysunku.
   */
  float SkalaX() const { return _Xskala; }
  /*!
   *  \brief Udostępnia skalę dla osi \e OZ.
   *
   *  Udostępnia skalę dla osi \e OZ dla tworzonego rysunku.
   */
  float SkalaZ() const { return _Zskala; }
  /*!
   *  \brief Zadaje skalę wzdłuż osi \e OZ.
   *
   *  Zadaje skalę wzdłuż osi \e OX dla tworzonego rysunku.
   *  \param skala_x - skala wzdłuż osi \e OX.
   */
  void UstawSkaleX( float skala_x ) { _Xskala = skala_x; }
  /*!
   *  \brief Zadaje skalę wzdłuż osi \e OZ.
   *
   *  Zadaje skalę wzdłuż osi \e OZ dla tworzonego rysunku.
   *  \param skala_z - skala wzdłuż osi \e OZ.
   */
  void UstawSkaleZ( float skala_z ) { _Zskala = skala_z; }
  /*!
   *  \brief Zadaje skalę wzdłuż osi \e OX i \e OZ.
   *
   *  Zadaje skalę wzdłuż osi \e OX i \e OZ dla tworzonego rysunku.
   *  \param skala_x - skala wzdłuż osi \e OX.
   *  \param skala_z - skala wzdłuż osi \e OZ.
   */
  void UstawSkaleXZ( float skala_x, float skala_z ) 
          { UstawSkaleX(skala_x);  UstawSkaleZ(skala_z); }

  /*!
   * \brief Wartość kąta rotacji względem osi \e OX
   *
   *  Udostępnia wartość kąta rotacji renderowanego rysunku wokół
   *  osi \e OX. Zwracana wartość wyrażona jest w stopiniach.
   */
  float RotacjaX() const { return _Xrotacja; }
  /*!
   * \brief Wartość kąta rotacji względem osi \e OZ
   *
   *  Udostępnia wartość kąta rotacji renderowanego rysunku wokół
   *  osi \e OZ. Zwracana wartość wyrażona jest w stopiniach.
   */
  float RotacjaZ() const { return _Zrotacja; }
  /*!
   * \brief Ustawia rotację wokół osi \e OX.
   *
   * Zadaje kąt rotacji wokół osi \e OX. Umożliwia to zmianę
   * punktu obserwacji renderowanego rysunku.
   * \param  kat_x - wartość kąta rotacji. Jego wartość podawana 
   *                 jest w stopniach.
   */
  void UstawRotacjeX( float kat_x ) { _Xrotacja = kat_x; }
  /*!
   * \brief Ustawia rotację wokół osi \e OZ.
   *
   * Zadaje kąt rotacji wokół osi \e OZ. Umożliwia to zmianę
   * punktu obserwacji renderowanego rysunku.
   * \param  kat_z - wartość kąta rotacji. Jego wartość podawana 
   *                 jest w stopniach.
   */
  void UstawRotacjeZ( float kat_z ) { _Zrotacja = kat_z; }
  /*!
   * \brief Ustawia rotację wokół osi \e OX i \e OZ.
   *
   * Zadaje jednocześnie kąt rotacji wokół osi \e OX i \e OZ. 
   * Umożliwia to zmianę
   * punktu obserwacji renderowanego rysunku.
   * \param  kat_x - wartość kąta rotacji względem osi \e OX. 
   *                 Jego wartość podawana 
   *                 jest w stopniach.
   * \param  kat_z - wartość kąta rotacji względem osi \e OZ. 
   *                 Jego wartość podawana 
   *                 jest w stopniach.
   */
  void UstawRotacjeXZ( float kat_x, float kat_z ) 
    { UstawRotacjeX(kat_x);  UstawRotacjeZ(kat_z); }  

  /*!
   *  \brief Zezwala lub zabrania wyświetlania komunikatów.
   *
   *  Metoda pozwala, albo też zabrania wyświetlania komunikatów o blędach.
   *  Jeżeli jakaś z operacji nie powiedzie się, to jako wynik zwracana
   *  jest wartość \p false. Oprócz tego metody takie moga wyświetlać
   *  komunikaty, które kierowane są na wyjście "standard error"
   *  Domyślnie przymuje się, że programista nie chce dodatkwego wyświetlania
   *  komunikatów.
   */
  void WyswietlajKomunikatyBledow( bool Tryb = true );

   /*!
    * \brief  Dodaje nazwę pliku.
    *
    * Powoduje dodanie do listy plików zawierajacych dane dla \e gnuplota,
    * nowej nazwy pliku.
    *
    * \param  NazwaPliku  - nazwa pliku z danymi dla gnuplota.
    * \param  SprawdzIstnienie - decyduje o tym czy będzie sprawdzane
    *                istnienie danego pliku w momencie wywołania
    *                niniejszej metody.
    * \param  Dostep - decyduje o tym, czy dany plik będzie \e widziany
    *                przez wszystkie łącza, czy też przez tylko jedno.
    *                Parametr ten ma znaczenie tylko wtedy, gdy programista
    *                chce aby ukazało się więcej niż jedno okienko programu
    *                \e gnuplot. Oznacza to uruchmienie tylu procesów programu
    *                \e gnuplot ile jest okienek. Parametr \e Dostep decyduje
    *                wówczas, czy dane zawarte w pliku będą wyświetlane w jednym
    *                okienku, czy też we wszystkich.
    *
    * \return Zwraca referencję do obiektu zawierającego atrybuty 
    *         rysowania danych w podanym pliku.
    */
    InfoPlikuDoRysowania& DodajNazwePliku(
                                 std::string NazwaPliku,
                                 bool                SprawdzIstnienie = false,
                                 TypDostepuDoZasobu   Dostep = DZ_Lokalny
                               );

   /*!
    * \brief  Dodaje nazwę pliku.
    *
    * Powoduje dodanie do listy plików zawierajacych dane dla \e gnuplota,
    * nowej nazwy pliku. Domyślnie dane z tego pliku będą rysowane 
    * jako łamana łącząca punkty o podanych współrzędnych.
    *
    * \param  NazwaPliku  - nazwa pliku z danymi dla gnuplota.
    * \param  SprawdzIstnienie - decyduje o tym czy będzie sprawdzane
    *                istnienie danego pliku w momencie wywołania
    *                niniejszej metody.
    * \param  Dostep - decyduje o tym, czy dany plik będzie \e widziany
    *                przez wszystkie łącza, czy też przez tylko jedno.
    *                Parametr ten ma znaczenie tylko wtedy, gdy programista
    *                chce aby ukazało się więcej niż jedno okienko programu
    *                \e gnuplot. Oznacza to uruchmienie tylu procesów programu
    *                \e gnuplot ile jest okienek. Parametr \e Dostep decyduje
    *                wówczas, czy dane zawarte w pliku będą wyświetlane w jednym
    *                okienku, czy też we wszystkich.
    *
    * \return Zwraca referencję do obiektu zawierającego atrybuty 
    *         rysowania danych w podanym pliku.
    */
   InfoPlikuDoRysowania& DodajNazwePliku_Lamana( 
                            const char         *NazwaPliku,
                            bool                SprawdzIstnienie = false,
                            TypDostepuDoZasobu   Dostep = DZ_Lokalny
                          );

   /*!
    * \brief  Dodaje nazwę pliku.
    *
    * Powoduje dodanie do listy plików zawierajacych dane dla \e gnuplota,
    * nowej nazwy pliku. Domyślnie dane z tego pliku będą rysowane 
    * jako zbiór jednakowych punktów o podanych współrzędnych.
    *
    * \param  NazwaPliku  - nazwa pliku z danymi dla gnuplota.
    * \param  SprawdzIstnienie - decyduje o tym czy będzie sprawdzane
    *                istnienie danego pliku w momencie wywołania
    *                niniejszej metody.
    * \param  Dostep - decyduje o tym, czy dany plik będzie \e widziany
    *                przez wszystkie łącza, czy też przez tylko jedno.
    *                Parametr ten ma znaczenie tylko wtedy, gdy programista
    *                chce aby ukazało się więcej niż jedno okienko programu
    *                \e gnuplot. Oznacza to uruchmienie tylu procesów programu
    *                \e gnuplot ile jest okienek. Parametr \e Dostep decyduje
    *                wówczas, czy dane zawarte w pliku będą wyświetlane w jednym
    *                okienku, czy też we wszystkich.
    *
    * \return Zwraca referencję do obiektu zawierającego atrybuty 
    *         rysowania danych w podanym pliku.
    */
   InfoPlikuDoRysowania& DodajNazwePliku_JednakowePunkty( 
                               const char         *NazwaPliku,
                               bool                SprawdzIstnienie = false,
                               TypDostepuDoZasobu   Dostep = DZ_Lokalny
                            );


   /*!
    * \brief  Dodaje nazwę pliku.
    *
    * Powoduje dodanie do listy plików zawierajacych dane dla \e gnuplota,
    * nowej nazwy pliku.
    *
    * \param  NazwaPliku  - nazwa pliku z danymi dla gnuplota.
    * \param  SprawdzIstnienie - decyduje o tym czy będzie sprawdzane
    *                istnienie danego pliku w momencie wywołania
    *                niniejszej metody.
    * \param  Dostep - decyduje o tym, czy dany plik będzie \e widziany
    *                przez wszystkie łącza, czy też przez tylko jedno.
    *                Parametr ten ma znaczenie tylko wtedy, gdy programista
    *                chce aby ukazało się więcej niż jedno okienko programu
    *                \e gnuplot. Oznacza to uruchmienie tylu procesów programu
    *                \e gnuplot ile jest okienek. Parametr \e Dostep decyduje
    *                wówczas, czy dane zawarte w pliku będą wyświetlane w jednym
    *                okienku, czy też we wszystkich.
    *
    * \return Zwraca referencję do obiektu zawierającego atrybuty 
    *         rysowania danych w podanym pliku.
    */
   InfoPlikuDoRysowania& DodajNazwePliku_PunktyRoznejWielkosci( 
                                  const char         *NazwaPliku,
                                  bool                SprawdzIstnienie = false,
                                  TypDostepuDoZasobu   Dostep = DZ_Lokalny
                                );



  /*!
   * \brief Tworzy listę parametrów umożliwiających rysowanie brył z plików.
   */
  bool DopiszRysowanieZPlikow( std::string &Polecenie, char const **Sep );

  /*!
   * \brief Tworzy listę parametrów umożliwiających rysowanie brył z plików.
   */
  bool DopiszRysowanieZRoznychPunktow( std::string   &Polecenie, 
                                       char const    *Sep 
                                     );


  /*!
   * \brief Informuje, czy połączenie z \e gnuplot'em jest zainicjalizowane.
   *
   * Informuje, czy połączenie z programem \e gnuplot jest zainicjowane.
   * \retval true - jeśli tak,
   * \retval false - w przypadku przeciwnym.
   */ 
  bool CzyPolaczenieJestZainicjowane() const;

  /*!
   * \brief Generuje polecenie rysowania i przesyła je do gnuplota
   *
   *  Jeżeli lista plików nie jest pusta, to generuje sekwencje poleceń
   *  dla programu \e gnuplot mająca na celu narysowanie płaszczyzn na
   *  na podstawie danych zawartych w plikach z listy. 
   *
   *  \pre  Lista plików nie powinna być pusta. Nazwy plików na niej
   *        można umieścić za pomoca metody 
   *        \link LaczeDoGNUPlota::DodajNazwePliku DodajNazwePliku\endlink
   *        jak też innych tego typu metod.
   *        Metoda nie wymaga wcześniejszego zainicjowania połączenia
   *        z \e gnuplotem.
   *  \retval true   - gdy zostają poprawnie wysłane polecenia dla gnuplota.
   *                 Nie oznacza to jednak, że proces rysowania zakończył
   *                 się pomyślnie.
   *  \retval false   - gdy połączenie z gnuplotem nie może zostać poprawnie
   *                 zainicjalizowane lub gdy lista plików jest pusta.
   */
  bool Rysuj();
  /*!
   * \brief Generuje polecenie rysowania do pliku i przesyła je do gnuplota
   *
   *  Działa analogicznie jak metoda 
   *  \link LaczeDoGNUPlota::Rysuj Rysuj\endlink, z tą różnicą, że 
   *  rysunek robota
   *  składowany jest w pliku o nazwie przekazanej przez parametr 
   *  \e NazwaPliku.
   *  Rysunek jest zapisywany w formacie \e PNG.
   *
   *  \post Lista plików nie powinna być pusta ponadto powinno być
   *        możliwe otwarcie do zapisu pliku o nazwie przekazanej przez
   *        parametr \e NazwaPliku, do której dołączane jest rozszerzenie
   *        .ps .
   *        Metoda nie wymaga wcześniejszego zainicjowania połączenia
   *        z programem \e gnuplot. 
   *
   *  \retval true   - gdy zostają poprawnie wysłane polecenia dla 
   *                 \e gnuplota.
   *                 Nie oznacza to jednak, że proces rysowania zakończył
   *                 się pomyślnie.
   *  \retval false   - gdy połączenie z gnuplotem nie może zostać poprawnie
   *                 zainicjalizowane lub gdy lista plików jest pusta lub
   *                 też gdy nie można otworzyć pliku do zapisu.
   */
  bool RysujDoPliku(const char *NazwaPliku);
  /*!
   *  \brief  Inicjalizuje połączenie z programem \e gnuplot.
   *
   *  Inicjalizuje połączenie z programem \e gnuplot. Realizowane jest to
   *  poprzez rozwidlenie procesu i uruchomienie jako procesu potomnego
   *  programu \e gnuplot. Komunikacja z programem \e gnuplot realizowana jest
   *  poprzez przejęcie jego wejścia i wyjścia standardowego.
   *
   *  \retval true - gdy połączenie z programem \e 0gnuplot zostało poprawnie
   *               zainicjalizowane lub gdy już wcześniej było 
   *               zainicjalizowane.
   *  \retval false - gdy proces inicjalizacji połączenia zakończył się
   *               niepowodzeniem.
   */
  bool Inicjalizuj();
  /*!
   *  \brief Usuwa ostatnią nazwę pliku.
   * 
   *  Usuwa ostatnią nazwę z lokalnej listy nazw plików, tzn.
   *  listy, która jest widoczna tylko w danym łączu z programem
   *  \e gnuplot.
   */
  void UsunOstatniaNazwe_ListaLokalna();
  /*!
   *  \brief Usuwa ostatnią nazwę pliku.
   * 
   *  Usuwa ostatnią nazwę z globalnej listy nazw plików, tzn.
   *  listy, która jest widoczna we wszystkich łączach z programem
   *  \e gnuplot.
   */
  void UsunOstatniaNazwe_ListaGlobalna();

  /*!
   *  \brief Kasuje zawartość listy nazw plików.
   * 
   *  Calkowicie kasuje zawartość listy nazw plików.
   */
  void UsunWszystkieNazwyPlikow();

  LaczeDoGNUPlota();
  virtual ~LaczeDoGNUPlota();
};

  inline
  bool LaczeDoGNUPlota::DopiszPlikiDoPoleceniaRysowania( std::string &,
                                                         char const  **
                                                       )
  { return false; }



}

#endif
