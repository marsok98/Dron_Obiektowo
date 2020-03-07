#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sstream>
#include <fstream>
#include <limits>

#ifdef __GNUG__
#pragma implementation
#endif

#include "lacze_do_gnuplota.hh"

using namespace std;


#define DOMYSLNA_SZEROKOSC        1
#define DOMYSLNY_KOLOR            1
#define DOMYSLNY_STYL             7

#define STDIN        0
#define STDOUT       1

namespace PzG {


 std::list<InfoPlikuDoRysowania>  LaczeDoGNUPlota::_InfoPlikow_Glb;



 //============================================================================
 //_____________________ InfoPlikuDoRysowania _________________________________

 /*!
  * Inicjalizuje obiekt.
  *  \param NazwaPliku - nazwa pliku, z którego pobierane będą dane,
  *  \param SposobRys    - rodzaj rysowanych obiektów (linia lub punkty),
  *  \param Szerokosc  - szerokosc linii lub wielkość punktu w zależności
  *                      od rodzaju rysowania.
  *  \param Kolor      - numer koloru jakim ma być rysowny dany element
  *                      graficzny.
  *  \param Styl       - typ obiektu graficznego, który ma być rysowany.
  */
 InfoPlikuDoRysowania::InfoPlikuDoRysowania( const char*      NazwaPliku, 
                                             TypSposobuRysowania  SposobRys, 
                                             int              Szerokosc,
                                             int              Kolor,
                                             int              Styl
                                           )
  {
     _NazwaPliku = NazwaPliku;
     _SposobRys = SposobRys;
     _Szerokosc = Szerokosc;    
     _Kolor = Kolor;
     _Styl = Styl;
  }

 //_____________________ InfoPlikuDoRysowania _________________________________
 //============================================================================




 //============================================================================
 //_____________________ LaczeDoGNUPlota ______________________________________


 void LaczeDoGNUPlota::WyswietlajKomunikatyBledow( bool Tryb )
 {
  _WyswietlajKomunikatyOBledach = Tryb;
 }


  LaczeDoGNUPlota::~LaczeDoGNUPlota() 
  {}


 bool LaczeDoGNUPlota::PrzeslijDoGNUPlota(const char *Komunikat)
 {
  int Ilosc = strlen(Komunikat);
  int IloscPrzeslanych;
  
  while (((IloscPrzeslanych = write(_Wejscie_GNUPlota,Komunikat,Ilosc)) != -1)
          && Ilosc > 0) {
    Komunikat += IloscPrzeslanych;
    Ilosc -= IloscPrzeslanych;
  }
  if (Ilosc > 0) {
    KomunikatBledu("!!! Przeslanie polecenia do GNUPlota nie powiodlo sie.");
    return false;
  }
  return true;
 }




 LaczeDoGNUPlota::LaczeDoGNUPlota() 
 { 
   _PokazOs_OX = _PokazOs_OY = true;

   _TrybRys = TR_2D;
   WyswietlajKomunikatyBledow();
   _Wyjscie_GNUPlota = _Wejscie_GNUPlota = -1; 
   UstawZakresX(-350,350);
   UstawZakresY(-350,350);
   UstawZakresZ(-200,200);
   UstawRotacjeXZ(60,30);
   UstawSkaleXZ(1,1);
 }




 bool CzyJestPlik(char const *NazwaPliku)
 {
  struct stat buf;

  if (stat(NazwaPliku,&buf)) return false;
  if (!(S_ISREG(buf.st_mode))) return false;
  if (!(buf.st_mode & S_IRUSR)) return false;
  return true;
 }




 //-------------------------------------------------------------------------
 // Powoduje dodanie do listy plikow zawierajacych dane dla gnuplota,
 // nowej nazwy pliku.
 //
 // PRE:  NazwaPliku  - nazwa pliku z danymi dla gnuplota.
 // POST:
 //  Zwraca wartosc:
 //     true - jezeli istnieje plik o nazwie zawartej w zmiennej NazwaPliku.
 //             Zostaje on ponadto dodany do listy plikow z danymi 
 //             dla gnuplota.
 //    fasle - Jezeli nie istnieje plik o nazwie zawartej w zmiennej
 //            NazwaPliku. Zadne dodatkowe dzialanie nie jest realizowane.
 //
/*
 bool LaczeDoGNUPlota::DodajNazwePliku( const char      * NazwaPliku,
                                        TypSposobRysoowania   SposobRys,
                                        int               Szerokosc
                                      )
 {
  bool rezultat = true;

  if (!CzyJestPlik(NazwaPliku)) {
    string Komunikat = "!!! Ostrzezenie: Brak pliku ";
    Komunikat += NazwaPliku;
    //TMP    KomunikatBledu(Komunikat.c_str());
    rezultat = false;
  }

  _InfoPlikow.push_back(InfoPlikuDoRysowania(NazwaPliku,SposobRys,Szerokosc));
  return rezultat;
 }
*/

 InfoPlikuDoRysowania&  LaczeDoGNUPlota::DodajNazwePliku(
                                    std::string NazwaPliku,
                                    bool                SprawdzIstnienie,
                                    TypDostepuDoZasobu  Dostep
                                  )
 
