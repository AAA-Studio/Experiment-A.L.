#include "Enemigo5.h"


Enemigo5::Enemigo5(MundoVirtual* pM, int x, int y, int w, int h, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto)
: Entidad(pM->getPJ(), x, y, w, h, textura, efecto, ONull)
{

}


Enemigo5::~Enemigo5()
{
}
