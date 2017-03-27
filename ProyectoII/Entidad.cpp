#include "Entidad.h"


Entidad::Entidad(Juego*pJ, double x, double y, Texturas_t textura, Efectos_t efecto)
{
	rect = { x, y, 100, 100 };
	pJuego = pJ;
	pTextura = textura;
	sonido = efecto;
}

Entidad::~Entidad()
{
}

void Entidad::draw()const
{
	pJuego->getTextura(pTextura)->draw(pJuego->getRender(), rect);//Dibujamos la textura
}