 {
    const char *NazwaPliku1 = NazwaPliku.c_str();
  if (SprawdzIstnienie && !CzyJestPlik(NazwaPliku1)) {
    cerr << "!!! Ostrzezenie: Brak pliku " << NazwaPliku1 << endl;
  }

  InfoPlikuDoRysowania Info(NazwaPliku1,SR_Ciagly,DOMYSLNA_SZEROKOSC);

  if (Dostep == DZ_Globalny) {  
    _InfoPlikow_Glb.push_back(Info);
    return  _InfoPlikow_Glb.back();
  }
  _InfoPlikow_Lok.push_back(Info);
  return _InfoPlikow_Lok.back();;
 }



/*!
 *
 */
 InfoPlikuDoRysowania& LaczeDoGNUPlota::DodajNazwePliku_PunktyRoznejWielkosci(
                                               const char         *NazwaPliku,
                                               bool                SprawdzIstnienie,
                                               TypDostepuDoZasobu  Dostep
                                            )
 {
  if (SprawdzIstnienie && !CzyJestPlik(NazwaPliku)) {
    cerr << "!!! Ostrzezenie: Brak pliku: " << NazwaPliku << endl;
  }

  InfoPlikuDoRysowania Info(NazwaPliku,SR_PunktowyNiejednorodny,
                                       DOMYSLNA_SZEROKOSC,
                                       DOMYSLNY_KOLOR,
	                               DOMYSLNY_STYL);
  if (Dostep == DZ_Globalny) {  
    _InfoPlikow_Glb.push_back(Info);
    return  _InfoPlikow_Glb.back();
  }
  _InfoPlikow_Lok.push_back(Info);
  return _InfoPlikow_Lok.back();;
 }



/*!
 *
 */
 InfoPlikuDoRysowania& LaczeDoGNUPlota::DodajNazwePliku_Lamana(
                                          const char         *NazwaPliku,
                                          bool                SprawdzIstnienie,
                                          TypDostepuDoZasobu  Dostep
                                         )
 {
     return DodajNazwePliku(NazwaPliku,SprawdzIstnienie,Dostep)
            .ZmienSposobRys(SR_Ciagly);
 }



/*!
 *
 */
 InfoPlikuDoRysowania& LaczeDoGNUPlota::DodajNazwePliku_JednakowePunkty(
                                            const char         *NazwaPliku,
                                            bool                SprawdzIstnienie,
                                            TypDostepuDoZasobu  Dostep
                                           )
 {
   return DodajNazwePliku(NazwaPliku,SprawdzIstnienie,Dostep)
            .ZmienSposobRys(SR_Punktowy);
 }


 //-------------------------------------------------------------------------
 // Informuje, czy połączenie z programem gnuplot zostało zainicjowane.
 // 
 bool LaczeDoGNUPlota::CzyPolaczenieJestZainicjowane() const
 {
  return _Wejscie_GNUPlota > -1 && _Wyjscie_GNUPlota > -1;
 }


 void LaczeDoGNUPlota::KomunikatBledu(const char *Komunikat) const
 {
  if (!CzyWyswietlacKomunikaty()) return;
  cerr << Komunikat << endl;
 }


#define ROZ_LINII   120



 bool LaczeDoGNUPlota::Inicjalizuj()
 {
  if (CzyPolaczenieJestZainicjowane()) return true;
  if (!UtworzProcesPotomny()) return false;

  return PrzeslijDoGNUPlota("\n");
 }


/*!
 *  Inicjalizuje połączenie z programem \e gnuplot. Realizowane jest to
 *  poprzez rozwidlenie procesu i uruchomienie jako procesu potomnego
 *  programu \e gnuplot. Komunikacja z programem \e gnuplot realizowana jest
 *  poprzez przejęcie jego wejścia i wyjścia standardowego.
 *
 *  \retval true - gdy połączenie z programem \e gnuplot zostało poprawnie
 *               zainicjalizowane lub gdy już wcześniej było 
 *               zainicjalizowane.
 *  \retval false - gdy proces inicjalizacji połączenia zakończył się
 *               niepowodzeniem.
 */
 bool LaczeDoGNUPlota::UtworzProcesPotomny()
 {
  int indesk[2],outdesk[2];

  if (pipe(indesk) == -1 || pipe(outdesk) == -1) {
    KomunikatBledu(
      "### Niemozliwe utworzenie kanalow komunikacyjnych do podprocesow.");
    exit(1);
  }

  switch (fork()) {
    case -1: KomunikatBledu("### Niemozliwe rozwidlenie procesu.");
             exit(1);
    case  0: 
       /* Start potomka */

       if (close(STDIN) == -1) { 
         KomunikatBledu("### Blad przy zamykaniu strumienia wejsciowego.");
         exit(1);
       }
       if (dup(outdesk[STDIN]) == -1) {
         KomunikatBledu("### Blad duplikacji kanalu wejsciowego.");  
         exit(1);
       }
       
       if (close(STDOUT) == -1) { 
         KomunikatBledu(
            "### Blad zamkniecia kanalu standardowego kanalu wyjsciowego."); 
         exit(1);
       }
       if (dup(indesk[STDOUT]) == -1) {
         KomunikatBledu("### Blad duplikacji kanalu wyjsciowego.");  
         exit(1);
       }       
       if (close(outdesk[STDIN]) == -1) {
         KomunikatBledu("### Blad zamkniecia kanalu wejsciowego.");
         exit(1);
       }
       if (close(outdesk[STDOUT]) == -1) {
         KomunikatBledu("### Blad zamkniecia kanalu wyjsciowego.");
         exit(1);
       }
       if (close(indesk[STDIN]) == -1) {
         KomunikatBledu("### Blad zamkniecia duplikatu kanalu wejsciowego.");
         exit(1);
       }
       if (close(indesk[STDOUT]) == -1) {
         KomunikatBledu("### Blad zamkniecia duplikatu kanalu wyjsciowego.");
         exit(1);
       }
       char Tab[3];
       read(STDIN,Tab,1);
       write(STDOUT,"\n",1); 
       const char *Comm;

       execlp(Comm = "gnuplot","gnuplot",NULL);

       KomunikatBledu("!!! Blad:"); 
       KomunikatBledu("!!! W procesie potomnym nie mogl zostac."); 
       KomunikatBledu("!!! uruchomiony program gnuplot."); 
       KomunikatBledu("!!! Nastapilo przerwanie dzialania procesu potomnego."); 
       KomunikatBledu("!!! Jednym z mozliwych powodow problemu moze byc"); 
       KomunikatBledu("!!! Brak programu gnuplot w szukanej sciezce."); 
       KomunikatBledu("!!! Do uruchomienia programu gnuplot bylo uzyte polecenie:");
       KomunikatBledu(Comm);
       exit(1);

    default:
       if (close(outdesk[STDIN]) == -1 || close(indesk[STDOUT]) == -1) { 
         KomunikatBledu(" Blad zamkniecia outpipe[STDIN], inpipe[STDOUT]."); 
       }

       fcntl(indesk[STDIN],F_SETFL,O_NDELAY);
       _Wyjscie_GNUPlota  = indesk[STDIN];
       _Wejscie_GNUPlota =  outdesk[STDOUT];
  }
  return true;
 }




