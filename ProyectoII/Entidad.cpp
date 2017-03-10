#include "Entidad.h"


Entidad::Entidad(Juego*pJ, double x, double y, Texturas_t textura, Efectos_t efecto)
{
	ancho = alto = 100;
	posX = x;
	posY = y;
	pJuego = pJ;
	pTextura = textura;
	sonido = efecto;
	rect = { posX, posY, ancho, alto };

}

Entidad::~Entidad()
{
}

void Entidad::draw()const
{
	if (visible)
		pJuego->getTextura(pTextura)->draw(pJuego->getRender(), rect);//Dibujamos la textura
}

