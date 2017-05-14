#include "Pildoras.h"


Pildoras::Pildoras(Juego*pJ, int x, int y, int w, int h, float salud, Texturas_t textura, Efectos_t efecto, Objetos_t tipo) : Entidad(pJ, x, y, w, h, textura, efecto, tipo)
{
	this->salud = salud;
}


Pildoras::~Pildoras()
{
}