 bool LaczeDoGNUPlota::RysujDoPliku(const char *NazwaPliku)
 {
  if (!CzyPolaczenieJestZainicjowane()) {
    if (!Inicjalizuj()) return false;
  }
  string Polecenie = "\n\n\nset output '";
  Polecenie += NazwaPliku;
  Polecenie += "\n set term png\n";
  if (!PrzeslijDoGNUPlota(Polecenie.c_str())) {
    KomunikatBledu("!!! Rysunek nie moze byc utworzony.");
    return false;
  }

  bool Wynik = Rysuj();
  if (!PrzeslijDoGNUPlota("\n\n\nset output \nset term x11\n")) {
    KomunikatBledu("!!! Wyjscie dla gnuplot'a nie zostalo poprawnie\n"
                   "!!! przestawione na STDOUT.\n");
    return false;
  }
  return Wynik;
 }




 bool DopiszRysowanieZPlikow( list<InfoPlikuDoRysowania>::const_iterator  &IterNazw,
                              list<InfoPlikuDoRysowania>::const_iterator  &IterKonca,
                              std::string                                 &Polecenie, 
                              char const                                **wwSep 
                            )
 {
  bool           Res = false;
  ostringstream  TStrmWy;

  for (; IterNazw != IterKonca; ++IterNazw ) {
       if (IterNazw->WezSposobRys() == SR_PunktowyNiejednorodny) continue;

       Polecenie += *wwSep;
       Polecenie += " \'";
       Polecenie += IterNazw->WezNazwePliku();
       (Polecenie += '\'') += " notitle ";

       TStrmWy.str("");
       switch (IterNazw->WezSposobRys()) {
        case SR_Ciagly:
	   TStrmWy << "w l " << " lt " << IterNazw->WezStyl()
                   << " lw " << IterNazw->WezSzerokosc();
	     //         << " lc " << IterNazw->WezKolor();
           break;

        case SR_Punktowy:
	   TStrmWy << "w p " << " pt " << IterNazw->WezStyl()
                   << " ps " << IterNazw->WezSzerokosc();
	    //         << " lc " << IterNazw->WezKolor();
	   break;

	case SR_PunktowyNiejednorodny:
	   break;
       }
/*
       (IterNazw->WezSposobRys() == SR_Ciagly ? " w l" : " w p pt 5");
       if  (IterNazw->WezSposobRys() == SR_Ciagly) 
                                OSStrm << " lw " << IterNazw->WezSzerokosc();
                           else OSStrm << " ps " << IterNazw->WezSzerokosc();
*/
       Polecenie += TStrmWy.str();
       *wwSep = ", ";
       Res = true;
  }
  return Res;
 }


/*!
 * Tworzy napis będący parametrami dla polecenie \e plot programu,
 * \e gnuplot. Parametry te pozwalają na rysowanie brył, których
 *  współrzędne wierzchołków zawarte są w plikach.
 *  Nazwy tych plików muszą być wcześniej dołączone do kolejki 
 *  plików poprzez zastosowanie polecenia
 *   \link LaczeDoGNUPlota::DodajNazwe DodajNazwe\endlink.
 *  
 * \param Polecenie - dopisywana jest do niego sekwencja znaków
 *                  tworzących parametry dla polecenia \e plot.
 * \param wwSep - zawiera znak separatora między poszczególnymi
 *              parametrami. Jeżeli parametry listy nazw plików
 *              są generowane jako pierwsze, to zmienna ta musi 
 *              być wskaźnikiem do wskaźnika na łańcuch: " ".
 * \retval true - jeśli lista nazw plików nie jest pusta.
 * \retval false - w przypadku przeciwnym.
 * \post Jeżeli  lista nazw plików nie jest pusta, to poprzez
 *              parametr \e Sep zostaje udostępniony łańcuch: ", ".
 */
 bool LaczeDoGNUPlota::DopiszRysowanieZPlikow( std::string   &Polecenie, 
                                                char const  **wwSep 
                                             )
 {
  list<InfoPlikuDoRysowania>::const_iterator IterNazw  = _InfoPlikow_Glb.begin();
  list<InfoPlikuDoRysowania>::const_iterator IterKonca = _InfoPlikow_Glb.end();
  bool Res = true;

  if (!_InfoPlikow_Glb.empty()) {
    Res = PzG::DopiszRysowanieZPlikow(IterNazw,IterKonca,Polecenie,wwSep);
  }

  if (_InfoPlikow_Lok.empty()) return Res;

  IterNazw  = _InfoPlikow_Lok.begin();
  IterKonca = _InfoPlikow_Lok.end();
  return  PzG::DopiszRysowanieZPlikow(IterNazw,IterKonca,Polecenie,wwSep) || Res;
 }



/*!
 * \brief Modeluje zestaw informacji będący atrybutami rysowania
 *
 * 
 */
 class AtrybutyRysowania {
    int  _Kolor;

