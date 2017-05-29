#include "Pildoras.h"


Pildoras::Pildoras(Juego*pJ, int x, int y, int w, int h, float salud, JuegoSDL::Texturas_t textura, JuegoSDL::Efectos_t efecto, Objetos_t tipo) : Entidad(pJ, x, y, w, h, textura, efecto, tipo)
{
	this->salud = salud;
}


Pildoras::~Pildoras()
{
}