#include "Enemigo.h"



Enemigo::Enemigo(Juego*pJ, int x, int y, Texturas_t textura, Efectos_t efecto) : Entidad(pJ, x, y, textura, efecto, ONull)
{
	vida = 3;
}


Enemigo::~Enemigo()
{
}

void Enemigo::update(){



}
