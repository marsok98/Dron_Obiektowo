#include "FabrykaObiektow.hh"

shared_ptr<ObiektSceny> FabrykaObiektow::StworzObiekt(TypObiektu Typ)
{
    switch(Typ)
    {
        case Robot: return make_shared<Dron>();
        case Przeszkoda: return make_shared<PrzeszkodaPr>();
    }
    return make_shared<PrzeszkodaPr>();
}