    int  _Rozmiar;
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

  public:
    AtrybutyRysowania()
	 {  _Styl = _Rozmiar = _Kolor = 0; }

    /*!
     * \brief Porównuje wszystkie pola atrybutów
     *
     *  ProrÓwnuje dwa atrybuty względem wszystkich pól
     *  w następującej kolejności: rozmiar, kolor i styl.
     *  Przy sortowaniu pozwala to zgrupować obok siebie 
     *  te elementy, które mają takie same wartości pól.
     */
    bool operator < (const AtrybutyRysowania& Atryb) const
     {  return _Rozmiar < Atryb._Rozmiar ? true :
                     _Kolor < Atryb._Kolor ? true :
	               _Styl < Atryb._Styl; 
     }
   /*!
    * \brief Porównuje wszystkie pola
    *
    * Porównuje wszystkie pola. Równość zachodzi wtedy, gdy
    * wartości wszystkich pól są takie same.
    */
    bool operator == (const AtrybutyRysowania& Atryb) const
     {
        return  _Rozmiar == Atryb._Rozmiar &&
                  _Kolor == Atryb._Kolor   &&
                   _Styl == Atryb._Styl;
     }

    /*!
     * \brief Udostępnia styl rysowania
     *
     * Udostępnia wartość parametru określającego styl rysowania
     * danego elementu graficznego (tzn. linii lub punktu).
     */
    int WezStyl() const { return _Styl; }
    /*!
     * \brief Udostępnia kolor rysowania
     *
     * Udostępnia wartość parametru określającego kolor rysowania
     * danego elementu graficznego (tzn. linii lub punktu).
     */
    int WezKolor() const { return _Kolor; }
    /*!
     * \brief Udostępnia rozmiar rysowania
     *
     * Udostępnia wartość parametru określającego rozmiar rysowanego
     * danego elementu graficznego. W przypadku linii jest to jej grubość,
     * zaś w przypdku punktu rozmiar okręgu.
     */
    int WezRozmiar() const { return _Rozmiar; }

    /*!
     * \brief Zmienia styl rysowania
     *
     * Zmienia parametr determinujący styl rysowania obiektu
     * graficznego.
     */
    AtrybutyRysowania& ZmienStyl(int Styl) { _Styl = Styl; return *this;}
    /*!
     * \brief Zmienia kolor rysowania
     *
     * Zmienia parametr determinujący kolor rysowania obiektu
     * graficznego.
     */
    AtrybutyRysowania& ZmienKolor(int Kolor) { _Kolor = Kolor; return *this;}
    /*!
     * \brief Zmienia rozmiar rysowania
     *
     * Zmienia parametr determinujący rozmiar rysowania obiektu
     * graficznego.
     */
    AtrybutyRysowania& ZmienRozmiar(int Rozmiar) 
                                          { _Rozmiar = Rozmiar; return *this;}
 };


/*!
 * \brief Współrzędne punktu
 *
 * Współrzędne punktu w przestrzeni dwuwymiarowej.
 */
 class Wspolrzedne2W {
    public:
      float  x, y;

      Wspolrzedne2W() { x = y = 0; }
      Wspolrzedne2W(float xx, float yy): x(xx), y(yy) {}
 
      Wspolrzedne2W& operator += (const Wspolrzedne2W& Skl) 
                       { x += Skl.x;  y += Skl.y;  return *this; }

      Wspolrzedne2W  operator + (Wspolrzedne2W Skl2) const
                       { return Skl2 += *this; }

      Wspolrzedne2W& operator *= (float Arg) 
                       { x *= Arg;  y *= Arg;  return *this; }

      Wspolrzedne2W  operator * (float Arg) const 
                       { return Wspolrzedne2W(*this) *= Arg; }

     void Zmien(float xx, float yy) {  x = xx;  y = yy; }
 };


/*!
 * \brief Wczytuje wartości współrzędnych
 *
 * Wczytuje wartości współrzędnych. Najpierw jest czytana współrzędna \e x,
 * a później \e y.
 */
 istream& operator >> (istream& StrmWe, Wspolrzedne2W &Wspolrz)
 {
   return StrmWe >> Wspolrz.x >> Wspolrz.y;
 }


/*!
 * \brief Modeluje zestaw informacji o rysowanych punktach
 *
 * Klasa ma charakter pomocniczy i modeluje zestaw informacji
 * o punktach, które mają być rysowane. Informacje te określają
 * styl rysowania punktu, kolor oraz jego rozmiar, jak też
 * współrzędne tego punktu.
 */
 class InfoPunktyDoRysowania {
    /*!
     * \brief Atrybuty rysowania elementu graficznego
     *
     * Pole zawiera wartości parametrów determinujące sposób
     * rysowania danego elementu graficznego.
     */
    AtrybutyRysowania  _Atryb;
    /*!
     * \brief Współrzędne punktu
     *
     * Współrzędne punktu, który ma być rysowany.
     */
    Wspolrzedne2W      _Wspolrz;
    /*!
     * \brief Przechowuje etykietę punktu
     *
     * Przechowuje etykietę, która może być wyświetlona razem z danym
     * punktem.
     */
    string             _Etykieta;
    /* !
     * \brief Współrzędne etykiety
     *
     * Współrzędne danej etykiety.
     */
     Wspolrzedne2W           _WspolrzEtykiety;

     /*!
      * \brief Stałe przesunięcie etykiety wzgl. punktu
      *
      * Stałe przesunięcie etykiety względem współrzędnych punktu
      */
    static  Wspolrzedne2W   _PrzesEtykiety_WzgWspoPunktu;
     /*!
      * \brief Współczynnik przesunięcia etykiety
      *
      * Współczynnik przesunięcia względem rozmiaru punktu.
      */
    static  Wspolrzedne2W   _PrzesEtykiety_WzgRozmPunktu;

     /*!
      * \brief Wyznacza współrzędne położenia etykiety
      *
      * Wyznacza współrzędne położenia etykiety.
      */
    Wspolrzedne2W  WyznaczWspolrzEtykiety() const
     {
       return _PrzesEtykiety_WzgRozmPunktu * _Atryb.WezRozmiar() + 
              _PrzesEtykiety_WzgWspoPunktu + WezWspolrz();
     }

   public:
    /*!
     * \brief Inicjalizuje obiekt
     */
     InfoPunktyDoRysowania( const Wspolrzedne2W      &Wspolrz, 
                            const AtrybutyRysowania  &Atryb,
                            const char*               sEtykieta
                          ):
	  _Atryb(Atryb), _Wspolrz(Wspolrz), _Etykieta(sEtykieta) 
       {
          UstawWspolrzEtykietyDlaPrzesuniecia(5,5);
       }

    /*!
     * \brief Wpisuje nowe współrzędne
     *
     * Wpisuje nowe współrzędne jako przesunięcie względem położenie puntku.
     */
     void UstawWspolrzEtykietyDlaPrzesuniecia(float x, float y)
       {
	  _WspolrzEtykiety = _Wspolrz;
          _WspolrzEtykiety.x += x;   _WspolrzEtykiety.y += y;
	  _WspolrzEtykiety = WyznaczWspolrzEtykiety(); 
       }
    /*!
     * \brief Udostępnia etykietę danego punktu
     *
     * Udostępnia etykietę danego punktu.
     */
     const string& WezEtykiete() const { return _Etykieta; }
    /*!
     * \brief Udostępnia wspólrzędne etykiety
     */
     const Wspolrzedne2W&  WezWspolrzEtykiety() const 
                                       {  return _WspolrzEtykiety; }
    /*!
     * \brief Porównuje tylko wg atrbutów
     *
     * Prównywane są tylko i wyłacznie same atrybuty.
     */
     bool operator < (const InfoPunktyDoRysowania& Info) const
                                 {  return _Atryb < Info._Atryb; }
    /*!
     * \brief Udostępnia atrybuty rysowania
     *
     * Udostępnia atrybuty rysowania danego elementu graficznego.
     */
    const AtrybutyRysowania& WezAtrybuty() const { return _Atryb; }
    /*!
     * \brief Udostępnia atrybuty do zmiany
     *
     * Udostępnia do zmiany atrybuty rysowania danego elementu
     * graficznego.
     */
    AtrybutyRysowania& OtworzAtrybuty() { return _Atryb; }
    /*!
     * \brief Udostępnia współrzędne rysowania
     *
     * Udostępnia współrzędne rysowania danego elementu graficznego.
     */
    const Wspolrzedne2W& WezWspolrz() const { return _Wspolrz; }
    /*!
     * \brief Udostępnia współrzędne do zmiany
     *
     * Udostępnia do zmiany współrzędne rysowania danego elementu
     * graficznego.
     */
    Wspolrzedne2W& OtworzWspolrz() { return _Wspolrz; }
    /*!
     * \brief Dopisuje do etykiety numer
     */
    void DodajDoEtykiety(int Num);
   /*!
    *
    */
    InfoPunktyDoRysowania& ZmienPrzesEtykiety_WzgWspoPunktu( float   xx,
                                                             float   yy
                                                           );
   /*!
    *
    */
    InfoPunktyDoRysowania& ZmienPrzesEtykiety_WzgRozmPunktu( float   xx,
                                                             float   yy
                                                           );
 };




Wspolrzedne2W InfoPunktyDoRysowania::_PrzesEtykiety_WzgWspoPunktu(0.5,0.5);
Wspolrzedne2W InfoPunktyDoRysowania::_PrzesEtykiety_WzgRozmPunktu(0.26,0.26);



InfoPunktyDoRysowania& InfoPunktyDoRysowania::ZmienPrzesEtykiety_WzgWspoPunktu(
                                                           float   xx,
                                                           float   yy
                                                        )
{
  _PrzesEtykiety_WzgWspoPunktu.Zmien(xx,yy);   return *this;
}



InfoPunktyDoRysowania& InfoPunktyDoRysowania::ZmienPrzesEtykiety_WzgRozmPunktu(
                                                           float   xx,
                                                           float   yy
                                                        )
{
  _PrzesEtykiety_WzgRozmPunktu.Zmien(xx,yy);  return *this;
}




/*!
 * Dopisuje do etykiety numer.
 * \param Num - liczba, która ma być dopisana do etykiety punktu.
 */
 void InfoPunktyDoRysowania::DodajDoEtykiety(int Num)
 {
   ostringstream   StrmWy;
   StrmWy << Num;
   _Etykieta += StrmWy.str();
 }




 typedef list<InfoPunktyDoRysowania>  TypListaPunktow;


/*!
 * \brief Wczytuje z pliku listę punktów
 *
 *  Wczytuje z pliku listę punktów, które mogą się różnić rozmiarem.
 *  Dane w pliku zapisywane są w postaci tekstowej wg następującego schematu:
 \verbatim
     x_1  y_1  rozmiar_1
     x_2  y_2  rozmiar_2
      ...
     x_n  y_n  rozmiar_n
 \verbatimend
 * gdzie \e x_i, \e y_i, \e rozmiar_i to współrzędna \e x-owa, \e y-owa
 * oraz rozmiar \e i-tego punktu.
 * Dopuszczalne jest również wstawianie komentarzy jedno liniowych.
 * Musi się on jednak rozpoczynać od początku linii znakiem \p #.
 *  \param NazwaPliku - nazwa pliku, z którego mają być wczytane informacje
 *                      dotyczące punktów.
 *  \para ListaPkt - lista punktów, do której składowane są wczytane dane
 *                   o punktach.
 */
 bool WczytajListeRoznychPunktow( const char*        NazwaPliku, 
                                  TypListaPunktow   &ListaPkt,
                                  int                Kolor,
                                  int                Styl,
                                  const char*        sEtykieta 
                                )
 {
   ifstream  StrmWe(NazwaPliku);

   if (!StrmWe.is_open()) {
     cerr << ":(  Nie mozna otworzyc do odczytu pliku:" << endl;
     cerr << ":(      " << NazwaPliku << endl;
     return false;
   }

   Wspolrzedne2W       Wspolrz;
   int                 Rozmiar;
   AtrybutyRysowania   Atryb;
   char                Znak;
   int                 Ilosc = 0;

   Atryb.ZmienKolor(Kolor).ZmienStyl(Styl);

   while (StrmWe >> Znak) {
       if (Znak == '#') { 
         StrmWe.ignore(numeric_limits<streamsize>::max(),'\n');
         continue;
       }
       StrmWe.unget();
       if (!(StrmWe >> Wspolrz >> Rozmiar)) break;
       Atryb.ZmienRozmiar(Rozmiar);
       ListaPkt.push_back(InfoPunktyDoRysowania(Wspolrz,Atryb,sEtykieta));
       ++Ilosc;
   }

   if (Ilosc  < 0) return false;
   if (Ilosc == 1) return true;

   TypListaPunktow::reverse_iterator Iter = ListaPkt.rbegin();
   for (; Ilosc > 0; --Ilosc, ++Iter) {
     Iter->DodajDoEtykiety(Ilosc);
   }
   return true;
 }


 bool DopiszUstawieniaEtykiet( TypListaPunktow &ListaPkt,
			       std::string     &Comm
                             )
 {
   if (ListaPkt.empty()) return false;

   ostringstream      StrmWy;

   TypListaPunktow::const_iterator  Iter = ListaPkt.begin();
   StrmWy << " unset label\n";
   for ( ;
         Iter != ListaPkt.end();
         ++Iter) {
       StrmWy << " set label \"" << Iter->WezEtykiete() << "\" at "
              << Iter->WezWspolrzEtykiety().x << ","
              << Iter->WezWspolrzEtykiety().y << endl;
   } 
   Comm = StrmWy.str() + Comm;
   return true;
 }


/*!
 *
 */
 bool DopiszRysowaniePunktowZListy( TypListaPunktow &ListaPkt,
                                    std::string     &Comm,
                                    const char      *Sep
                                  )
 {
   TypListaPunktow::const_iterator  Iter = ListaPkt.begin(); 

   if (Iter == ListaPkt.end()) return false;


   AtrybutyRysowania  Atryb;

   if (Sep)  Comm += Sep;

   ostringstream      StrmWy;

   Atryb = Iter->WezAtrybuty();
   StrmWy << " \'-\' notitle w p ps " << Atryb.WezRozmiar()
          << " pt " << Atryb.WezStyl();
     //  << " lc " << Atryb.WezKolor();

   for ( ++Iter;
         Iter != ListaPkt.end();
         ++Iter ) {
       if (Atryb == Iter->WezAtrybuty()) continue;
       Atryb = Iter->WezAtrybuty();
       StrmWy << ", \'-\' notitle w p ps " << Atryb.WezRozmiar()
              << " pt " << Atryb.WezStyl();
       // << " lc " << Atryb.WezKolor();
   }
   StrmWy << endl;

   Iter = ListaPkt.begin(); 
   Atryb = Iter->WezAtrybuty();
   StrmWy << Iter->WezWspolrz().x << " " << Iter->WezWspolrz().y << endl;

   for ( ++Iter;
         Iter != ListaPkt.end();
         ++Iter ) {
       if (Atryb == Iter->WezAtrybuty()) {
         StrmWy << Iter->WezWspolrz().x << " " << Iter->WezWspolrz().y << endl;
         continue;
       }
       StrmWy << " e\n";
       Atryb = Iter->WezAtrybuty();
       StrmWy << Iter->WezWspolrz().x << " " << Iter->WezWspolrz().y << endl;
   }
   StrmWy << "e\n\n";
   Comm += StrmWy.str();
   return true;
 }




 void DopiszRysowanieZRoznychPunktow( 
                           list<InfoPlikuDoRysowania>::const_iterator  &IterNazw,
                           list<InfoPlikuDoRysowania>::const_iterator  &IterKonca,
                           list<InfoPunktyDoRysowania>                 &ListaPunktow
                        )
 {
   for (; IterNazw != IterKonca; ++IterNazw ) {
      if (IterNazw->WezSposobRys() != SR_PunktowyNiejednorodny) continue;

      WczytajListeRoznychPunktow( IterNazw->WezNazwePliku().c_str(),
                                  ListaPunktow,
                                  IterNazw->WezKolor(), IterNazw->WezStyl(),
                                  IterNazw->WezEtykiete().c_str()
	                        );
   }
 }


/*!
 * Tworzy napis będący parametrami dla polecenie \e plot programu,
 * \e gnuplot. Parametry te pozwalają na rysowanie brył, których
 *  współrzędne wierzchołków zawarte są w plikach.
 *  Nazwy tych plików muszą być wcześniej dołączone do kolejki 
 *  plików poprzez zastosowanie polecenia
 *   \link LaczeDoGNUPlota::DodajNazwe DodajNazwe\endlink.
 *  
 * \param Polecenie - dopisywana jest do niego sekwencja znaków
 *                  tworzących parametry dla polecenia \e plot.
 * \param Sep - zawiera znak separatora między poszczególnymi
 *              parametrami. Jeżeli parametry listy nazw plików
 *              są generowane jako pierwsze, to zmienna ta musi 
 *              być wskaźnikiem do wskaźnika na łańcuch: " ".
 * \retval true - jeśli lista nazw plików nie jest pusta.
 * \retval false - w przypadku przeciwnym.
 * \post Jeżeli  lista nazw plików nie jest pusta, to poprzez
 *              parametr \e Sep zostaje udostępniony łańcuch: ", ".
 */
 bool LaczeDoGNUPlota::DopiszRysowanieZRoznychPunktow( 
                                                std::string  &Polecenie, 
                                                char const   *Sep 
                                             )
 {
  string  UstawieniaEtykiet;

  list<InfoPunktyDoRysowania>  ListaPunktow;

  list<InfoPlikuDoRysowania>::const_iterator IterNazw  = _InfoPlikow_Glb.begin();
  list<InfoPlikuDoRysowania>::const_iterator IterKonca = _InfoPlikow_Glb.end();

  PzG::DopiszRysowanieZRoznychPunktow(IterNazw,IterKonca,ListaPunktow); 

  IterNazw  = _InfoPlikow_Lok.begin();
  IterKonca = _InfoPlikow_Lok.end();

  PzG::DopiszRysowanieZRoznychPunktow(IterNazw,IterKonca,ListaPunktow); 

  if (ListaPunktow.empty()) return false;
  ListaPunktow.sort();

  DopiszUstawieniaEtykiet(ListaPunktow, Polecenie);
  return DopiszRysowaniePunktowZListy(ListaPunktow, Polecenie, Sep);
 }



 //-------------------------------------------------------------------------
 //  Jezeli lista plikow nie jest pusta, to generuje sekwencje polecen
 //  dla programu gnuplot majaca na celu narysowanie plaszczyzn na
 //  na podstawie danych zawartych w plikach z listy. 
 //
 //  PRE:  Na liscie plikow nie powinna byc pusta. Nazwy plikow na niej
 //        mozna umiescic za pomoca metody 'DodajNazwe'.
 //        Metoda nie wymaga wcześniejszego zainicjowania połączenia
 //        z gnuplotem.
 //  POST: true   - gdy zostaja poprawnie wyslane polecenia dla gnuplota.
 //                 Nie oznacza to jednak, ze proces rysowania zakończył
 //                 się pomyślnie.
 //       false   - gdy połączenie z gnuplotem nie moze zostac poprawnie
 //                 zainicjalizowane lub gdy lista plikow jest pusta.
 //
 bool LaczeDoGNUPlota::Rysuj()
 {
  if (!CzyPolaczenieJestZainicjowane()) {
    if (!Inicjalizuj()) return false;
  }

  string Polecenie;

  BudujPreambulePoleceniaRysowania(Polecenie);

  char const *Sep = "";
  bool TrzebaRysowac = DopiszPlikiDoPoleceniaRysowania(Polecenie,&Sep);
  /*

  */
  TrzebaRysowac = DopiszRysowanieZPlikow(Polecenie,&Sep) || TrzebaRysowac;
  TrzebaRysowac = DopiszRysowanieZRoznychPunktow(Polecenie,Sep) 
                      || TrzebaRysowac;
  if (!TrzebaRysowac) return false;
 /*
  cerr << "Polecenie: =============================================" << endl;
  cerr << Polecenie << endl;
   cerr << "-----------------------------" << endl;
 */
  Polecenie += "\npause -1\n";

  return PrzeslijDoGNUPlota(Polecenie.c_str());
 }



 void  LaczeDoGNUPlota::BudujPreambulePoleceniaRysowania(std::string &Preambula) const
 {
  switch (_TrybRys) {
   case TR_2D: BudujPreambule_2D(Preambula); break;
   case TR_3D: BudujPreambule_3D(Preambula); break;
  }
 }



 void  LaczeDoGNUPlota::BudujPreambule_2D(std::string &Preambula) const
 {
  Preambula.clear();
  Preambula.reserve(1000);
  Preambula = "\n\n";

  if (_PokazOs_OX) Preambula += "set xzeroaxis lt 0 lw 1\n";
  if (_PokazOs_OY) Preambula += "set yzeroaxis lt 0 lw 1\n";

  Preambula += ZapiszUstawienieZakresu('x');
  Preambula += ZapiszUstawienieZakresu('y');
  Preambula += "\nplot ";
 }



 void  LaczeDoGNUPlota::BudujPreambule_3D(std::string &Preambula) const
 {
  Preambula.clear();
  Preambula.reserve(1000);
  Preambula = "\n\n"
                       "set parametric\n"
                       "set isosamples 9\n"
                       "set urange [-180:180]\n"
                       "set vrange [-90:90]\n";  

  if (_PokazOs_OX) Preambula += "set xzeroaxis lt 0 lw 1\n";
  if (_PokazOs_OY) Preambula += "set yzeroaxis lt 0 lw 1\n";

  Preambula += ZapiszUstawienieZakresu('x');
  Preambula += ZapiszUstawienieZakresu('y');
  Preambula += ZapiszUstawienieZakresu('z');
  Preambula += ZapiszUstawienieRotacjiISkali();
  Preambula += "set hidden3d\nsplot ";
 }



std::string LaczeDoGNUPlota::ZapiszUstawienieZakresu(char Os) const
{
  ostringstream strm;
  float Min, Max;

  switch (Os) {
   case 'x':  Min = Xmin();  Max = Xmax();  break;
   case 'y':  Min = Ymin();  Max = Ymax();  break;
   case 'z':  Min = Zmin();  Max = Zmax();  break;
   default: cerr << "!!! Blad w 'ZapiszUstawienieZakresu' niedozwolony"
                    " znak: " << Os << endl;
            return "";
  }
  strm << "set " << Os << "range [" <<  Min << ":" << Max << "]\n";
  return strm.str();
}



std::string LaczeDoGNUPlota::ZapiszUstawienieRotacjiISkali() const
{
  ostringstream strm;
  strm << "set view " << RotacjaX() << "," << RotacjaZ() 
       << "," << SkalaX() << "," << SkalaZ() << endl;
  return strm.str();
}





 void UsunOstatniaNazwePliku(list<InfoPlikuDoRysowania>& Lista)
 { 
   list<InfoPlikuDoRysowania>::iterator IterNazw = Lista.end();
   Lista.erase(--IterNazw);
 }

 //-------------------------------------------------------------------------
 //  Metda usuwa ostatnia nazwe z listy nazw plikow.
 //
 void LaczeDoGNUPlota::UsunOstatniaNazwe_ListaLokalna()
 {
   PzG::UsunOstatniaNazwePliku(_InfoPlikow_Lok);
 }


 //-------------------------------------------------------------------------
 //  Metda usuwa ostatnia nazwe z listy nazw plikow.
 //
 void LaczeDoGNUPlota::UsunOstatniaNazwe_ListaGlobalna()
 {
   PzG::UsunOstatniaNazwePliku(_InfoPlikow_Glb);
 }



 //-------------------------------------------------------------------------
 //  Metda calkowicie kasuje zawartosc listy nazw plikow.
 //
 void LaczeDoGNUPlota::UsunWszystkieNazwyPlikow()
 {
  _InfoPlikow_Lok.clear();
  _InfoPlikow_Glb.clear();
 }

 //_____________________ LaczeDoGNUPlota ______________________________________
 //============================================================================


} //___ Koniec przestrzeni nazw: PzG ____________________________________________
